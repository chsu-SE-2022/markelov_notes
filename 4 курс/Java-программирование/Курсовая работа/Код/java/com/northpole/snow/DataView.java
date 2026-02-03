package com.northpole.snow;

import com.northpole.snow.db.AccessDatabaseService;
import com.northpole.snow.db.ColumnInfo;
import com.northpole.snow.db.PrimaryKeyInfo;
import com.northpole.snow.db.RowData;
import com.northpole.snow.db.TableInfo;
import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.checkbox.Checkbox;
import com.vaadin.flow.component.confirmdialog.ConfirmDialog;
import com.vaadin.flow.component.datetimepicker.DateTimePicker;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.grid.GridVariant;
import com.vaadin.flow.component.html.H2;
import com.vaadin.flow.component.html.Span;
import com.vaadin.flow.component.icon.VaadinIcon;
import com.vaadin.flow.component.select.Select;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.FlexComponent;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.ComponentUtil;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.component.timepicker.TimePicker;
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
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.LinkedHashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Optional;

@PageTitle("Таблицы")
@Route(value = "table", layout = MainLayout.class)
public class DataView extends VerticalLayout implements HasUrlParameter<String> {

    private record TimeDigitsEditorMarker() {
    }

    private final AccessDatabaseService db;

    private final Select<String> searchColumn = new Select<>();

    private final TextField searchField = new TextField("Поиск");

    private final Grid<RowData> grid = new Grid<>(RowData.class, false);

    private final H2 title = new H2("Таблица");

    private String currentTableName;

    // Explicit FK map (ported from C# UX idea): table -> (column -> referenced table)
    private static final Map<String, Map<String, String>> EXPLICIT_FK = Map.of(
            "Маршруты", Map.of(
                    "Тип транспорта", "Типы транспорта",
                    "Тип маршрута", "Типы маршрута",
                    "Начальная остановка", "Остановки",
                    "Конечная остановка", "Остановки",
                    "Перевозчик", "Перевозчики",
                    "Тариф", "Тарифы"
            ),
            "Интервалы движения", Map.of(
                    "Код маршрута", "Маршруты",
                    "Дни недели", "Дни недели"
            ),
            "Остановки", Map.of(
                    "Улица", "Улицы"
            ),
            "Улицы", Map.of(
                    "Населенный пункт", "Населенные пункты"
            )
    );

    private List<ColumnInfo> currentColumns = List.of();
    private Optional<PrimaryKeyInfo> currentPk = Optional.empty();

    private final Button refreshBtn = new Button("Обновить", VaadinIcon.REFRESH.create());
    private final Button addBtn = new Button("Добавить запись", VaadinIcon.PLUS.create());
    private final Button editBtn = new Button("Редактировать", VaadinIcon.EDIT.create());
    private final Button deleteBtn = new Button("Удалить", VaadinIcon.TRASH.create());

    private final HorizontalLayout toolbar;

    public DataView(AccessDatabaseService db) {
        this.db = db;

        setSizeFull();

        title.setText("Таблица");

        searchColumn.setLabel("Поле");
        searchColumn.setWidth("260px");

        searchField.setPlaceholder("Введите текст для поиска...");
        searchField.setClearButtonVisible(true);
        searchField.setWidth("360px");
        searchField.setValueChangeMode(ValueChangeMode.EAGER);

        searchColumn.setVisible(false);
        searchField.setVisible(false);

        deleteBtn.setEnabled(false);
        editBtn.setEnabled(false);

        toolbar = new HorizontalLayout(searchColumn, searchField, refreshBtn, addBtn, editBtn, deleteBtn);
        toolbar.setDefaultVerticalComponentAlignment(FlexComponent.Alignment.END);
        toolbar.setWidthFull();
        toolbar.setFlexGrow(1, searchField);
        toolbar.setJustifyContentMode(FlexComponent.JustifyContentMode.START);

        grid.setSizeFull();
        grid.addClassName("header-wrap");
        grid.addThemeVariants(GridVariant.LUMO_WRAP_CELL_CONTENT);

        add(title, toolbar, grid);
        expand(grid);

        refreshBtn.addClickListener(e -> refresh());
        searchField.addValueChangeListener(e -> refresh());
        searchColumn.addValueChangeListener(e -> refresh());

        grid.asSingleSelect().addValueChangeListener(e -> updateDeleteState(e.getValue()));
        deleteBtn.addClickListener(e -> deleteSelected());
        addBtn.addClickListener(e -> openAddDialog());
        editBtn.addClickListener(e -> openEditDialog());

        updateToolbarAlignment();
    }

