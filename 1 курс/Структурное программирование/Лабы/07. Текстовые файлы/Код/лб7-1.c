#include <iostream>
using namespace std;

int main() {
	FILE* f = fopen("input.txt", "w+t");
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= i; j++)
			fprintf(f, "%d", i);
		fprintf(f, "\n");
	}
	fclose(f);

	char a[100];
	f = fopen("input.txt", "r+t");
	for (int i = 1; i <= 9; i++) {
		fgets(a, 100, f);
		printf("%s", a);
	}
	fclose(f);
	system("pause");
	return 0;
}
