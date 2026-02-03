#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream f1;
	f1.open("input.txt");
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= i; j++)
			f1 << i;
		f1 << endl;
	}
	f1.close();

	
	ifstream f2;
	int a;
	f2.open("input.txt");
	for (int i = 1; i <= 9; i++) {
		f2 >> a;
		cout << a << endl;
	}
	f2.close();
	system("pause");
	return 0;
}