    private void updateToolbarAlignment() {
        boolean searchVisible = searchField.isVisible() || searchColumn.isVisible();
        if (searchVisible) {
            toolbar.setJustifyContentMode(FlexComponent.JustifyContentMode.START);
            toolbar.setFlexGrow(1, searchField);
        } else {
            toolbar.setFlexGrow(0, searchField);
            toolbar.setJustifyContentMode(FlexComponent.JustifyContentMode.END);
        }
    }

    @Override
    public void setParameter(BeforeEvent event, String parameter) {
        if (parameter == null || parameter.isBlank()) {
            currentTableName = null;
            title.setText("Таблица");
            grid.removeAllColumns();
            grid.setItems(List.of());
            currentColumns = List.of();
            currentPk = Optional.empty();
            deleteBtn.setEnabled(false);
            editBtn.setEnabled(false);
            updateToolbarAlignment();
            return;
        }

        String decoded;
        try {
            decoded = URLDecoder.decode(parameter, StandardCharsets.UTF_8);
        } catch (IllegalArgumentException ex) {
            decoded = parameter;
        }

        final String decodedFinal = decoded;

        String matchName = db.listTables().stream()
                .map(TableInfo::name)
                .filter(name -> name.equalsIgnoreCase(decodedFinal) || name.equalsIgnoreCase(parameter))
                .findFirst()
                .orElse(null);

        if (matchName == null) {
            currentTableName = null;
            title.setText("Таблица: " + decoded);
            grid.removeAllColumns();
            grid.setItems(List.of());
            currentColumns = List.of();
            currentPk = Optional.empty();
            deleteBtn.setEnabled(false);
            editBtn.setEnabled(false);
            Notification.show("Не найдена таблица: " + decoded, 5000, Notification.Position.MIDDLE);
            return;
        }

        currentTableName = matchName;
        title.setText("Таблица: " + currentTableName);
        loadTable(currentTableName);
    }

    private void loadTable(String tableName) {
        if (tableName == null || tableName.isBlank()) {
            grid.removeAllColumns();
            grid.setItems(List.of());
            currentColumns = List.of();
            currentPk = Optional.empty();
            deleteBtn.setEnabled(false);
            searchColumn.clear();
            searchColumn.setItems(List.of());
            searchColumn.setEnabled(false);
            searchColumn.setVisible(false);
            searchField.clear();
            searchField.setVisible(false);
            updateToolbarAlignment();
            return;
        }

        currentColumns = reorderColumnsIfNeeded(tableName, db.listColumns(tableName));
        currentPk = db.findSinglePrimaryKey(tableName);

        List<String> textCols = currentColumns.stream()
                .filter(c -> isTextJdbcType(c.jdbcType()))
                .map(ColumnInfo::name)
                .toList();
        if (textCols.isEmpty()) {
            searchColumn.clear();
            searchColumn.setItems(List.of());
            searchColumn.setEnabled(false);
            searchColumn.setVisible(false);
            searchField.clear();
            searchField.setVisible(false);
        } else {
            searchColumn.setItems(textCols);
            searchColumn.setEnabled(true);
            searchColumn.setVisible(true);
            searchField.setVisible(true);
            if (searchColumn.getValue() == null || !textCols.contains(searchColumn.getValue())) {
                searchColumn.setValue(textCols.getFirst());
            }
        }

        updateToolbarAlignment();

        grid.removeAllColumns();
        for (ColumnInfo c : currentColumns) {
            grid.addColumn(row -> {
                        Object v = row.get(c.name());
                        return formatCellValue(v);
                    })
                    .setHeader(c.name())
                    .setAutoWidth(true)
                    .setResizable(true);
        }

        refresh();
    }

