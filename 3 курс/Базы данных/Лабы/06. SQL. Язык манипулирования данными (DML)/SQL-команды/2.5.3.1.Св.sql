SELECT ПР, SUM(Цена)
    FROM Поставки
    GROUP BY ПР;