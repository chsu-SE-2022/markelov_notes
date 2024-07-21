#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Wireless.h"
using namespace std;

enum security { WEP, WPA, WPA2, WPA3, NoProtection };

class WiFi_router : public Wireless {
private:
	string password;
	security protection;

public:

	bool operator > (const WiFi_router& other) {
		return this->speed > other.speed;
	}

	bool operator < (const WiFi_router& other) {
		return this->speed < other.speed;
	}

	bool operator == (const WiFi_router& other) {
		return this->speed == other.speed;
	}

	int operator + (const WiFi_router& other) {
		return this->traffic + other.traffic;
	}

	WiFi_router(string valueName, string valuePassword, security valueProtection, int valueSpeed, int valueRadius, double valueFrequency) {
		this->name = valueName;                      //����������� �� ����� �����������
		this->password = valuePassword;
		this->protection = valueProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router() {
		this->name = "�������������� ����";                      //����������� �� ���������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = 0;
		this->time = rand() / 100.0;
	}

	WiFi_router(string valueName) {
		this->name = valueName;                      //����������� � 1 ����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(double valueFrequency, string valueName) {
		this->name = valueName;                      //����������� � 2 �����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = valueFrequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(int valueSpeed, int valueRadius, string valueName) {
		this->name = valueName;                      //����������� � 3 �����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	WiFi_router(const WiFi_router& obj) {
		this->name = obj.name;                      //���������� �����������
		this->password = obj.password;
		this->protection = obj.protection;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getPassword() {   //������ ��� ������
		return password;
	}

	string getProtection() {   //������ ��� ��������� ������������
		switch (protection) {
		case WEP: return "WEP";
		case WPA: return "WPA";
		case WPA2: return "WPA2";
		case WPA3: return "WPA3";
		case NoProtection: return "��� ������";
		default: return "N/A";
		}
	}

	friend ostream& operator<<(ostream& info, WiFi_router& other) {      //����� ���������� � ����
		info << "�� ������� ������������ � WiFi-���� " << other.name << endl << endl;
		info << "���������� � ����" << endl;
		info << "��������: " << other.speed << " ����/�" << endl;
		info << "�������: " << other.frequency << " ���" << endl;
		info << "������ ��������: " << other.radius << " �" << endl;
		info << "�������� ������������: " << other.getProtection() << endl;
		info << "C��� ��������: " << other.work << endl;
		info << "�������� ������: " << other.traffic << " ��" << endl;
		info << "����� ����������: " << other.time << " ���" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~WiFi_router() {  //����������

	}
};