    private static List<ColumnInfo> reorderColumnsIfNeeded(String tableName, List<ColumnInfo> cols) {
        if ("Интервалы движения".equals(tableName)) {
            // Want: ... 'Дни недели', 'Начало работы', 'Конец работы', '05:00-10:00', ...
            int idxDays = indexOfColumn(cols, "Дни недели");
            int idxSlot = indexOfColumn(cols, "05:00-10:00");
            int idxStart = indexOfColumn(cols, "Начало работы");
            int idxEnd = indexOfColumn(cols, "Конец работы");

            if (idxDays < 0 || idxSlot < 0 || idxStart < 0 || idxEnd < 0) {
                return cols;
            }

            // Already between days and slot? then no-op
            if (idxStart > idxDays && idxStart < idxSlot && idxEnd > idxDays && idxEnd < idxSlot) {
                return cols;
            }

            List<ColumnInfo> out = new ArrayList<>(cols);

            ColumnInfo startCol = out.remove(indexOfColumn(out, "Начало работы"));
            ColumnInfo endCol = out.remove(indexOfColumn(out, "Конец работы"));

            int insertAt = indexOfColumn(out, "05:00-10:00");
            if (insertAt < 0) {
                return cols;
            }

            out.add(insertAt, endCol);
            out.add(insertAt, startCol);
            return out;
        }

        if ("Тарифы".equals(tableName)) {
            int idxCode = indexOfColumn(cols, "Код тарифа");
            int idxName = indexOfColumn(cols, "Название");
            int idxCash = indexOfColumn(cols, "Наличный");
            if (idxCode < 0 || idxName < 0 || idxCash < 0) {
                return cols;
            }

            if (idxName > idxCode && idxName < idxCash) {
                return cols;
            }

            List<ColumnInfo> out = new ArrayList<>(cols);
            ColumnInfo nameCol = out.remove(indexOfColumn(out, "Название"));

            int insertAt = indexOfColumn(out, "Наличный");
            if (insertAt < 0) {
                return cols;
            }
            out.add(insertAt, nameCol);
            return out;
        }

        return cols;
    }

    private static int indexOfColumn(List<ColumnInfo> cols, String name) {
        for (int i = 0; i < cols.size(); i++) {
            if (cols.get(i).name().equalsIgnoreCase(name)) {
                return i;
            }
        }
        return -1;
    }

    private void refresh() {
        if (currentTableName == null || currentTableName.isBlank()) {
            return;
        }
        try {
            List<RowData> rows = db.fetchRows(currentTableName, currentColumns, searchField.getValue(), searchColumn.getValue(), 200);
            grid.setItems(rows);
            deleteBtn.setEnabled(false);
        } catch (Exception ex) {
            Notification.show("Ошибка загрузки данных: " + ex.getMessage(), 5000, Notification.Position.MIDDLE);
        }
    }

    private static boolean isTextJdbcType(int jdbcType) {
        return jdbcType == java.sql.Types.VARCHAR
                || jdbcType == java.sql.Types.NVARCHAR
                || jdbcType == java.sql.Types.LONGVARCHAR
                || jdbcType == java.sql.Types.LONGNVARCHAR
                || jdbcType == java.sql.Types.CHAR
                || jdbcType == java.sql.Types.NCHAR;
    }

    private void updateDeleteState(RowData selected) {
        if (selected == null) {
            deleteBtn.setEnabled(false);
            editBtn.setEnabled(false);
            return;
        }
        if (currentPk.isEmpty()) {
            deleteBtn.setEnabled(false);
            editBtn.setEnabled(false);
            return;
        }
        Object pkValue = selected.get(currentPk.get().columnName());
        deleteBtn.setEnabled(pkValue != null);
        editBtn.setEnabled(pkValue != null);
    }

