#include <iostream>
using namespace std;

double s_prizm(double a, double b, double c);

int main() {
	setlocale(LC_ALL, "Russian");
	double a, b, c;
	cout << "Введите длину основания призмы: ";
	cin >> a;
	cout << "Введите ширину основания призмы: ";
	cin >> b;
	cout << "Введите высоту призмы: ";
	cin >> c;
	if (a <= 0 || b <= 0 || c <= 0) cout << "Стороны призмы должны быть больше нуля" << endl;
	else cout << "Площадь поверхности призмы: " << s_prizm(a, b, c) << endl;
	system("pause");
	return 0;
}
double s_prizm(double a, double b, double c) {
	return 2 * (a*b + a*c + b*c);
}