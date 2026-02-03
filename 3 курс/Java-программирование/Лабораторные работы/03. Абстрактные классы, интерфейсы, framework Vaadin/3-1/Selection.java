package com.northpole.snow.logic;

public class Selection extends Array {

    // Реализация метода ввода данных
    @Override
    public void input(String input) {
        // Удаляем лишние пробелы и разбиваем строку на отдельные числа
        String[] tokens = input.trim().split("\\s+");
        // Создаем массив для хранения чисел
        data = new double[tokens.length];
        // Преобразуем каждую подстроку в число типа double
        for (int i = 0; i < tokens.length; i++) {
            data[i] = Double.parseDouble(tokens[i]);
        }
    }

    // Реализация метода вывода данных
    @Override
    public String output() {
        // Используем StringBuilder для эффективного построения строки
        StringBuilder sb = new StringBuilder();
        // Форматируем каждое число с тремя знаками после запятой
        for (double d : data) {
            sb.append(String.format("%.3f ", d));
        }
        // Возвращаем результат, обрезая последний пробел
        return sb.toString().trim();
    }

    // Реализация алгоритма сортировки выбором
    @Override
    public void sort() {
        // Проходим по всем элементам массива, кроме последнего
        for (int i = 0; i < data.length - 1; i++) {
            // Предполагаем, что минимальный элемент находится на текущей позиции
            int minIdx = i;
            // Ищем минимальный элемент в оставшейся части массива
            for (int j = i + 1; j < data.length; j++) {
                if (data[j] < data[minIdx]) {
                    minIdx = j;  // Нашли новый минимальный элемент
                }
            }
            // Обмен местами текущего элемента с найденным минимальным
            double tmp = data[i];
            data[i] = data[minIdx];
            data[minIdx] = tmp;
        }
    }

    // Реализация операции для каждого элемента массива
    @Override
    public void foreach() {
        // Применяем натуральный логарифм (Math.log) к каждому элементу массива
        for (int i = 0; i < data.length; i++) {
            data[i] = Math.log(data[i]);
        }
    }
}