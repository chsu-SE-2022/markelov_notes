#include <iostream>
#include <time.h>
using namespace std;

int main() {
	srand(time(0));
	const int n1 = 6, n2 = 8;
	int a[n1][n2];
	int m;
	for (int i=0; i < n1; i++)
		for (int j=0; j < n2; j++)
			a[i][j] = rand() % 1000 - 500;
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2 - 2; j += 4) {
			m = a[i][j];
			a[i][j] = a[i][j + 2];
			a[i][j + 2] = m;
		}
	for (int i = 0; i < n1; i++)
		for (int j = 1; j < n2 - 2; j += 4) {
			m = a[i][j];
			a[i][j] = a[i][j + 2];
			a[i][j + 2] = m;
		}
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	system("pause");
	return 0;
}