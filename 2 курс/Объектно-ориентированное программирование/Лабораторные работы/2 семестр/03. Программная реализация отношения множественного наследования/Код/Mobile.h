#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "WiFi.h"
using namespace std;

enum generation { GPRS, Edge, _2G, _3G, _4G, _5G, unknown };

class Mobile : public WiFi {
protected: 
	generation type;
	int signal;

public:
	Mobile(string valueName, generation valueType, int valueSpeed, int valueRadius, double valueFrequency) {
		this->name = valueName;                      //конструктор со всеми параметрами
		this->type = valueType;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile() {
		this->name = "Неопределенный оператор";                      //конструктор по умолчанию
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile(string valueName) {
		this->name = valueName;                      //конструктор с 1 параметром
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile(string valueName, generation valueType) {
		this->name = valueName;                      //конструктор с 2 параметрами
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile(string valueName, generation valueType, int valueSpeed) {
		this->name = valueName;                      //конструктор с 3 параметрами
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile(const Mobile& obj) {
		this->name = obj.name;                      //конструктор с 3 параметрами
		this->type = obj.type;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	string getType() {   //геттер для поколения сети
		switch (type) {
		case GPRS: return "GPRS";
		case Edge: return "Edge";
		case _2G: return "2G";
		case _3G: return "3G";
		case _4G: return "4G";
		case _5G: return "5G";
		case unknown: return "unknown";
		default: return "N/A";
		}
	}

	friend ostream& operator<<(ostream& info, Mobile& other) {      //вывод информации о сети
		info << "Вы успешно подключились к мобильной сети " << other.name << endl << endl;
		info << "Информация о сети" << endl;
		info << "Скорость: " << other.speed << " Мбит/с" << endl;
		info << "Уровень сигнала: " << other.signal << endl;
		info << "Частота: " << other.frequency << " ГГц" << endl;
		info << "Радиус покрытия: " << other.radius << " м" << endl;
		info << "Поколение сети: " << other.getType() << endl;
		info << "Cеть работает: " << other.work << endl;
		info << "Передано данных: " << other.traffic << " Мб" << endl;
		info << "Время соединения: " << other.time << " сек" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Mobile() {  //деструктор

	}

};