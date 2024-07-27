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
	string getCord() {   //������ ��� ������
		switch (cord) {
		case Twisted: return "����� ����";
		case Coaxial: return "������������ ������";
		case Optical: return "�����������";
		case other: return "������ ��� ������";
		default: return "N/A";
		}
	}
};