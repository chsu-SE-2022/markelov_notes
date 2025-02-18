using DataDevice;
using Showcase;
using System;
using System.Collections.Generic;

public class Terminal
{
    private List<Showcase<IDataDevice>> showcases;
    public Terminal(List<Showcase<IDataDevice>> showcases)
    {
        this.showcases = showcases;
    }
    public void Start()
    {
        while (true)
        {
            Console.Clear();
            Console.WriteLine("=== Меню управления ===");
            Console.WriteLine("1. Выставить товар на витрину");
            Console.WriteLine("2. Снять товар с витрины");
            Console.WriteLine("3. Вывести витрину");
            Console.WriteLine("4. Переставить товары местами");
            Console.WriteLine("5. Заменить товар");
            Console.WriteLine("6. Переместить товар между витринами");
            Console.WriteLine("7. Отсортировать товары по ID");
            Console.WriteLine("8. Отсортировать товары по имени");
            Console.WriteLine("9. Найти товар по ID");
            Console.WriteLine("10. Найти товар по имени");
            Console.WriteLine("11. Создать новую витрину");
            Console.WriteLine("12. Очистить витрину");
            Console.WriteLine("0. Выход");

            int command = ReadNumber("\nВведите номер команды: ");
            HandleCommand(command);
        }
    }

    private void HandleCommand(int command)
    {
        switch (command)
        {
            case 1:
                AddDevice();
                break;
            case 2:
                RemoveDevice();
                break;
            case 3:
                PrintShowcase();
                break;
            case 4:
                SwapDevices();
                break;
            case 5:
                ReplaceDevice();
                break;
            case 6:
                MoveDevice();
                break;
            case 7:
                SortById();
                break;
            case 8:
                SortByName();
                break;
            case 9:
                SearchById();
                break;
            case 10:
                SearchByName();
                break;
            case 11:
                CreateShowcase();
                break;
            case 12:
                ClearShowcase();
                break;
            case 0:
                Console.WriteLine("Завершение программы...");
                Environment.Exit(0);
                break;
            default:
                Console.WriteLine("Неверная команда. Попробуйте снова");
                Console.ReadKey();
                break;
        }
    }

    private int ReadNumber(string prompt, int min = int.MinValue, int max = int.MaxValue)
    {
        int value;
        Console.WriteLine(prompt);
        while (!int.TryParse(Console.ReadLine(), out value) || value < min || value > max)
        {
            Console.WriteLine($"Ошибка! Введите корректное число");
            Console.WriteLine(prompt);
        }
        return value;
    }
    private Showcase<IDataDevice> GetShowcase(string prompt)
    {
        int showcaseNumber = ReadNumber(prompt, 1, showcases.Count);
        return showcases[showcaseNumber - 1];
    }

    private void CreateShowcase()
    {
        int maxSize = ReadNumber("Введите максимальное количество товаров для новой витрины: ", 1);
        Showcase<IDataDevice> newShowcase = maxSize;
        showcases.Add(newShowcase);
        Console.WriteLine("Новая витрина успешно создана!");
    }

    private Showcase<IDataDevice> SelectShowcase(int showcaseNumber)
    {
        if (showcaseNumber > 0 && showcaseNumber <= showcases.Count)
        {
            return showcases[showcaseNumber - 1];
        }
        else
        {
            Console.WriteLine("Неверный номер витрины");
            return null;
        }
    }

    private void AddDevice()
    {
        Console.Clear();
        Console.WriteLine("=== Выставить товар ===");

        int id = ReadNumber("Введите ID товара: ");
        Console.Write("Введите имя товара: ");
        string name = Console.ReadLine();

        var showcase = GetShowcase("Введите номер витрины: ");
        int index = ReadNumber("Введите индекс (или -1 для первой свободной ячейки): ", -1);

        Random random = new Random();

        var newDevice = new WiFi(id, name, Math.Round(random.Next(50, 300) + random.NextDouble(), 2), Math.Round(random.Next(3, 10) + random.NextDouble(), 1), true);

        if (index == -1)
        {
            showcase.AddDevice(newDevice);
            Console.WriteLine("Товар успешно добавлен!");
        }
        else if (showcase[index] == null)
        {
            showcase.AddDevice(newDevice, index);
            Console.WriteLine("Товар успешно добавлен!");
        }
        else Console.WriteLine("Эта ячейка занята!");
        

        Console.ReadKey();
    }

    private void RemoveDevice()
    {
        Console.Clear();
        Console.WriteLine("=== Снять товар ===");

        var showcase = GetShowcase("Введите номер витрины: ");
        int index = ReadNumber("Введите индекс (или -1 для снятия первого товара): ", -1);

        if (index == -1)
        {
            showcase.RemoveDevice();
            Console.WriteLine("Первый товар успешно снят!");
        }
        else if (showcase[index] == null)
            Console.WriteLine($"Ячейка {index} пуста или выходит за пределы витрины");
        else
        {
            showcase.RemoveDevice(index);
            Console.WriteLine($"Товар из ячейки {index} успешно снят!");
        }

        Console.ReadKey();
    }

    private void PrintShowcase()
    {
        Console.Clear();
        Console.WriteLine("=== Содержимое витрины ===");

        int showcaseNumber = ReadNumber("Введите номер витрины для вывода (или -1 для вывода всех витрин): ");
        if (showcaseNumber == -1)
        {
            foreach (var showcase in showcases) Console.WriteLine(showcase.ToString());
        }
        else if (showcaseNumber >= 1 && showcaseNumber <= showcases.Count)
            Console.WriteLine(showcases[showcaseNumber - 1].ToString());
        else Console.WriteLine("Неверный номер витрины");
        Console.ReadKey();
    }