    private void deleteSelected() {
        RowData selected = grid.asSingleSelect().getValue();
        if (currentTableName == null || currentTableName.isBlank() || selected == null) {
            return;
        }
        if (currentPk.isEmpty()) {
            Notification.show("Не удалось определить первичный ключ (удаление отключено)", 4000,
                    Notification.Position.MIDDLE);
            return;
        }

        PrimaryKeyInfo pk = currentPk.get();
        Object pkValue = selected.get(pk.columnName());
        if (pkValue == null) {
            Notification.show("Выбранная запись не содержит значения PK", 4000, Notification.Position.MIDDLE);
            return;
        }

        List<AccessDatabaseService.ReferenceInfo> refs;
        try {
            refs = db.findReferencesTo(currentTableName, pk, pkValue);
        } catch (Exception ex) {
            refs = List.of();
        }

        if (refs == null || refs.isEmpty()) {
            ConfirmDialog dialog = new ConfirmDialog();
            dialog.setHeader("Подтверждение удаления");
            dialog.setText("Удалить запись по ключу " + pk.columnName() + " = " + pkValue + "?");
            dialog.setCancelable(true);
            dialog.setConfirmText("Удалить");
            dialog.addConfirmListener(e -> {
                try {
                    int affected = db.deleteByPrimaryKey(currentTableName, pk, pkValue);
                    Notification.show("Удалено: " + affected, 2500, Notification.Position.BOTTOM_END);
                    refresh();
                } catch (Exception ex) {
                    Notification.show("Ошибка удаления: " + ex.getMessage(), 5000, Notification.Position.MIDDLE);
                }
            });
            dialog.open();
            return;
        }

        StringBuilder details = new StringBuilder();
        details.append("Найдены ссылки на удаляемую запись в других таблицах.\n\n");
        for (var r : refs) {
            details.append("- ").append(r.tableName()).append(".").append(r.columnName())
                    .append(": ").append(r.count()).append(" записей");
            if (!r.nullable()) {
                details.append(" (NULL недопустим)");
            }
            details.append("\n");
        }
        details.append("\nВыберите действие:");

        ConfirmDialog dialog = new ConfirmDialog();
        dialog.setHeader("Связанные записи");
        dialog.setText(details.toString());
        dialog.setConfirmText("Каскадно удалить");
        dialog.setRejectText("Заменить ссылки на NULL");
        dialog.setCancelText("Отмена");
        dialog.setCancelable(true);

        dialog.addConfirmListener(e -> {
            try {
                int affected = db.deleteByPrimaryKeyWithStrategy(
                        currentTableName,
                        pk,
                        pkValue,
                        AccessDatabaseService.DeleteStrategy.CASCADE
                );
                Notification.show("Удалено: " + affected, 2500, Notification.Position.BOTTOM_END);
                refresh();
            } catch (Exception ex) {
                Notification.show("Ошибка удаления: " + ex.getMessage(), 6000, Notification.Position.MIDDLE);
            }
        });

        dialog.addRejectListener(e -> {
            try {
                int affected = db.deleteByPrimaryKeyWithStrategy(
                        currentTableName,
                        pk,
                        pkValue,
                        AccessDatabaseService.DeleteStrategy.NULLIFY_REFERENCES
                );
                Notification.show("Выполнено: " + affected, 2500, Notification.Position.BOTTOM_END);
                refresh();
            } catch (Exception ex) {
                Notification.show("Ошибка удаления: " + ex.getMessage(), 6000, Notification.Position.MIDDLE);
            }
        });

        dialog.open();
    }

