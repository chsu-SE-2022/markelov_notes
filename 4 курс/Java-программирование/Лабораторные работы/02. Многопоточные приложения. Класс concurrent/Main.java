import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

// Класс Bid – ставка участника
class Bid {
    final int participantId; // идентификатор участника, сделавшего ставку
    final int amount;        // сумма ставки

    Bid(int participantId, int amount) { // конструктор
        this.participantId = participantId;
        this.amount = amount;
    }
}

// Класс Lot – лот, выставляемый на торги
class Lot {
    final int id;        // идентификатор лота
    final String name;   // название лота
    final int basePrice; // начальная цена

    Lot(int id, String name, int basePrice) { // конструктор
        this.id = id;
        this.name = name;
        this.basePrice = basePrice;
    }
}

// Класс Participant – участник аукциона (выполняется в отдельном потоке)
class Participant implements Runnable {
    final int id;            // идентификатор участника
    final String name;       // имя участника
    private final Auction auction; // ссылка на объект аукциона
    private final int maxWillingness; // максимальная сумма, которую участник готов заплатить
    private final Random rnd = new Random(); // генератор случайных чисел
    private int balance; // текущий баланс участника

    Participant(int id, String name, int maxWillingness, Auction auction) {
        this.id = id;
        this.name = name;
        this.maxWillingness = maxWillingness;
        this.auction = auction;
        this.balance = maxWillingness;
    }

    @Override
    public void run() {
        // Ждём, пока первый лот не откроется
        while (auction.getCurrentLot() == null && !auction.isFinished()) {
            sleep(50);
        }

        // Основной цикл работы участника
        while (!auction.isFinished()) {
            Lot lot = auction.getCurrentLot();
            if (lot == null || auction.isSuspended(id)) { // если лот отсутствует или участник отстранён
                sleep(50);
                continue;
            }

            // Формирование стартовой ставки (не ниже текущей минимально допустимой)
            int highest = auction.getCurrentHighestAmount();
            int minRequired = (highest < lot.basePrice) ? lot.basePrice : highest + 10;
            int bid = Math.max(minRequired, lot.basePrice + rnd.nextInt(Math.max(1, maxWillingness - lot.basePrice + 1)));
            long endTime = System.currentTimeMillis() + auction.biddingDurationMillis;

            // Пока торги открыты и время не вышло
            while (auction.isBiddingOpen() && System.currentTimeMillis() < endTime) {
                // Перед каждой попыткой убедиться, что ставка не ниже текущей минимальной с шагом 10
                int h = auction.getCurrentHighestAmount();
                int required = (h < lot.basePrice) ? lot.basePrice : h + 10;
                if (bid < required) bid = required;
                if (bid <= balance) {
                    auction.submitBid(id, bid); // отправка ставки
                    bid += 10 + rnd.nextInt(41); // случайное повышение ставки (>=10)
                }
                sleep(200 + rnd.nextInt(200)); // пауза между ставками
            }
        }
    }

    // Оплата выигрыша; возвращает true, если оплата прошла успешно
    boolean pay(Lot lot, int amount) {
        sleep(200 + rnd.nextInt(800)); // имитация оплаты
        if (amount <= balance && rnd.nextDouble() > 0.15) {
            balance -= amount;
            return true;
        }
        return false;
    }

    int getMaxWillingness() {
        return maxWillingness;
    }

    int getBalance() {
        return balance;
    }

    // Вспомогательный метод для пауз
    private void sleep(int ms) {
        try { Thread.sleep(ms); } catch (InterruptedException ignored) {}
    }
}

// Класс Auction – управление ходом торгов
class Auction {
    private final List<Lot> lots;                  // список всех лотов
    private final List<Participant> participants;  // список всех участников
    private final Map<Integer, Integer> suspendedUntilLot = new ConcurrentHashMap<>(); // отстранённые участники
    private volatile int currentHighest = 0; // текущая максимальная ставка по открытому лоту
    private volatile int currentHighestParticipantId = -1; // участник, сделавший текущую максимальную ставку

