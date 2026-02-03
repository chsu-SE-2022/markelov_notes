#include <iostream>
using namespace std;

int main() {
	double x = 25.43, y = 40.08, z = 32.3;
	double t = pow(3, -x + 1) * sin(x);
	double u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
	cout << "x=" << x << endl; cout << "y=" << y << endl; cout << "z=" << z << endl;
	cout << "t=" << t << endl; cout << "u=" << u << endl;

	system("pause");
	return 0;
}