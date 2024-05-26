#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

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

	bool empty() {  //проверка очереди на пустоту
		return head == NULL;
	}

	void add(T value) {  //добавление элемента в очередь
		if (empty()) {  //если она пустая
			head = new Node;
			head->data = value;
			head->next = NULL;
			tail = head;
			size++;
		}
		else {  //если она не пустая
			tail->next = new Node;
			tail = tail->next;
			tail->data = value;
			tail->next = NULL;
			size++;
		}
	}

	T del() {  //взятие и удаление элемента из очереди
		if (empty()) {
			cout << "Queue is empty" << endl;
		}
		else {
			T d = head->data;
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

	bool operator >= (const Queue& other) {
		return this->size >= other.size;
	}

	bool operator < (const Queue& other) {
		return this->size < other.size;
	}

	int getSize() {  //геттер для логина
		return size;
	}

	friend ostream& operator<<(ostream& del, Queue& q) {
		while (!q.empty())
			del << q.del() << endl;
		return del;
	}

	void arr(T* a, int& i) {
		while (!empty()) {
			a[i] = del();
			i++;
		}
	}

	void print_NewOld() {
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		i--;
		for (i; i >= 0; i--)
			cout << networks[i] << endl;
	}

	void print_AZ() {
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		string k;
		for (i = 0; i < size; i++)
			for (int j = i; j < size; j++) {
				if (networks[i] > networks[j]) {
					k = networks[i];
					networks[i] = networks[j];
					networks[j] = k;
				}
			}
		for (i = 0; i < size; i++)
			cout << networks[i] << endl;
	}

	void print_ZA() {
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		string k;
		for (i = 0; i < size; i++)
			for (int j = i; j < size; j++) {
				if (networks[i] < networks[j]) {
					k = networks[i];
					networks[i] = networks[j];
					networks[j] = k;
				}
			}
		for (i = 0; i < size; i++)
			cout << networks[i] << endl;
	}

	void search(string name) {
		string* networks = new string[size];
		int i = 0;
		arr(networks, i);
		int k2 = 0;
		for (i = 0; i < size; i++) {
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

	void search(int number) {
		int* networks = new int[size];
		int i = 0, k = 0;
		arr(networks, i);
		for (i = 0; i < size; i++) {
			if (networks[i] == number) k++;
		}
		if (k == 0) cout << "Подключений к сети №" << number << " не было" << endl;
		else cout << "К сети №" << number << " подключались " << k << " раз(а)" << endl;
	}

	~Queue() {   //деструктор

	}
};