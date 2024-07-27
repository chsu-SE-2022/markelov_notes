#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wired.h"
using namespace std;
using namespace System;

enum line { Dial_Up, ADSL, Ethernet, NoConnect };

class Modem : public Wired {
private:
	line connect;

public:
	Modem(string valueName, cable valueCord, int valueSpeed, int valueLength, line valueConnect) {
		this->name = valueName;                      //конструктор со всеми параметрами
		this->speed = valueSpeed;
		this->cord = valueCord;
		this->connect = valueConnect;
		this->length_cable = valueLength;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Modem() {
		this->name = "Неизвестный роутер";                      //конструктор по умолчанию
		this->speed = 0;
		this->cord = other;
		this->connect = NoConnect;
		this->length_cable = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Modem(const Modem& obj) {
		this->name = obj.name;                      //копирующий конструктор
		this->speed = obj.speed;
		this->cord = obj.cord;
		this->connect = obj.connect;
		this->length_cable = obj.length_cable;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getLine() {   //геттер для типа линии
		switch (connect) {
		case Dial_Up: return "Dial Up";
			break;
		case ADSL: return "ADSL";
			break;
		case Ethernet: return "Ethernet";
			break;
		case NoConnect: return "Другой тип линии";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //вывод информации о сети
		String^ info;
		info += "Вы успешно подключились к модему " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "Информация о сети\n";
		info += "Скорость: " + speed + " Мбит/с\n";
		info += "Тип подключения: " + msclr::interop::marshal_as<String^>(getCord()) + "\n";
		info += "Тип линии: " + msclr::interop::marshal_as<String^>(getLine()) + "\n";
		info += "Длина кабеля: " + length_cable + " м\n";
		info += "Cеть работает: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "Передано данных: " + traffic + " Мб\n";
		info += "Время соединения: " + time + " сек\n";
		ofstream result;
		result.open("Modem.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~Modem() {   //деструктор

	}
};