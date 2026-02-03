#include <iostream>

int main() {
	printf("x="); scanf("%lf", &x);
	printf("y="); scanf("%lf", &y);
	printf("z="); scanf("%lf", &z);
	t = pow(3, -x + 1) * sin(x);
	u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
	printf("t=%e\n", t); printf("u=%lf\n", u);

	system("pause");
	return 0;
}