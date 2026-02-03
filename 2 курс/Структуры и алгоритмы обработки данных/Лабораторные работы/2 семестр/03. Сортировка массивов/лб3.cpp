#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

void insertion(int* m, int n) {       //метод прямого включения
	for (int i = 1; i < n; i++) {
		int x = m[i], j = i;
		while (j != 0 && x < m[j - 1]) m[j] = m[j - 1], j--;
		m[j] = x;
	}
}

void shaker(int* m, int n) {          //шейкерная сортировка
	int left = 0, right = n - 1, k = right;
	do {
		for (int j = right; j >= left; j--)
			if (m[j] < m[j - 1]) {
				swap(m[j], m[j - 1]);
				k = j;
			}
		left = k + 1;

		for (int j = left; j <= right; j++)
			if (m[j] < m[j - 1]) {
				swap(m[j], m[j - 1]);
				k = j;
			}
		right = k - 1;
	} while (left <= right);
}

void shell(int* m, int n) {           //метод Шелла
	int step = n / 2;
	while (step > 0) {
		for (int i = 0; i < n - step; i++) {
			int j = i;
			while (j >= 0 && m[j] > m[j + step]) {
				swap(m[j], m[j + step]);
				j -= step;
			}
		}
		step /= 2;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	cout << "СОРТИРОВКА НЕБОЛЬШИХ МАССИВОВ" << endl;
	cout << "Исходный массив:" << endl;
	const int n = 10;
	int original[n], sorted[n];
	for (int i = 0; i < n; i++) {
		original[i] = rand() % 1000 - 500;
		cout << original[i] << ' ';
	}
	cout << endl;

	cout << "Метод прямого включения:" << endl;
	for (int i = 0; i < n; i++) {
		sorted[i] = original[i];
	}
	insertion(sorted, n);
	for (int i = 0; i < n; i++)
		cout << sorted[i] << ' ';
	cout << endl;

	cout << "Шейкерная сортировка:" << endl;
	for (int i = 0; i < n; i++) {
		sorted[i] = original[i];
	}
	shaker(sorted, n);
	for (int i = 0; i < n; i++)
		cout << sorted[i] << ' ';
	cout << endl;

	cout << "Метод Шелла:" << endl;
	for (int i = 0; i < n; i++) {
		sorted[i] = original[i];
	}
	shell(sorted, n);
	for (int i = 0; i < n; i++)
		cout << sorted[i] << ' ';
	cout << endl << endl;
	
	int m;
	double result[3][3];
	cout << "СОРТИРОВКА БОЛЬШИХ МАССИВОВ" << endl;
	cout << "Введите размер массива: ";
	cin >> m;
	if (m < 1) {
		cout << "Введен недопустимый размер массива!" << endl;
		return 0;
	}
	int* random = new int[m];
	int* random_sorted = new int[m];
	int* forward = new int[m];
	int* forward_sorted = new int[m];
	int* reverse = new int[m];
	int* reverse_sorted = new int[m];

	cout << "Рандомный массив" << endl;
	for (int i = 0; i < m; i++)
		random[i] = rand() % 1000 - 500;

	cout << "Метод прямого включения:" << endl;
	for (int i = 0; i < m; i++) {
		random_sorted[i] = random[i];
	}
	auto start = chrono::steady_clock::now();
	insertion(random_sorted, m);
	auto end = chrono::steady_clock::now();
	result[0][0] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[0][0] << " мс" << endl;

	cout << "Шейкерная сортировка:" << endl;
	for (int i = 0; i < m; i++) {
		random_sorted[i] = random[i];
	}
	start = chrono::steady_clock::now();
	shaker(random_sorted, m);
	end = chrono::steady_clock::now();
	result[1][0] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[1][0] << " мс" << endl;

	cout << "Метод Шелла:" << endl;
	for (int i = 0; i < m; i++) {
		random_sorted[i] = random[i];
	}
	start = chrono::steady_clock::now();
	shell(random_sorted, m);
	end = chrono::steady_clock::now();
	result[2][0] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[2][0] << " мс" << endl;

	cout << "Отсортированный массив" << endl;
	forward[0] = rand() % 1000 - 500;
	for (int i = 1; i < m; i++)
		forward[i] = forward[i - 1] + rand() % 10;

	cout << "Метод прямого включения:" << endl;
	for (int i = 0; i < m; i++) {
		forward_sorted[i] = forward[i];
	}
	start = chrono::steady_clock::now();
	insertion(forward_sorted, m);
	end = chrono::steady_clock::now();
	result[0][1] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[0][1] << " мс" << endl;

	cout << "Шейкерная сортировка:" << endl;
	for (int i = 0; i < m; i++) {
		forward_sorted[i] = forward[i];
	}
	start = chrono::steady_clock::now();
	shaker(forward_sorted, m);
	end = chrono::steady_clock::now();
	result[1][1] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[1][1] << " мс" << endl;

	cout << "Метод Шелла:" << endl;
	for (int i = 0; i < m; i++) {
		forward_sorted[i] = forward[i];
	}
	start = chrono::steady_clock::now();
	shell(forward_sorted, m);
	end = chrono::steady_clock::now();
	result[2][1] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[2][1] << " мс" << endl;

	cout << "Отсортированный в обратном порядке массив" << endl;
	reverse[0] = rand() % 1000;
	for (int i = 1; i < m; i++)
		reverse[i] = reverse[i - 1] - rand() % 10;

	cout << "Метод прямого включения:" << endl;
	for (int i = 0; i < m; i++) {
		reverse_sorted[i] = reverse[i];
	}
	start = chrono::steady_clock::now();
	insertion(reverse_sorted, m);
	end = chrono::steady_clock::now();
	result[0][2] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[0][2] << " мс" << endl;

	cout << "Шейкерная сортировка:" << endl;
	for (int i = 0; i < m; i++) {
		reverse_sorted[i] = reverse[i];
	}
	start = chrono::steady_clock::now();
	shaker(reverse_sorted, m);
	end = chrono::steady_clock::now();
	result[1][2] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[1][2] << " мс" << endl;

	cout << "Метод Шелла:" << endl;
	for (int i = 0; i < m; i++) {
		reverse_sorted[i] = reverse[i];
	}
	start = chrono::steady_clock::now();
	shell(reverse_sorted, m);
	end = chrono::steady_clock::now();
	result[2][2] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
	cout << result[2][2] << " мс" << endl;

	cout << "------------------------------------------------------------------------------------------\n";
	cout << "|         Метод         |     Рандомный     |    Отсортированный     |     Обратный      |\n";
	cout << "|Метод прямого включения|" << setw(13) << result[0][0] << "      |" << setw(15) << result[0][1] << "         |" << setw(13) << result[0][2] << "      |\n";
	cout << "|Шейкерная сортировка   |" << setw(13) << result[1][0] << "      |" << setw(15) << result[1][1] << "         |" << setw(13) << result[1][2] << "      |\n";
	cout << "|Метод Шелла            |" << setw(13) << result[2][0] << "      |" << setw(15) << result[2][1] << "         |" << setw(13) << result[2][2] << "      |\n";
	cout << "------------------------------------------------------------------------------------------\n";

	delete[] random;
	delete[] random_sorted;
	delete[] forward;
	delete[] forward_sorted;
	delete[] reverse;
	delete[] reverse_sorted;
	system("pause");
	return 0;
}