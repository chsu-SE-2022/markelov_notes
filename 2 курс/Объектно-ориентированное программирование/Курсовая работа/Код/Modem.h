#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wired.h"
using namespace std;
using namespace System;

enum line { Dial_Up, ADSL, Ethernet, NoConnect };

class Modem : public Wired {
private:
	line connect;

public:
	Modem(string valueName, cable valueCord, int valueSpeed, int valueLength, line valueConnect) {
		this->name = valueName;                      //����������� �� ����� �����������
		this->speed = valueSpeed;
		this->cord = valueCord;
		this->connect = valueConnect;
		this->length_cable = valueLength;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Modem() {
		this->name = "����������� ������";                      //����������� �� ���������
		this->speed = 0;
		this->cord = other;
		this->connect = NoConnect;
		this->length_cable = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Modem(const Modem& obj) {
		this->name = obj.name;                      //���������� �����������
		this->speed = obj.speed;
		this->cord = obj.cord;
		this->connect = obj.connect;
		this->length_cable = obj.length_cable;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getLine() {   //������ ��� ���� �����
		switch (connect) {
		case Dial_Up: return "Dial Up";
			break;
		case ADSL: return "ADSL";
			break;
		case Ethernet: return "Ethernet";
			break;
		case NoConnect: return "������ ��� �����";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //����� ���������� � ����
		String^ info;
		info += "�� ������� ������������ � ������ " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "���������� � ����\n";
		info += "��������: " + speed + " ����/�\n";
		info += "��� �����������: " + msclr::interop::marshal_as<String^>(getCord()) + "\n";
		info += "��� �����: " + msclr::interop::marshal_as<String^>(getLine()) + "\n";
		info += "����� ������: " + length_cable + " �\n";
		info += "C��� ��������: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "�������� ������: " + traffic + " ��\n";
		info += "����� ����������: " + time + " ���\n";
		ofstream result;
		result.open("Modem.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~Modem() {   //����������

	}
};