    private void openAddDialog() {
        if (currentTableName == null || currentTableName.isBlank()) {
            return;
        }
        if (currentColumns.isEmpty()) {
            Notification.show("Нет колонок для вставки", 3000, Notification.Position.MIDDLE);
            return;
        }

        try {
            Map<String, com.vaadin.flow.component.Component> fields = new LinkedHashMap<>();
            VerticalLayout form = new VerticalLayout();
            form.setPadding(false);
            form.setSpacing(false);

            for (ColumnInfo c : currentColumns) {
                if (c.autoIncrement()) {
                    continue;
                }

                com.vaadin.flow.component.Component editor = buildEditorForColumn(currentTableName, c, null);
                if (editor == null) {
                    continue;
                }
                fields.put(c.name(), editor);
                form.add(editor);
            }

            ConfirmDialog dialog = new ConfirmDialog();
            dialog.setHeader("Добавление записи");
            dialog.add(form);
            dialog.setCancelable(true);
            dialog.setConfirmText("Добавить");
            dialog.addConfirmListener(e -> {
                try {
                    Map<String, Object> values = new LinkedHashMap<>();
                    for (var entry : fields.entrySet()) {
                        Object v = extractEditorValue(entry.getValue());
                        if (v != null) {
                            values.put(entry.getKey(), v);
                        }
                    }
                    int affected = db.insertRow(currentTableName, values);
                    Notification.show("Добавлено: " + affected, 2500, Notification.Position.BOTTOM_END);
                    refresh();
                } catch (Exception ex) {
                    String msg = ex.getMessage();
                    if (msg == null || msg.isBlank()) {
                        msg = ex.getClass().getSimpleName();
                    }
                    Notification.show("Ошибка добавления: " + msg, 7000, Notification.Position.MIDDLE);
                }
            });
            dialog.open();
        } catch (Exception ex) {
            String msg = ex.getMessage();
            if (msg == null || msg.isBlank()) {
                msg = ex.getClass().getSimpleName();
            }
            Notification.show("Ошибка открытия формы добавления: " + msg, 7000, Notification.Position.MIDDLE);
        }
    }

    private void openEditDialog() {
        RowData selected = grid.asSingleSelect().getValue();
        if (currentTableName == null || currentTableName.isBlank() || selected == null) {
            return;
        }
        if (currentPk.isEmpty()) {
            return;
        }

        PrimaryKeyInfo pk = currentPk.get();
        Object pkValue = selected.get(pk.columnName());
        if (pkValue == null) {
            return;
        }

        try {
            Map<String, com.vaadin.flow.component.Component> fields = new LinkedHashMap<>();
            VerticalLayout form = new VerticalLayout();
            form.setPadding(false);
            form.setSpacing(false);

            for (ColumnInfo c : currentColumns) {
                if (c.autoIncrement()) {
                    continue;
                }
                if (c.name().equalsIgnoreCase(pk.columnName())) {
                    continue;
                }

                Object existing = selected.get(c.name());
                com.vaadin.flow.component.Component editor = buildEditorForColumn(currentTableName, c, existing);
                if (editor == null) {
                    continue;
                }
                fields.put(c.name(), editor);
                form.add(editor);
            }

            ConfirmDialog dialog = new ConfirmDialog();
            dialog.setHeader("Редактирование записи");
            dialog.add(form);
            dialog.setCancelable(true);
            dialog.setConfirmText("Сохранить");
            dialog.addConfirmListener(e -> {
                try {
                    Map<String, Object> values = new LinkedHashMap<>();
                    for (var entry : fields.entrySet()) {
                        values.put(entry.getKey(), extractEditorValue(entry.getValue()));
                    }
                    int affected = db.updateByPrimaryKey(currentTableName, pk, pkValue, values);
                    Notification.show("Обновлено: " + affected, 2500, Notification.Position.BOTTOM_END);
                    refresh();
                } catch (Exception ex) {
                    String msg = ex.getMessage();
                    if (msg == null || msg.isBlank()) {
                        msg = ex.getClass().getSimpleName();
                    }
                    Notification.show("Ошибка обновления: " + msg, 7000, Notification.Position.MIDDLE);
                }
            });
            dialog.open();
        } catch (Exception ex) {
            String msg = ex.getMessage();
            if (msg == null || msg.isBlank()) {
                msg = ex.getClass().getSimpleName();
            }
            Notification.show("Ошибка открытия формы редактирования: " + msg, 7000, Notification.Position.MIDDLE);
        }
    }

