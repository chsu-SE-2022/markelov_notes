#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "DataDevices.h"
using namespace std;

class Wireless : public DataDevices {   
protected:
	int radius;
	double frequency;
};