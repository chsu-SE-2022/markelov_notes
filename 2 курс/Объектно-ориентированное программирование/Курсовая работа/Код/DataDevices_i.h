#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
using namespace msclr::interop;

class DataDevices_i {
public:
	virtual string getName() = 0;   //геттер для имени
	virtual int getTraffic() = 0;   //геттер для траффика
	virtual double getTime() = 0;  //геттер для времени
	virtual int getSpeed() = 0;   //геттер для скорости
	virtual void setData(string value) = 0;   //сеттер для передачи данных

	virtual ~DataDevices_i() = default; // Виртуальный деструктор
};
