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
	string getName() {  //������ ��� �����
		return name;
	}
	int getTraffic() {  //������ ��� ��������
		return traffic;
	}

	double getTime() {  //������ ��� �������
		return time;
	}

	int getSpeed() {    //������ ��� ��������
		return speed;
	}

	void setData(string value) {   //c����� ��� �������� ������
		this->data = value;
	}
};