#include <iostream>
using namespace std;

//Стек

struct Stack1 {         //определение стека
	int top;
	int* data;
	int capacity;
};

void InitStack(Stack1& st, int capacity) {      //инициализация стека
	st.data = new int[capacity];
	st.top = -1;
	st.capacity = capacity;
}

bool empty(Stack1& st) {    //проверка стека на пустоту
	return st.top == -1;
}

void push(Stack1& st, int value, int& err) {     //добавление элемента в стек
	if (st.top + 1 >= st.capacity) err++;
	else st.data[++st.top] = value;
}

int pop(Stack1& st) {       //взятие и удаление элемента из стека
	if (!empty(st)) return st.data[st.top--];
	else return 0;
}

void nullStack(Stack1& st) {       //обнуление стека
	st.top = -1;
}

void print(Stack1& st, int& err) {    //вывод стека
	if (!empty(st) && err == 0) 
		for (int i = 0; i <= st.top; i++)
			cout << st.data[i] << ' ';
	else if (empty(st) && err == 0) cout << "Stack is empty";
	if (err != 0) cout << "Stack overflow";
	cout << endl;
}

//Очередь

struct Queue1 {         //определение очереди
	int head, tail, size;
	int* data;
};

void nullQueue(Queue1& q) {    //обнуление очереди
	q.head = 0;
	q.tail = q.size - 1;
}

void InitQueue(Queue1& q, int capacity) {     //инициализация очереди
	q.size = capacity + 1;
	q.data = new int[q.size];
	nullQueue(q);
}

int next(Queue1& q, int n) {        //вычисление следующего индекса
	return (n + 1) % q.size;
}

bool empty(Queue1& q) {          //проверка очереди на пустоту
	return next(q, q.tail) == q.head;
}

void add(Queue1& q, int value, int& err) {  //добавление элемента в очередь
	if (next(q, next(q, q.tail)) == q.head) err++; //проверка очереди на переполнение
	else {
		q.tail = next(q, q.tail);
		q.data[q.tail] = value;
	}
}

int del(Queue1& q) {  //взятие и удаление элемента из очереди
	if (empty(q)) return 0;
	else {
		int d = q.data[q.head];
		q.head = next(q, q.head);
		return d;
	}
}

void print(Queue1& q, int& err) {   //вывод очереди
	if (!empty(q) && err == 0) 
		for (int i = q.head; i <= q.tail; i++)
			cout << q.data[i] << ' ';
	else if (empty(q) && err == 0) cout << "Queue is empty";
	if (err != 0) cout << "Queue overflow";
	cout << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Stack1 st;
	int capacity = rand() % 20 + 1, err1 = 0;
	InitStack(st, capacity);
	for (int i = 0; i < capacity; i++) {
		push(st, rand() % 100 - 50, err1);
	}
	cout << "Исходный стек: ";
	print(st, err1);

	Queue1 q;
	int capacity2 = rand() % 20 + 1, err2 = 0;
	InitQueue(q, capacity2);
	for (int i = 0; i < capacity2; i++) {
		add(q, rand() % 100 - 30, err2);
	}
	cout << "Исходная очередь: ";
	print(q, err2);

	int a, min = q.data[q.tail];
	if (!empty(q) && err1 == 0 && err2 == 0) {
		while (!empty(q)) {
			a = del(q);
			if (a < min) min = a;
		}

		cout << "Минимальный элемент очереди: " << min << endl;

		Stack1 st2;
		InitStack(st2, capacity);
		int err3 = 0;
		while (!empty(st)) {
			a = pop(st);
			if (a < min) push(st2, a, err3);
		}
		if (empty(st2)) cout << "Таких элементов нет!" << endl;
		else {
			cout << "Полученный стек: ";
			print(st2, err3);
		}
		delete[] st2.data;
	}

	delete[] st.data;
	delete[] q.data;

	system("pause");
	return 0;
}