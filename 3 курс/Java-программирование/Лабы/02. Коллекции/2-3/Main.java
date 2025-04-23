import java.util.*;

public class Main {
    public static void main(String[] args) {
        // 1. Создание LinkedList и заполнение
        LinkedList<Receipt> list = new LinkedList<>();
        list.add(new Receipt(1, 20250401, 1200.50f));
        list.add(new Receipt(2, 20250402, 800.00f));
        list.add(new Receipt(3, 20250403, 950.75f));
        list.add(new Receipt(4, 20250404, 1800.25f));
        list.add(new Receipt(5, 20250405, 600.00f));

        // 2. Сортировка по возрастанию суммы
        list.sort(Comparator.comparingDouble(Receipt::getSum));

        // 3. Просмотр контейнера
        System.out.println("Сортировка по возрастанию (LinkedList):");
        for (Receipt k : list) {
            System.out.println(k);
        }

        // 4. Поиск элемента с суммой > 1000
        Receipt found = null;
        for (Receipt k : list) {
            if (k.sum > 1000) {
                found = k;
                break;
            }
        }

        System.out.println("\nПервый элемент с суммой > 1000:");
        if (found != null) {
            System.out.println(found);
        } else {
            System.out.println("Не найдено");
        }

        // 5. Переместить элементы с суммой < 1000 в TreeMap
        TreeMap<Integer, Receipt> map = new TreeMap<>();
        Iterator<Receipt> it = list.iterator();
        while (it.hasNext()) {
            Receipt k = it.next();
            if (k.sum < 1000) {
                map.put(k.number, k);
                it.remove();
            }
        }

        // 6. Просмотр второго контейнера
        System.out.println("\nTreeMap с квитанциями < 1000:");
        for (Map.Entry<Integer, Receipt> entry : map.entrySet()) {
            System.out.println(entry.getValue());
        }

        // 7. Сортировка обоих контейнеров по убыванию
        list.sort((a, b) -> Float.compare(b.sum, a.sum));

        TreeMap<Integer, Receipt> sortedMap = new TreeMap<>((a, b) -> b - a);
        sortedMap.putAll(map);

        // 8. Просмотр после сортировки по убыванию
        System.out.println("\nLinkedList по убыванию:");
        for (Receipt k : list) {
            System.out.println(k);
        }

        System.out.println("\nTreeMap по убыванию ключей:");
        for (Map.Entry<Integer, Receipt> entry : sortedMap.entrySet()) {
            System.out.println(entry.getValue());
        }

        // 9. Слияние в третий контейнер (ArrayList)
        ArrayList<Receipt> merged = new ArrayList<>();
        merged.addAll(list);
        merged.addAll(sortedMap.values());

        // 10. Просмотр третьего контейнера
        System.out.println("\nИтоговый контейнер (ArrayList):");
        for (Receipt k : merged) {
            System.out.println(k);
        }
    }
}
