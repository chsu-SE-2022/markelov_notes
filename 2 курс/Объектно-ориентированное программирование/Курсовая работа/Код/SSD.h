#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Storage.h"
using namespace std;
using namespace System;

enum connect_type2 { _SATA, NVMe, _M2, _U2, _PCIe, _other_type };

class SSD : public Storage {
private:
	connect_type2 connector;

public:
	SSD(string valueName, int valueCapacity, connect_type2 valueConnector, int valueSpeed) {
		this->name = valueName;
		this->speed = valueSpeed;
		this->capacity = valueCapacity;
		this->connector = valueConnector;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	SSD() {
		this->name = "Неопознанный SSD-диск";
		this->speed = 0;
		this->capacity = 0;
		this->connector = _other_type;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	SSD(const SSD& obj) {
		this->name = obj.name;
		this->speed = obj.speed;
		this->capacity = obj.capacity;
		this->connector = obj.connector;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getType() {   //геттер для разъема
		switch (connector) {
		case _SATA: return "SATA";
			break;
		case NVMe: return "NVMe";
			break;
		case _M2: return "M2";
			break;
		case _U2: return "U2";
			break;
		case _PCIe: return "PCIe";
			break;
		case _other_type: return "Другой разъем";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //вывод информации о сети
		String^ info;
		info += "Подключен SSD-диск " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "Информация об устройстве\n";
		info += "Скорость: " + speed + " Мб/с\n";
		info += "Объем диска: " + capacity + " Гб\n";
		info += "Разъем: " + msclr::interop::marshal_as<String^>(getType()) + "\n";
		info += "Передано данных: " + traffic + " Мб\n";
		info += "Время соединения: " + time + " сек\n";
		ofstream result;
		result.open("SSD.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~SSD() {               //деструктор

	}
};