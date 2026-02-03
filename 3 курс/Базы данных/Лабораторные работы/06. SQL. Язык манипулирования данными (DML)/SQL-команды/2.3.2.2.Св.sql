SELECT ПР, К_во, Стоим
    FROM Наличие
    WHERE К_во NOT BETWEEN 50 AND 100 AND Стоим < 100;