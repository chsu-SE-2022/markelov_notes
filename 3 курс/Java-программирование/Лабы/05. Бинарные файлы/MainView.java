package com.northpole.snow;

import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.dialog.Dialog;
import com.vaadin.flow.component.html.Label;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.textfield.IntegerField;
import com.vaadin.flow.component.textfield.TextArea;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.router.Route;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.TreeSet;
import java.util.Random;

// Аннотация Route указывает, что этот класс является корневым представлением
@Route("")
public class MainView extends VerticalLayout {

    // Поля ввода и отображения данных
    private final TextArea outputArea = new TextArea("Содержимое файла");
    private final TextArea squaresArea = new TextArea("Отсутствующие точные квадраты");
    private final IntegerField nField = new IntegerField("Макс количество чисел (n)");
    private final IntegerField aField = new IntegerField("Диапазон a");
    private final IntegerField bField = new IntegerField("Диапазон b");

    // Конструктор главного представления
    public MainView() {
        setSizeFull(); // Занимать все доступное пространство
        setPadding(true); // Внутренние отступы
        setSpacing(true); // Расстояние между компонентами

        // Настройка размеров текстовых областей
        outputArea.setWidthFull();
        outputArea.setHeight("200px");
        squaresArea.setWidthFull();
        squaresArea.setHeight("150px");

        // Установка значений по умолчанию для полей ввода
        nField.setValue(100);
        aField.setValue(0);
        bField.setValue(1000);

        // Создание кнопок
        Button createFileBtn = new Button("Создать файл");
        Button openFileBtn = new Button("Открыть файл и показать");
        Button showSquaresBtn = new Button("Показать отсутствующие точные квадраты");

        // Назначение обработчиков событий для кнопок
        createFileBtn.addClickListener(e -> showFileNameDialog("Создать файл", this::createFile));
        openFileBtn.addClickListener(e -> showFileNameDialog("Открыть файл", this::openFile));
        showSquaresBtn.addClickListener(e -> showFileNameDialog("Показать квадраты", this::showMissingSquares));

        // Добавление компонентов на форму в определенном порядке
        add(nField, aField, bField,
                createFileBtn, openFileBtn, showSquaresBtn,
                new Label("Содержимое файла:"), outputArea,
                new Label("Отсутствующие точные квадраты:"), squaresArea);
    }

    // Метод для отображения диалогового окна с вводом имени файла
    private void showFileNameDialog(String title, java.util.function.Consumer<String> action) {
        Dialog dialog = new Dialog();
        dialog.setWidth("300px");
        dialog.setCloseOnEsc(true); // Закрывать по ESC
        dialog.setCloseOnOutsideClick(false); // Не закрывать по клику вне диалога

        // Поле для ввода имени файла
        TextField fileNameInput = new TextField("Имя файла");
        fileNameInput.setWidthFull();

        // Кнопка OK - выполняет действие с переданным именем файла
        Button okButton = new Button("OK", event -> {
            String fileName = fileNameInput.getValue();
            if (fileName == null || fileName.trim().isEmpty()) {
                Notification.show("Введите имя файла");
                return;
            }
            dialog.close();
            action.accept(fileName.trim()); // Вызов переданного действия
        });

        // Кнопка отмены - просто закрывает диалог
        Button cancelButton = new Button("Отмена", event -> dialog.close());

        // Компоновка компонентов в диалоге
        VerticalLayout layout = new VerticalLayout(new Label(title), fileNameInput, okButton, cancelButton);
        layout.setPadding(false);
        layout.setSpacing(true);
        dialog.add(layout);
        dialog.open(); // Открытие диалога
    }

    // Метод для создания файла с случайными числами
    private void createFile(String fileName) {
        Integer n = nField.getValue();
        Integer a = aField.getValue();
        Integer b = bField.getValue();

        // Валидация введенных данных
        if (n == null || n <= 0) {
            Notification.show("Введите корректное n (>0)");
            return;
        }
        if (a == null || b == null || a > b) {
            Notification.show("Введите корректный диапазон a <= b");
            return;
        }

        // Запись данных в файл
        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(fileName))) {
            // Записываем диапазон в начало файла
            dos.writeInt(a);
            dos.writeInt(b);

            // Генерация случайных чисел в заданном диапазоне
            Random rand = new Random();
            int count = 1 + rand.nextInt(n); // Случайное количество чисел
            for (int i = 0; i < count; i++) {
                int val = a + rand.nextInt(b - a + 1);
                dos.writeInt(val);
            }
            Notification.show("Файл создан с " + count + " элементами");
            outputArea.clear();
            squaresArea.clear();
        } catch (IOException ex) {
            Notification.show("Ошибка записи файла: " + ex.getMessage());
        }
    }

    // Метод для открытия файла и отображения его содержимого
    private void openFile(String fileName) {
        if (!Files.exists(Paths.get(fileName))) {
            Notification.show("Файл не найден");
            return;
        }
        try (DataInputStream dis = new DataInputStream(new FileInputStream(fileName))) {
            // Читаем диапазон (но не выводим его)
            dis.readInt(); // a
            dis.readInt(); // b

            // Чтение и отображение содержимого файла
            StringBuilder sb = new StringBuilder();
            while (dis.available() >= 4) {
                int val = dis.readInt();
                sb.append(val).append("\n");
            }
            outputArea.setValue(sb.toString());
            squaresArea.clear();
            Notification.show("Файл успешно открыт");
        } catch (IOException ex) {
            Notification.show("Ошибка чтения файла: " + ex.getMessage());
        }
    }

    // Метод для поиска отсутствующих точных квадратов в файле
    private void showMissingSquares(String fileName) {
        if (!Files.exists(Paths.get(fileName))) {
            Notification.show("Файл не найден");
            return;
        }

        try (DataInputStream dis = new DataInputStream(new FileInputStream(fileName))) {
            // Читаем диапазон из файла
            int a = dis.readInt();
            int b = dis.readInt();

            // Создаем множество всех возможных квадратов в диапазоне
            TreeSet<Integer> allSquares = new TreeSet<>();
            int i = 0;
            while (true) {
                int square = i * i;
                if (square > b) break; // Прекращаем, если квадрат превышает верхнюю границу
                if (square >= a) {
                    allSquares.add(square); // Добавляем квадрат, если он в диапазоне
                }
                i++;
            }

            // Читаем числа из файла и удаляем встречающиеся квадраты из множества
            while (dis.available() >= 4) {
                int val = dis.readInt();
                allSquares.remove(val);
            }

            // Формируем результат - только квадраты, не превышающие b
            StringBuilder sb = new StringBuilder();
            for (Integer square : allSquares) {
                sb.append(square).append("\n");
            }

            // Отображаем результат
            squaresArea.setValue(sb.length() == 0 ? "Все квадраты присутствуют" : sb.toString());

        } catch (IOException ex) {
            Notification.show("Ошибка обработки файла: " + ex.getMessage());
        }
    }
}