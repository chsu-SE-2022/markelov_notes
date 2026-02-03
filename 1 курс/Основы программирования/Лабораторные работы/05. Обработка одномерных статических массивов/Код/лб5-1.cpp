#include <iostream>
#include <time.h>
using namespace std;

int main() {
	srand(time(0));
	const int n = 10;
	int s = 0;
	char a[n];
	for (int i = 0; i < n; i++)
		a[i] = rand();
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		if (a[i] == '0' || a[i] == '1' || a[i] == '2' || a[i] == '3' || a[i] == '4' || a[i] == '5' || a[i] == '6' || a[i] == '7' || a[i] == '8' || a[i] == '9') s++;
	cout << s << endl;

	system("pause");
	return 0;
}
