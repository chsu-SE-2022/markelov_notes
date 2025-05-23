package com.northpole.snow.logic;

public class Bubble extends Array {

    // Реализация метода ввода данных
    @Override
    public void input(String input) {
        // Разбиваем входную строку по пробелам (с учетом нескольких пробелов)
        String[] tokens = input.trim().split("\\s+");
        // Создаем массив чисел нужного размера
        data = new double[tokens.length];
        // Преобразуем каждую строку в число и сохраняем в массив
        for (int i = 0; i < tokens.length; i++) {
            data[i] = Double.parseDouble(tokens[i]);
        }
    }

    // Реализация метода вывода данных
    @Override
    public String output() {
        // Используем StringBuilder для эффективной конкатенации строк
        StringBuilder sb = new StringBuilder();
        // Форматируем каждое число с 3 знаками после запятой
        for (double d : data) {
            sb.append(String.format("%.3f ", d));
        }
        // Возвращаем результат, убирая последний пробел
        return sb.toString().trim();
    }

    // Реализация алгоритма пузырьковой сортировки
    @Override
    public void sort() {
        // Внешний цикл - проходим по всем элементам
        for (int i = 0; i < data.length - 1; i++) {
            // Внутренний цикл - сравниваем соседние элементы
            for (int j = data.length - 1; j > i; j--) {
                // Если текущий элемент больше следующего - меняем их местами
                if (data[j] < data[j - 1]) {
                    double tmp = data[j]; // Временная переменная для обмена
                    data[j] = data[j - 1];// Перемещаем меньший элемент влево
                    data[j - 1] = tmp; // Перемещаем больший элемент вправо
                }
            }
        }
    }

    // Реализация операции для каждого элемента массива
    @Override
    public void foreach() {
        // Применяем квадратный корень к каждому элементу массива
        for (int i = 0; i < data.length; i++) {
            data[i] = Math.sqrt(data[i]);  // Math.sqrt - стандартная функция Java
        }
    }
}