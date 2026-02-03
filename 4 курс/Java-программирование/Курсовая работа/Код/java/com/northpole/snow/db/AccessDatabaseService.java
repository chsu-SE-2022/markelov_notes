package com.northpole.snow.db;

import org.springframework.jdbc.core.ConnectionCallback;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.support.rowset.SqlRowSet;
import org.springframework.stereotype.Service;

import java.sql.DatabaseMetaData;
import java.sql.PreparedStatement;
import java.sql.ResultSetMetaData;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;

@Service
public class AccessDatabaseService {

    private final JdbcTemplate jdbcTemplate;

    public record LookupItem(Object key, String label) {}

    public AccessDatabaseService(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public List<TableInfo> listTables() {
        return jdbcTemplate.execute((ConnectionCallback<List<TableInfo>>) conn -> {
            DatabaseMetaData meta = conn.getMetaData();
            try (ResultSet rs = meta.getTables(null, null, "%", new String[] {"TABLE"})) {
                List<TableInfo> tables = new ArrayList<>();
                while (rs.next()) {
                    String name = rs.getString("TABLE_NAME");
                    if (name == null) {
                        continue;
                    }
                    // UCanAccess exposes system tables too; filter common prefixes
                    String normalized = name.trim();
                    if (normalized.startsWith("MSys")) {
                        continue;
                    }
                    tables.add(new TableInfo(normalized));
                }
                tables.sort((a, b) -> a.name().compareToIgnoreCase(b.name()));
                return tables;
            }
        });
    }

    public List<TableInfo> listViews() {
        return jdbcTemplate.execute((ConnectionCallback<List<TableInfo>>) conn -> {
            DatabaseMetaData meta = conn.getMetaData();
            try (ResultSet rs = meta.getTables(null, null, "%", new String[] {"VIEW"})) {
                List<TableInfo> views = new ArrayList<>();
                while (rs.next()) {
                    String name = rs.getString("TABLE_NAME");
                    if (name == null) {
                        continue;
                    }
                    String normalized = name.trim();
                    if (normalized.startsWith("MSys")) {
                        continue;
                    }
                    views.add(new TableInfo(normalized));
                }
                views.sort((a, b) -> a.name().compareToIgnoreCase(b.name()));
                return views;
            }
        });
    }

    public boolean objectExists(String objectName) {
        if (objectName == null || objectName.isBlank()) {
            return false;
        }

        String needle = objectName.trim();
        return jdbcTemplate.execute((ConnectionCallback<Boolean>) conn -> {
            DatabaseMetaData meta = conn.getMetaData();
            try (ResultSet rs = meta.getTables(null, null, needle, null)) {
                while (rs.next()) {
                    String name = rs.getString("TABLE_NAME");
                    if (name != null && name.trim().equalsIgnoreCase(needle)) {
                        return true;
                    }
                }
                return false;
            }
        });
    }

    public List<ColumnInfo> listColumns(String tableName) {
        return jdbcTemplate.execute((ConnectionCallback<List<ColumnInfo>>) conn -> {
            DatabaseMetaData meta = conn.getMetaData();
            try (ResultSet rs = meta.getColumns(null, null, tableName, "%")) {
                List<ColumnInfo> cols = new ArrayList<>();
                while (rs.next()) {
                    String name = rs.getString("COLUMN_NAME");
                    int jdbcType = rs.getInt("DATA_TYPE");
                    String typeName = rs.getString("TYPE_NAME");
                    boolean nullable = rs.getInt("NULLABLE") != DatabaseMetaData.columnNoNulls;
                    boolean autoIncrement = false;
                    try {
                        autoIncrement = "YES".equalsIgnoreCase(rs.getString("IS_AUTOINCREMENT"));
                    } catch (SQLException ignored) {
                        // Some drivers don't support IS_AUTOINCREMENT
                    }
                    cols.add(new ColumnInfo(name, jdbcType, typeName, nullable, autoIncrement));
                }
                return cols;
            }
        });
    }

    public Optional<PrimaryKeyInfo> findSinglePrimaryKey(String tableName) {
        return jdbcTemplate.execute((ConnectionCallback<Optional<PrimaryKeyInfo>>) conn -> {
            DatabaseMetaData meta = conn.getMetaData();
            try (ResultSet rs = meta.getPrimaryKeys(null, null, tableName)) {
                List<String> cols = new ArrayList<>();
                while (rs.next()) {
                    String col = rs.getString("COLUMN_NAME");
                    if (col != null) {
                        cols.add(col);
                    }
                }
                if (cols.size() == 1) {
                    return Optional.of(new PrimaryKeyInfo(cols.getFirst()));
                }
                return Optional.empty();
            }
        });
    }

    public List<RowData> fetchRows(String tableName, List<ColumnInfo> columns, String searchText, int limit) {
        if (columns.isEmpty()) {
            return Collections.emptyList();
        }

        // Access search with CStr(...) can break on some column names/types.
        // To keep the UI reliable, fetch TOP N rows without WHERE and filter client-side.
        boolean hasSearch = searchText != null && !searchText.isBlank();
        String needle = hasSearch ? searchText.trim().toLowerCase() : "";

        int sqlLimit = hasSearch ? Math.max(1000, Math.max(1, limit)) : Math.max(1, limit);
        String sql = "SELECT TOP " + sqlLimit + " * FROM [" + tableName + "]";

        SqlRowSet rs = jdbcTemplate.queryForRowSet(sql);

        List<RowData> rows = new ArrayList<>();
        while (rs.next()) {
            RowData row = new RowData();
            boolean matches = !hasSearch;
            for (ColumnInfo c : columns) {
                Object v = rs.getObject(c.name());
                row.put(c.name(), v);
                if (!matches && v != null) {
                    String s = String.valueOf(v).toLowerCase();
                    if (s.contains(needle)) {
                        matches = true;
                    }
                }
            }
            if (matches) {
                rows.add(row);
                if (rows.size() >= limit) {
                    break;
                }
            }
        }
        return rows;
    }

    public List<RowData> fetchRows(String tableName, List<ColumnInfo> columns, String searchText, String searchColumn, int limit) {
        if (columns.isEmpty()) {
            return Collections.emptyList();
        }

        String col = (searchColumn == null || searchColumn.isBlank()) ? null : searchColumn.trim();
        ColumnInfo chosen = null;
        if (col != null) {
            for (ColumnInfo c : columns) {
                if (c.name() != null && c.name().equalsIgnoreCase(col)) {
                    chosen = c;
                    break;
                }
            }
        }

        boolean hasSearch = searchText != null && !searchText.isBlank();
        String needle = hasSearch ? searchText.trim().toLowerCase() : "";

        // If no valid chosen column, fall back to the generic search (across all columns)
        if (chosen == null) {
            return fetchRows(tableName, columns, searchText, limit);
        }

        int sqlLimit = hasSearch ? Math.max(1000, Math.max(1, limit)) : Math.max(1, limit);
        String sql = "SELECT TOP " + sqlLimit + " * FROM [" + tableName + "]";

        SqlRowSet rs = jdbcTemplate.queryForRowSet(sql);

        List<RowData> rows = new ArrayList<>();
        while (rs.next()) {
            RowData row = new RowData();
            Object chosenValue = null;

            for (ColumnInfo c : columns) {
                Object v = rs.getObject(c.name());
                row.put(c.name(), v);
                if (c.name() != null && c.name().equalsIgnoreCase(chosen.name())) {
                    chosenValue = v;
                }
            }

            boolean matches;
            if (!hasSearch) {
                matches = true;
            } else if (chosenValue == null) {
                matches = false;
            } else {
                matches = String.valueOf(chosenValue).toLowerCase().contains(needle);
            }

            if (matches) {
                rows.add(row);
                if (rows.size() >= limit) {
                    break;
                }
            }
        }
        return rows;
    }

    public int deleteByPrimaryKey(String tableName, PrimaryKeyInfo pk, Object pkValue) {
        String sql = "DELETE FROM [" + tableName + "] WHERE [" + pk.columnName() + "] = ?";
        return jdbcTemplate.update(sql, pkValue);
    }

    public enum DeleteStrategy {
        CASCADE,
        NULLIFY_REFERENCES
    }

    public record ReferenceInfo(String tableName, String columnName, boolean nullable, int count) {
    }

    private record ForeignKeyRef(String fkTable, String fkColumn, String pkColumn) {
    }

    public List<ReferenceInfo> findReferencesTo(String parentTableName, PrimaryKeyInfo parentPk, Object parentPkValue) {
        if (parentTableName == null || parentTableName.isBlank() || parentPk == null || parentPkValue == null) {
            return List.of();
        }

        String parentTable = parentTableName.trim();
        String pkCol = parentPk.columnName();

        List<ForeignKeyRef> refs = listExportedForeignKeys(parentTable);
        if (refs.isEmpty()) {
            return List.of();
        }

        List<ReferenceInfo> out = new ArrayList<>();
        for (ForeignKeyRef r : refs) {
            if (r.pkColumn == null || !r.pkColumn.equalsIgnoreCase(pkCol)) {
                continue;
            }

            boolean nullable = true;
            try {
                for (ColumnInfo c : listColumns(r.fkTable)) {
                    if (c.name() != null && c.name().equalsIgnoreCase(r.fkColumn)) {
                        nullable = c.nullable();
                        break;
                    }
                }
            } catch (Exception ignored) {
                nullable = true;
            }

            int count;
            try {
                Integer c = jdbcTemplate.queryForObject(
                        "SELECT COUNT(*) FROM [" + r.fkTable + "] WHERE [" + r.fkColumn + "] = ?",
                        Integer.class,
                        parentPkValue
                );
                count = c == null ? 0 : c;
            } catch (Exception ex) {
                count = 0;
            }

            if (count > 0) {
                out.add(new ReferenceInfo(r.fkTable, r.fkColumn, nullable, count));
            }
        }
        return out;
    }

    public int deleteByPrimaryKeyWithStrategy(
            String tableName,
            PrimaryKeyInfo pk,
            Object pkValue,
            DeleteStrategy strategy
    ) {
        if (strategy == null) {
            return deleteByPrimaryKey(tableName, pk, pkValue);
        }

        return switch (strategy) {
            case CASCADE -> cascadeDeleteByPrimaryKey(tableName, pk, pkValue);
            case NULLIFY_REFERENCES -> nullifyReferencesAndDelete(tableName, pk, pkValue);
        };
    }

    private int nullifyReferencesAndDelete(String parentTableName, PrimaryKeyInfo parentPk, Object parentPkValue) {
        List<ReferenceInfo> refs = findReferencesTo(parentTableName, parentPk, parentPkValue);
        for (ReferenceInfo r : refs) {
            if (!r.nullable) {
                throw new IllegalStateException(
                        "Нельзя заменить ссылки на NULL: " + r.tableName + "." + r.columnName + " не допускает NULL"
                );
            }
        }

        int affected = 0;
        for (ReferenceInfo r : refs) {
            affected += jdbcTemplate.update(
                    "UPDATE [" + r.tableName + "] SET [" + r.columnName + "] = NULL WHERE [" + r.columnName + "] = ?",
                    parentPkValue
            );
        }

        affected += deleteByPrimaryKey(parentTableName, parentPk, parentPkValue);
        return affected;
    }

    private int cascadeDeleteByPrimaryKey(String parentTableName, PrimaryKeyInfo parentPk, Object parentPkValue) {
        return cascadeDeleteByPrimaryKeyInternal(parentTableName, parentPk, parentPkValue, new HashSet<>());
    }

    private int cascadeDeleteByPrimaryKeyInternal(
            String parentTableName,
            PrimaryKeyInfo parentPk,
            Object parentPkValue,
            Set<String> visiting
    ) {
        String key = (parentTableName == null ? "" : parentTableName.trim().toLowerCase())
                + "|"
                + (parentPk == null ? "" : parentPk.columnName().trim().toLowerCase())
                + "|"
                + String.valueOf(parentPkValue);

        if (visiting.contains(key)) {
            return 0;
        }
        visiting.add(key);

        List<ForeignKeyRef> exported = listExportedForeignKeys(parentTableName);
        for (ForeignKeyRef fk : exported) {
            if (fk.pkColumn == null || !fk.pkColumn.equalsIgnoreCase(parentPk.columnName())) {
                continue;
            }

            Optional<PrimaryKeyInfo> childPkOpt = Optional.empty();
            try {
                childPkOpt = findSinglePrimaryKey(fk.fkTable);
            } catch (Exception ignored) {
                childPkOpt = Optional.empty();
            }

            if (childPkOpt.isPresent()) {
                String childPkCol = childPkOpt.get().columnName();
                List<Object> childPkValues;
                try {
                    childPkValues = jdbcTemplate.query(
                            "SELECT [" + childPkCol + "] FROM [" + fk.fkTable + "] WHERE [" + fk.fkColumn + "] = ?",
                            (rs, rowNum) -> rs.getObject(1),
                            parentPkValue
                    );
                } catch (Exception ex) {
                    childPkValues = List.of();
                }

                for (Object childPkValue : childPkValues) {
                    if (childPkValue == null) {
                        continue;
                    }
                    cascadeDeleteByPrimaryKeyInternal(fk.fkTable, childPkOpt.get(), childPkValue, visiting);
                }
            }

            jdbcTemplate.update(
                    "DELETE FROM [" + fk.fkTable + "] WHERE [" + fk.fkColumn + "] = ?",
                    parentPkValue
            );
        }

        int affected = deleteByPrimaryKey(parentTableName, parentPk, parentPkValue);
        visiting.remove(key);
        return affected;
    }

    private List<ForeignKeyRef> listExportedForeignKeys(String parentTableName) {
        if (parentTableName == null || parentTableName.isBlank()) {
            return List.of();
        }

        String parentTable = parentTableName.trim();
        return jdbcTemplate.execute((ConnectionCallback<List<ForeignKeyRef>>) conn -> {
            DatabaseMetaData meta = conn.getMetaData();
            try (ResultSet rs = meta.getExportedKeys(null, null, parentTable)) {
                List<ForeignKeyRef> out = new ArrayList<>();
                while (rs.next()) {
                    String fkTable = rs.getString("FKTABLE_NAME");
                    String fkColumn = rs.getString("FKCOLUMN_NAME");
                    String pkColumn = rs.getString("PKCOLUMN_NAME");
                    if (fkTable == null || fkColumn == null || pkColumn == null) {
                        continue;
                    }
                    out.add(new ForeignKeyRef(fkTable.trim(), fkColumn.trim(), pkColumn.trim()));
                }
                return out;
            }
        });
    }

    public int insertRow(String tableName, Map<String, Object> values) {
        if (values.isEmpty()) {
            return 0;
        }

        StringBuilder sql = new StringBuilder();
        sql.append("INSERT INTO [").append(tableName).append("] (");

        List<String> cols = new ArrayList<>(values.keySet());
        for (int i = 0; i < cols.size(); i++) {
            if (i > 0) {
                sql.append(", ");
            }
            sql.append("[").append(cols.get(i)).append("]");
        }
        sql.append(") VALUES (");
        for (int i = 0; i < cols.size(); i++) {
            if (i > 0) {
                sql.append(", ");
            }
            sql.append("?");
        }
        sql.append(")");

        List<Object> params = new ArrayList<>();
        for (String c : cols) {
            params.add(values.get(c));
        }
        return jdbcTemplate.update(sql.toString(), params.toArray());
    }

    public int updateByPrimaryKey(String tableName, PrimaryKeyInfo pk, Object pkValue, Map<String, Object> values) {
        if (values.isEmpty()) {
            return 0;
        }

        List<String> cols = new ArrayList<>(values.keySet());
        StringBuilder sql = new StringBuilder();
        sql.append("UPDATE [").append(tableName).append("] SET ");

        for (int i = 0; i < cols.size(); i++) {
            if (i > 0) {
                sql.append(", ");
            }
            sql.append("[").append(cols.get(i)).append("] = ?");
        }
        sql.append(" WHERE [").append(pk.columnName()).append("] = ?");

        List<Object> params = new ArrayList<>();
        for (String c : cols) {
            params.add(values.get(c));
        }
        params.add(pkValue);
        return jdbcTemplate.update(sql.toString(), params.toArray());
    }

    public List<LookupItem> fetchLookupItems(String tableName, int limit) {
        int n = Math.max(1, limit);
        return jdbcTemplate.execute((ConnectionCallback<List<LookupItem>>) conn -> {
            // Determine key/display columns by real column order
            String keyColumn;
            String displayColumn;
            try (PreparedStatement ps = conn.prepareStatement("SELECT * FROM [" + tableName + "] WHERE 1=0")) {
                try (ResultSet rs = ps.executeQuery()) {
                    ResultSetMetaData md = rs.getMetaData();
                    int colCount = md.getColumnCount();
                    if (colCount < 1) {
                        return List.of();
                    }
                    keyColumn = md.getColumnLabel(1);

                    displayColumn = null;
                    boolean hasTariffName = false;
                    for (int i = 1; i <= colCount; i++) {
                        String name = md.getColumnLabel(i);
                        int type = md.getColumnType(i);
                        if (name == null) {
                            continue;
                        }
                        if (name.equalsIgnoreCase("Название")) {
                            hasTariffName = true;
                        }
                        // Prefer a textual, non-code column
                        boolean isText = type == java.sql.Types.VARCHAR
                                || type == java.sql.Types.NVARCHAR
                                || type == java.sql.Types.LONGVARCHAR
                                || type == java.sql.Types.LONGNVARCHAR
                                || type == java.sql.Types.CHAR
                                || type == java.sql.Types.NCHAR;
                        if (isText && !name.startsWith("Код ")) {
                            displayColumn = name;
                            break;
                        }
                    }

                    if ("Тарифы".equalsIgnoreCase(tableName) && hasTariffName) {
                        displayColumn = "Название";
                    }
                    if (displayColumn == null) {
                        displayColumn = colCount >= 2 ? md.getColumnLabel(2) : keyColumn;
                    }
                }
            }

            final String keyColumnFinal = keyColumn;
            final String displayColumnFinal = displayColumn;

            String sql;
            if (displayColumnFinal.equalsIgnoreCase(keyColumnFinal)) {
                sql = "SELECT TOP " + n + " [" + keyColumnFinal + "] FROM [" + tableName + "]";
            } else {
                sql = "SELECT TOP " + n + " [" + keyColumnFinal + "], [" + displayColumnFinal + "] FROM [" + tableName + "]";
            }

            return jdbcTemplate.query(sql, (rs, rowNum) -> {
                Object key = rs.getObject(keyColumnFinal);
                String label;
                if (displayColumnFinal.equalsIgnoreCase(keyColumnFinal)) {
                    label = key == null ? "" : String.valueOf(key);
                } else {
                    Object dv = rs.getObject(displayColumnFinal);
                    label = dv == null ? "" : String.valueOf(dv);
                }
                return new LookupItem(key, label);
            });
        });
    }

    public List<LookupItem> fetchRouteLookupItems(int limit) {
        int n = Math.max(1, limit);
        String sql = "SELECT TOP " + n
                + " m.[Код маршрута] AS [id], tt.[Тип транспорта] AS [type], m.[Номер маршрута] AS [num] "
                + "FROM [Маршруты] AS m "
                + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]";

        record RouteRow(Object id, String type, String num) {}

        List<RouteRow> rows = jdbcTemplate.query(sql, (rs, rowNum) -> new RouteRow(
                rs.getObject("id"),
                rs.getString("type"),
                rs.getString("num")
        ));

        rows.sort((a, b) -> {
            int ai = parseLeadingInt(a.num);
            int bi = parseLeadingInt(b.num);
            if (ai != bi) {
                return Integer.compare(ai, bi);
            }
            String as = a.num == null ? "" : a.num;
            String bs = b.num == null ? "" : b.num;
            int c = String.CASE_INSENSITIVE_ORDER.compare(as, bs);
            if (c != 0) {
                return c;
            }
            String at = a.type == null ? "" : a.type;
            String bt = b.type == null ? "" : b.type;
            return String.CASE_INSENSITIVE_ORDER.compare(at, bt);
        });

        List<LookupItem> items = new ArrayList<>(rows.size());
        for (RouteRow r : rows) {
            String t = r.type == null ? "" : r.type;
            String num = r.num == null ? "" : r.num;
            String label = (t.isBlank() ? "" : (t + " ")) + num;
            items.add(new LookupItem(r.id, label));
        }
        return items;
    }

