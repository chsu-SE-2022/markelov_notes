SELECT ПР, SUM(К_во)
    FROM Поставки
    WHERE ПС <> 2
    GROUP BY ПР;