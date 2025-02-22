SELECT Продукт, Цена, Название, Статус
    FROM Продукты, Состав, Блюда, Поставки, Поставщики
    WHERE Продукты.ПР = Состав.ПР
    AND Состав.БЛ = Блюда.БЛ
    AND Поставки.ПР = Состав.ПР
    AND Поставки.ПС = Поставщики.ПС
    AND Блюдо = 'Сырники'
    AND Цена = (
        SELECT MIN(Цена) 
        FROM Поставки X 
        WHERE X.ПР = Поставки.ПР
    );