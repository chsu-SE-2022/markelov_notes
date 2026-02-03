SELECT БЛ
    FROM Состав
    GROUP BY БЛ
    HAVING COUNT(*) >= 3;