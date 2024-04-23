#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct node {
	string word;           //слово
	int k;                 //сколько раз встретилось слово
	node* left;            //указатель на левое поддерево
	node* right;           //указатель на правое поддерево
};

void insert(node*& root, string word, int& count) {     //построение дерева
	if (root == NULL) {
		root = new node;
		root->word = word;
		root->k = 1;
		count++;
		root->left = NULL;
		root->right = NULL;
	}
	else if (word < root->word) { 
		insert(root->left, word, count); 
	}
	else if (word > root->word) { 
		insert(root->right, word, count); 
	}
	else root->k++;
}

void printTree(node* root, int count, ofstream& result) {           //вывод дерева в алфавитном порядке
	if (root != NULL) {
		printTree(root->left, count, result);
		if (count <= 50) cout << root->word << " - " << root->k << endl;
		else result << root->word << " - " << root->k << endl; 
		printTree(root->right, count, result);
	}
}

void arrayTree(node* root, node**& nodes, int& index, int& capacity) {       //запись дерева в массив
	if (root != NULL) {
		arrayTree(root->left, nodes, index, capacity);
		if (index == capacity) {
			capacity *= 2;
			node** temp = new node * [capacity];
			for (int i = 0; i < index; ++i) {
				temp[i] = nodes[i];
			}
			delete[] nodes;
			nodes = temp;
		}
		nodes[index++] = root;
		arrayTree(root->right, nodes, index, capacity);
	}
}

void sortTree(node** nodes, int size) {            //сортировка массива по частоте
	for (int i = 0; i < size - 1; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (nodes[i]->k < nodes[j]->k) {
				node* temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
}

void printSortTree(node** nodes, node* root, int size, int count, ofstream& result) {       //вывод дерева в частотном порядке
	for (int i = 0; i < size; ++i) {
		if (count <= 50) cout << nodes[i]->word << " - " << nodes[i]->k << endl;
		else result << nodes[i]->word << " - " << nodes[i]->k << endl;
	}
}

node* search(node* root, string word) {       //поиск
	if (root == NULL || root->word == word) return root;
	if (word < root->word) return search(root->left, word);
	else return search(root->right, word);
}

void lengthSearch(node* root, int length, int count, ofstream& result) {      //фильтрация по количеству букв
	if (root != NULL) {
		lengthSearch(root->left, length, count, result);
		if (root->word.length() == length) {
			if (count <= 50) cout << root->word << " - " << root->k << endl;
			else result << root->word << " - " << root->k << endl; 
		}
		lengthSearch(root->right, length, count, result);
	}
}

bool symbol(char c) {      //проверка символа
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я');
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Программа строит дерево для файла. Пожалуйста, подождите..." << endl;
	ifstream f("voina-i-mir3.txt");
	if (!f.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return 0;
	}
	node* root = NULL;
	string word;
	char c;
	int capacity = 1000, count = 0;
	node** nodes = new node* [capacity];
	int index = 0;
	while (f.get(c)) {
		if (symbol(c)) {
			//c = tolower(c);    //убрать символ комментария, чтобы не учитывать регистр
			word += c;
		}
		else {
			if (!word.empty()) {
				insert(root, word, count);
				word.clear();
			}
		}
	}
	if (!word.empty()) {
		insert(root, word, count);
	}
	if (word.empty() && root == NULL) {
		cout << "Файл не содержит слов" << endl;
		return 0;
	}
	int n;
	cout << "Выберите режим работы программы:" << endl;
	cout << "1 - вывод словаря в алфавитном порядке" << endl;
	cout << "2 - вывод словаря в частотном порядке" << endl;
	cout << "3 - поиск по слову" << endl;
	cout << "4 - поиск по количеству букв" << endl;
	cin >> n;
	cin.ignore();
	ofstream result;
	result.open("result.txt");
	switch (n) {
	case 1: {
		if (count > 50) cout << "Результаты записываются в файл. Пожалуйста, подождите..." << endl;
		printTree(root, count, result);
		if (count > 50) cout << "Результаты записаны в файл result.txt" << endl;
	}
		break;
	case 2: {
		if (count > 50) cout << "Результаты записываются в файл. Пожалуйста, подождите..." << endl;
		arrayTree(root, nodes, index, capacity);
		sortTree(nodes, index);
		printSortTree(nodes, root, index, count, result);
		if (count > 50) cout << "Результаты записаны в файл result.txt" << endl;
	}
		  break;
	case 3: {
		string searchWord;
		cout << "Введите слово для поиска: ";
		cin >> searchWord;
		node* foundNode = search(root, searchWord);
		if (foundNode != NULL) {
			cout << "Слово \"" << searchWord << "\" встречается в файле " << foundNode->k << " раз" << endl;
		}
		else {
			cout << "Слово \"" << searchWord << "\" не найдено" << endl;
		}
	}
		  break;
	case 4: {
		int wordLength;
		cout << "Введите длину слова: ";
		cin >> wordLength;
		if (count > 50) cout << "Результаты записываются в файл. Пожалуйста, подождите..." << endl;
		lengthSearch(root, wordLength, count, result);
		if (count > 50) cout << "Результаты записаны в файл result.txt" << endl;
	}
		  break;
	default: cout << "Введен неверный номер" << endl;
		break;
	}
	
	delete[] nodes;
	f.close();
	result.close();
	system("pause");
}