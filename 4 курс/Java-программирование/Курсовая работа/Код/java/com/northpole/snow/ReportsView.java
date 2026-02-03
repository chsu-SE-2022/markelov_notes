package com.northpole.snow;

import com.northpole.snow.db.AccessDatabaseService;
import com.northpole.snow.db.QueryResult;
import com.northpole.snow.db.RowData;
import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.grid.GridVariant;
import com.vaadin.flow.component.html.H2;
import com.vaadin.flow.component.icon.VaadinIcon;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.select.Select;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.data.value.ValueChangeMode;
import com.vaadin.flow.router.PageTitle;
import com.vaadin.flow.router.BeforeEvent;
import com.vaadin.flow.router.HasUrlParameter;
import com.vaadin.flow.router.Route;

import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.sql.Time;
import java.sql.Timestamp;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Date;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

@PageTitle("Запросы")
@Route(value = "report", layout = MainLayout.class)
public class ReportsView extends VerticalLayout implements HasUrlParameter<String> {

    private final AccessDatabaseService db;

    private final H2 title = new H2("Отчёт");

    private final Button runBtn = new Button("Обновить", VaadinIcon.REFRESH.create());

    private final Select<String> searchColumn = new Select<>();

    private final TextField searchField = new TextField("Поиск");

    private final Grid<RowData> grid = new Grid<>(RowData.class, false);

    private final Map<String, String> presets = createPresets();

    private String currentReportKey;

    private List<RowData> loadedRows = List.of();
    private List<String> loadedColumns = List.of();

    private final HorizontalLayout actions;

    public ReportsView(AccessDatabaseService db) {
        this.db = db;

        setSizeFull();

        title.setText("Отчёт");

        searchColumn.setLabel("Поле");
        searchColumn.setWidth("260px");

        searchField.setPlaceholder("Введите текст для поиска...");
        searchField.setClearButtonVisible(true);
        searchField.setWidth("360px");
        searchField.setValueChangeMode(ValueChangeMode.EAGER);

        searchColumn.setVisible(false);
        searchField.setVisible(false);

        actions = new HorizontalLayout(searchColumn, searchField, runBtn);
        actions.setWidthFull();
        actions.setDefaultVerticalComponentAlignment(Alignment.END);
        actions.setFlexGrow(1, searchField);
        actions.setJustifyContentMode(JustifyContentMode.START);
        actions.getStyle().set("flex-wrap", "nowrap");

        searchColumn.getStyle().set("flex-shrink", "0");
        runBtn.getStyle().set("flex-shrink", "0");

        grid.setSizeFull();
        grid.addClassName("header-wrap");
        grid.addThemeVariants(GridVariant.LUMO_WRAP_CELL_CONTENT);

        add(title, actions, grid);
        expand(grid);

        runBtn.addClickListener(e -> run());
        searchColumn.addValueChangeListener(e -> applyReportFilter());
        searchField.addValueChangeListener(e -> applyReportFilter());

        updateActionsAlignment();
    }

    private void updateActionsAlignment() {
        boolean searchVisible = searchField.isVisible() || searchColumn.isVisible();
        if (searchVisible) {
            actions.setJustifyContentMode(JustifyContentMode.START);
            actions.setFlexGrow(1, searchField);
        } else {
            actions.setFlexGrow(0, searchField);
            actions.setJustifyContentMode(JustifyContentMode.END);
        }
    }

    private void run() {
        String key = currentReportKey;
        if (key == null || key.isBlank()) {
            Notification.show("Не выбран отчёт", 3000, Notification.Position.MIDDLE);
            return;
        }

        String sql = presets.get(key);
        if (sql == null || sql.isBlank()) {
            Notification.show("Не найдено описание отчёта", 4000, Notification.Position.MIDDLE);
            return;
        }

        sql = applySchemaFallbacks(sql);

        try {
            QueryResult result = db.executeSelect(sql, 500);

            List<RowData> rows = new ArrayList<>(result.rows());
            if (result.columns().contains("Номер маршрута")) {
                boolean sortByTransport = "Время работы".equals(currentReportKey)
                        || "Интервальное расписание".equals(currentReportKey);
                rows.sort(routeNumberComparator(result.columns(), sortByTransport));
            }

            loadedRows = rows;
            loadedColumns = result.columns();

            List<String> textCols = buildSearchOptions(loadedColumns, loadedRows);
            if (textCols.isEmpty()) {
                searchColumn.clear();
                searchColumn.setItems(List.of());
                searchColumn.setVisible(false);
                searchField.clear();
                searchField.setVisible(false);
            } else {
                searchColumn.setItems(textCols);
                searchColumn.setVisible(true);
                searchField.setVisible(true);
                if (searchColumn.getValue() == null || !textCols.contains(searchColumn.getValue())) {
                    searchColumn.setValue(textCols.getFirst());
                }
            }

            updateActionsAlignment();

            grid.removeAllColumns();
            for (String col : result.columns()) {
                grid.addColumn(row -> {
                            Object v = row.get(col);
                            return formatReportCellValue(currentReportKey, col, v);
                        })
                        .setHeader(col)
                        .setAutoWidth(true)
                        .setResizable(true);
            }

            applyReportFilter();

            Notification.show("Строк: " + rows.size(), 2000, Notification.Position.BOTTOM_END);
        } catch (IllegalArgumentException ex) {
            Notification.show(ex.getMessage(), 4000, Notification.Position.MIDDLE);
        } catch (Exception ex) {
            Notification.show("Ошибка выполнения запроса: " + ex.getMessage(), 6000, Notification.Position.MIDDLE);
        }
    }

