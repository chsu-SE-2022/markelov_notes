public class Main {
    public static void main(String[] args) {
        // Вывод инструкций по запуску чат-сервера и клиента
        System.out.println("Использование:");
        System.out.println("  Запуск сервера: java ChatServer"); // как запустить сервер
        System.out.println("  Запуск клиента: java ChatClient [host] [port]"); // как запустить клиента
        System.out.println();
        System.out.println("По умолчанию: host=127.0.0.1, port=8088"); // значения по умолчанию
        System.out.println("Примеры:");
        System.out.println("  java ChatServer"); // пример запуска сервера
        System.out.println("  java ChatClient 127.0.0.1 8088"); // пример запуска клиента
    }
}