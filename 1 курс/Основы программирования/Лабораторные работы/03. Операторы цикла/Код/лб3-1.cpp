#include <iostream>
using namespace std;

int main() {
	int i;
	for (i = 1000; i <= 9999; i++) 
		if (i % 133 == 125 && i % 134 == 111) 
			cout << i << endl;

	system("pause");
	return 0;
}