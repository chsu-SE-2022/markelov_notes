#include <iostream>
#include <time.h>
using namespace std;

int main() {
	srand(time(0));
	int n;
	double p=1, o=1;
	cout << "n=";  cin >> n;
	double* a = new double[n];
	for (int i = 0; i < n; i++)
		a[i] = rand() / 100.0 - 50;
	for (int i = 0; i < n; i++)
		cout << a[i] << "  ";
	cout << endl;
	for (int i = 0; i < n; i++) {
		if (a[i] > 0) p *= a[i];
		else if (a[i] < 0) o *= a[i];
	}
	cout << "Positive: " << p << endl;
	cout << "Negative: " << o << endl;
	o = fabs(o);
	if (p > o) cout << "Positive" << endl;
	else if (p < o) cout << "Negative" << endl;
	else cout << "Equally" << endl;
	delete[] a;
	system("pause");
	return 0;
}