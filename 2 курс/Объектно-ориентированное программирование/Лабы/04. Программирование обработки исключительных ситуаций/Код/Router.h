#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices.h"
#include "Wired.h"
using namespace std;

enum cable { Twisted, Coaxial, Optical, other };

class Router : public Wired {
private:
	cable cord;
	int length_cable;
public:
	Router(string valueName, cable valueCord, int valueSpeed, int valueLength) {
		this->name = valueName;                      //����������� �� ����� �����������
		this->speed = valueSpeed;
		this->cord = valueCord;
		this->length_cable = valueLength;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Router() {
		this->name = "����������� ������";                      //����������� �� ���������
		this->speed = 0;
		this->cord = other;
		this->length_cable = 0;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	Router(const Router& obj) {
		this->name = obj.name;                      //���������� �����������
		this->speed = obj.speed;
		this->cord = obj.cord;
		this->length_cable = obj.length_cable;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getCord() {   //������ ��� ��������� ������������
		switch (cord) {
		case Twisted: return "����� ����";
		case Coaxial: return "������������ ������";
		case Optical: return "�����������";
		case other: return "������ ��� ������";
		default: return "N/A";
		}
	}

	friend ostream& operator<<(ostream& info, Router& other) {      //����� ���������� � ����
		info << "�� ������� ������������ � ������� " << other.name << endl << endl;
		info << "���������� � ����" << endl;
		info << "��������: " << other.speed << " ����/�" << endl;
		info << "��� �����������: " << other.getCord() << endl;
		info << "����� ������: " << other.length_cable << " �" << endl;
		info << "C��� ��������: " << other.work << endl;
		info << "�������� ������: " << other.traffic << " ��" << endl;
		info << "����� ����������: " << other.time << " ���" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Router() {   //����������

	}
};