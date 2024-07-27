#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_windows.h>
#include "DataDevices.h"
#include "WiFi_router.h"
#include "Mobile_antenna.h"
#include "Modem.h"
#include "Switch.h"
#include "Hub.h"
#include "Flash.h"
#include "HDD.h"
#include "SSD.h"
#include "MyForm.h"
using namespace std;
using namespace msclr::interop;

template <class T>
class Queue {

private:
	struct Node {  //узел очереди
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;
	int size = 0;

public:

	Queue() {  //конструктор
		head = NULL;
		tail = NULL;
	}

	Queue(const Queue& other) { //копирующий конструктор
		Node* current = other.head;
		while (current) {
			add(new T(*current->data));
			current = current->next;
		}
	}

	bool empty() {  //проверка очереди на пустоту
		return head == NULL;
	}

	void add(T value) {  //добавление элемента в очередь
		Node* newNode = new Node;
		newNode->data = value;
		newNode->next = NULL;
		if (empty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	string del() {  //взятие и удаление элемента из очереди
		if (!empty())  {
			string d = head->data.DataDevices::getName();
			Node* tmp = head;
			head = head->next;
			delete(tmp);
			size--;
			return d;
		}
	}

	void nullQueue() {  //обнуление очереди
		Node* tmp;
		while (!empty()) {
			tmp = head;
			head = head->next;
			delete(tmp);
		}
	}

	bool operator >= (const Queue& other) {
		return this->size >= other.size;
	}

	bool operator < (const Queue& other) {
		return this->size < other.size;
	}

	int getSize() {  //геттер для размера очереди
		return size;
	}

	friend ostream& operator<<(ostream& del, Queue& q) {
		while (!q.empty())
			del << q.del() << endl;
		return del;
	}

	friend string& operator<<(std::string& s, Queue& q) {
		stringstream ss;
		while (!q.empty()) {
			ss << q.del() << "\n";
		}
		s = ss.str();
		return s;
	}

	void arr(string* a, int& i) {
		while (!empty()) {
			a[i] = del();
			i++;
		}
	}

	void print_NewOld(ofstream& result, Device::MyForm^ myForm) {
		myForm->setClear();
		int n = size;
		string s;
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		i--;
		if (n == 0) myForm->setText("Подключений не было");
		for (i; i >= 0; i--) {
			if (n <= 20) { 
				myForm->setText(marshal_as<System::String^>(networks[i])); 
			}
			else result << networks[i] << endl;
		}
		if (n > 20) myForm->setText("История подключений записана в файл result.txt");
	}

	void print_AZ(ofstream& result, Device::MyForm^ myForm) {
		myForm->setClear();
		int n = size;
		string s;
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				if (networks[i] > networks[j]) {
					swap(networks[i], networks[j]);
				}
			}
		if (n == 0) myForm->setText("Подключений не было");
		for (int i = 0; i < n; i++) {
			if (n <= 20) myForm->setText(marshal_as<System::String^>(networks[i]));
			else result << networks[i] << endl;
		}
		if (n > 20) myForm->setText("История подключений записана в файл result.txt");
		delete[] networks; 
	}

	void print_ZA(ofstream& result, Device::MyForm^ myForm) {
		myForm->setClear();
		int n = size;
		string s;
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				if (networks[i] < networks[j]) {
					swap(networks[i], networks[j]);
				}
			}
		if (n == 0) myForm->setText("Подключений не было");
		for (int i = 0; i < n; i++) {
			if (n <= 20) myForm->setText(marshal_as<System::String^>(networks[i]));
			else
				result << networks[i] << endl;
		}
		if (n > 20) myForm->setText("История подключений записана в файл result.txt");
		delete[] networks; 
	}

	void search(string name, Device::MyForm^ myForm) {
		myForm->setClear();
		int n = size;
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		int found = 0;
		for (int i = 0; i < n; i++) {
			if (networks[i] == name) {
				myForm->setText(marshal_as<System::String^>(networks[i]));
				found++;
			}
		}
		if (found == 0) myForm->setText("Устройство не найдено");
		delete[] networks; 
	}

	~Queue() {   //деструктор

	}
};