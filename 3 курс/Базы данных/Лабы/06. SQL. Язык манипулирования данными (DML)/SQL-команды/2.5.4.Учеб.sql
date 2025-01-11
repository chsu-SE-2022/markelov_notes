SELECT ПР
    FROM Поставки
    GROUP BY ПР
    HAVING COUNT(*) > 2;