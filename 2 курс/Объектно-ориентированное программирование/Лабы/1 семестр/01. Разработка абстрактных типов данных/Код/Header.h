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
	int speed, radius;
	double frequency;

public:

	WiFi(string valueLogin, string valuePassword, security valueProtection, int valueSpeed, int valueRadius, double valueFrequency) {
		this->login = valueLogin;                      //�����������
		this->password = valuePassword;
		this->protection = valueProtection;
		this->speed = valueSpeed;
		this->radius = valueRadius;
		this->frequency = valueFrequency;
		this->work = "��";
	}

	WiFi() {
		this->login = "�������������� ����";                      //�����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = 0;
		this->work = "��";
	}

	WiFi(double valueFrequency, string valueLogin) {
		this->login = valueLogin;                      //�����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = 0;
		this->radius = 0;
		this->frequency = valueFrequency;
		this->work = "��";
	}

	WiFi(int valueSpeed, string valueLogin) {
		this->login = valueLogin;                      //�����������
		this->password = "0";
		this->protection = NoProtection;
		this->speed = valueSpeed;
		this->radius = 0;
		this->frequency = 0;
		this->work = "��";
	}

	WiFi(const WiFi &obj) {
		this->login = obj.login;                      //�����������
		this->password = obj.password;
		this->protection = obj.protection;
		this->speed = obj.speed;
		this->radius = obj.radius;
		this->frequency = obj.frequency;
		this->work = "��";
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

	void networkInfo() {      //����� ���������� � ����
		cout << "�� ������� ������������ � WiFi-���� " << login << endl << endl;
		cout << "���������� � ����" << endl;
		cout << "��������: " << speed << " ����/�" << endl;
		cout << "�������: " << frequency << " ���" << endl;
		cout << "������ ��������: " << radius << " �" << endl;
		cout << "�������� ������������: " << getProtection() << endl;
		cout << "C��� ��������: " << work << endl;
	}

	~WiFi() {  //����������

	}
};