SELECT ПР, SUM(К_во)
    FROM Поставки
    GROUP BY ПР
    ORDER BY ПР;