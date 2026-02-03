#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int k = 0, n = 0;
	char str[100];
	cin >> str;
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		if (str[i] == ',') k = i + 1;
		if (str[i] == 'w' && (str[i + 1] == ',' || str[i + 1] == '\0')) {
			for (k; k <= i; k++, n++)
				cout << str[k];
			cout << endl;
		}
	}
	if (n == 0) cout << "Нет слов, заканчивающихся на букву w" << endl;
	system("pause");
	return 0;
}