#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int m, n, min;
	cout << "m="; cin >> m;
	cout << "n="; cin >> n;
	int** a = new int* [m];
	for (int i = 0; i < m; i++)
		a[i] = new int[n];
	for (int i = 0; i < m; i++) {
		cout << "¬ведите по очереди элементы " << i << " строки:" << endl;
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	for (int j = 1; j < n; j+=2) {
		min = a[0][j];
		for (int i = 0; i < m; i++)
			if (a[i][j] < min) min = a[i][j];
		cout << min << endl;
	}
	for (int i = 0; i < m; i++) delete[] a[i];
	delete[] a;
	system("pause");
	return 0;
}