using BarcodeLibrary;
using DataDevices;
using Showcase;
using System;

Barcode barcode = new("");

var router1 = new WiFi(1000, "TP-Link", 100.0, 5.0, true);
var router2 = new WiFi(1001, "Huawei", 200.0, 7.0, true);
var router3 = new WiFi(1002, "Xiaomi", 150.0, 3.0, true);
var router4 = new WiFi(1003, "Mercusys", 175.0, 5.0, true);
var router5 = new WiFi(1004, "Keenetic", 120.0, 6.0, true);

Showcase.Showcase showcase = 10; // Инициализация витрины

/// <summary>
/// Добавление, удаление, перестановка, замена
/// </summary>
showcase.AddDevice(router1); // Добавляем на витрину роутер1 в первую свободную ячейку
// Console.WriteLine(showcase.ToString());
showcase.AddDevice(router2); // Добавляем на витрину роутер2 в первую свободную ячейку
// Console.WriteLine(showcase.ToString());
showcase.AddDevice(router3, 5); // Добавляем на витрину роутер3 в 5 ячейку
// Console.WriteLine(showcase.ToString());
showcase.RemoveDevice(1); // Убираем с витрины роутер на 1 ячейке
// Console.WriteLine(showcase.ToString());
showcase.RemoveDevice(); // Убираем с витрины роутер на первой занятой ячейке
// Console.WriteLine(showcase.ToString());
showcase.ReplaceDevice(5, router4); // Заменяем роутер в 5 ячейке на роутер4
// Console.WriteLine(showcase.ToString());
showcase.AddDevice(router5); // Добавляем на витрину роутер5 в первую свободную ячейку
// Console.WriteLine(showcase.ToString());
showcase.SwapDevices(0, 5); // Меняем местами роутеры в 0 и 5 ячейках
// Console.WriteLine(showcase.ToString());
showcase.Id = 5;

/// <summary>
/// Поиск
/// </summary>
showcase.AddDevice(router1);
// Console.WriteLine(showcase.ToString());
showcase.AddDevice(router2);
// Console.WriteLine(showcase.ToString());
showcase.AddDevice(router3);
Console.WriteLine(showcase.ToString());

int id;  string name;
id = 1001;
Console.WriteLine(showcase.FindById(id) != -1 ? $"Роутер с ID {id} находится на {showcase.FindById(id)} ячейке витрины" : $"Роутер с ID {id} не найден"); // Поиск по существующему ID
id = 1011;
Console.WriteLine(showcase.FindById(id) != -1 ? $"Роутер с ID {id} находится на {showcase.FindById(id)} ячейке витрины" : $"Роутер с ID {id} не найден"); // Поиск по несуществующему ID
name = "TP-Link";
Console.WriteLine(showcase.FindByName(name) != -1 ? $"Роутер {name} находится на {showcase.FindByName(name)} ячейке витрины" : $"Роутер {name} не найден"); // Поиск по существующему имени
name = "D-Link";
Console.WriteLine(showcase.FindByName(name) != -1 ? $"Роутер {name} находится на {showcase.FindByName(name)} ячейке витрины" : $"Роутер {name} не найден"); // Поиск по несуществующему имени

/// <summary>
/// Сортировка
/// </summary>
showcase.SortById();
// Console.WriteLine(showcase.ToString());
showcase.SortByName();
// Console.WriteLine(showcase.ToString());
