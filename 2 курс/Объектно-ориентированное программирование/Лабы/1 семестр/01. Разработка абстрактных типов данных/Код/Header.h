#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum security { WEP, WPA, WPA2, WPA3, NoProtection };

class WiFi {
private:
	string login;
	string password;
	static string work;
	security protection;
	int speed, radius;
	double frequency;

public:

	WiFi(string valueLogin, string valuePassword, security valueProtection, int valueSpeed, int valueRadius, double valueFrequency) {
		this->login = valueLogin;                      //конструктор
		this->password = valuePassword;
		this->protection = valueProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->work = "Да";
	}

	WiFi() {
		this->login = "Неопределенная сеть";                      //конструктор
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->work = "Да";
	}

	WiFi(double valueFrequency, string valueLogin) {
		this->login = valueLogin;                      //конструктор
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = valueFrequency;
		this->work = "Да";
	}

	WiFi(int valueSpeed, string valueLogin) {
		this->login = valueLogin;                      //конструктор
		this->password = "0";
		this->protection = NoProtection;
		this->speed = valueSpeed;
		this->radius = 0;
		this->frequency = 0;
		this->work = "Да";
	}

	WiFi(const WiFi &obj) {
		this->login = obj.login;                      //конструктор
		this->password = obj.password;
		this->protection = obj.protection;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->work = "Да";
	}

	string getLogin() {  //геттер для логина
		return login;
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

	void networkInfo() {      //вывод информации о сети
		cout << "Вы успешно подключились к WiFi-сети " << login << endl << endl;
		cout << "Информация о сети" << endl;
		cout << "Скорость: " << speed << " Мбит/с" << endl;
		cout << "Частота: " << frequency << " ГГц" << endl;
		cout << "Радиус покрытия: " << radius << " м" << endl;
		cout << "Протокол безопасности: " << getProtection() << endl;
		cout << "Cеть работает: " << work << endl;
	}

	~WiFi() {  //деструктор

	}
};