#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class MyException : public exception
{
private:
    string message_error;

public:
    MyException(string error) {
        this->message_error = error;
    }

    const char* what() const noexcept {
        return message_error.c_str();
    }
};