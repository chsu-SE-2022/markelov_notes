#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wired.h"
using namespace std;
using namespace System;

class Hub : public Wired {
private:
	int ports;

public:
	Hub(string valueName, cable valueCord, int valueSpeed, int valueLength, int valuePorts) {
		this->name = valueName;                      //конструктор со всеми параметрами
		this->speed = valueSpeed;
		this->cord = valueCord;
		this->length_cable = valueLength;
		this->ports = valuePorts;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Hub() {
		this->name = "Неизвестный хаб";                      //конструктор по умолчанию
		this->speed = 0;
		this->cord = other;
		this->length_cable = 0;
		this->ports = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Hub(const Hub& obj) {
		this->name = obj.name;                      //копирующий конструктор
		this->speed = obj.speed;
		this->cord = obj.cord;
		this->length_cable = obj.length_cable;
		this->ports = obj.ports;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	String^ getInfo() {      //вывод информации о сети
		String^ info;
		info += "Вы успешно подключились к хабу " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "Информация о сети\n";
		info += "Скорость: " + speed + " Мбит/с\n";
		info += "Тип подключения: " + msclr::interop::marshal_as<String^>(getCord()) + "\n";
		info += "Длина кабеля: " + length_cable + " м\n";
		info += "Количество портов: " + ports + "\n";
		info += "Cеть работает: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "Передано данных: " + traffic + " Мб\n";
		info += "Время соединения: " + time + " сек\n";
		ofstream result;
		result.open("Hub.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~Hub() {   //деструктор

	}
};