    private com.vaadin.flow.component.Component buildEditorForColumn(String tableName, ColumnInfo c, Object existingValue) {
        String col = c.name();

        String label = fieldLabel(tableName, col);

        if ("Интервалы движения".equals(tableName)
                && (col.equalsIgnoreCase("Начало работы") || col.equalsIgnoreCase("Конец работы"))) {
            TextField tf = new TextField(label);
            tf.setWidth("8em");
            tf.setPlaceholder("HH:mm");
            tf.getElement().setProperty("inputmode", "numeric");
            tf.getElement().setProperty("pattern", "[0-9]*");
            tf.getElement().setProperty("maxlength", 5);
            tf.setValueChangeMode(ValueChangeMode.EAGER);

            ComponentUtil.setData(tf, TimeDigitsEditorMarker.class, new TimeDigitsEditorMarker());

            tf.addValueChangeListener(e -> {
                String raw = e.getValue() == null ? "" : e.getValue();
                String digits = raw.replaceAll("\\D", "");
                if (digits.length() > 4) {
                    digits = digits.substring(0, 4);
                }
                String formatted;
                if (digits.length() <= 2) {
                    formatted = digits;
                } else {
                    formatted = digits.substring(0, 2) + ":" + digits.substring(2);
                }
                if (!formatted.equals(raw)) {
                    tf.setValue(formatted);
                }
            });

            if (existingValue != null) {
                LocalTime lt;
                if (existingValue instanceof Timestamp ts) {
                    lt = ts.toLocalDateTime().toLocalTime();
                } else if (existingValue instanceof Date d) {
                    lt = Instant.ofEpochMilli(d.getTime()).atZone(ZoneId.systemDefault()).toLocalTime();
                } else if (existingValue instanceof Time t) {
                    lt = t.toLocalTime();
                } else {
                    lt = parseTime(String.valueOf(existingValue));
                }
                if (lt != null) {
                    tf.setValue(String.format("%02d:%02d", lt.getHour(), lt.getMinute()));
                }
            }
            return tf;
        }

        // Boolean
        if (c.jdbcType() == java.sql.Types.BIT || c.jdbcType() == java.sql.Types.BOOLEAN) {
            Checkbox cb = new Checkbox(label);
            cb.setValue(existingValue != null && Boolean.parseBoolean(String.valueOf(existingValue)));
            return cb;
        }

        // FK: use ComboBox with labels
        String refTable = EXPLICIT_FK.getOrDefault(tableName, Map.of()).get(col);
        if (refTable != null) {
            Select<AccessDatabaseService.LookupItem> combo = new Select<>();
            combo.setLabel(label);
            combo.setWidthFull();

            List<AccessDatabaseService.LookupItem> items;
            try {
                if ("Маршруты".equals(refTable)) {
                    items = db.fetchRouteLookupItems(500);
                } else {
                    items = db.fetchLookupItems(refTable, 500);
                }
            } catch (Exception ex) {
                Notification.show("Ошибка загрузки справочника '" + refTable + "': " + ex.getMessage(),
                        6000, Notification.Position.MIDDLE);
                return null;
            }

            combo.setItems(items);
            combo.setItemLabelGenerator(it -> {
                if (it == null) {
                    return "";
                }
                String lbl = it.label();
                if (lbl == null || lbl.isBlank()) {
                    return String.valueOf(it.key());
                }
                return lbl;
            });

            if (existingValue != null) {
                Object needle = existingValue;
                items.stream()
                        .filter(it -> String.valueOf(it.key()).equals(String.valueOf(needle)))
                        .findFirst()
                        .ifPresent(combo::setValue);
            }
            return combo;
        }

        // Date/time
        if (c.jdbcType() == java.sql.Types.TIME) {
            TimePicker tp = new TimePicker(label);
            tp.setWidthFull();
            ComponentUtil.setData(tp, Integer.class, c.jdbcType());
            if (existingValue != null) {
                if (existingValue instanceof Time t) {
                    tp.setValue(t.toLocalTime());
                } else {
                    tp.setValue(parseTime(String.valueOf(existingValue)));
                }
            }
            return tp;
        }
        if (c.jdbcType() == java.sql.Types.TIMESTAMP || c.jdbcType() == java.sql.Types.DATE) {
            // In this app we don't need dates in forms, only time
            TimePicker tp = new TimePicker(label);
            tp.setWidthFull();
            ComponentUtil.setData(tp, Integer.class, c.jdbcType());
            if (existingValue != null) {
                if (existingValue instanceof Timestamp ts) {
                    tp.setValue(ts.toLocalDateTime().toLocalTime());
                } else if (existingValue instanceof Date d) {
                    tp.setValue(Instant.ofEpochMilli(d.getTime()).atZone(ZoneId.systemDefault()).toLocalTime());
                } else {
                    tp.setValue(parseTime(String.valueOf(existingValue)));
                }
            }
            return tp;
        }

        // Default text
        TextField tf = new TextField(label);
        tf.setWidthFull();
        tf.setValue(existingValue == null ? "" : String.valueOf(existingValue));
        return tf;
    }