    private void SwapDevices()
    {
        Console.Clear();
        Console.WriteLine("=== Переставить товары местами ===");

        int showcaseNumber = ReadNumber("Введите номер витрины: ", 1, showcases.Count);
        var showcase = showcases[showcaseNumber - 1];

        int index1 = ReadNumber("Введите индекс первого товара: ");
        int index2 = ReadNumber("Введите индекс второго товара: ");

        if (showcase != null)
        {
            if (showcase[index1] == null || showcase[index2] == null)
                Console.WriteLine("Один из индексов выходит за пределы витрины, либо ячейка пуста");
            else
            {
                showcase.SwapDevices(index1, index2);
                Console.WriteLine("Товары успешно переставлены!");
            }
        }
        Console.ReadKey();
    }

    private void ReplaceDevice()
    {
        Console.Clear();
        Console.WriteLine("=== Заменить товар ===");

        int showcaseNumber;
        var showcase = GetShowcase("Введите номер витрины: ");

        int index = ReadNumber("Введите индекс заменяемого товара: ");

        if (showcase != null)
        {
            if (showcase[index] == null)
                Console.WriteLine("Индекс выходит за пределы витрины, либо ячейка пуста");
            else
            {
                Console.Write("Введите ID нового товара: ");
                int id = int.Parse(Console.ReadLine());

                Console.Write("Введите имя нового товара: ");
                string name = Console.ReadLine();

                Random random = new Random();
                var newDevice = new WiFi(id, name, Math.Round(random.Next(50, 300) + random.NextDouble(), 2), Math.Round(random.Next(3, 10) + random.NextDouble(), 1), true);

                showcase.ReplaceDevice(index, newDevice);
                Console.WriteLine("Товар успешно заменён.");
            }
        }

        Console.ReadKey();
    }

    private void MoveDevice()
    {
        Console.Clear();
        Console.WriteLine("=== Переместить товар ===");

        int sourceShowcaseNumber = ReadNumber("Введите номер витрины для перемещения товара: ", 1, showcases.Count);
        var sourceShowcase = showcases[sourceShowcaseNumber - 1];

        int sourceIndex = ReadNumber("Введите номер ячейки товара для перемещения: ");
        if (sourceShowcase[sourceIndex] == null)
        {
            Console.WriteLine("Товар в указанной ячейке не найден");
            Console.ReadKey();
            return;
        }

        int targetShowcaseNumber = ReadNumber("Введите номер целевой витрины: ", 1, showcases.Count);
        var targetShowcase = showcases[targetShowcaseNumber - 1];

        int targetIndex = ReadNumber("Введите номер ячейки для перемещения товара: ");
        if (targetShowcase[targetIndex] != null)
        {
            Console.WriteLine("Целевая ячейка уже занята");
            Console.ReadKey();
            return;
        }

        // Перемещаем товар
        targetShowcase.AddDevice(sourceShowcase[sourceIndex], targetIndex);
        sourceShowcase.RemoveDevice(sourceIndex);

        Console.WriteLine("Товар успешно перемещён!");
        Console.ReadKey();
    }

    private void SearchById()
    {
        int id;
        Console.Write("Введите ID товара: ");
        while (!int.TryParse(Console.ReadLine(), out id))
        {
            Console.WriteLine("Ошибка! Введите корректный ID товара.");
            Console.Write("Введите ID товара: ");
        }

        bool found = false;
        foreach (var showcase in showcases)
        {
            int index = showcase.FindById(id);
            if (index != -1)
            {
                Console.WriteLine($"Товар с ID {id} найден на витрине с номером {showcases.IndexOf(showcase) + 1} на позиции {index}");
                found = true;
            }
        }

        if (!found)
        {
            Console.WriteLine($"Товар с ID {id} не найден");
        }

        Console.ReadKey();
    }

    private void SearchByName()
    {
        Console.Write("Введите имя товара: ");
        string name = Console.ReadLine();

        bool found = false;
        foreach (var showcase in showcases)
        {
            int index = showcase.FindByName(name);
            if (index != -1)
            {
                Console.WriteLine($"Товар с именем '{name}' найден на витрине с номером {showcases.IndexOf(showcase) + 1} на позиции {index}");
                found = true;
            }
        }

        if (!found)
        {
            Console.WriteLine($"Товар с именем '{name}' не найден");
        }

        Console.ReadKey();
    }

    private void SortById()
    {
        foreach (var showcase in showcases)
        {
            showcase.SortById();
        }
        Console.WriteLine("Товары отсортированы по ID");
        Console.ReadKey();
    }

    private void SortByName()
    {
        foreach (var showcase in showcases)
        {
            showcase.SortByName();
        }
        Console.WriteLine("Товары отсортированы по имени");
        Console.ReadKey();
    }

    private void ClearShowcase()
    {
        Console.Clear();
        Console.WriteLine("=== Очистка витрины ===");

        Console.Write("Введите номер витрины: ");
        if (!int.TryParse(Console.ReadLine(), out int showcaseNumber) || showcaseNumber <= 0 || showcaseNumber > showcases.Count)
        {
            Console.WriteLine("Ошибка! Введите корректный номер витрины.");
            Console.ReadKey();
            return;
        }

        var showcase = showcases[showcaseNumber - 1];
        showcase.Clear();

        Console.WriteLine($"Витрина №{showcaseNumber} успешно очищена.");
        Console.ReadKey();
    }
}
