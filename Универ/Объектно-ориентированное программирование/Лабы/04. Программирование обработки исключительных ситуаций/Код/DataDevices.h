#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Site;

class DataDevices {   //������� �����-���������
protected:
	string name;
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

	virtual void openSite(Site& site) = 0;  //�������, ����������������� � �������� ������ Site

	template<class T>
	T sum(T a, T b) {
		return a + b;
	}
};