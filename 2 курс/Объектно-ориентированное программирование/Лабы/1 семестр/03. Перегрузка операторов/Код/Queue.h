#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Queue {

private:
	struct Node {  //���� �������
		string data;
		Node* next;
	};

	Node* head;
	Node* tail;
	int size = 0;

public:

	Queue() {  //�����������
		head = NULL;
		tail = NULL;
	}

	bool empty() {  //�������� ������� �� �������
		return head == NULL;
	}

	void add(string value) {  //���������� �������� � �������
		if (empty()) {  //���� ��� ������
			head = new Node;
			head->data = value;
			head->next = NULL;
			tail = head;
			size++;
		}
		else {  //���� ��� �� ������
			tail->next = new Node;
			tail = tail->next;
			tail->data = value;
			tail->next = NULL;
			size++;
		}
	}

	string del() {  //������ � �������� �������� �� �������
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

	void nullQueue() {  //��������� �������
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

	int getSize() {  //������ ��� ������
		return size;
	}

	friend ostream& operator<<(ostream& del, Queue& q) {
		while (!q.empty())
			del << q.del() << endl;
		return del;
	}

	void print_NewOld() {
		string* networks = new string[size];
		int i = 0;
		while (!empty()) {
			networks[i] = del();
			i++;
		}
		i--;
		for (i; i >= 0; i--)
			cout << networks[i] << endl;
	}

	void print_AZ() {
		string* networks = new string[size];
		int i = 0;
		while (!empty()) {
			networks[i] = del();
			i++;
		}
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
		while (!empty()) {
			networks[i] = del();
			i++;
		}
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
		while (!empty()) {
			networks[i] = del();
			i++;
		}
		int k2 = 0;
		for (i = 0; i < size; i++) {
			int k1 = 0;
			string s;
			for (int l = 0; l < name.length(); l++) {
				s = networks[i];
				if (s[l] == name[l]) k1++;
			}
			if (k1 == name.length()) {
				if (k2 == 0) cout << endl << "��������� ����:" << endl;
				cout << networks[i] << endl;
				k2++;
			}
		}
	if (k2 == 0) cout << "������ �� �������!" << endl;
	}

	void search(int number, int* history) {
		int k = 0;
		for (int i = 0; i < size; i++) {
			if (number == history[i]) k++;
		}
		if (k == 0) cout << "����������� � ���� �" << number << " �� ����" << endl;
		else cout << "� ���� �" << number << " ������������ " << k << " ���(�)" << endl;
	}

	~Queue() {   //����������

	}
};