    private static int parseLeadingInt(String s) {
        if (s == null) {
            return Integer.MAX_VALUE;
        }
        int i = 0;
        while (i < s.length() && Character.isWhitespace(s.charAt(i))) {
            i++;
        }
        int start = i;
        while (i < s.length() && Character.isDigit(s.charAt(i))) {
            i++;
        }
        if (i == start) {
            return Integer.MAX_VALUE;
        }
        try {
            return Integer.parseInt(s.substring(start, i));
        } catch (NumberFormatException e) {
            return Integer.MAX_VALUE;
        }
    }

    public int countRows(String tableName) {
        if (tableName == null || tableName.isBlank()) {
            return 0;
        }
        try {
            Integer c = jdbcTemplate.queryForObject("SELECT COUNT(*) FROM [" + tableName.trim() + "]", Integer.class);
            return c == null ? 0 : c;
        } catch (Exception e) {
            return 0;
        }
    }

    public int countRoutesWithIntervals() {
        try {
            Integer c = jdbcTemplate.queryForObject(
                    "SELECT COUNT(*) FROM [Маршруты] AS m "
                            + "WHERE EXISTS (SELECT 1 FROM [Интервалы движения] AS i WHERE i.[Код маршрута] = m.[Код маршрута])",
                    Integer.class
            );
            return c == null ? 0 : c;
        } catch (Exception e) {
            return 0;
        }
    }

