#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "На какие оценки ты учился в школе?" << endl;
	cin >> n;
	switch (n) {
	case 1: cout << "Какой ужас!" << endl; break;
	case 2: cout << "Наверное, ты часто прогуливал уроки" << endl; break;
	case 3: cout << "Нужно было стараться лучше!" << endl; break;
	case 4: cout << "Четверка - это почти пятерка" << endl; break;
	case 5: cout << "Молодец!" << endl; break;
	default: cout << "Похоже, ты не из России" << endl;
	}
	cout << "Сколько у тебя сегодня пар?" << endl;
	cin >> n;
	switch (n) {
	case 0: cout << "Ура, выходной!" << endl; break;
	case 1: cout << "Всего одна? Это даже мало" << endl; break;
	case 2: cout << "Это хорошо" << endl; break;
	case 3: cout << "Это нормально" << endl; break;
	case 4: cout << "Это много" << endl; break;
	default: cout << "Какой ужас!" << endl;
	}
	cout << "Тебе нравится учиться в ЧГУ? (Да - 1/Нет - 0)" << endl;
	cin >> n;
	switch (n) {
	case 1: cout << "Мне тоже" << endl; break;
	case 0: cout << "Жаль" << endl; break;
	default: cout << "Я тебя не понимаю" << endl;
	}
	cout << "Оцени свое настроение по 5-бальной шкале" << endl;
	cin >> n;
	switch (n) {
	case 1: cout << "Мне очень жаль" << endl; break;
	case 2: cout << "Грустно" << endl; break;
	case 3: cout << "Надеюсь скоро будет на 5" << endl; break;
	case 4: cout << "Здорово!" << endl; break;
	case 5: cout << "Классно!" << endl;
	default: {
		if (n <= 0) cout << "Не расстраивайся!!!" << endl;
		if (n > 5) cout << "Это очень здорово!!!" << endl;
	}
	}
	cout << "Сколько будет 2+2*2?" << endl;
	cin >> n;
	switch (n) {
	case 6: cout << "Правильно!" << endl; break;
	case 8: cout << "Тебе стоит вернуться в школу" << endl; break;
	default: cout << "Ты совсем неправильно считаешь" << endl;
	}
	system("pause");
	return 0;
}