    private static Object extractEditorValue(com.vaadin.flow.component.Component c) {
        if (c instanceof TextField tf) {
            TimeDigitsEditorMarker marker = ComponentUtil.getData(tf, TimeDigitsEditorMarker.class);
            if (marker != null) {
                String v = tf.getValue();
                if (v == null || v.isBlank()) {
                    return null;
                }
                String digits = v.replaceAll("\\D", "");
                if (digits.isBlank()) {
                    return null;
                }
                if (digits.length() != 4) {
                    throw new IllegalArgumentException("Введите время в формате HHmm (4 цифры)");
                }
                int h;
                int m;
                try {
                    h = Integer.parseInt(digits.substring(0, 2));
                    m = Integer.parseInt(digits.substring(2, 4));
                } catch (Exception ex) {
                    throw new IllegalArgumentException("Введите время в формате HHmm (4 цифры)");
                }
                if (h < 0 || h > 23 || m < 0 || m > 59) {
                    throw new IllegalArgumentException("Некорректное время: " + String.format("%02d:%02d", h, m));
                }
                LocalTime lt = LocalTime.of(h, m);
                LocalDate base = LocalDate.of(1899, 12, 30);
                return Timestamp.valueOf(LocalDateTime.of(base, lt));
            }

            String v = tf.getValue();
            return (v == null || v.isBlank()) ? null : v;
        }
        if (c instanceof Checkbox cb) {
            return cb.getValue();
        }
        if (c instanceof TimePicker tp) {
            LocalTime lt = tp.getValue();
            if (lt == null) {
                return null;
            }
            Integer jdbcType = ComponentUtil.getData(tp, Integer.class);
            if (jdbcType != null && jdbcType == java.sql.Types.TIME) {
                return Time.valueOf(lt);
            }
            // Access stores "time" as date-time; keep a stable date part
            LocalDate base = LocalDate.of(1899, 12, 30);
            return Timestamp.valueOf(LocalDateTime.of(base, lt));
        }
        if (c instanceof com.vaadin.flow.component.combobox.ComboBox<?> generic) {
            Object v = generic.getValue();
            if (v instanceof AccessDatabaseService.LookupItem li) {
                return li.key();
            }
            return v;
        }
        if (c instanceof Select<?> generic) {
            Object v = generic.getValue();
            if (v instanceof AccessDatabaseService.LookupItem li) {
                return li.key();
            }
            return v;
        }
        return null;
    }

    private static String rootCauseMessage(Throwable t) {
        Throwable cur = t;
        int guard = 0;
        while (cur.getCause() != null && cur.getCause() != cur && guard < 20) {
            cur = cur.getCause();
            guard++;
        }
        String msg = cur.getMessage();
        if (msg == null || msg.isBlank()) {
            msg = cur.getClass().getSimpleName();
        }
        return msg;
    }

    private static LocalTime parseTime(String s) {
        try {
            return LocalTime.parse(s);
        } catch (Exception ignored) {
            return null;
        }
    }

    private static String fieldLabel(String tableName, String columnName) {
        // Remove leading "Код" and normalize some common genitive forms
        if (columnName == null) {
            return "";
        }
        String name = columnName;
        if (name.startsWith("Код ")) {
            name = name.substring(4);
            name = capitalize(name);
        }

        return switch (name) {
            case "Маршрута" -> "Маршрут";
            case "Остановки" -> "Остановка";
            case "Перевозчика" -> "Перевозчик";
            case "Тарифа" -> "Тариф";
            case "Улицы" -> "Улица";
            case "Населенного пункта" -> "Населенный пункт";
            default -> name;
        };
    }

    private static String capitalize(String s) {
        if (s == null || s.isBlank()) {
            return "";
        }
        return Character.toUpperCase(s.charAt(0)) + s.substring(1);
    }

    private static String formatCellValue(Object v) {
        if (v == null) {
            return "";
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
