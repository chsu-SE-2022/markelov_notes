#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "�� ����� ������ �� ������ � �����?" << endl;
	cin >> n;
	switch (n) {
	case 1: cout << "����� ����!" << endl; break;
	case 2: cout << "��������, �� ����� ���������� �����" << endl; break;
	case 3: cout << "����� ���� ��������� �����!" << endl; break;
	case 4: cout << "�������� - ��� ����� �������" << endl; break;
	case 5: cout << "�������!" << endl; break;
	default: cout << "������, �� �� �� ������" << endl;
	}
	cout << "������� � ���� ������� ���?" << endl;
	cin >> n;
	switch (n) {
	case 0: cout << "���, ��������!" << endl; break;
	case 1: cout << "����� ����? ��� ���� ����" << endl; break;
	case 2: cout << "��� ������" << endl; break;
	case 3: cout << "��� ���������" << endl; break;
	case 4: cout << "��� �����" << endl; break;
	default: cout << "����� ����!" << endl;
	}
	cout << "���� �������� ������� � ���? (�� - 1/��� - 0)" << endl;
	cin >> n;
	switch (n) {
	case 1: cout << "��� ����" << endl; break;
	case 0: cout << "����" << endl; break;
	default: cout << "� ���� �� �������" << endl;
	}
	cout << "����� ���� ���������� �� 5-������� �����" << endl;
	cin >> n;
	switch (n) {
	case 1: cout << "��� ����� ����" << endl; break;
	case 2: cout << "�������" << endl; break;
	case 3: cout << "������� ����� ����� �� 5" << endl; break;
	case 4: cout << "�������!" << endl; break;
	case 5: cout << "�������!" << endl;
	default: {
		if (n <= 0) cout << "�� �������������!!!" << endl;
		if (n > 5) cout << "��� ����� �������!!!" << endl;
	}
	}
	cout << "������� ����� 2+2*2?" << endl;
	cin >> n;
	switch (n) {
	case 6: cout << "���������!" << endl; break;
	case 8: cout << "���� ����� ��������� � �����" << endl; break;
	default: cout << "�� ������ ����������� ��������" << endl;
	}
	system("pause");
	return 0;
}