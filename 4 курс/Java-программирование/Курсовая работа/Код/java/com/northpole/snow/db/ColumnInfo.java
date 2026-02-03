package com.northpole.snow.db;

public record ColumnInfo(
        String name,
        int jdbcType,
        String typeName,
        boolean nullable,
        boolean autoIncrement
) {}
