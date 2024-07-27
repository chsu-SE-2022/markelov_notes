#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wireless.h"
using namespace std;
using namespace System;

enum generation { GPRS, Edge, _2G, _3G, _4G, _5G, unknown };

class Mobile_antenna : public Wireless {
private: 
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
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(string valueName) {
		this->name = valueName;                      //����������� � 1 ����������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(string valueName, generation valueType) {
		this->name = valueName;                      //����������� � 2 �����������
		this->type = valueType;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(string valueName, generation valueType, int valueSpeed) {
		this->name = valueName;                      //����������� � 3 �����������
		this->type = unknown;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	Mobile_antenna(const Mobile_antenna& obj) {
		this->name = obj.name;                      //����������� � 3 �����������
		this->type = obj.type;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
		this->signal = rand() % 5;
	}

	string getType() {   //������ ��� ��������� ����
		switch (type) {
		case GPRS: return "GPRS";
			break;
		case Edge: return "Edge";
			break;
		case _2G: return "2G";
			break;
		case _3G: return "3G";
			break;
		case _4G: return "4G"; 
			break;
		case _5G: return "5G";
			break;
		case unknown: return "unknown";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //����� ���������� � ����
		String^ info;
		info += "�� ������� ������������ � ��������� ���� " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "���������� � ����\n";
		info += "��������: " + speed + " ����/�\n";
		info += "������� �������: " + signal + "\n";
		info += "�������: " + frequency + " ���\n";
		info += "������ ��������: " + radius + " �\n";
		info += "��������� ����: " + msclr::interop::marshal_as<String^>(getType()) + "\n";
		info += "C��� ��������: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "�������� ������: " + traffic + " ��\n";
		info += "����� ����������: " + time + " ���\n";
		ofstream result;
		result.open("Mobile.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~Mobile_antenna() {  //����������

	}

};