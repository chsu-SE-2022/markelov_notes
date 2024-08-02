#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum protocol { http, https, NoProtocol };

class WiFi;

class Site {
private:
	string name, type, address;
	static string work;
	double time;
	protocol connect;

public:
	Site(string valueName, string valueType, string valueAddress, protocol valueConnect) {
		this->name = valueName;                      //����������� �� ����� �����������
		this->type = valueType;
		this->address = valueAddress;
		this->connect = valueConnect;
		this->time = rand() / 1000.0;
	}

	Site() {
		this->name = "����������� ����";                      //����������� �� ���������
		this->type = "����������� ���";
		this->address = "about:blank";
		this->connect = NoProtocol;
		this->time = rand() / 1000.0;
	}

	Site(string valueAddress) {
		this->name = "����������� ����";                      //����������� c 1 ����������
		this->type = "����������� ���";
		this->address = valueAddress;
		this->connect = NoProtocol;
		this->time = rand() / 1000.0;
	}

	Site(string valueAddress, protocol valueConnect) {
		this->name = "����������� ����";                      //����������� c 2 �����������
		this->type = "����������� ���";
		this->address = valueAddress;
		this->connect = valueConnect;
		this->time = rand() / 1000.0;
	}

	Site(string valueName, string valueAddress, protocol valueConnect) {
		this->name = "����������� ����";                      //����������� c 3 �����������
		this->type = "����������� ���";
		this->address = valueAddress;
		this->connect = valueConnect;
		this->time = rand() / 1000.0;
	}

	Site(const Site& obj) {
		this->name = obj.name;                      //���������� �����������
		this->type = obj.type;
		this->address = obj.address;
		this->connect = obj.connect;
		this->time = rand() / 1000.0;
	}

	string getName() {  //������ ��� �������� �����
		return name;
	}

	string getWork() {  //������ ��� ������� ������ �����
		return work;
	}

	double getTime() {  //������ ��� ������� �������� �����
		return time;
	}

	friend ostream& operator<<(ostream& info, Site& other) {
		switch (other.connect) {
		case NoProtocol: info << other.name << " - " << other.address << " (" << other.type << ")";
			break;
		case http: info << other.name << " - " << " http://" << other.address << " (" << other.type << ")";
			break;
		case https: info << other.name << " - " << " https://" << other.address << " (" << other.type << ")";
			break;
		}
		return info;
	}

	void status(WiFi& wifi);  //�������, ����������������� � �������� ������ WiFi

	~Site() {  //����������

	}
};