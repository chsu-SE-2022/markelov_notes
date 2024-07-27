#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Wired.h"
using namespace std;
using namespace System;

class Hub : public Wired {
private:
	int ports;

public:
	Hub(string valueName, cable valueCord, int valueSpeed, int valueLength, int valuePorts) {
		this->name = valueName;                      //����������� �� ����� �����������
		this->speed = valueSpeed;
		this->cord = valueCord;
		this->length_cable = valueLength;
		this->ports = valuePorts;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Hub() {
		this->name = "����������� ���";                      //����������� �� ���������
		this->speed = 0;
		this->cord = other;
		this->length_cable = 0;
		this->ports = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Hub(const Hub& obj) {
		this->name = obj.name;                      //���������� �����������
		this->speed = obj.speed;
		this->cord = obj.cord;
		this->length_cable = obj.length_cable;
		this->ports = obj.ports;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	String^ getInfo() {      //����� ���������� � ����
		String^ info;
		info += "�� ������� ������������ � ���� " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "���������� � ����\n";
		info += "��������: " + speed + " ����/�\n";
		info += "��� �����������: " + msclr::interop::marshal_as<String^>(getCord()) + "\n";
		info += "����� ������: " + length_cable + " �\n";
		info += "���������� ������: " + ports + "\n";
		info += "C��� ��������: " + msclr::interop::marshal_as<String^>(work) + "\n";
		info += "�������� ������: " + traffic + " ��\n";
		info += "����� ����������: " + time + " ���\n";
		ofstream result;
		result.open("Hub.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~Hub() {   //����������

	}
};
