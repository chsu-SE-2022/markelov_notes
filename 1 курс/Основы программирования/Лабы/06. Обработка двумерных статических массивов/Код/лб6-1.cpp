#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	const int n = 5;
	int a[n][n];
	for (int i = 0; i < n; i++) {
		cout << "������� �� ������� �������� " << i << " ������:" << endl;
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	int g = a[0][0], p = a[0][n - 1];
	for (int i = 0; i < n; i++) {
		if (a[i][i] > g) g = a[i][i];
		if (a[i][n - i - 1] > p) p = a[i][n - i - 1];
	}
	cout << "���������� ������� ������� ���������: " << g << endl;
	cout << "���������� ������� �������� ���������: " << p << endl;
	cout << "���������� ������� ����� ����� ����������: ";
	if (g > p) cout << g << endl;
	else cout << p << endl;
	system("pause");
	return 0;
}