package com.northpole.snow.db;

import java.util.LinkedHashMap;
import java.util.Map;

public class RowData {

    private final Map<String, Object> values = new LinkedHashMap<>();

    public Map<String, Object> values() {
        return values;
    }

    public Object get(String column) {
        return values.get(column);
    }

    public void put(String column, Object value) {
        values.put(column, value);
    }
}
