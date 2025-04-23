import java.util.*;

public class Main {
    public static void main(String[] args) {
        // 1. Создать контейнер LinkedList и заполнить его данными типа Receipt
        LinkedList<Receipt> list1 = new LinkedList<>();
        list1.add(new Receipt(1, 20250401, 1200.50f));
        list1.add(new Receipt(2, 20250402, 800.00f));
        list1.add(new Receipt(3, 20250403, 950.75f));
        list1.add(new Receipt(4, 20250404, 1100.25f));
        list1.add(new Receipt(5, 20250405, 300.00f));

        // 2. Просмотреть контейнер
        System.out.println("Первый контейнер:");
        for (Receipt k : list1) {
            System.out.println(k);
        }

        // 3. Удалить из контейнера одни элементы и заменить другие
        list1.removeIf(k -> k.sum < 900); // удалить квитанции с суммой < 900
        for (int i = 0; i < list1.size(); i++) {
            if (list1.get(i).number == 3) {
                list1.set(i, new Receipt(33, 20250410, 3333.33f)); // замена по номеру
            }
        }

        // 4. Просмотреть контейнер с использованием итераторов
        System.out.println("\nПервый контейнер (через итератор):");
        Iterator<Receipt> it = list1.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }

        // 5. Создать второй контейнер и заполнить его данными типа Receipt
        LinkedList<Receipt> list2 = new LinkedList<>();
        list2.add(new Receipt(10, 20250406, 1500.00f));
        list2.add(new Receipt(11, 20250407, 1750.50f));
        list2.add(new Receipt(12, 20250408, 1800.00f));

        // 6. Удалить из первого контейнера n элементов после заданного и добавить элементы из второго
        int startIndex = 0; // после первого элемента
        int n = 1;          // количество удаляемых элементов

        int removeStart = Math.min(startIndex + 1, list1.size());
        for (int i = 0; i < n && removeStart < list1.size(); i++) {
            list1.remove(removeStart);
        }

        list1.addAll(list2);

        // 7. Просмотреть оба контейнера
        System.out.println("\nПервый контейнер после изменений:");
        for (Receipt k : list1) {
            System.out.println(k);
        }

        System.out.println("\nВторой контейнер:");
        for (Receipt k : list2) {
            System.out.println(k);
        }
    }
}
