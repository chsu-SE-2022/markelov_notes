#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices.h"
using namespace std;

class Site;

class Wired : public DataDevices {   //базовый класс-интерфейс
public:
	void openSite(Site& site);  //функция, взаимодействующая с объектом класса Site
};