#include <iostream>
#include <fstream>
using namespace std;

void search(int n) {
	int comb[20], count = 0, count2 = 0;
	ofstream result;
	if (n > 6) result.open("result.txt");

	for (int i = 0; i < pow(2, n); i++) {
		int k = i;
		for (int j = 0; j < n; j++) {
			comb[j] = k % 2;
			k /= 2;
		}
		count = 0;
		for (int j = 0; j < n; j++) {
			if (comb[j] == 0) count++;
			else count--;
			if (count < 0) break;
		}
		if (count == 0 && n <= 6) {
			count2++;
			for (int j = 0; j < n; j++) {
				if (comb[j] == 0) cout << '(';
				else cout << ')';
			}
			cout << endl;
		}
		if (count == 0 && n > 6) {
			count2++;
			for (int j = 0; j < n; j++) {
				if (comb[j] == 0) result << '(';
				else result << ')';
			}
			result << endl;
		}
	}

	if (count2 == 0) cout << "Таких выражений нет!" << endl;
	else if (n > 6) {
		cout << "Результаты доступны в файле result.txt" << endl;
	}
	if (n > 6) result.close();

}

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите количество скобок: ";
	cin >> n;
	if (n > 20 || n < 1)
		cout << "Ошибка! Введено недопустимое значение N" << endl;
	else search(n);
	system("pause");
	return 0;
}