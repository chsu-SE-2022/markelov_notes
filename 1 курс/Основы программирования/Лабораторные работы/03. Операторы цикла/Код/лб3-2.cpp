#include <iostream>
using namespace std;

int main() {
	int i=1000;
	while (i<=9999) {
		if (i % 133 == 125 && i % 134 == 111) 
			cout << i << endl;
		i++;
	}

	system("pause");
	return 0;
}
