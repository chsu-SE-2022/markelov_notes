#include <iostream>
using namespace std;

struct AEROFLOT {
	string city, date, time;
};

int main() {
	setlocale(LC_ALL, "Russian");
	const int n = 5;
	AEROFLOT a[n];
	for (int i = 0; i < n; i++) {
		cout << "���� �" << i+1 << endl;
		cout << "������� �����: ";
		cin >> a[i].city;
		cout << "������� ����: ";
		cin >> a[i].date;
		cout << "������� �����: ";
		cin >> a[i].time;
	}
	cout << endl;
	string date;
	int k = 0;
	cout << "������� ������ ����: ";
	cin >> date;
	for (int i = 0; i < n; i++) {
		if (date == a[i].date) {
			cout << a[i].time << ' ' << a[i].city << endl;
			k++;
		}
	}
	if (k == 0)
		cout << "� ���� ���� ��� ������";
	system("pause");
	return 0;
}