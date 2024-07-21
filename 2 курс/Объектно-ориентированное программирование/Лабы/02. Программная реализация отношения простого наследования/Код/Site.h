#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum protocol { http, https, NoProtocol };

class WiFi;

class Site {
private:
	string name, type, address;
	static string work;
	double time;
	protocol connect;

public:
	Site(string valueName, string valueType, string valueAddress, protocol valueConnect) {
		this->name = valueName;                      //конструктор со всеми параметрами
		this->type = valueType;
		this->address = valueAddress;
		this->connect = valueConnect;
		this->time = rand() / 1000.0;
	}

	Site() {
		this->name = "Неизвестный сайт";                      //конструктор по умолчанию
		this->type = "Неизвестный тип";
		this->address = "about:blank";
		this->connect = NoProtocol;
		this->time = rand() / 1000.0;
	}

	Site(string valueAddress) {
		this->name = "Неизвестный сайт";                      //конструктор c 1 параметром
		this->type = "Неизвестный тип";
		this->address = valueAddress;
		this->connect = NoProtocol;
		this->time = rand() / 1000.0;
	}

	Site(string valueAddress, protocol valueConnect) {
		this->name = "Неизвестный сайт";                      //конструктор c 2 параметрами
		this->type = "Неизвестный тип";
		this->address = valueAddress;
		this->connect = valueConnect;
		this->time = rand() / 1000.0;
	}

	Site(string valueName, string valueAddress, protocol valueConnect) {
		this->name = "Неизвестный сайт";                      //конструктор c 3 параметрами
		this->type = "Неизвестный тип";
		this->address = valueAddress;
		this->connect = valueConnect;
		this->time = rand() / 1000.0;
	}

	Site(const Site& obj) {
		this->name = obj.name;                      //копирующий конструктор
		this->type = obj.type;
		this->address = obj.address;
		this->connect = obj.connect;
		this->time = rand() / 1000.0;
	}

	string getName() {  //геттер для названия сайта
		return name;
	}

	string getWork() {  //геттер для статуса работы сайта
		return work;
	}

	double getTime() {  //геттер для времени загрузки сайта
		return time;
	}

	friend ostream& operator<<(ostream& info, Site& other) {
		switch (other.connect) {
		case NoProtocol: info << other.name << " - " << other.address << " (" << other.type << ")";
			break;
		case http: info << other.name << " - " << " http://" << other.address << " (" << other.type << ")";
			break;
		case https: info << other.name << " - " << " https://" << other.address << " (" << other.type << ")";
			break;
		}
		return info;
	}

	void status(WiFi& wifi);  //функция, взаимодействующая с объектом класса WiFi

	~Site() {  //деструктор

	}
};