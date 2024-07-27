#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wireless.h"
using namespace std;
using namespace System;

enum security { WEP, WPA, WPA2, WPA3, NoProtection };

class WiFi_router : public Wireless {
private:
	string password;
	security protection;

public:

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
		this->traffic = rand() % 100;
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
			break;
		case WPA: return "WPA";
			break;
		case WPA2: return "WPA2";
			break;
		case WPA3: return "WPA3";
			break;
		case NoProtection: return "��� ������";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //����� ���������� � ����
		String^ info;
		info += "�� ������� ������������ � WiFi-���� " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "���������� � ����\n";
		info += "��������: " + speed + " ����/�\n";
		info += "�������: " + frequency + " ���\n";
		info += "������ ��������: " + radius + " �\n";
		info += "�������� ������������: " + msclr::interop::marshal_as<String^>(getProtection()) + "\n";
		info += "C��� ��������: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "�������� ������: " + traffic + " ��\n";
		info += "����� ����������: " + time + " ���\n";
		ofstream result;
		result.open("WiFi.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~WiFi_router() {  //����������

	}
};