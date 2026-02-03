SELECT ПР, SUM(Цена)
    FROM Поставки
    WHERE ПС <> 2
    GROUP BY ПР;