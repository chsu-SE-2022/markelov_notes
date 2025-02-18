using BarcodeLibrary;
using DataDevice;
using Showcase;
using System;
using System.Collections.Generic;

Barcode barcode = new("");

List<Showcase<IDataDevice>> showcases = new List<Showcase<IDataDevice>>(); // Список витрин

// Изначально создаём две витрины
Showcase<IDataDevice> showcase1 = 10; // Первая витрина
Showcase<IDataDevice> showcase2 = 10;  // Вторая витрина
showcases.Add(showcase1);
showcases.Add(showcase2);

var router1 = new WiFi(1000, "TP-Link", 100.0, 5.0, true);
var router2 = new DemoWiFi(1001, "Huawei", 200.0, 7.0, true);
WiFi router3 = new WiFi(1002, "Xiaomi", 150.0, 3.0, true);
DemoWiFi router4 = new DemoWiFi(1003, "Mercusys", 175.0, 5.0, true);
DataDevice.DataDevice router5 = new WiFi(1004, "Keenetic", 120.0, 6.0, true);

showcase1.AddDevice(router1);
showcase2.AddDevice(router2);
showcase1.AddDevice(router3, 5);
showcase2.AddDevice(router4);
showcase1.AddDevice(router5);

Terminal terminal = new Terminal(showcases);
terminal.Start();

/*
Showcase<IDataDevice> showcase11 = 10; // Инициализация витрин
Showcase<DemoWiFi> showcase22 = 5;
IShowcase<IDataDevice> showcase1 = showcase11;
IShowcase<DemoWiFi> showcase2 = showcase22;


// Изменения номера витрины и идентификатора
showcase11.Id = 42;
router1.Id = 42;

//Console.WriteLine(showcase1.ToString());

/// <summary>
/// Перемещение товара из одной витрины в другую
/// </summary>
showcase1.MoveDevice(router2, showcase2);
showcase1.MoveDevice(router2, showcase2);
//Console.WriteLine(showcase1.ToString());
//Console.WriteLine(showcase2.ToString());
showcase2.MoveDevice(router2, showcase1);
Console.WriteLine(showcase1.ToString());
Console.WriteLine(showcase2.ToString());
Console.WriteLine(showcase11.ToString());
Console.WriteLine(showcase22.ToString());

/// <summary>
/// Применение сортировки по ID и имени
/// </summary>

// Сортировка по ID
showcase1.SortById();
Console.WriteLine("После сортировки по ID:");
Console.WriteLine(showcase1.ToString());

// Сортировка по имени
showcase1.SortByName();
Console.WriteLine("После сортировки по имени:");
Console.WriteLine(showcase1.ToString());

/// <summary>
/// Применение поиска
/// </summary>
// Поиск товара по ID
int indexById = showcase1.FindById(1002);
if (indexById != -1) Console.WriteLine($"Товар с ID 1002 найден в ячейке: {indexById}");
else Console.WriteLine("Товар с ID 1002 не найден.");

// Поиск товара по имени
int indexByName = showcase1.FindByName("Mercusys");
if (indexByName != -1) Console.WriteLine($"Товар с именем 'Mercusys' найден в ячейке: {indexByName}");
else Console.WriteLine("Товар с именем 'Mercusys' не найден.");
*/