    private volatile Lot currentLot;    // текущий лот
    private volatile boolean biddingOpen = false; // флаг активности торгов
    private volatile int lotIndex = -1;           // индекс текущего лота

    final int biddingDurationMillis;   // длительность торгов по одному лоту (мс)
    final int suspensionLots;          // количество лотов, на которое отстраняется неплательщик
    private final AtomicBoolean finished = new AtomicBoolean(false); // флаг завершения аукциона

    // Конструктор, инициализирующий аукцион
    Auction(List<Lot> lots, List<Participant> participants,
            int biddingDurationMillis, int suspensionLots) {
        this.lots = lots;
        this.participants = participants;
        this.biddingDurationMillis = biddingDurationMillis;
        this.suspensionLots = suspensionLots;
    }

    // Запуск аукциона
    void start() {
        // Создаём и запускаем отдельный поток для каждого участника
        for (Participant p : participants) {
            new Thread(p, "Participant-" + p.id).start();
        }

        // Поочерёдное открытие лотов и проведение торгов
        for (int i = 0; i < lots.size(); i++) {
            openLot(i);                   // открытие нового лота
            sleep(biddingDurationMillis); // ждём окончания торгов
            closeLotAndSettle();          // подводим итоги
        }

        finished.set(true); // аукцион завершён
        System.out.println("Аукцион завершён");
    }

    // Открытие нового лота
    private void openLot(int index) {
        currentLot = lots.get(index);
        lotIndex = index;
        // Инициализируем текущую максимальную ставку так, чтобы первая допустимая была ровно базовая цена
        currentHighest = currentLot.basePrice - 1;
        currentHighestParticipantId = -1;
        // Сначала объявляем лот, затем открываем торги, чтобы исключить ставки до объявления
        System.out.println("Открыт лот: [" + currentLot.id + "] " + currentLot.name + ", базовая цена=" + currentLot.basePrice);
        biddingOpen = true; // разрешаем торги
    }

    // Завершение торгов по лоту и подведение итогов
    private void closeLotAndSettle() {
        biddingOpen = false;

        if (currentHighest < currentLot.basePrice || currentHighestParticipantId == -1) {
            System.out.println("Лот " + currentLot.name + " не продан.");
            return;
        }

        Participant winner = participants.stream()
                .filter(p -> p.id == currentHighestParticipantId)
                .findFirst()
                .orElse(null);

        // Информационное сообщение о предварительном победителе и ожидании оплаты
        if (winner != null) {
            System.out.println("Предварительный победитель: участник: " + winner.name + 
                    ", ставка: " + currentHighest + ". Ожидание оплаты...");
        }

        boolean paid = winner != null && winner.pay(currentLot, currentHighest);

        if (paid) {
            System.out.println("ПРОДАНО: лот " + currentLot.name + " участнику " + (winner != null ? winner.name : ("#" + currentHighestParticipantId)) +
                    " за " + currentHighest + ".");
        } else if (winner != null) {
            suspendedUntilLot.put(winner.id, lotIndex + suspensionLots + 1);
            System.out.println("Оплата не поступила. Участник " + winner.name + " отстранён на " + suspensionLots + " лота(ов).");
        }
    }

    // Приём ставки (минимальный шаг повышения 10)
    synchronized boolean submitBid(int participantId, int amount) {
        Lot lot = currentLot;
        if (lot == null) return false;
        if (!isBiddingOpen()) return false;
        if (isSuspended(participantId)) return false;
        // Запрет на несколько ставок подряд от одного участника
        if (participantId == currentHighestParticipantId) return false;
        int highest = getCurrentHighestAmount();
        int minRequired = (currentHighestParticipantId == -1)
                ? lot.basePrice
                : Math.max(lot.basePrice, highest + 10);
        if (amount < minRequired) return false;
        if (amount > currentHighest) {
            currentHighest = amount;
            currentHighestParticipantId = participantId;
        }
        System.out.println("Ставка принята: участник: " + getParticipantName(participantId) + ", лот: " + lot.id + ", сумма: " + amount + ".");
        return true;
    }

