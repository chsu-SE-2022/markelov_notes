using BarcodeLibrary;
using DataDevice;
using Showcase;
using System;

Barcode barcode = new("");

var router1 = new WiFi(1000, "TP-Link", 100.0, 5.0, true);
var router2 = new DemoWiFi(1001, "Huawei", 200.0, 7.0, true);
WiFi router3 = new WiFi(1002, "Xiaomi", 150.0, 3.0, true);
DemoWiFi router4 = new DemoWiFi(1003, "Mercusys", 175.0, 5.0, true);
DataDevice.DataDevice router5 = new WiFi(1004, "Keenetic", 120.0, 6.0, true);

Showcase<IDataDevice> showcase11 = 10; // Инициализация витрин
Showcase<DemoWiFi> showcase22 = 5;
IShowcase<IDataDevice> showcase1 = showcase11;
IShowcase<DemoWiFi> showcase2 = showcase22;

/// <summary>
/// Добавление в первую витрину
/// </summary>
showcase1.AddDevice(router1);
showcase1.AddDevice(router2);
showcase1.AddDevice(router3, 5);
showcase1.AddDevice(router4);
showcase1.AddDevice(router5);

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