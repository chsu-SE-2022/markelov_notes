#include <iostream>
using namespace std;

int main() {
	__int64 i, j = 0, m, n, d, p = 1;
	cout << "m="; cin >> m;
	cout << "n="; cin >> n;
	for (m; m <= n; m++) {
		for (i = 1; i <= m; i++)
			if (m % i == 0) p *= i;
		d = p;
		while (d > 0) {
			j++;
			d /= 10;
		}
		if (p % j == 0) cout << m << endl;
		p = 1; j = 0;
	}
	system("pause");
	return 0;
}