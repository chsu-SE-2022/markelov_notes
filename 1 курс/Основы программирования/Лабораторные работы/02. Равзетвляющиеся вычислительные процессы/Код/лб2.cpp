#include <iostream>
using namespace std;

int main() {
	int n;
	cout << "Enter number a program: "; cin >> n;
	switch (n) {

	case 1: {
		int h, m, s;
		cout << "Enter hours: "; cin >> h;
		cout << "Enter minutes: "; cin >> m;
		cout << "Enter seconds: "; cin >> s;
		if (h < 24 && m < 60 && s < 60 && h >= 0 && m >= 0 && s >= 0) {
			if (s >= 30) m++;
			if (m == 60) {
				h++;
				m = 0;
			}
			if (h == 24) h = 0;
			if (m >= 10) cout << h << ":" << m << endl;
			else cout << h << ":0" << m << endl;
			if (m >= 30) h++;
			cout << h << endl;
		}
		else cout << "Error!" << endl;
	}
		  break;

    case 2: {
		int n, n1, n2, n3, n4;
		cout << "n="; cin >> n;
		if (n >= 0 && n <= 9999) {
			n1 = n % 10;
			n = n / 10;
			n2 = n % 10;
			n = n / 10;
			n3 = n % 10;
			n = n / 10;
			n4 = n % 10;
			if (n1 == n4 && n2 == n3) cout << "Palindrome" << endl;
			else cout << "Not a palindrome" << endl;
		}
		else cout << "Error!" << endl;
    }
		  break;

	case 3: {
		double x = -2, y = 0.59, z = -4.8;
		double t = pow(3, -x + 1) * sin(x);
		double u = log(y + pow(z, 2)) + pow(sin(z / y), 2);
		cout << "t=" << t << endl; cout << "u=" << u << endl;
		bool a;
		if (t > u) a = true;
		else a = false;
		if (a == true) cout << "True" << endl;
		else if (t != u) cout << "False" << endl;
	}
		  break;

	default: cout << "No such program" << endl;
	}

	system("pause");
	return 0;
}