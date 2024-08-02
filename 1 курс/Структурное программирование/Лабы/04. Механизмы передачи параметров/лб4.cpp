#include <iostream>
using namespace std;

double row1(double x, double e) {
	double sum = x;
	int n = 1;
	bool f = 0;
	while (f == 0) {
		n++;
		sum -= (pow(x, 2 * n - 1)) / (2 * n - 1);
		if (fabs((pow(x, 2 * n - 1)) / (2 * n - 1)) < e) f++;
	}
	return sum;
};

void row2(double* x2, double* e2, double* s2) {
	double sum = *x2;
	int n = 1;
	bool f = 0;
	while (f == 0) {
		n++;
		sum -= (pow(*x2, 2 * n - 1)) / (2 * n - 1);
		if (fabs((pow(*x2, 2 * n - 1)) / (2 * n - 1)) < *e2) f++;
	}
	s2 = &sum;
	cout << *s2 << endl;
};

double row3(double& x, double& e) {
	double sum = x;
	int n = 1;
	bool f = 0;
	while (f == 0) {
		n++;
		sum -= (pow(x, 2 * n - 1)) / (2 * n - 1);
		if (fabs((pow(x, 2 * n - 1)) / (2 * n - 1)) < e) f++;
	}
	return sum;
};

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	double x = 0.1, e = 0.5 * pow(10, -4), sum = 0;
	cout << "Введите номер задания: "; cin >> n;
	switch (n) {
	case 1: cout << row1(x, e) << endl; break;
	case 2: row2(&x, &e, &sum); break;
	case 3: cout << row3(x, e) << endl; break;
	default: cout << "Такого задания нет" << endl;
	}
	system("pause");
	return 0;
}