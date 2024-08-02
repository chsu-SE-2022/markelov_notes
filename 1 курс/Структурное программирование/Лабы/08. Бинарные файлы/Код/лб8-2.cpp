#include <iostream>
#include <fstream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int a[3][3], n, k = 0;
	ofstream f1;
	f1.open("f.txt", ios::binary | ios::out);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			a[i][j] = rand() % 100 - 50;
			f1.write((char*)&a[i][j], sizeof(a));
		}
	f1.close();

	ifstream f2;
	f2.open("f.txt", ios::binary | ios::in);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			f2.read((char*)&a[i][j], sizeof(a));
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
	f2.close();

	ofstream g1;
	g1.open("g.txt", ios::binary | ios::out);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (a[i][j] < 0) {
				g1.write((char*)&a[i][j], sizeof(n));
				k++;
			}
	g1.close();

	ifstream g2;
	g2.open("g.txt", ios::binary | ios::in);
	if (k == 0) cout << "Отрицательных элементов нет" << endl;
	else {
		cout << "Отрицательные элементы массива:" << endl;
		for (int i = 0; i < k; i++) {
			g2.read((char*)&n, sizeof(n));
			cout << n << endl;
		}
	}
	g2.close();

	system("pause");
	return 0;
}