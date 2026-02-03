import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

// Класс Picture – рисует кривую "Декартов лист" на заданном холсте в отдельном потоке
class Picture implements Runnable {
    private final DrawCanvas canvas; // Холст для рисования
    private final double a;          // Параметр кривой
    private final double scale;      // Масштаб (пиксели на единицу)
    private final int originX;       // Центр холста X
    private final int originY;       // Центр холста Y
    private final int offsetX;       // Сдвиг по X относительно центра
    private final int offsetY;       // Сдвиг по Y относительно центра
    private final Color color;       // Цвет кривой

    // Конструктор – задаёт все параметры кривой и холста
    public Picture(DrawCanvas canvas, double a, double scale, int originX, int originY, int offsetX, int offsetY, Color color) {
        this.canvas = canvas;
        this.a = a;
        this.scale = scale;
        this.originX = originX;
        this.originY = originY;
        this.offsetX = offsetX;
        this.offsetY = offsetY;
        this.color = color;
    }

    // Метод start() – создаёт новый поток и запускает run()
    public void start() {
        new Thread(this).start();
    }

    // Метод run() – рисует кривую
    @Override
    public void run() {
        Graphics2D g2 = canvas.getBufferGraphics(); // Получаем графику буфера холста
        if (g2 == null) return;

        try {
            // Включаем сглаживание линий и задаём толщину
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2.setStroke(new BasicStroke(2f));

            // Запуск анимационного рисования кривой
            drawFoliumAnimated(g2);
        } finally {
            g2.dispose(); // Освобождаем ресурсы графики
        }
    }

    // Делим кривую на два сегмента для обхода разрыва при t = -1
    private void drawFoliumAnimated(Graphics2D g) {
        int step = 0;
        step += plotRangeAnimated(g, -100.0, -1.001, Double.NaN, step);
        step += plotRangeAnimated(g, -0.999, 100.0, Double.NaN, step);
    }

    // Рисование сегмента кривой с анимацией
    private int plotRangeAnimated(Graphics2D g, double tStart, double tEnd, double tStep, int stepStart) {
        int step = stepStart;
        double t = tStart;
        long lastRepaint = System.nanoTime();
        final long frameNs = 25_000_000L; // интервал обновления экрана ~25 мс
        int prevPx = Integer.MIN_VALUE;
        int prevPy = Integer.MIN_VALUE;

        // Основной цикл вычисления точек кривой
        while ((tStart < tEnd && t <= tEnd) || (tStart > tEnd && t >= tEnd)) {
            double dt;

            // Определяем шаг по t
            if (!Double.isNaN(tStep)) {
                dt = tStep;
            } else {
                double at = Math.abs(t);
                if (at < 2) dt = 0.0025;
                else if (at < 5) dt = 0.005;
                else if (at < 15) dt = 0.025;
                else dt = 0.05;
                if (tStart > tEnd) dt = -dt;
            }

            double denom = 1.0 + t * t * t;
            if (Math.abs(denom) >= 1e-6) {
                double x = (3.0 * a * t) / denom;
                double y = (3.0 * a * t * t) / denom;

                // Преобразование координат в экранные пиксели с учётом сдвига offset
                int px = (int) Math.round(originX + offsetX + x * scale);
                int py = (int) Math.round(originY + offsetY - y * scale);

                // Синхронизация для многопоточного рисования
                synchronized (canvas) {
                    g.setColor(color);
                    if (prevPx != Integer.MIN_VALUE) {
                        g.drawLine(prevPx, prevPy, px, py); // Соединяем точки линией
                    } else {
                        g.drawLine(px, py, px, py); // Рисуем первую точку
                    }
                }

                prevPx = px;
                prevPy = py;

                step++;
                long now = System.nanoTime();
                if (now - lastRepaint >= frameNs) {
                    canvas.repaint(); // Обновляем экран
                    lastRepaint = now;
                }
            }

            try { Thread.sleep(1); } catch (InterruptedException ignored) {} // Пауза для плавности
            t += dt;
        }
        canvas.repaint();
        return step - stepStart;
    }
}

// Класс DrawCanvas – холст с буфером для рисования
class DrawCanvas extends Canvas {
    private final BufferedImage buffer;

    public DrawCanvas(int width, int height) {
        buffer = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2 = buffer.createGraphics();
        try {
            g2.setColor(Color.WHITE);
            g2.fillRect(0, 0, width, height); // Заливаем белым цветом
        } finally {
            g2.dispose();
        }
    }

    // Возвращает объект Graphics2D для рисования на буфере
    public Graphics2D getBufferGraphics() {
        return buffer.createGraphics();
    }

    @Override
    public void paint(Graphics g) {
        g.drawImage(buffer, 0, 0, null); // Отображение буфера на экране
    }

    @Override
    public void update(Graphics g) {
        paint(g); // Избегаем мерцания при обновлении
    }
}

// Главный класс Main – создаёт окно и запускает рисование кривых
public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            int width = 600;
            int height = 600;

            // Создание окна JFrame
            JFrame window = new JFrame("Descartes Folium - Multi-threaded");
            window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
            window.setSize(width, height);
            window.setLocationRelativeTo(null); // Центр экрана
            window.setResizable(false);

            // Создание холста с буфером
            DrawCanvas canvas = new DrawCanvas(width, height);
            canvas.setBackground(Color.WHITE);
            window.add(canvas, BorderLayout.CENTER);
            window.setVisible(true);

            double scale = 60.0;
            int originX = width / 2;
            int originY = height / 2;

            // Создание трёх кривых с разными параметрами и сдвигами
            Picture p1 = new Picture(canvas, 0.5, scale, originX, originY, 0, 0, Color.RED);
            Picture p2 = new Picture(canvas, 1.0, scale, originX, originY, 0, 0, Color.GREEN);
            Picture p3 = new Picture(canvas, 2.0, scale, originX, originY, 0, 0, Color.BLUE);

            // Запуск кривых в отдельных потоках
            p1.start();
            p2.start();
            p3.start();
        });
    }
}