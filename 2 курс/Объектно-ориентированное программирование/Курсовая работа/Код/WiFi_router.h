#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wireless.h"
using namespace std;
using namespace System;

enum security { WEP, WPA, WPA2, WPA3, NoProtection };

class WiFi_router : public Wireless {
private:
	string password;
	security protection;

public:

	WiFi_router(string valueName, string valuePassword, security valueProtection, int valueSpeed, int valueRadius, double valueFrequency) {
		this->name = valueName;                      //конструктор со всеми параметрами
		this->password = valuePassword;
		this->protection = valueProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router() {
		this->name = "Неопределенная сеть";                      //конструктор по умолчанию
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(string valueName) {
		this->name = valueName;                      //конструктор с 1 параметром
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(double valueFrequency, string valueName) {
		this->name = valueName;                      //конструктор с 2 параметрами
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(int valueSpeed, int valueRadius, string valueName) {
		this->name = valueName;                      //конструктор с 3 параметрами
		this->password = "0";
		this->protection = NoProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(const WiFi_router& obj) {
		this->name = obj.name;                      //копирующий конструктор
		this->password = obj.password;
		this->protection = obj.protection;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getPassword() {   //геттер для пароля
		return password;
	}

	string getProtection() {   //геттер для протокола безопасности
		switch (protection) {
		case WEP: return "WEP";
			break;
		case WPA: return "WPA";
			break;
		case WPA2: return "WPA2";
			break;
		case WPA3: return "WPA3";
			break;
		case NoProtection: return "Без защиты";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //вывод информации о сети
		String^ info;
		info += "Вы успешно подключились к WiFi-сети " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "Информация о сети\n";
		info += "Скорость: " + speed + " Мбит/с\n";
		info += "Частота: " + frequency + " ГГц\n";
		info += "Радиус покрытия: " + radius + " м\n";
		info += "Протокол безопасности: " + msclr::interop::marshal_as<String^>(getProtection()) + "\n";
		info += "Cеть работает: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "Передано данных: " + traffic + " Мб\n";
		info += "Время соединения: " + time + " сек\n";
		ofstream result;
		result.open("WiFi.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~WiFi_router() {  //деструктор

	}
};