package com.northpole.snow.logic;

public abstract class Array {
    protected double[] data;

    public abstract void input(String input); // ввод данных
    public abstract String output(); // вывод данных
    public abstract void sort(); // сортировка
    public abstract void foreach(); // применение операции
}
