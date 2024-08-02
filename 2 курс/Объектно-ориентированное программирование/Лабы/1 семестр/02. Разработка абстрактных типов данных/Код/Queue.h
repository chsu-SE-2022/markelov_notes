#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Queue {

private:
	struct Node {  //узел очереди
		string data;
		Node* next;
	};

	Node* head;
	Node* tail;

public:
	Queue() {  //конструктор
		head = NULL;
		tail = NULL;
	}

	bool empty() {  //проверка очереди на пустоту
		return head == NULL;
	}

	void add(string value) {  //добавление элемента в очередь
		if (empty()) {  //если она пустая
			head = new Node;
			head->data = value;
			head->next = NULL;
			tail = head;
		}
		else {  //если она не пустая
			tail->next = new Node;
			tail = tail->next;
			tail->data = value;
			tail->next = NULL;
		}
	}

	string del() {  //взятие и удаление элемента из очереди
		if (empty()) {
			cout << "Queue is empty" << endl;
		}
		else {
			string d = head->data;
			Node* tmp = head;
			head = head->next;
			delete(tmp);
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

	void print_OldNew() {
		while (!empty())
			cout << del() << endl;
	}

	void print_NewOld(int count) {
		string* networks = new string[count];
		int i = 0;
		while (!empty()) {
			networks[i] = del();
			i++;
		}
		i--;
		for (i; i >= 0; i--)
			cout << networks[i] << endl;
	}

	void print_AZ(int count) {
		string* networks = new string[count];
		int i = 0;
		while (!empty()) {
			networks[i] = del();
			i++;
		}
		string k;
		for (i = 0; i < count; i++)
			for (int j = i; j < count; j++) {
				if (networks[i] > networks[j]) {
					k = networks[i];
					networks[i] = networks[j];
					networks[j] = k;
				}
			}
		for (i = 0; i < count; i++)
			cout << networks[i] << endl;
	}

	void print_ZA(int count) {
		string* networks = new string[count];
		int i = 0;
		while (!empty()) {
			networks[i] = del();
			i++;
		}
		string k;
		for (i = 0; i < count; i++)
			for (int j = i; j < count; j++) {
				if (networks[i] < networks[j]) {
					k = networks[i];
					networks[i] = networks[j];
					networks[j] = k;
				}
			}
		for (i = 0; i < count; i++)
			cout << networks[i] << endl;
	}

	void search(string name, int count) {
		string* networks = new string[count];
		int i = 0;
		while (!empty()) {
			networks[i] = del();
			i++;
		}
		int k2 = 0;
		for (i = 0; i < count; i++) {
			int k1 = 0;
			string s;
			for (int l = 0; l < name.length(); l++) {
				s = networks[i];
				if (s[l] == name[l]) k1++;
			}
			if (k1 == name.length()) {
				if (k2 == 0) cout << endl << "Найденные сети:" << endl;
				cout << networks[i] << endl;
				k2++;
			}
		}
	if (k2 == 0) cout << "Ничего не найдено!" << endl;
	}

	~Queue() {   //деструктор

	}
};