    boolean isBiddingOpen() { return biddingOpen; }
    Lot getCurrentLot() { return currentLot; }
    int getLotIndex() { return lotIndex; }

    int getCurrentHighestAmount() { return currentHighest; }

    // Проверка, отстранён ли участник
    boolean isSuspended(int participantId) {
        Integer until = suspendedUntilLot.get(participantId);
        return until != null && lotIndex < until;
    }

    boolean isFinished() { return finished.get(); }

    // Получение имени участника по id
    private String getParticipantName(int id) {
        return participants.stream()
                .filter(p -> p.id == id)
                .map(p -> p.name)
                .findFirst()
                .orElse("Участник#" + id);
    }

    // Вспомогательный метод для пауз
    private void sleep(int ms) {
        try { Thread.sleep(ms); } catch (InterruptedException ignored) {}
    }
}

// Главный класс программы
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите количество участников: ");
        int participantCount;
        try {
            participantCount = sc.nextInt();
        } catch (Exception e) {
            participantCount = 4;
        }
        sc.nextLine();

        System.out.print("Введите количество лотов: ");
        int lotCount;
        try {
            lotCount = sc.nextInt();
        } catch (Exception e) {
            lotCount = 4;
        }
        sc.nextLine();

        String[] namePool = {"Сергей", "Влад", "Алена", "Артемий", "Дима", "Миша", "Макс", "Виталя", "Никита", "Ваня", "Илья", "Катя", "Арина", "Артем"};
        String[] techPool = {"Ноутбук", "Смартфон", "Наушники", "Фотоаппарат", "Планшет", "Смарт-часы", "Монитор", "Принтер", "Видеокамера", "Кофемашина"};

        Random rnd = new Random();

        List<Lot> lots = new ArrayList<>();
        for (int i = 1; i <= lotCount; i++) {
            String techName = techPool[rnd.nextInt(techPool.length)];
            int base = 100 + rnd.nextInt(901);
            base = base - (base % 10);
            lots.add(new Lot(i, techName, base));
        }

        List<Participant> participants = new ArrayList<>();
        Auction auction = new Auction(lots, participants, 2000, 2);
        int maxBasePrice = lots.stream().mapToInt(l -> l.basePrice).max().orElse(0);
        // Подготовим пул имён: сначала используем каждое имя не более одного раза, затем начинаем добавлять суффиксы
        List<String> availableNames = new ArrayList<>(Arrays.asList(namePool));
        Collections.shuffle(availableNames, rnd);
        Map<String, Integer> assignedCounts = new HashMap<>();
        for (int i = 1; i <= participantCount; i++) {
            String baseName;
            String finalName;
            if (!availableNames.isEmpty()) {
                baseName = availableNames.remove(availableNames.size() - 1);
                int c = assignedCounts.getOrDefault(baseName, 0) + 1; // станет 1
                assignedCounts.put(baseName, c);
                finalName = baseName; // без суффикса, пока пул не исчерпан
            } else {
                baseName = namePool[rnd.nextInt(namePool.length)];
                int c = assignedCounts.getOrDefault(baseName, 0) + 1; // 2, 3, ...
                assignedCounts.put(baseName, c);
                finalName = (c == 1) ? baseName : (baseName + " " + c);
            }
            // Генерируем бюджет участника так, чтобы он был явно выше самого дорогого лота
            int maxWillingness = maxBasePrice + 300 + rnd.nextInt(901); // [maxBase+300 .. maxBase+1200)
            maxWillingness = maxWillingness - (maxWillingness % 10); // кратно 10
            participants.add(new Participant(i, finalName, maxWillingness, auction));
        }

        System.out.println("Список участников и их деньги:");
        for (Participant p : participants) {
            System.out.println("- " + p.name + ": " + p.getBalance());
        }

        auction.start();
    }
}