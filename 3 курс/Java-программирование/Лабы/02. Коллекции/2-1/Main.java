import java.util.*;

public class Main {
    public static void main(String[] args) {
        // 1. Создать контейнер LinkedList и заполнить его данными типа int
        LinkedList<Integer> list1 = new LinkedList<>();
        for (int i = 1; i <= 10; i++) {
            list1.add(i);
        }

        // 2. Просмотреть контейнер
        System.out.println("Первый контейнер:");
        System.out.println(list1);

        // 3. Удалить из контейнера одни элементы и заменить другие
        list1.removeIf(n -> n % 2 == 0); // удалить чётные
        for (int i = 0; i < list1.size(); i++) {
            if (list1.get(i) == 5) {
                list1.set(i, 55); // заменить 5 на 55
            }
        }

        // 4. Просмотреть контейнер с использованием итераторов
        System.out.println("Первый контейнер (через итератор):");
        Iterator<Integer> it = list1.iterator();
        while (it.hasNext()) {
            System.out.print(it.next() + " ");
        }
        System.out.println();

        // 5. Создать второй контейнер и заполнить его данными типа int
        LinkedList<Integer> list2 = new LinkedList<>();
        for (int i = 100; i <= 105; i++) {
            list2.add(i);
        }

        // 6. Удалить из первого контейнера n элементов после заданного и добавить элементы из второго
        int startIndex = 1;
        int n = 2;

        int removeStart = Math.min(startIndex + 1, list1.size());
        for (int i = 0; i < n && removeStart < list1.size(); i++) {
            list1.remove(removeStart);
        }

        list1.addAll(list2);

        // 7. Просмотреть оба контейнера
        System.out.println("Первый контейнер после изменений:");
        System.out.println(list1);

        System.out.println("Второй контейнер:");
        System.out.println(list2);
    }
}
