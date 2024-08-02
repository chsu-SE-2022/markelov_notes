#include <iostream>
using namespace std;
int main() {

	cout << "Program 1" << endl;
	double x = 25.43, y = 40.08, z = 32.3;
	double t = pow(3, -x + 1) * sin(x);
	double u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
	cout << "x=" << x << endl; cout << "y=" << y << endl; cout << "z=" << z << endl;
	cout << "t=" << t << endl; cout << "u=" << u << endl;

	cout << "Program 2" << endl;
	cout << "x="; cin >> x;
	cout << "y="; cin >> y;
	cout << "z="; cin >> z;
	t = pow(3, -x + 1) * sin(x);
	u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
	cout << "t=" << t << endl; cout << "u=" << u << endl;

	printf("%s \n", "Program 3");
	printf("x="); scanf("%lf", &x);
	printf("y="); scanf("%lf", &y);
	printf("z="); scanf("%lf", &z);
	t = pow(3, -x + 1) * sin(x);
	u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
	printf("t=%e\n", t); printf("u=%lf\n", u);

	system("pause");
	return 0;
}
