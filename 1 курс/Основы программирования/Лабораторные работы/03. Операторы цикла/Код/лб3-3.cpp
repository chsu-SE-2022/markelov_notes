#include <iostream>
using namespace std;

int main() {
	int n, k;
	double x, z=0;
	cout << "k="; cin >> k;
	cout << "x="; cin >> x;
	for (n = 1; n <= k + 1; n++) z+= sin(2 * n - 1) * pow(x, n);
	cout << "z=" << z << endl;
	system("pause");
	return 0;
}