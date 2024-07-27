#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices.h"
using namespace std;

enum cable { Twisted, Coaxial, Optical, other };

class Wired : public DataDevices {   
protected:
	cable cord;
	int length_cable;
public:
	string getCord() {   //геттер для кабеля
		switch (cord) {
		case Twisted: return "Витая пара";
		case Coaxial: return "Коаксиальный кабель";
		case Optical: return "Оптоволокно";
		case other: return "Другой тип кабеля";
		default: return "N/A";
		}
	}
};