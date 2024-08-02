#include <iostream>
#include <time.h>
using namespace std;

void array_input(int n, double* a);
void array_output(int n, double* a);

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int n, kp = 0, ko = 0;
	double p=1, o=1;
	cout << "������� ���������� ��������� �������: ";  cin >> n;
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
	cout << "������������ ������������� ���������: " << p << endl;
	cout << "������������ ������������� ���������: " << o << endl;
	o = fabs(o);
	if (p > o) cout << "������ ������������ ������������� ����� ������" << endl;
	else if (p < o) cout << "������ ������������ ������������� ����� ������" << endl;
	else cout << "������ ������������ ������������� � ������������� ����� ���������" << endl;
	delete[] a;
	system("pause");
	return 0;
}

void array_input(int n, double* a) {
	for (int i = 0; i < n; i++)
		a[i] = rand() / 100.0 - 50;
		//cin >> a[i];
}

void array_output(int n, double* a) {
	for (int i = 0; i < n; i++)
		cout << a[i] << "  ";
}