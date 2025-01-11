SELECT 'Кол-во супов =', SUM(Выход), COUNT(Выход)
    FROM Блюда  
    WHERE В = 'С';