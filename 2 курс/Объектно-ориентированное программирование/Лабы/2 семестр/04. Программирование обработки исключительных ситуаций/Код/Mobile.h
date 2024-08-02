#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Wireless.h"
using namespace std;

enum generation { GPRS, Edge, _2G, _3G, _4G, _5G, unknown };

class Mobile_antenna : public Wireless {
protected: 
	generation type;
	int signal;

public:
	Mobile_antenna(string valueName, generation valueType, int valueSpeed, int valueRadius, double valueFrequency) {
		this->name = valueName;                      //����������� �� ����� �����������
		this->type = valueType;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna() {
		this->name = "�������������� ��������";                      //����������� �� ���������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(string valueName) {
		this->name = valueName;                      //����������� � 1 ����������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(string valueName, generation valueType) {
		this->name = valueName;                      //����������� � 2 �����������
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(string valueName, generation valueType, int valueSpeed) {
		this->name = valueName;                      //����������� � 3 �����������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(const Mobile_antenna& obj) {
		this->name = obj.name;                      //����������� � 3 �����������
		this->type = obj.type;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = rand() / 100.0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	string getType() {   //������ ��� ��������� ����
		switch (type) {
		case GPRS: return "GPRS";
		case Edge: return "Edge";
		case _2G: return "2G";
		case _3G: return "3G";
		case _4G: return "4G";
		case _5G: return "5G";
		case unknown: return "unknown";
		default: return "N/A";
		}
	}

	friend ostream& operator<<(ostream& info, Mobile_antenna& other) {      //����� ���������� � ����
		info << "�� ������� ������������ � ��������� ���� " << other.name << endl << endl;
		info << "���������� � ����" << endl;
		info << "��������: " << other.speed << " ����/�" << endl;
		info << "������� �������: " << other.signal << endl;
		info << "�������: " << other.frequency << " ���" << endl;
		info << "������ ��������: " << other.radius << " �" << endl;
		info << "��������� ����: " << other.getType() << endl;
		info << "C��� ��������: " << other.work << endl;
		info << "�������� ������: " << other.traffic << " ��" << endl;
		info << "����� ����������: " << other.time << " ���" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Mobile_antenna() {  //����������

	}

};