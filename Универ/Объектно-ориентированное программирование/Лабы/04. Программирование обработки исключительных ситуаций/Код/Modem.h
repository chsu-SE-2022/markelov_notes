#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Mobile.h"
#include "Flash.h"
using namespace std;

class Modem : public Mobile_antenna, public Flash {
private: 
	bool antenna, sd;

public:
	Modem(string valueName, generation valueType, int valueSpeed, int valueRadius, double valueFrequency, double valueVersion, char valueConnector, bool valueAntenna, bool valueSd) {
		this->Wireless::name = valueName;                      //����������� �� ����� �����������
		this->type = valueType;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = valueVersion;
		this->connector = valueConnector;
		this->antenna = valueAntenna;
		this->sd = valueSd;
	}

	Modem() {
		this->Wireless::name = "������������ USB-����������";                      //����������� �� ���������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = 'N';
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(string valueName) {
		this->Wireless::name = valueName;                      //����������� c 1 ����������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = 'N';
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(string valueName, generation valueType) {
		this->Wireless::name = valueName;                      //����������� c 2 �����������
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = 'N';
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(string valueName, generation valueType, char valueConnector) {
		this->Wireless::name = valueName;                      //����������� c 3 �����������
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = 0.0;
		this->connector = valueConnector;
		this->antenna = 0;
		this->sd = 0;
	}

	Modem(const Modem& obj) {
		this->Wireless::name = obj.Wireless::name;                      //���������� �����������
		this->type = obj.type;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = obj.traffic;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
		this->version = obj.version;
		this->connector = obj.connector;
		this->antenna = obj.antenna;
		this->sd = obj.sd;
	}

	string getAntenna() {
		if (antenna) return "����";
		else return "���";
	}

	string getSd() {
		if (sd) return "����";
		else return "���";
	}

	friend ostream& operator<<(ostream& info, Modem& other) {      //����� ���������� � ����
		info << "�� ������� ������������ � ������ " << other.Wireless::name << endl << endl;
		info << "���������� � ����" << endl;
		info << "��������: " << other.speed << " ����/�" << endl;
		info << "������� �������: " << other.signal << endl;
		info << "�������: " << other.frequency << " ���" << endl;
		info << "������ ��������: " << other.radius << " �" << endl;
		info << "��������� ����: " << other.getType() << endl;
		info << "C��� ��������: " << other.work << endl;
		info << "������ USB: " << other.version << endl;
		info << "������: " << "Type-" << other.connector << endl;
		info << "������� �������: " << other.getAntenna() << endl;
		info << "������� ������� ��� SD-�����: " << other.getSd() << endl;
		info << "�������� ������: " << other.traffic << " ��" << endl;
		info << "����� ����������: " << other.time << " ���" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Modem() {            //����������

	}
};
