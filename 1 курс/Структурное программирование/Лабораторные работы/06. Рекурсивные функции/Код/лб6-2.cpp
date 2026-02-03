#include <iostream>
#include <time.h>
using namespace std;

int i = 0;

void array_input(int n, double* a) {
	a[i] = rand() / 100.0 - 50;
	i++;
	if (i < n) array_input(n, a);
	else i = 0;
};
void array_output(int n, double* a) {
	cout << a[i] << "  ";
	i++;
	if (i < n) array_output(n, a);
	else i = 0;
};

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int n, kp = 0, ko = 0;
	double p=1, o=1;
	cout << "Введите количество элементов массива: ";  cin >> n;
	double* a = new double[n];
	array_input(n, a);
	array_output(n, a);
	cout << endl;
	for (int i = 0; i < n; i++) {
		if (a[i] > 0) { 
			p *= a[i];
			kp++;
		}
		else if (a[i] < 0) { 
			o *= a[i]; 
			ko++;
		}
	}
	if (kp == 0) p = 0;
	if (ko == 0) o = 0;
	cout << "Произведение положительных элементов: " << p << endl;
	cout << "Произведение отрицательных элементов: " << o << endl;
	o = fabs(o);
	if (p > o) cout << "Модуль произведения положительных чисел больше" << endl;
	else if (p < o) cout << "Модуль произведения отрицательных чисел больше" << endl;
	else cout << "Модули произведений положительных и отрицательных чисел одинаковы" << endl;
	delete[] a;
	system("pause");
	return 0;
}