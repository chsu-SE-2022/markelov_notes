import java.io.BufferedReader; // для чтения данных из сокета
import java.io.IOException; // для обработки исключений ввода-вывода
import java.io.InputStreamReader; // для оборачивания InputStream в Reader
import java.io.PrintWriter; // для отправки текста клиенту
import java.io.OutputStreamWriter; // для указания кодировки при записи
import java.io.PrintStream;
import java.net.ServerSocket; // серверный сокет, слушающий порт
import java.net.Socket; // сокет для связи с клиентом
import java.time.LocalDateTime; // для получения текущего времени
import java.time.format.DateTimeFormatter; // для форматирования времени
import java.util.Map; // для хранения клиентов по имени
import java.util.Set; // для хранения уникальных клиентов
import java.util.concurrent.ConcurrentHashMap; // потокобезопасная карта и набор
import java.nio.charset.StandardCharsets; // для указания UTF-8
import java.nio.charset.Charset;

public class ChatServer {
    public static final int PORT = 8088; // порт, на котором будет работать сервер

    // Карта для быстрого поиска клиентов по имени
    private final Map<String, ClientHandler> clientsByName = new ConcurrentHashMap<>();
    // Набор всех подключенных клиентов
    private final Set<ClientHandler> clients = ConcurrentHashMap.newKeySet();

    public static void main(String[] args) throws IOException {
        try {
            Charset consoleCs = getConsoleCharset();
            if (consoleCs != null) {
                System.setOut(new PrintStream(System.out, true, consoleCs.name()));
                System.setErr(new PrintStream(System.err, true, consoleCs.name()));
            }
        } catch (Exception ignored) {
        }
        new ChatServer().start(); // запуск сервера
    }

    public void start() throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) { // создаем серверный сокет
            System.out.println("Чат-сервер запущен на порту " + PORT);
            while (true) {
                Socket socket = serverSocket.accept(); // ждем подключения клиента
                ClientHandler handler = new ClientHandler(socket); // создаем обработчик клиента
                Thread t = new Thread(handler, "ClientHandler-" + socket.getPort()); // запускаем обработчик в отдельном потоке
                t.start();
            }
        }
    }

    // Метод для отправки сообщения всем клиентам, кроме исключенного
    private void broadcast(String message, ClientHandler exclude) {
        for (ClientHandler client : clients) {
            if (client != exclude) {
                client.send(message);
            }
        }
    }

    // Метод для получения текущего времени в формате HH:mm:ss
    private String timestamp() {
        return LocalDateTime.now().format(DateTimeFormatter.ofPattern("HH:mm:ss"));
    }

    private static Charset getConsoleCharset() {
        String os = System.getProperty("os.name", "").toLowerCase();
        if (os.contains("win")) {
            try {
                return Charset.forName("cp866");
            } catch (Exception ignored) {
            }
        }
        return StandardCharsets.UTF_8;
    }

    // Внутренний класс для обработки отдельного клиента
    private class ClientHandler implements Runnable {
        private final Socket socket; // сокет клиента
        private BufferedReader in; // для чтения сообщений от клиента
        private PrintWriter out; // для отправки сообщений клиенту
        private String name; // имя клиента

        ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try {
                in = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8)); // создаем поток чтения в UTF-8
                out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8), true); // создаем поток записи в UTF-8

                out.println("WELCOME Добро пожаловать! Чат-сервер на порту " + PORT); // приветствие клиента
                out.println("ENTER_NAME"); // просим клиента ввести имя

                // Цикл регистрации имени
                while (true) {
                    String requested = in.readLine();
                    if (requested == null) return; // клиент отключился
                    requested = requested.trim();
                    if (requested.isEmpty()) {
                        out.println("NAME_REJECTED Пустое имя недопустимо"); // пустое имя запрещено
                        continue;
                    }
                    if (clientsByName.containsKey(requested)) {
                        out.println("NAME_REJECTED Имя уже занято"); // имя уже занято
                        continue;
                    }
                    name = requested;
                    clientsByName.put(name, this); // сохраняем клиента по имени
                    clients.add(this); // добавляем в общий набор клиентов
                    out.println("NAME_ACCEPTED " + name); // подтверждение регистрации
                    break;
                }

                System.out.println("[" + timestamp() + "] Подключился: " + name + " с " + socket.getRemoteSocketAddress());
                broadcast("[" + timestamp() + "] * " + name + " вошёл(ла) в чат", this); // уведомляем других о подключении
                send("Введите сообщения и нажмите Enter для отправки. Используйте /users для списка пользователей, /quit или END для выхода."); // инструкции клиенту

                // Основной цикл получения сообщений от клиента
                String line;
                while ((line = in.readLine()) != null) {
                    line = line.trim();
                    if (line.equalsIgnoreCase("END") || line.equalsIgnoreCase("/quit")) {
                        break; // клиент выходит
                    }
                    if (line.equalsIgnoreCase("/users")) {
                        send("Пользователи: " + String.join(", ", clientsByName.keySet())); // вывод списка пользователей
                        continue;
                    }
                    String msg = "[" + timestamp() + "] " + name + ": " + line;
                    System.out.println(msg); // вывод в консоль сервера
                    broadcast(msg, null); // отправка всем клиентам
                }
            } catch (IOException e) {
                // соединение сброшено; обработка в cleanup
            } finally {
                cleanup(); // очистка ресурсов после выхода клиента
            }
        }

        // Метод для корректного завершения работы с клиентом
        private void cleanup() {
            try {
                if (name != null) {
                    clientsByName.remove(name); // удаляем из карты по имени
                }
                clients.remove(this); // удаляем из набора клиентов
                if (name != null) {
                    String msg = "[" + timestamp() + "] * " + name + " вышел(ла) из чата";
                    System.out.println(msg); // уведомление о выходе
                    broadcast(msg, null);
                }
                if (out != null) out.close(); // закрываем поток записи
                if (in != null) in.close(); // закрываем поток чтения
                if (socket != null && !socket.isClosed()) socket.close(); // закрываем сокет
            } catch (IOException ignored) {
            }
        }

        // Метод отправки сообщения конкретному клиенту
        void send(String message) {
            if (out != null) {
                out.println(message);
            }
        }
    }
}