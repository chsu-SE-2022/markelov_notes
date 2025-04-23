import Bus.Bus;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ArrayList<Bus> Buses = new ArrayList<>();
        Bus bus1 = new Bus("Маркелов", 130, 2, "НеФАЗ-5299", 2024, 1000);
        Bus bus2 = new Bus("Подтелков", 122, 2, "НеФАЗ-5299", 2024, 1500);
        Bus bus3 = new Bus("Фатькина", 542, 8, "ЛиАЗ-5292", 2021, 4000);
        Bus bus4 = new Bus("Беляков", 1308, 18, "МАЗ-103", 2017, 15000);
        Bus bus5 = new Bus("Бурмистров", 509, 12, "ЛиАЗ-5292", 2019, 12000);
        Bus bus6 = new Bus("Минеев", 109, 9, "НеФАЗ-5299", 2024, 2000);
        Bus bus7 = new Bus("Цветков", 717, 7, "МАЗ-103", 2013, 24000);

        Buses.add(bus1);
        Buses.add(bus2);
        Buses.add(bus3);
        //Buses.add(bus4);
        //Buses.add(bus5);
        Buses.add(bus6);
        //Buses.add(bus7);

        System.out.println(
                "1. Вывести список автобусов по номеру маршрута\n" +
                "2. Вывести список автобусов, которые эксплуатируются более 10 лет\n" +
                "3. Вывести список автобусов с пробегом более 10000 км\n" +
                "Введите номер операции: ");
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        switch (n) {
            case 1: {
                System.out.println("Введите номер маршрута: ");
                Scanner in1 = new Scanner(System.in);
                int route = in.nextInt();
                int count = 0;
                for (Bus b : Buses) count = b.checkRoute(route, count);
                if (count == 0) System.out.println("За данным маршрутом не закреплены автобусы, либо такого маршрута не существует");
                in1.close();
                break;
            }
            case 2: {
                int count = 0;
                for (Bus b : Buses) count = b.checkYear(count);
                if (count == 0) System.out.println("Нет автобусов, эксплуатирующихся более 10 лет");
                break;
            }
            case 3: {
                int count = 0;
                for (Bus b : Buses) count = b.checkMileage(count);
                if (count == 0) System.out.println("Нет автобусов с пробегом более 10000 км");
                break;
            }
            default: System.out.println("Такой операции нет!");
        }
        in.close();
    }
}