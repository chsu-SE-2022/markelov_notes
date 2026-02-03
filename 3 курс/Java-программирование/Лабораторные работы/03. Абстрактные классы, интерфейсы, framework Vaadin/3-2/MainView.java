package com.northpole.snow;

import com.northpole.snow.logic.Array;
import com.northpole.snow.logic.Bubble;
import com.northpole.snow.logic.Selection;
import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.html.H2;
import com.vaadin.flow.component.html.Label;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.router.Route;

@Route("")
public class MainView extends VerticalLayout {

    // Конструктор класса MainView
    public MainView() {
        // Создание заголовка страницы
        H2 title = new H2("Сортировка и обработка массива");

        // Создание текстового поля для ввода чисел
        TextField inputField = new TextField("Введите числа через пробел");
        inputField.setWidth("500px");  // Установка ширины поля ввода

        // Создание кнопок для разных видов сортировки
        Button bubbleBtn = new Button("Bubble: sort + sqrt");
        Button selectionBtn = new Button("Selection: sort + log");

        // Создание метки для вывода результата
        Label sortedLabel = new Label();
        Label processedLabel = new Label();

        // Обработчик клика для кнопки Bubble sort
        bubbleBtn.addClickListener(e -> {
            Array arr = new Bubble();
            arr.input(inputField.getValue());
            arr.sort();
            sortedLabel.setText("Отсортированный массив (Bubble): " + arr.output());
            arr.foreach();
            processedLabel.setText("После sqrt: " + arr.output());
        });

        // Обработчик клика для кнопки Selection sort
        selectionBtn.addClickListener(e -> {
            Array arr = new Selection();
            arr.input(inputField.getValue());
            arr.sort();
            sortedLabel.setText("Отсортированный массив (Bubble): " + arr.output());
            arr.foreach();
            processedLabel.setText("После log: " + arr.output());
        });

        // Добавляем все компоненты на страницу в вертикальном layout
        add(title, inputField, bubbleBtn, selectionBtn, sortedLabel, processedLabel);
    }
}