import java.sql.*;

public class Main {
    public static void main(String[] args) {
        String url = "jdbc:ucanaccess://sales.accdb";

        try (Connection conn = DriverManager.getConnection(url);
             Statement stmt = conn.createStatement()) {

            String query = """
                    SELECT
                        SUM(CASE WHEN T.[Отдел] = 'Молоко' THEN D.[Количество упаковок] * D.[Цена] ELSE 0 END)
                        * 100.0 / SUM(D.[Количество упаковок] * D.[Цена]) AS Доля
                    FROM [Движение товаров] AS D
                    INNER JOIN [Магазин] AS M ON D.[ID магазина] = M.[ID магазина]
                    INNER JOIN [Товар] AS T ON D.[Артикул] = T.[Артикул]
                    WHERE M.[Район] = 'Октябрьский'
                      AND D.[Тип операции] = 'Продажа';
                    """;

            ResultSet rs = stmt.executeQuery(query);

            if (rs.next()) {
                double percent = rs.getDouble("Доля");
                System.out.printf("Доля продаж отдела 'Молоко': %.1f%%\n", percent);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
