#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <msclr\marshal.h>
#include "Storage.h"
using namespace std;
using namespace System;

enum connect_type { SATA, IDE, SCSI, SAS, M2, U2, PCIe, other_type };

class HDD : public Storage {
private:
	connect_type connector;

public:
	HDD(string valueName, int valueCapacity, connect_type valueConnector, int valueSpeed) {
		this->name = valueName;
		this->speed = valueSpeed;
		this->capacity = valueCapacity;
		this->connector = valueConnector;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	HDD() {
		this->name = "������������ ������� ����";
		this->speed = 0;
		this->capacity = 0;
		this->connector = other_type;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	HDD(const HDD& obj) {
		this->name = obj.name;
		this->speed = obj.speed;
		this->capacity = obj.capacity;
		this->connector = obj.connector;
		this->traffic = rand() % 100;
		this->time = rand() / 100.0;
	}

	string getType() {   //������ ��� �������
		switch (connector) {
		case SATA: return "SATA";
			break;
		case IDE: return "IDE";
			break;
		case SCSI: return "SCSI";
			break;
		case SAS: return "SAS";
			break;
		case M2: return "M2";
			break;
		case U2: return "U2";
			break;
		case PCIe: return "PCIe";
			break;
		case other_type: return "������ ������";
			break;
		default: return "N/A";
			break;
		}
	}

	String^ getInfo() {      //����� ���������� � ����
		String^ info;
		info += "��������� ������� ���� " + msclr::interop::marshal_as<String^>(name) + "\n\n";
		info += "���������� �� ����������\n";
		info += "��������: " + speed + " ��/�\n";
		info += "����� �����: " + capacity + " ��\n";
		info += "������: " + msclr::interop::marshal_as<String^>(getType()) + "\n";
		info += "�������� ������: " + traffic + " ��\n";
		info += "����� ����������: " + time + " ���\n";
		ofstream result;
		result.open("HDD.txt");
		result << marshal_as<string>(info);
		result.close();
		return info;
	}

	~HDD() {               //����������

	}
};