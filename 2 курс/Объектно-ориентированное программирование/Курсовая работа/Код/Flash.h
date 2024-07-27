#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Storage.h"
using namespace std;
using namespace System;

class Flash : public Storage {
private:
	double version;
	char connector;

public:
	Flash(string valueName, int valueCapacity, double valueVersion, char valueConnector, int valueSpeed) {
		this->name = valueName;
		this->speed = valueSpeed;
		this->capacity = valueCapacity;
		this->version = valueVersion;
		this->connector = valueConnector;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Flash() {
		this->name = "Неопознанное USB-устройство";
		this->speed = 0;
		this->capacity = 0;
		this->version = 0.0;
		this->connector = 'N';
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Flash(string valueName) {
		this->name = valueName;
		this->speed = 0;
		this->capacity = 0;
		this->version = 0.0;
		this->connector = 'N';
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Flash(string valueName, int valueCapacity) {
		this->name = valueName;
		this->speed = 0;
		this->capacity = valueCapacity;
		this->version = 0.0;
		this->connector = 'N';
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Flash(const Flash& obj) {
		this->name = obj.name;
		this->speed = obj.speed;
		this->capacity = obj.capacity;
		this->version = obj.version;
		this->connector = obj.connector;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	String^ getInfo() {      //вывод информации о сети
		String^ info;
		info += "Подключено USB-устройство " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "Информация об устройстве\n";
		info += "Скорость: " + speed + " Мб/с\n";
		info += "Объем USB-накопителя: " + capacity + " Гб\n";
		info += "Версия USB: " + version + "\n";
		info += "Разъем: Type-" + connector + "\n";
		info += "Передано данных: " + traffic + " Мб\n";
		info += "Время соединения: " + time + " сек\n";
		ofstream result;
		result.open("Flash.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~Flash() {               //деструктор

	}
};