    public int countRoutesWithMissingRefs() {
        try {
            Integer c = jdbcTemplate.queryForObject(
                    "SELECT COUNT(*) FROM [Маршруты] AS m WHERE "
                            + "m.[Тип транспорта] IS NULL OR "
                            + "m.[Тип маршрута] IS NULL OR "
                            + "m.[Начальная остановка] IS NULL OR "
                            + "m.[Конечная остановка] IS NULL OR "
                            + "m.[Перевозчик] IS NULL OR "
                            + "m.[Тариф] IS NULL",
                    Integer.class
            );
            return c == null ? 0 : c;
        } catch (Exception e) {
            return 0;
        }
    }

    public record Stat(String label, int value) {}

    private static List<Stat> topWithOthers(List<Stat> all, int topN, String othersLabel, boolean includeOthers) {
        if (all == null || all.isEmpty()) {
            return List.of();
        }
        int n = Math.max(1, topN);
        if (all.size() <= n) {
            return all;
        }

        List<Stat> top = new ArrayList<>(all.subList(0, n));
        if (!includeOthers) {
            return top;
        }
        int otherSum = 0;
        for (int i = n; i < all.size(); i++) {
            otherSum += Math.max(0, all.get(i).value());
        }
        if (otherSum > 0) {
            top.add(new Stat(othersLabel, otherSum));
        }
        return top;
    }

