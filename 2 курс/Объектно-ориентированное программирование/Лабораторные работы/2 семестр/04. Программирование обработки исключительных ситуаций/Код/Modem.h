#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Mobile.h"
#include "Flash.h"
using namespace std;

class Modem : public Mobile_antenna, public Flash {
private: 
	bool antenna, sd;

public:
	Modem(string valueName, generation valueType, int valueSpeed, int valueRadius, double valueFrequency, double valueVersion, char valueConnector, bool valueAntenna, bool valueSd) {
		this->Wireless::name = valueName;                      //конструктор со всеми параметрами
		this->type = valueType;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = valueVersion;
		this->connector = valueConnector;
		this->antenna = valueAntenna;
		this->sd = valueSd;
	}

	Modem() {
		this->Wireless::name = "Неопознанное USB-устройство";                      //конструктор по умолчанию
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = 'N';
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(string valueName) {
		this->Wireless::name = valueName;                      //конструктор c 1 параметром
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = 'N';
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(string valueName, generation valueType) {
		this->Wireless::name = valueName;                      //конструктор c 2 параметрами
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = 'N';
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(string valueName, generation valueType, char valueConnector) {
		this->Wireless::name = valueName;                      //конструктор c 3 параметрами
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = valueConnector;
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(const Modem& obj) {
		this->Wireless::name = obj.Wireless::name;                      //копирующий конструктор
		this->type = obj.type;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = obj.traffic;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = obj.version;
		this->connector = obj.connector;
		this->antenna = obj.antenna;
		this->sd = obj.sd;
	}

	string getAntenna() {
		if (antenna) return "Есть";
		else return "Нет";
	}

	string getSd() {
		if (sd) return "Есть";
		else return "Нет";
	}

	friend ostream& operator<<(ostream& info, Modem& other) {      //вывод информации о сети
		info << "Вы успешно подключились к модему " << other.Wireless::name << endl << endl;
		info << "Информация о сети" << endl;
		info << "Скорость: " << other.speed << " Мбит/с" << endl;
		info << "Уровень сигнала: " << other.signal << endl;
		info << "Частота: " << other.frequency << " ГГц" << endl;
		info << "Радиус покрытия: " << other.radius << " м" << endl;
		info << "Поколение сети: " << other.getType() << endl;
		info << "Cеть работает: " << other.work << endl;
		info << "Версия USB: " << other.version << endl;
		info << "Разъем: " << "Type-" << other.connector << endl;
		info << "Наличие антенны: " << other.getAntenna() << endl;
		info << "Наличие разъема для SD-карты: " << other.getSd() << endl;
		info << "Передано данных: " << other.traffic << " Мб" << endl;
		info << "Время соединения: " << other.time << " сек" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Modem() {            //деструктор

	}
};
