import java.io.BufferedReader; // для чтения данных из сокета и консоли
import java.io.IOException; // для обработки исключений ввода-вывода
import java.io.InputStreamReader; // для оборачивания InputStream в Reader
import java.io.PrintWriter; // для отправки текста серверу
import java.io.OutputStreamWriter; // для указания кодировки при записи
import java.io.PrintStream; // для переназначения System.out с нужной кодировкой
import java.net.Socket; // сокет для связи с сервером
import java.nio.charset.StandardCharsets; // для указания UTF-8
import java.nio.charset.Charset; // для выбора кодировки консоли

public class ChatClient {
    public static void main(String[] args) throws IOException {
        // Настроим вывод в консоль в кодировке реальной консоли (на Windows: CP866), иначе UTF-8
        try {
            Charset consoleCs = getConsoleCharset();
            if (consoleCs != null) {
                System.setOut(new PrintStream(System.out, true, consoleCs.name()));
                System.setErr(new PrintStream(System.err, true, consoleCs.name()));
            }
        } catch (Exception ignored) {
        }
        // Определяем хост и порт: либо из аргументов, либо по умолчанию
        String host = args.length > 0 ? args[0] : "127.0.0.1";
        int port = args.length > 1 ? Integer.parseInt(args[1]) : 8088;

        // Создаем сокет и подключаемся к серверу
        try (Socket socket = new Socket(host, port)) {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8)); // поток чтения от сервера в UTF-8
            PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8), true); // поток отправки на сервер в UTF-8
            BufferedReader console = new BufferedReader(new InputStreamReader(System.in, getConsoleCharset() != null ? getConsoleCharset() : Charset.defaultCharset())); // поток чтения с консоли в кодировке консоли

            // Обработка приветствия и регистрации имени
            String line;
            socket.setSoTimeout(0); // отключаем таймаут чтения
            while ((line = in.readLine()) != null) {
                if (line.startsWith("WELCOME")) { // вывод приветствия сервера
                    String msg = line.length() > 8 ? line.substring(8).trim() : ""; // убрать токен
                    System.out.println(msg.isEmpty() ? "" : msg);
                } else if (line.startsWith("ENTER_NAME")) { // сервер просит ввести имя
                    System.out.print("Введите ваше имя: ");
                    String name = console.readLine();
                    if (name == null) return; // если EOF
                    name = name.trim();
                    out.println(name);
                } else if (line.startsWith("NAME_REJECTED")) { // сервер отклонил имя
                    String reason = line.indexOf(' ') > 0 ? line.substring(line.indexOf(' ') + 1) : "";
                    System.out.println("Сервер: " + (reason.isEmpty() ? "Имя отклонено" : reason));
                    System.out.print("Выберите другое имя: ");
                    String name = console.readLine();
                    if (name == null) return;
                    name = name.trim();
                    out.println(name);
                } else if (line.startsWith("NAME_ACCEPTED")) { // имя принято
                    String[] parts = line.split(" ", 2);
                    String accepted = parts.length > 1 ? parts[1] : "";
                    System.out.println("Вы вошли как: " + accepted);
                    break; // регистрация завершена
                } else {
                    // Любое другое сообщение от сервера во время регистрации
                    System.out.println(line);
                }
            }



            // Поток для чтения сообщений с сервера и вывода на консоль
            Thread reader = new Thread(() -> {
                try {
                    String s;
                    while ((s = in.readLine()) != null) {
                        System.out.println(s);
                    }
                } catch (IOException ignored) {
                } finally {
                    System.out.println("Отключено от сервера."); // уведомление при отключении
                }
            }, "ServerReader");
            reader.setDaemon(true); // поток завершится вместе с главным
            reader.start();

            // Главный цикл чтения сообщений с консоли и отправки серверу
            String input;
            while ((input = console.readLine()) != null) {
                out.println(input); // отправка сообщения
                if ("/quit".equalsIgnoreCase(input) || "END".equalsIgnoreCase(input)) {
                    break; // выход из чата
                }
            }
        }
    }

    private static Charset getConsoleCharset() {
        String os = System.getProperty("os.name", "").toLowerCase();
        if (os.contains("win")) {
            try {
                return Charset.forName("cp866"); // кодовая страница консоли Windows
            } catch (Exception ignored) {
            }
        }
        return StandardCharsets.UTF_8; // для *nix терминалов
    }
}