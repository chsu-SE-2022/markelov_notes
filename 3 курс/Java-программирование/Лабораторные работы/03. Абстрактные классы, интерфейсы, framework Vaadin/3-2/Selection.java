package com.northpole.snow.logic;

public class Selection implements Array {
    private double[] data;  // Внутренний массив для хранения данных

    // Преобразует строку чисел в массив double
    @Override
    public void input(String input) {
        // Удаляем пробелы по краям и разбиваем строку по пробелам
        String[] tokens = input.trim().split("\\s+");
        // Создаем массив нужного размера
        data = new double[tokens.length];
        // Конвертируем каждую строку в число
        for (int i = 0; i < tokens.length; i++) {
            data[i] = Double.parseDouble(tokens[i]);
        }
    }

    // Возвращает отформатированную строку элементов массива
    @Override
    public String output() {
        StringBuilder sb = new StringBuilder();
        // Форматируем каждое число с 3 знаками после запятой
        for (double d : data) {
            sb.append(String.format("%.3f ", d));
        }
        // Удаляем последний пробел и возвращаем
        return sb.toString().trim();
    }

    // Реализация сортировки выбором
    @Override
    public void sort() {
        // Проходим по всем элементам кроме последнего
        for (int i = 0; i < data.length - 1; i++) {
            int minIdx = i;  // Индекс минимального элемента
            // Ищем минимальный элемент в оставшейся части
            for (int j = i + 1; j < data.length; j++) {
                if (data[j] < data[minIdx]) {
                    minIdx = j;
                }
            }
            // Меняем местами текущий и минимальный элементы
            double tmp = data[i];
            data[i] = data[minIdx];
            data[minIdx] = tmp;
        }
    }

    // Применяет натуральный логарифм к каждому элементу
    @Override
    public void foreach() {
        // Обрабатываем каждый элемент массива
        for (int i = 0; i < data.length; i++) {
            data[i] = Math.log(data[i]);  // Math.log - натуральный логарифм
        }
    }
}
