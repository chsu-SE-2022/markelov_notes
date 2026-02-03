#include <iostream>
#include <time.h>
using namespace std;

const int n1 = 6, n2 = 9;
int a[n1][n2];
double b[n1][n2];
char c[n1][n2];
double m;

void array_input(int* a, int n1, int n2) {
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			a[i * n2 + j] = rand() % 1000 - 500;
};

void array_input(double* a, int n1, int n2) {
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			a[i * n2 + j] = rand() / 1000.0 - 500;
};

void array_input(char* a, int n1, int n2) {
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			a[i * n2 + j] = rand() % 1000 - 500;
};

void array_output(int* a, int n1, int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++)
			cout << a[i * n2 + j] << "  ";
		cout << endl;
	}
	cout << endl;
};

void array_output(double* a, int n1, int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++)
			cout << a[i * n2 + j] << "  ";
		cout << endl;
	}
	cout << endl;
};

void array_output(char* a, int n1, int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++)
			cout << a[i * n2 + j] << "  ";
		cout << endl;
	}
	cout << endl;
};

void array_swap(int* a, int n1, int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2 - 2; j += 4) {
			m = a[i * n2 + j];
			a[i * n2 + j] = a[i * n2 + j + 2];
			a[i * n2 + j + 2] = m;
		}
		for (int j = 1; j < n2 - 2; j += 4) {
			m = a[i * n2 + j];
			a[i * n2 + j] = a[i * n2 + j + 2];
			a[i * n2 + j + 2] = m;
		}
	}
}

void array_swap(double* a, int n1, int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2 - 2; j += 4) {
			m = a[i * n2 + j];
			a[i * n2 + j] = a[i * n2 + j + 2];
			a[i * n2 + j + 2] = m;
		}
		for (int j = 1; j < n2 - 2; j += 4) {
			m = a[i * n2 + j];
			a[i * n2 + j] = a[i * n2 + j + 2];
			a[i * n2 + j + 2] = m;
		}
	}
}

void array_swap(char* a, int n1, int n2) {
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2 - 2; j += 4) {
			m = a[i * n2 + j];
			a[i * n2 + j] = a[i * n2 + j + 2];
			a[i * n2 + j + 2] = m;
		}
		for (int j = 1; j < n2 - 2; j += 4) {
			m = a[i * n2 + j];
			a[i * n2 + j] = a[i * n2 + j + 2];
			a[i * n2 + j + 2] = m;
		}
	}
}

int main() {
	srand(time(0));
	array_input(&a[0][0], n1, n2);
	array_output(&a[0][0], n1, n2);
	array_swap(&a[0][0], n1, n2);
	array_output(&a[0][0], n1, n2);

	array_input(&b[0][0], n1, n2);
	array_output(&b[0][0], n1, n2);
	array_swap(&b[0][0], n1, n2);
	array_output(&b[0][0], n1, n2);

	array_input(&c[0][0], n1, n2);
	array_output(&c[0][0], n1, n2);
	array_swap(&c[0][0], n1, n2);
	array_output(&c[0][0], n1, n2);
	system("pause");
	return 0;
}