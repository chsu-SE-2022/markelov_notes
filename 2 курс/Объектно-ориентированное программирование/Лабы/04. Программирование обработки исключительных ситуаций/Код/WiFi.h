#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Wireless.h"
using namespace std;

enum security { WEP, WPA, WPA2, WPA3, NoProtection };

class WiFi_router : public Wireless {
private:
	string password;
	security protection;

public:

	bool operator > (const WiFi_router& other) {
		return this->speed > other.speed;
	}

	bool operator < (const WiFi_router& other) {
		return this->speed < other.speed;
	}

	bool operator == (const WiFi_router& other) {
		return this->speed == other.speed;
	}

	int operator + (const WiFi_router& other) {
		return this->traffic + other.traffic;
	}

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
		this->traffic = 0;
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
		case WPA: return "WPA";
		case WPA2: return "WPA2";
		case WPA3: return "WPA3";
		case NoProtection: return "Без защиты";
		default: return "N/A";
		}
	}

	friend ostream& operator<<(ostream& info, WiFi_router& other) {      //вывод информации о сети
		info << "Вы успешно подключились к WiFi-сети " << other.name << endl << endl;
		info << "Информация о сети" << endl;
		info << "Скорость: " << other.speed << " Мбит/с" << endl;
		info << "Частота: " << other.frequency << " ГГц" << endl;
		info << "Радиус покрытия: " << other.radius << " м" << endl;
		info << "Протокол безопасности: " << other.getProtection() << endl;
		info << "Cеть работает: " << other.work << endl;
		info << "Передано данных: " << other.traffic << " Мб" << endl;
		info << "Время соединения: " << other.time << " сек" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~WiFi_router() {  //деструктор

	}
};