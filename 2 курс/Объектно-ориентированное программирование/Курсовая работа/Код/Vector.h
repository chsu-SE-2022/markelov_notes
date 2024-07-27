#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <msclr/marshal_cppstd.h>
#include "Container.h"
#include "DataDevices_i.h"
using namespace std;
using namespace msclr::interop;

template <class T>
class Vector : private Container {
public:
    Vector() {
        capacity = 10;
        data = new void* [capacity];
        size = 0;
    }

    Vector(const Vector& other) {
        capacity = other.capacity;
        size = other.size;
        data = new void* [capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = new T(*static_cast<T*>(other.data[i]));
        }
    }

    ~Vector() {
        clear();
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            delete static_cast<T*>(data[i]);
        }
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    bool empty() const {
        return size == 0;
    }

    void add(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = new T(value);
    }

    T get() {
        if (empty()) {
            throw out_of_range("Vector is empty");
        }
        T value = *static_cast<T*>(data[--size]);
        delete static_cast<T*>(data[size]);
        return value;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return *static_cast<T*>(data[index]);
    }

    size_t getSize() const {
        return size;
    }

    friend ostream& operator<<(ostream& os, const Vector& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            T value = *reinterpret_cast<T*>(vec.data[i]);
            os << value->getName() << endl;
        }
        return os;
    }

    friend string& operator<<(string& s, const Vector& vec) {
        stringstream ss;
        for (size_t i = 0; i < vec.size; ++i) {
            T value = *reinterpret_cast<T*>(vec.data[i]);
            ss << value->getName() << "\n";
        }
        s = ss.str();
        return s;
    }

    void print_NewOld(ofstream& result, Device::MyForm^ myForm) {
        myForm->setClear();
        if (size == 0) {
            myForm->setText("Подключений не было");
        }
        for (int i = size - 1; i >= 0; --i) {
            T value = *reinterpret_cast<T*>(data[i]);
            if (value != nullptr) {
                if (size <= 20) {
                    myForm->setText(marshal_as<System::String^>(value->getName()));
                }
                else {
                    result << value->getName() << endl;
                }
            }
        }
        if (size > 20) {
            myForm->setText("История подключений записана в файл result.txt");
        }
    }

    void arr(string* networks) {
        for (size_t i = 0; i < size; ++i) {
            T value = *reinterpret_cast<T*>(data[i]);
            if (value != nullptr) {
                networks[i] = value->getName();
            }
        }
    }

    void print_AZ(ofstream& result, Device::MyForm^ myForm) {
        myForm->setClear();
        int n = size;
        string* networks = new string[size];
        arr(networks);
        sort(networks, networks + n);
        if (n == 0) {
            myForm->setText("Подключений не было");
        }
        else {
            for (int i = 0; i < n; ++i) {
                if (size <= 20) {
                    myForm->setText(marshal_as<System::String^>(networks[i]));
                }
                else {
                    result << networks[i] << endl;
                }
            }
            if (size > 20) {
                myForm->setText("История подключений записана в файл result.txt");
            }
        }
        delete[] networks;
    }

    void print_ZA(ofstream& result, Device::MyForm^ myForm) {
        myForm->setClear();
        int n = size;
        string* networks = new string[size];
        arr(networks);
        sort(networks, networks + n, greater<string>());
        if (n == 0) {
            myForm->setText("Подключений не было");
        }
        else {
            for (int i = 0; i < n; ++i) {
                if (size <= 20) {
                    myForm->setText(marshal_as<System::String^>(networks[i]));
                }
                else {
                    result << networks[i] << endl;
                }
            }
            if (size > 20) {
                myForm->setText("История подключений записана в файл result.txt");
            }
        }
        delete[] networks;
    }

    void search(const string& name, Device::MyForm^ myForm) {
        myForm->setClear();
        int n = size;
        int found = 0;
        for (int i = 0; i < n; ++i) {
            T value = *reinterpret_cast<T*>(data[i]);
            if (value != nullptr && value->getName() == name) {
                myForm->setText(marshal_as<System::String^>(value->getName()));
                found++;
            }
        }
        if (found == 0) {
            myForm->setText("Устройство не найдено");
        }
    }

    void broadcast(String^ info, Device::MyForm^ myForm) {
        T value = *reinterpret_cast<T*>(data[size - 1]);
        value->setData(marshal_as<string>(info));
    }
};