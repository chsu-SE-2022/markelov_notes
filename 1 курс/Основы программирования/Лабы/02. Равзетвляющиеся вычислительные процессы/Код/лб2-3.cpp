#include <iostream>
using namespace std;

int main() {
	double x = -2, y = 0.59, z = -4.8;
	double t = pow(3, -x + 1) * sin(x);
	double u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
	cout << "t=" << t << endl; cout << "u=" << u << endl;
	bool a;
	if (t > u) a=true;
	else a = false;
	if (a == true) cout << "True" << endl;
	else if (t != u) cout << "False" << endl;

	system("pause");
	return 0;
}