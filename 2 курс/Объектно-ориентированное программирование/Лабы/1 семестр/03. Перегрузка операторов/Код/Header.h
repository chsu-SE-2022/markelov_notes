#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum security { WEP, WPA, WPA2, WPA3, NoProtection };

class WiFi {
private:
	string login;
	string password;
	static string work;
	security protection;
	int speed, radius, traffic;
	double frequency;

public:

	bool operator > (const WiFi& other) {
		return this->speed > other.speed;
	}

	bool operator < (const WiFi& other) {
		return this->speed < other.speed;
	}

	bool operator == (const WiFi& other) {
		return this->speed == other.speed;
	}

	int operator + (const WiFi& other) {
		return this->traffic + other.traffic;
	}

	WiFi(string valueLogin, string valuePassword, security valueProtection, int valueSpeed, int valueRadius, double valueFrequency) {
		this->login = valueLogin;                      //����������� �� ����� �����������
		this->password = valuePassword;
		this->protection = valueProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->work = "��";
		this->traffic = rand() % 100;
	}

	WiFi() {
		this->login = "�������������� ����";                      //����������� �� ���������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->work = "��";
		this->traffic = 0;
	}

	WiFi(string valueLogin) {
		this->login = valueLogin;                      //����������� � 1 ����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->work = "��";
		this->traffic = rand() % 100;
	}

	WiFi(double valueFrequency, string valueLogin) {
		this->login = valueLogin;                      //����������� � 2 �����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = valueFrequency;
		this->work = "��";
		this->traffic = rand() % 100;
	}

	WiFi(int valueSpeed, int valueRadius, string valueLogin) {
		this->login = valueLogin;                      //����������� � 3 �����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = 0;
		this->work = "��";
		this->traffic = rand() % 100;
	}

	WiFi(const WiFi& obj) {
		this->login = obj.login;                      //���������� �����������
		this->password = obj.password;
		this->protection = obj.protection;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->work = "��";
		this->traffic = rand() % 100;
	}

	string getLogin() {  //������ ��� ������
		return login;
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

	friend ostream& operator<<(ostream& info, WiFi& other) {      //����� ���������� � ����
		info << "�� ������� ������������ � WiFi-���� " << other.login << endl << endl;
		info << "���������� � ����" << endl;
		info << "��������: " << other.speed << " ����/�" << endl;
		info << "�������: " << other.frequency << " ���" << endl;
		info << "������ ��������: " << other.radius << " �" << endl;
		info << "�������� ������������: " << other.getProtection() << endl;
		info << "C��� ��������: " << other.work << endl;
		info << "�������� ������: " << other.traffic << " ��" << endl;
		info << endl << "=======================" << endl << endl;
		return info;
	}

	~WiFi() {  //����������

	}
};