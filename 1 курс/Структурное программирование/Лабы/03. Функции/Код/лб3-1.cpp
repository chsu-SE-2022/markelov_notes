#include <iostream>
using namespace std;

double s_prizm(double a, double b, double c);

int main() {
	setlocale(LC_ALL, "Russian");
	double a, b, c;
	cout << "������� ����� ��������� ������: ";
	cin >> a;
	cout << "������� ������ ��������� ������: ";
	cin >> b;
	cout << "������� ������ ������: ";
	cin >> c;
	if (a <= 0 || b <= 0 || c <= 0) cout << "������� ������ ������ ���� ������ ����" << endl;
	else cout << "������� ����������� ������: " << s_prizm(a, b, c) << endl;
	system("pause");
	return 0;
}
double s_prizm(double a, double b, double c) {
	return 2 * (a*b + a*c + b*c);
}