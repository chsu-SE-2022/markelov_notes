#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Flash {
private:
	int capacity;
	string name;

protected:
	double version;
	char connector;

public:
	Flash(string valueName, int valueCapacity, double valueVersion, char valueConnector) {
		this->name = valueName;
		this->capacity = valueCapacity;
		this->version = valueVersion;
		this->connector = valueConnector;
	}

	Flash() {
		this->name = "������������ USB-����������";
		this->capacity = 0;
		this->version = 0.0;
		this->connector = 'N';
	}

	Flash(string valueName) {
		this->name = valueName;
		this->capacity = 0;
		this->version = 0.0;
		this->connector = 'N';
	}

	Flash(string valueName, int valueCapacity) {
		this->name = valueName;
		this->capacity = valueCapacity;
		this->version = 0.0;
		this->connector = 'N';
	}

	Flash(const Flash& obj) {
		this->name = obj.name;
		this->capacity = obj.capacity;
		this->version = obj.version;
		this->connector = obj.connector;
	}

	string getName() {
		return name;
	}

	friend ostream& operator<<(ostream& info, Flash& other) {      //����� ���������� � ����
		info << "���������� USB-���������� " << other.name << endl << endl;
		info << "���������� �� ����������" << endl;
		info << "����� USB-����������: " << other.capacity << " ��" << endl;
		info << "������ USB: " << other.version << endl;
		info << "������: " << "Type-" << other.connector << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~Flash() {               //����������

	}
};