    private void applyReportFilter() {
        if (loadedRows == null || loadedRows.isEmpty() || loadedColumns == null || loadedColumns.isEmpty()) {
            grid.setItems(List.of());
            return;
        }

        String col = searchColumn.getValue();
        if (col == null || col.isBlank()) {
            grid.setItems(loadedRows);
            return;
        }

        String q = searchField.getValue();
        if (q == null || q.isBlank()) {
            grid.setItems(loadedRows);
            return;
        }

        String needle = q.trim().toLowerCase();

        List<RowData> out;
        if ("Остановки".equals(col)
                && loadedColumns.contains("Начальная остановка")
                && loadedColumns.contains("Конечная остановка")) {
            out = loadedRows.stream()
                    .filter(r -> {
                        Object v1 = r.get("Начальная остановка");
                        Object v2 = r.get("Конечная остановка");
                        boolean m1 = v1 != null && String.valueOf(v1).toLowerCase().contains(needle);
                        boolean m2 = v2 != null && String.valueOf(v2).toLowerCase().contains(needle);
                        return m1 || m2;
                    })
                    .toList();
        } else if (!loadedColumns.contains(col)) {
            out = loadedRows;
        } else {
            out = loadedRows.stream()
                    .filter(r -> {
                        Object v = r.get(col);
                        return v != null && String.valueOf(v).toLowerCase().contains(needle);
                    })
                    .toList();
        }
        grid.setItems(out);
    }

    private static List<String> detectTextColumns(List<String> columns, List<RowData> rows) {
        if (columns == null || columns.isEmpty()) {
            return List.of();
        }
        if (rows == null || rows.isEmpty()) {
            return List.of();
        }

        int sample = Math.min(50, rows.size());
        List<String> out = new ArrayList<>();
        for (String c : columns) {
            boolean anyString = false;
            for (int i = 0; i < sample; i++) {
                Object v = rows.get(i).get(c);
                if (v instanceof String) {
                    anyString = true;
                    break;
                }
            }
            if (anyString) {
                out.add(c);
            }
        }
        return out;
    }

    private static List<String> buildSearchOptions(List<String> columns, List<RowData> rows) {
        if (columns == null || columns.isEmpty()) {
            return List.of();
        }
        if (rows == null || rows.isEmpty()) {
            return List.of();
        }

        List<String> textCols = detectTextColumns(columns, rows);
        if (textCols.isEmpty()) {
            return List.of();
        }

        boolean hasStart = columns.contains("Начальная остановка") && textCols.contains("Начальная остановка");
        boolean hasEnd = columns.contains("Конечная остановка") && textCols.contains("Конечная остановка");
        if (!(hasStart && hasEnd)) {
            return textCols;
        }

        // Replace two stop columns with a single synthetic option, preserving column order.
        List<String> out = new ArrayList<>();
        boolean addedStops = false;
        for (String c : textCols) {
            if ("Начальная остановка".equals(c) || "Конечная остановка".equals(c)) {
                if (!addedStops) {
                    out.add("Остановки");
                    addedStops = true;
                }
                continue;
            }
            out.add(c);
        }
        return out;
    }

    private String applySchemaFallbacks(String sql) {
        if (sql == null || sql.isBlank()) {
            return sql;
        }

        return sql;
    }

    @Override
    public void setParameter(BeforeEvent event, String parameter) {
        if (parameter == null || parameter.isBlank()) {
            searchColumn.clear();
            searchColumn.setItems(List.of());
            searchColumn.setVisible(false);
            searchField.clear();
            searchField.setVisible(false);

            updateActionsAlignment();
            return;
        }

        String decoded;
        try {
            decoded = URLDecoder.decode(parameter, StandardCharsets.UTF_8);
        } catch (IllegalArgumentException ex) {
            decoded = parameter;
        }

        if (presets.containsKey(decoded)) {
            currentReportKey = decoded;
            title.setText(currentReportKey);
            run();
            return;
        }

        currentReportKey = decoded;
        title.setText(currentReportKey);
        grid.removeAllColumns();
        grid.setItems(List.of());

        loadedRows = List.of();
        loadedColumns = List.of();
        searchColumn.clear();
        searchColumn.setItems(List.of());
        searchColumn.setVisible(false);
        searchField.clear();
        searchField.setVisible(false);
        Notification.show("Не найден отчёт: " + decoded, 5000, Notification.Position.MIDDLE);
    }

