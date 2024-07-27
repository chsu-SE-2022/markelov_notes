#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices_i.h"
using namespace std;

class DataDevices : public DataDevices_i {
protected:
	string name, data;
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

	void setData(string value) {   //cеттер для передачи данных
		this->data = value;
	}
};