#include <iostream>
#include <time.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	const int n = 10;
	int nums[]{ 1,2,3,4,5,6,7,8,9,0 };

	for (int x : nums) {
		while (x <= 1) {
			x /= 3;
		}
		if (x = 1) { cout « "степень тройки"; }
		else { cout « "нет"; }


	}



	system("pause");
	return 0;
}