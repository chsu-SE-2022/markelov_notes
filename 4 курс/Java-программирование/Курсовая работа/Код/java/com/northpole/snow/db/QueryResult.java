package com.northpole.snow.db;

import java.util.List;

public record QueryResult(List<String> columns, List<RowData> rows) {}
