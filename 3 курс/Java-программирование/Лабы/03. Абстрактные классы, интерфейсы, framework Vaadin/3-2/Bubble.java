package com.northpole.snow.logic;

public class Bubble implements Array {
    private double[] data;  // Массив для хранения чисел

    // Преобразует строку чисел в массив double
    @Override
    public void input(String input) {
        // Разбиваем строку по пробелам и удаляем пустые элементы
        String[] tokens = input.trim().split("\\s+");
        data = new double[tokens.length];

        // Парсим каждую подстроку в число
        for (int i = 0; i < tokens.length; i++) {
            data[i] = Double.parseDouble(tokens[i]);
        }
    }

    // Форматирует массив в строку с 3 знаками после запятой
    @Override
    public String output() {
        StringBuilder sb = new StringBuilder();

        // Добавляем каждое число с форматированием
        for (double d : data) {
            sb.append(String.format("%.3f ", d));
        }

        // Удаляем последний пробел и возвращаем результат
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

    // Применяет квадратный корень к каждому элементу
    @Override
    public void foreach() {
        // Обрабатываем каждый элемент массива
        for (int i = 0; i < data.length; i++) {
            data[i] = Math.sqrt(data[i]);
        }
    }
}