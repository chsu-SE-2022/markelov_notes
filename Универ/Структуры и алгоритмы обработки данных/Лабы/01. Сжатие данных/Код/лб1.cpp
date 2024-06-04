#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"

using namespace std;

// Структура для узла дерева Хаффмана
class HuffmanNode {
public:
    unsigned char data; //символ
    size_t frequency; //частота
    HuffmanNode* left; //указатель на левое поддерево
    HuffmanNode* right; //указатель на правое поддерево

    // Конструктор для создания узла дерева
    HuffmanNode(unsigned char data, size_t frequency) {
        this->data = data;
        this->frequency = frequency;
        this->left = NULL;
        this->right = NULL;
    }

    // Перегрузка оператора < для использования при сортировке узлов
    bool operator<(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }

    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Функция для построения дерева Хаффмана
HuffmanNode* buildHuffmanTree(const size_t* frequency, const int size) {
    // Создание массива указателей на узлы
    HuffmanNode** trees = new HuffmanNode * [size];

    // Заполнение массива узлами
    for (int i = 0; i < size; ++i) {
        trees[i] = new HuffmanNode(static_cast<unsigned char>(i), frequency[i]);
    }

    // Построение дерева Хаффмана
    while (true) {
        int minIdx1 = -1, minIdx2 = -1;
        for (int i = 0; i < size; ++i) {
            if (trees[i] != NULL) {
                if (minIdx1 == -1 || trees[i]->frequency < trees[minIdx1]->frequency) {
                    minIdx2 = minIdx1;
                    minIdx1 = i;
                }
                else if (minIdx2 == -1 || trees[i]->frequency < trees[minIdx2]->frequency) {
                    minIdx2 = i;
                }
            }
        }

        if (minIdx2 == -1) {
            break;
        }

        HuffmanNode* tmp = new HuffmanNode(0, trees[minIdx1]->frequency + trees[minIdx2]->frequency);
        tmp->left = trees[minIdx1];
        tmp->right = trees[minIdx2];
        trees[minIdx1] = tmp;
        trees[minIdx2] = NULL;
    }

    // Находим корень дерева
    HuffmanNode* root = NULL;
    for (int i = 0; i < size; ++i) {
        if (trees[i] != NULL) {
            root = trees[i];
            break;
        }
    }

    delete[] trees;
    return root;
}

// Функция для построения таблицы кодов Хаффмана
void buildHuffmanCodes(HuffmanNode* root, const string& code, string codes[]) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->data] = code;
    }

    buildHuffmanCodes(root->left, code + "0", codes);
    buildHuffmanCodes(root->right, code + "1", codes);
}

// Функция для сжатия файла
void compressFile(const string& inputFile, const string& outputFile) {
    // Открытие входного файла
    ifstream inFile(inputFile, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Ошибка открытия входного файла" << endl;
        return;
    }

    // Получение размера исходного файла
    inFile.seekg(0, ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);

    // Подсчет частоты вхождения каждого байта в файле
    size_t frequency[256] = { 0 };
    unsigned char byte;
    while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        frequency[byte]++;
    }

    // Построение дерева Хаффмана
    HuffmanNode* root = buildHuffmanTree(frequency, 256);

    // Построение таблицы кодов Хаффмана
    string codes[256];
    buildHuffmanCodes(root, "", codes);

    // Закрытие входного файла
    inFile.close();

    // Открытие выходного файла для записи архива
    ofstream outFile(outputFile, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия выходного файла" << endl;
        delete root;
        return;
    }

    cout << "Идет архивация файла. Пожалуйста, подождите..." << endl;

    // Запись размера исходного файла в архив
    outFile.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));

    // Запись заголовка в выходной файл
    for (int i = 0; i < 256; ++i) {
        outFile.write(reinterpret_cast<char*>(&frequency[i]), sizeof(size_t));
    }

    // Переоткрытие входного файла для сжатия
    inFile.open(inputFile, ios::binary);

    // Сжатие данных и запись их в выходной файл
    string buffer;
    while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        buffer += codes[byte];
        while (buffer.size() >= 8) {
            unsigned char compressedByte = 0;
            for (int i = 0; i < 8; ++i) {
                if (buffer[i] == '1') {
                    compressedByte += static_cast<unsigned char>(pow(2, 7 - i));
                }
            }
            outFile.write(reinterpret_cast<const char*>(&compressedByte), sizeof(compressedByte));
            buffer = buffer.substr(8);
        }
    }

    // Обработка оставшихся битов
    if (!buffer.empty()) {
        unsigned char compressedByte = 0;
        for (size_t i = 0; i < buffer.size(); ++i) {
            if (buffer[i] == '1') {
                compressedByte |= (1 << (7 - i));
            }
        }
        outFile.write(reinterpret_cast<const char*>(&compressedByte), sizeof(compressedByte));
    }

    // Закрытие выходного файла
    outFile.close();

    // Освобождение памяти, выделенной для дерева Хаффмана
    delete root;

    cout << "Архив сохранен в " << outputFile << endl;
}

