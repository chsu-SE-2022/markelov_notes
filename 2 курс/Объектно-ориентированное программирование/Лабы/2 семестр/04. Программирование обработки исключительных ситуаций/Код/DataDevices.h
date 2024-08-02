#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Site;

class DataDevices {   //базовый класс-интерфейс
protected:
	string name;
	static string work;
	int speed, traffic;
	double time;

public:
	string getName() {  //геттер для имени
		return name;
	}
	int getTraffic() {  //геттер для траффика
		return traffic;
	}

	double getTime() {  //геттер для времени
		return time;
	}

	int getSpeed() {    //геттер для скорости
		return speed;
	}

	virtual void openSite(Site& site) = 0;  //функция, взаимодействующая с объектом класса Site

	template<class T>
	T sum(T a, T b) {
		return a + b;
	}
};