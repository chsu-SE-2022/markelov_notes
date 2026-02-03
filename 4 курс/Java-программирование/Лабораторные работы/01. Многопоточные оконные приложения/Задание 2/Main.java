import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

// Класс Picture – рисует кривую "Декартов лист" в отдельном окне и потоке
class Picture implements Runnable {
    private DrawCanvas canvas; // Холст для рисования
    private final double a;    // Параметр кривой
    private final double scale; // Масштаб (пиксели на единицу)
    private int originX;       // Центр холста X
    private int originY;       // Центр холста Y
    private final Color color; // Цвет кривой
    private final String title; // Название окна
    private final int width;   // Ширина окна
    private final int height;  // Высота окна
    private final int posX;    // Позиция окна на экране X
    private final int posY;    // Позиция окна на экране Y
    private final int offsetX; // Сдвиг по X
    private final int offsetY; // Сдвиг по Y

    // Конструктор – задаёт параметры кривой и окна
    public Picture(double a, double scale, Color color, String title, int width, int height, int posX, int posY, int offsetX, int offsetY) {
        this.a = a;
        this.scale = scale;
        this.color = color;
        this.title = title;
        this.width = width;
        this.height = height;
        this.posX = posX;
        this.posY = posY;
        this.offsetX = offsetX;
        this.offsetY = offsetY;
    }

    // Метод start() – создаёт поток и запускает run()
    public void start() {
        new Thread(this).start();
    }

    // Метод run() – создаёт окно и рисует кривую
    @Override
    public void run() {
        try {
            // Создание окна и холста в потоке
            SwingUtilities.invokeAndWait(() -> {
                JFrame w = new JFrame(title);
                w.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
                w.setSize(width, height);
                w.setLocation(posX, posY); // Позиция окна на экране
                w.setResizable(false);

                DrawCanvas c = new DrawCanvas(width, height);
                c.setBackground(Color.WHITE);
                w.add(c, BorderLayout.CENTER);
                w.setVisible(true);

                this.canvas = c;
                // Центр холста с учётом сдвига offset
                this.originX = width / 2 + offsetX;
                this.originY = height / 2 + offsetY;
            });
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }

        Graphics2D g2 = canvas.getBufferGraphics();
        if (g2 == null) return;
        try {
            // Включаем сглаживание и задаём толщину линии
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2.setStroke(new BasicStroke(2f));
            drawFoliumAnimated(g2); // Анимационное рисование кривой
        } finally {
            g2.dispose();
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
        final long frameNs = 25_000_000L;
        int prevPx = Integer.MIN_VALUE;
        int prevPy = Integer.MIN_VALUE;

        while ((tStart < tEnd && t <= tEnd) || (tStart > tEnd && t >= tEnd)) {
            double dt;
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

                int px = (int) Math.round(originX + x * scale);
                int py = (int) Math.round(originY - y * scale);

                synchronized (canvas) {
                    g.setColor(color);
                    if (prevPx != Integer.MIN_VALUE) {
                        g.drawLine(prevPx, prevPy, px, py);
                    } else {
                        g.drawLine(px, py, px, py);
                    }
                }

                prevPx = px;
                prevPy = py;

                step++;
                long now = System.nanoTime();
                if (now - lastRepaint >= frameNs) {
                    canvas.repaint();
                    lastRepaint = now;
                }
            }

            try { Thread.sleep(1); } catch (InterruptedException ignored) {}
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
            g2.fillRect(0, 0, width, height);
        } finally {
            g2.dispose();
        }
    }

    public Graphics2D getBufferGraphics() {
        return buffer.createGraphics();
    }

    @Override
    public void paint(Graphics g) {
        g.drawImage(buffer, 0, 0, null);
    }

    @Override
    public void update(Graphics g) {
        paint(g);
    }
}

// Главный класс Main – создаёт три окна и запускает кривые
public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            double scale = 60.0;

            // Создание трёх кривых в отдельных окнах с разными позициями
            new Picture(0.5, scale, Color.RED,
                    "Descartes Folium - 1", 600, 600, 100, 80, 0, 0).start();
            new Picture(1.0, scale, Color.GREEN,
                    "Descartes Folium - 2", 600, 600, 760, 120, 0, 0).start();
            new Picture(2.0, scale, Color.BLUE,
                    "Descartes Folium - 3", 600, 600, 1420, 160, 0, 0).start();
        });
    }
}