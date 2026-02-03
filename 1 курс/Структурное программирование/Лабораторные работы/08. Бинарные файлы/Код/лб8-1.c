#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	float a;
	printf("Текст файла:\n");
	FILE* f;
	f = fopen("input.txt", "w+b");
	for (int i = 1; i <= 10; i++) {
		a = rand() / 100.0 - 150;
		fwrite(&a, sizeof(a), 1, f);
	}
	fclose(f);

	f = fopen("input.txt", "r+b");
	for (int i = 1; i <= 10; i++) {
		fread(&a, sizeof(a), 1, f);
		printf("%f\n", a);
	}
	fclose(f);

	float b; int c = 0;
	printf("Введите число: ");
	scanf("%f", &b);

	f = fopen("input.txt", "r+b");
	for (int i = 1; i <= 10; i++) {
		fread(&a, sizeof(a), 1, f);
		if (a<b) c++;
	}
	fclose(f);

	printf("Количество элементов, меньших %f: %i\n", b, c);
	system("pause");
	return 0;
}