    public static Map<String, String> createPresets() {
        Map<String, String> presets = new LinkedHashMap<>();

        presets.put("Все маршруты",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], tm.[Тип маршрута], "
                        + "o1.[Остановка] AS [Начальная остановка], o2.[Остановка] AS [Конечная остановка] "
                        + "FROM ((([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Типы маршрута] AS tm ON m.[Тип маршрута] = tm.[Код типа маршрута]) "
                        + "INNER JOIN [Остановки] AS o1 ON m.[Начальная остановка] = o1.[Код остановки]) "
                        + "INNER JOIN [Остановки] AS o2 ON m.[Конечная остановка] = o2.[Код остановки] "
                        + "ORDER BY m.[Номер маршрута]");
        presets.put("Автобусы",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], tm.[Тип маршрута], "
                        + "o1.[Остановка] AS [Начальная остановка], o2.[Остановка] AS [Конечная остановка] "
                        + "FROM ((([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Типы маршрута] AS tm ON m.[Тип маршрута] = tm.[Код типа маршрута]) "
                        + "INNER JOIN [Остановки] AS o1 ON m.[Начальная остановка] = o1.[Код остановки]) "
                        + "INNER JOIN [Остановки] AS o2 ON m.[Конечная остановка] = o2.[Код остановки] "
                        + "WHERE tt.[Тип транспорта] = 'Автобус' "
                        + "ORDER BY m.[Номер маршрута]");
        presets.put("Трамваи",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], tm.[Тип маршрута], "
                        + "o1.[Остановка] AS [Начальная остановка], o2.[Остановка] AS [Конечная остановка] "
                        + "FROM ((([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Типы маршрута] AS tm ON m.[Тип маршрута] = tm.[Код типа маршрута]) "
                        + "INNER JOIN [Остановки] AS o1 ON m.[Начальная остановка] = o1.[Код остановки]) "
                        + "INNER JOIN [Остановки] AS o2 ON m.[Конечная остановка] = o2.[Код остановки] "
                        + "WHERE tt.[Тип транспорта] = 'Трамвай' "
                        + "ORDER BY m.[Номер маршрута]");
        presets.put("Городские маршруты",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], tm.[Тип маршрута], "
                        + "o1.[Остановка] AS [Начальная остановка], o2.[Остановка] AS [Конечная остановка] "
                        + "FROM ((([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Типы маршрута] AS tm ON m.[Тип маршрута] = tm.[Код типа маршрута]) "
                        + "INNER JOIN [Остановки] AS o1 ON m.[Начальная остановка] = o1.[Код остановки]) "
                        + "INNER JOIN [Остановки] AS o2 ON m.[Конечная остановка] = o2.[Код остановки] "
                        + "WHERE tm.[Тип маршрута] = 'Городской' "
                        + "ORDER BY m.[Номер маршрута]");
        presets.put("Пригородные маршруты",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], tm.[Тип маршрута], "
                        + "o1.[Остановка] AS [Начальная остановка], o2.[Остановка] AS [Конечная остановка] "
                        + "FROM ((([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Типы маршрута] AS tm ON m.[Тип маршрута] = tm.[Код типа маршрута]) "
                        + "INNER JOIN [Остановки] AS o1 ON m.[Начальная остановка] = o1.[Код остановки]) "
                        + "INNER JOIN [Остановки] AS o2 ON m.[Конечная остановка] = o2.[Код остановки] "
                        + "WHERE tm.[Тип маршрута] = 'Пригородный' "
                        + "ORDER BY m.[Номер маршрута]");
        presets.put("Тарифы",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], t.[Наличный], t.[Безналичный], t.[Льготный], "
                        + "t.[Проездные], t.[Бесплатная пересадка] "
                        + "FROM (([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Тарифы] AS t ON m.[Тариф] = t.[Код тарифа]) "
                        + "ORDER BY m.[Номер маршрута]");
        presets.put("Перевозчики",
                "SELECT p.[Перевозчик] FROM [Перевозчики] AS p ORDER BY p.[Перевозчик]");
        presets.put("Маршруты по перевозчикам",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], p.[Перевозчик] "
                        + "FROM (([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Перевозчики] AS p ON m.[Перевозчик] = p.[Код перевозчика]) "
                        + "ORDER BY p.[Перевозчик], m.[Номер маршрута]");
        presets.put("Время работы",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], d.[Название], i.[Начало работы], i.[Конец работы] "
                        + "FROM ((([Интервалы движения] AS i "
                        + "INNER JOIN [Маршруты] AS m ON i.[Код маршрута] = m.[Код маршрута]) "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Дни недели] AS d ON i.[Дни недели] = d.[Код дней недели]) "
                        + "ORDER BY m.[Номер маршрута], d.[Название]");
        presets.put("Интервальное расписание",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], d.[Название], "
                        + "i.[05:00-10:00], i.[10:00-15:00], i.[15:00-19:00], i.[19:00-00:00] "
                        + "FROM ((([Интервалы движения] AS i "
                        + "INNER JOIN [Маршруты] AS m ON i.[Код маршрута] = m.[Код маршрута]) "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Дни недели] AS d ON i.[Дни недели] = d.[Код дней недели]) "
                        + "ORDER BY m.[Номер маршрута], d.[Название]");
        presets.put("Бесплатная пересадка",
                "SELECT m.[Номер маршрута], tt.[Тип транспорта], t.[Бесплатная пересадка] "
                        + "FROM (([Маршруты] AS m "
                        + "INNER JOIN [Типы транспорта] AS tt ON m.[Тип транспорта] = tt.[Код типа транспорта]) "
                        + "INNER JOIN [Тарифы] AS t ON m.[Тариф] = t.[Код тарифа]) "
                        + "WHERE t.[Бесплатная пересадка] = TRUE "
                        + "ORDER BY m.[Номер маршрута]");

        return presets;
    }

    private static Comparator<RowData> routeNumberComparator(List<String> columns, boolean sortByTransport) {
        boolean hasCarrier = columns.contains("Перевозчик");
        boolean hasDayName = columns.contains("Название");
        boolean hasTransportType = columns.contains("Тип транспорта");

        Comparator<RowData> cmp = (a, b) -> 0;

        // Primary sort: route number (numeric), then full string (to keep 10, 10A, 10Б stable)
        cmp = cmp.thenComparingInt(r -> parseLeadingInt(safeString(r.get("Номер маршрута"))));
        cmp = cmp.thenComparing(r -> safeString(r.get("Номер маршрута")), String.CASE_INSENSITIVE_ORDER);

        // Special requirement for specific reports
        if (sortByTransport && hasTransportType) {
            cmp = cmp.thenComparing(r -> safeString(r.get("Тип транспорта")), String.CASE_INSENSITIVE_ORDER);
        }

        // Secondary sorts if present in the report
        if (hasCarrier) {
            cmp = cmp.thenComparing(r -> safeString(r.get("Перевозчик")), String.CASE_INSENSITIVE_ORDER);
        }
        if (hasDayName) {
            cmp = cmp.thenComparing(r -> safeString(r.get("Название")), String.CASE_INSENSITIVE_ORDER);
        }
        return cmp;
    }

    private static String safeString(Object v) {
        return v == null ? "" : String.valueOf(v);
    }

    private static int parseLeadingInt(String s) {
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

    private static String formatReportCellValue(String reportKey, String columnName, Object v) {
        if (v == null) {
            return "";
        }

        if ("Интервальное расписание".equals(reportKey)
                && ("05:00-10:00".equals(columnName)
                || "10:00-15:00".equals(columnName)
                || "15:00-19:00".equals(columnName)
                || "19:00-00:00".equals(columnName))) {
            if (v instanceof Number n && n.doubleValue() == 0.0d) {
                return "—";
            }
            if (v instanceof String s && s.trim().equals("0")) {
                return "—";
            }
        }

        if (v instanceof Boolean b) {
            return b ? "✓" : "";
        }

        if (v instanceof String s) {
            if (s.equalsIgnoreCase("true")) {
                return "✓";
            }
            if (s.equalsIgnoreCase("false")) {
                return "";
            }
            return s;
        }

        DateTimeFormatter tf = DateTimeFormatter.ofPattern("HH:mm");
        if (v instanceof Time t) {
            return t.toLocalTime().format(tf);
        }
        if (v instanceof Timestamp ts) {
            return ts.toLocalDateTime().toLocalTime().format(tf);
        }
        if (v instanceof LocalTime lt) {
            return lt.format(tf);
        }
        if (v instanceof LocalDateTime ldt) {
            return ldt.toLocalTime().format(tf);
        }
        if (v instanceof Date d) {
            return Instant.ofEpochMilli(d.getTime()).atZone(ZoneId.systemDefault()).toLocalTime().format(tf);
        }

        return String.valueOf(v);
    }
}
