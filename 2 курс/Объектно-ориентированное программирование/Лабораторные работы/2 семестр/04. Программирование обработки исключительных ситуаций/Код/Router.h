#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices.h"
#include "Wired.h"
using namespace std;

enum cable { Twisted, Coaxial, Optical, other };

class Router : public Wired {
private:
	cable cord;
	int length_cable;
public:
	Router(string valueName, cable valueCord, int valueSpeed, int valueLength) {
		this->name = valueName;                      //конструктор со всеми параметрами
		this->speed = valueSpeed;
		this->cord = valueCord;
		this->length_cable = valueLength;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Router() {
		this->name = "Неизвестный роутер";                      //конструктор по умолчанию
		this->speed = 0;
		this->cord = other;
		this->length_cable = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Router(const Router& obj) {
		this->name = obj.name;                      //копирующий конструктор
		this->speed = obj.speed;
		this->cord = obj.cord;
		this->length_cable = obj.length_cable;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getCord() {   //геттер для протокола безопасности
		switch (cord) {
		case Twisted: return "Витая пара";
		case Coaxial: return "Коаксиальный кабель";
		case Optical: return "Оптоволокно";
		case other: return "Другой тип кабеля";
		default: return "N/A";
		}
	}

	friend ostream& operator<<(ostream& info, Router& other) {      //вывод информации о сети
		info << "Вы успешно подключились к роутеру " << other.name << endl << endl;
		info << "Информация о сети" << endl;
		info << "Скорость: " << other.speed << " Мбит/с" << endl;
		info << "Тип подключения: " << other.getCord() << endl;
		info << "Длина кабеля: " << other.length_cable << " м" << endl;
		info << "Cеть работает: " << other.work << endl;
		info << "Передано данных: " << other.traffic << " Мб" << endl;
		info << "Время соединения: " << other.time << " сек" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Router() {   //деструктор

	}
};