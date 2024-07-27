#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
using namespace msclr::interop;

class DataDevices_i {
public:
	virtual string getName() = 0;   //������ ��� �����
	virtual int getTraffic() = 0;   //������ ��� ��������
	virtual double getTime() = 0;  //������ ��� �������
	virtual int getSpeed() = 0;   //������ ��� ��������
	virtual void setData(string value) = 0;   //������ ��� �������� ������

	virtual ~DataDevices_i() = default; // ����������� ����������
};