    private static List<Stat> topWithOthers(List<Stat> all, int topN, String othersLabel) {
        return topWithOthers(all, topN, othersLabel, true);
    }

    public List<Stat> routesByTransportType(int topN) {
        String sql = "SELECT tt.[Тип транспорта] AS [label], COUNT(*) AS cnt "
                + "FROM [Маршруты] AS m "
                + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта] "
                + "GROUP BY tt.[Тип транспорта] "
                + "ORDER BY 2 DESC";
        List<Stat> all = jdbcTemplate.query(sql, (rs, rowNum) -> new Stat(rs.getString("label"), rs.getInt("cnt")));
        return topWithOthers(all, topN, "Прочие", true);
    }

    public List<Stat> routesByCarrier(int topN) {
        String sql = "SELECT p.[Перевозчик] AS [label], COUNT(*) AS cnt "
                + "FROM [Маршруты] AS m "
                + "INNER JOIN [Перевозчики] AS p ON m.[Перевозчик] = p.[Код перевозчика] "
                + "GROUP BY p.[Перевозчик] "
                + "ORDER BY 2 DESC";
        List<Stat> all = jdbcTemplate.query(sql, (rs, rowNum) -> new Stat(rs.getString("label"), rs.getInt("cnt")));
        return topWithOthers(all, topN, "Прочие");
    }

    public List<Stat> routesByRouteType(int topN) {
        String typesTable = "Типы маршрута";
        String typesPk = "Код типа маршрута";
        String typesLabel = "Тип маршрута";

        String sql = "SELECT tm.[" + typesLabel + "] AS [label], COUNT(*) AS cnt "
                + "FROM [Маршруты] AS m "
                + "INNER JOIN [" + typesTable + "] AS tm ON m.[Тип маршрута] = tm.[" + typesPk + "] "
                + "GROUP BY tm.[" + typesLabel + "] "
                + "ORDER BY 2 DESC";
        List<Stat> all = jdbcTemplate.query(sql, (rs, rowNum) -> new Stat(rs.getString("label"), rs.getInt("cnt")));
        return topWithOthers(all, topN, "Прочие");
    }

    public List<Stat> topStopsByUsageInRoutes(int topN) {
        String sql = "SELECT s.[Остановка] AS [label], COUNT(*) AS cnt FROM ("
                + " SELECT m.[Начальная остановка] AS [stopId] FROM [Маршруты] AS m "
                + " UNION ALL "
                + " SELECT m.[Конечная остановка] AS [stopId] FROM [Маршруты] AS m "
                + ") AS x "
                + " INNER JOIN [Остановки] AS s ON x.[stopId] = s.[Код остановки] "
                + " GROUP BY s.[Остановка] "
                + " ORDER BY 2 DESC";
        List<Stat> all = jdbcTemplate.query(sql, (rs, rowNum) -> new Stat(rs.getString("label"), rs.getInt("cnt")));
        return topWithOthers(all, topN, "Прочие", false);
    }

    public record BoolSplit(int yes, int no) {}

    public BoolSplit routeTariffBoolSplit(String tariffColumnName) {
        if (tariffColumnName == null || tariffColumnName.isBlank()) {
            return new BoolSplit(0, 0);
        }
        String col = tariffColumnName.trim();
        try {
            Integer totalRoutes = jdbcTemplate.queryForObject("SELECT COUNT(*) FROM [Маршруты]", Integer.class);
            Integer yes = jdbcTemplate.queryForObject(
                    "SELECT COUNT(*) FROM [Маршруты] AS m "
                            + "INNER JOIN [Тарифы] AS t ON m.[Тариф] = t.[Код тарифа] "
                            + "WHERE t.[" + col + "] <> 0",
                    Integer.class
            );

            int total = totalRoutes == null ? 0 : totalRoutes;
            int y = yes == null ? 0 : yes;
            int n = Math.max(0, total - y);
            return new BoolSplit(y, n);
        } catch (Exception e) {
            return new BoolSplit(0, 0);
        }
    }

    public BoolSplit tariffBoolSplit(String columnName) {
        if (columnName == null || columnName.isBlank()) {
            return new BoolSplit(0, 0);
        }
        String col = columnName.trim();
        try {
            Integer total = jdbcTemplate.queryForObject("SELECT COUNT(*) FROM [Тарифы]", Integer.class);
            Integer yes = jdbcTemplate.queryForObject(
                    "SELECT COUNT(*) FROM [Тарифы] WHERE [" + col + "] <> 0",
                    Integer.class
            );
            int t = total == null ? 0 : total;
            int y = yes == null ? 0 : yes;
            int n = Math.max(0, t - y);
            return new BoolSplit(y, n);
        } catch (Exception e) {
            return new BoolSplit(0, 0);
        }
    }

    public List<Stat> intervalsByRoute(int topN) {
        int n = Math.max(1, topN);
        String sql = "SELECT TOP " + n
                + " tt.[Тип транспорта] AS [type], m.[Номер маршрута] AS [num], COUNT(i.[Код интервала]) AS cnt "
                + "FROM ([Маршруты] AS m "
                + "INNER JOIN [Интервалы движения] AS i ON m.[Код маршрута] = i.[Код маршрута]) "
                + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта] "
                + "GROUP BY tt.[Тип транспорта], m.[Номер маршрута] "
                + "ORDER BY 3 DESC";

        record R(String type, String num, int cnt) {}
        List<R> rows = jdbcTemplate.query(sql, (rs, rowNum) -> new R(
                rs.getString("type"),
                rs.getString("num"),
                rs.getInt("cnt")
        ));

        List<Stat> out = new ArrayList<>(rows.size());
        for (R r : rows) {
            String t = r.type == null ? "" : r.type;
            String num = r.num == null ? "" : r.num;
            String label = (t.isBlank() ? "" : (t + " ")) + num;
            out.add(new Stat(label, r.cnt));
        }
        return out;
    }

    public Map<String, Integer> countRowsByTable(List<TableInfo> tables) {
        Map<String, Integer> counts = new LinkedHashMap<>();
        for (TableInfo t : tables) {
            try {
                Integer c = jdbcTemplate.queryForObject("SELECT COUNT(*) FROM [" + t.name() + "]", Integer.class);
                counts.put(t.name(), c == null ? 0 : c);
            } catch (Exception e) {
                counts.put(t.name(), -1);
            }
        }
        return counts;
    }

    public QueryResult executeSelect(String sql, int limit) {
        if (sql == null || sql.isBlank()) {
            throw new IllegalArgumentException("Пустой SQL");
        }

        String normalized = sql.trim();
        String upper = normalized.toUpperCase();
        if (!upper.startsWith("SELECT")) {
            throw new IllegalArgumentException("Разрешены только SELECT-запросы");
        }
        if (upper.contains(";")) {
            throw new IllegalArgumentException("Запрещены многооператорные запросы (разделитель ';')");
        }
        // Basic blocklist
        if (upper.contains("INSERT ") || upper.contains("UPDATE ") || upper.contains("DELETE ") || upper.contains("DROP ")
                || upper.contains("ALTER ") || upper.contains("CREATE ") || upper.contains("TRUNCATE ")) {
            throw new IllegalArgumentException("Запрещены DDL/DML операции. Разрешён только SELECT");
        }

        String toRun = normalized;
        if (!upper.contains(" TOP ")) {
            int n = Math.max(1, limit);

            // Access-friendly limiting: inject TOP N right after SELECT or SELECT DISTINCT
            // Examples:
            //   SELECT ...        -> SELECT TOP N ...
            //   SELECT DISTINCT.. -> SELECT DISTINCT TOP N ..
            String trimmedUpper = upper;
            if (trimmedUpper.startsWith("SELECT DISTINCT")) {
                // preserve original casing after the keyword block
                int idx = upper.indexOf("SELECT DISTINCT") + "SELECT DISTINCT".length();
                toRun = normalized.substring(0, idx) + " TOP " + n + normalized.substring(idx);
            } else {
                int idx = upper.indexOf("SELECT") + "SELECT".length();
                toRun = normalized.substring(0, idx) + " TOP " + n + normalized.substring(idx);
            }
        }

        return jdbcTemplate.query(toRun, rs -> {
            ResultSetMetaData md = rs.getMetaData();
            int colCount = md.getColumnCount();

            List<String> cols = new ArrayList<>();
            for (int i = 1; i <= colCount; i++) {
                String label = md.getColumnLabel(i);
                cols.add(label == null || label.isBlank() ? md.getColumnName(i) : label);
            }

            List<RowData> rows = new ArrayList<>();
            int read = 0;
            while (rs.next()) {
                RowData row = new RowData();
                for (int i = 0; i < cols.size(); i++) {
                    String col = cols.get(i);
                    row.put(col, rs.getObject(i + 1));
                }
                rows.add(row);
                read++;
                if (read >= limit) {
                    break;
                }
            }

            return new QueryResult(cols, rows);
        });
    }
}
