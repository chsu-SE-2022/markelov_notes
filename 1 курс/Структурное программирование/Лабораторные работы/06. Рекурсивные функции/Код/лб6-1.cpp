#include <iostream>
using namespace std;

int p=1;

int not_recursion(int n) {
	while (n > 0) {
		p *= n % 10;
		n /= 10;
	}
	return p;
};

int int_recursion(int n) {
		p *= n % 10;
		n /= 10;
		if (n > 0) return int_recursion(n);
		else return p;
};

void void_recursion(int n) {
		p *= n % 10;
		n /= 10;
		if (n > 0) void_recursion(n);
		else cout << p << endl;
};

int main() {
	setlocale(LC_ALL, "Russian");
	int n, f;
	cout << "Введите число: "; cin >> n;
	cout << "Введите номер функции: "; cin >> f;
	switch (f) {
	case 1: cout << not_recursion(n) << endl; break;
	case 2: cout << int_recursion(n) << endl; break;
	case 3: void_recursion(n); break;
	default: cout << "Такой функции нет!" << endl;
	}
	system("pause");
	return 0;
}