// Функция для распаковки файла
void decompressFile(const string& inputFile, const string& outputFile) {
    // Открытие входного файла архива
    ifstream inFile(inputFile, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Ошибка открытия входного файла" << endl;
        return;
    }

    cout << "Идет разархивация файла. Пожалуйста, подождите..." << endl;

    // Чтение размера исходного файла из архива
    size_t fileSize;
    inFile.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));

    // Перемещение указателя текущей позиции в потоке ввода-вывода
    inFile.seekg(sizeof(size_t), ios::cur);

    // Чтение частот из входного файла
    size_t frequency[256];
    for (int i = 0; i < 256; ++i) {
        inFile.read(reinterpret_cast<char*>(&frequency[i]), sizeof(size_t));
    }

    // Построение дерева Хаффмана
    HuffmanNode* root = buildHuffmanTree(frequency, 256);

    // Открытие выходного файла для распаковки
    ofstream outFile(outputFile, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия выходного файла" << endl;
        delete root;
        return;
    }

    // Чтение данных и их распаковка с использованием дерева Хаффмана
    HuffmanNode* currentNode = root;
    unsigned char byte;
    size_t bytesRead = 0;
    while (bytesRead < fileSize && inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        for (int i = 0; i < 8; ++i) {
            if (byte & (1 << (7 - i))) {
                currentNode = currentNode->right;
            }
            else {
                currentNode = currentNode->left;
            }

            if (!currentNode->left && !currentNode->right) {
                outFile.write(reinterpret_cast<char*>(&currentNode->data), sizeof(currentNode->data));
                currentNode = root;
                bytesRead++;
                if (bytesRead == fileSize) {
                    break; // Достигнут конец файла
                }
            }
        }
    }

    // Закрытие файлов
    inFile.close();
    outFile.close();

    // Освобождение памяти, выделенной для дерева Хаффмана
    delete root;

    cout << "Файл сохранен в " << outputFile << endl;
}

int main() {
    // Пример использования: сжатие и распаковка файла
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    string input, output;
    cout << "Какую операцию вы хотите выполнить?" << endl;
    cout << "1. Архивация" << endl;
    cout << "2. Разархивация" << endl;
    cout << "Введите номер операции: ";
    cin >> n;
    switch (n) {
    case 1:
        cout << "Введите путь и имя исходного файла: ";
        cin >> input;
        cout << "Введите путь для сохранения архива и его имя: ";
        cin >> output;
        compressFile(input, output);
        break;
    case 2:
        cout << "Введите путь и имя исходного файла: ";
        cin >> input;
        cout << "Введите путь для сохранения архива и его имя: ";
        cin >> output;
        decompressFile(input, output);
        break;
    default:
        cout << "Такой операции нет!" << endl;
    }

    return 0;
}