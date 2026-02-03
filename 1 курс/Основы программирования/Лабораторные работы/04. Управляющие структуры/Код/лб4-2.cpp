#include <iostream>
using namespace std;

int main() {
	int i,j,n,k;
	cout << "n="; cin >> n;
	for (i = 1; i <= n; i++) {
		j = i; k = n;
		while (j > 0) {
			cout << k << " ";
			k--; j--;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}