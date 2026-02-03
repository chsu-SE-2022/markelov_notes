#include <iostream>
using namespace std;

//Стек

struct Node {  //узел стека
	int data;
	Node* next;
};

void InitStack(Node*& top) {  //инициализация стека
	top = NULL;
}

void push(Node*& top, int value) {  //добавление элемента в стек
	Node* tmp = new Node;
	tmp->next = top;
	top = tmp;
	top->data = value;
}

bool empty(Node*& top) {  //проверка стека на пустоту
	return top == NULL;
}

int pop(Node*& top) {  //взятие и удаление элемента и стека
	if (!empty(top)) {
		Node* tmp = top;
		int d = top->data;
		top = top->next;
		delete(tmp);
		return d;
	}
	else return 0;
}

void nullStack(Node*& top) {  //обнуление стека
	Node* tmp;
	while (!empty(top)) {
		tmp = top;
		top = top->next;
		delete(tmp);
	}
}

void print(Node*& top) {   //вывод стека
	if (!empty(top)) {
		Node* tmp = top;
		while (tmp != NULL) {
			cout << tmp->data << " ";
			tmp = tmp->next;
		}
		cout << endl;
		delete(tmp);
	}
	else cout << "Stack is empty" << endl;
}

//Очередь

class Queue {

private:
	struct Node {  //узел очереди
		int data;
		Node* next;
	};

	Node* head;
	Node* tail;

public:
	Queue() {  //инициализация очереди
		head = NULL;
		tail = NULL;
	}

	bool empty() {  //проверка очереди на пустоту
		return head == NULL;
	}

	void add(int value) {  //добавление элемента в очередь
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

	int del() {  //взятие и удаление элемента из очереди
		if (!empty()) {
			int d = head->data;
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

	void print() {   //вывод очереди
		if (!empty()) {
			Node* tmp = head;
			while (tmp != NULL) {
				cout << tmp->data << ' ';
				tmp = tmp->next;
			}
			cout << endl;
			delete(tmp);
		}
		else cout << "Queue is empty" << endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Node* st = NULL;
	InitStack(st);
	int capacity = rand() % 20 + 1;
	for (int i = 0; i < capacity; i++) {
		push(st, rand() % 100 - 50);
	}
	cout << "Исходный стек: ";
	print(st);

	Queue q;
	int capacity2 = rand() % 20 + 1;
	for (int i = 0; i < capacity2; i++) {
		q.add(rand() % 100 - 30);
	}
	cout << "Исходная очередь: ";
	q.print();

	int min, a = 0;
	if (!q.empty()) {
		min = q.del();
		while (!q.empty()) {
			a = q.del();
			if (a < min) min = a;
		}

		cout << "Минимальный элемент очереди: " << min << endl;

		Node* st2 = NULL;
		InitStack(st2);
		while (!empty(st)) {
			a = pop(st);
			if (a < min) push(st2, a);
		}
		if (empty(st2)) cout << "Таких элементов нет!";
		else {
			cout << "Полученный стек: ";
			while (!empty(st2)) {
				a = pop(st2);
				cout << a << ' ';
			}
		}
	}
	cout << endl;

	system("pause");
	return 0;
}