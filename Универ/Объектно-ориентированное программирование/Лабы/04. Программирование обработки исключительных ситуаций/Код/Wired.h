#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices.h"
using namespace std;

class Site;

class Wired : public DataDevices {   //������� �����-���������
public:
	void openSite(Site& site);  //�������, ����������������� � �������� ������ Site
};