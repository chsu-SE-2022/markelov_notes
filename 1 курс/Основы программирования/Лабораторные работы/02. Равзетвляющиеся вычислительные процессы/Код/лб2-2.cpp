#include <iostream>
using namespace std;

int main() {
	int n, n1, n2, n3, n4;
	cout << "n="; cin >> n;
	if (n>=0 && n<=9999) {
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

	system("pause");
	return 0;
}