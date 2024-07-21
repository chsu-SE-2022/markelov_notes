#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Hash {
private:
    struct Node {
        int key;
        double value;
        Node* next;
    };

    int B, a, c;
    Node** element;

public:
    Hash(int B) {                                                      //конструктор при B <= 30
        this->B = B;
        element = new Node * [B]();
    }

    Hash(int B, int a, int c) {                                        //конструктор при B > 30
        this->B = B;
        this->a = a;
        this->c = c;
        element = new Node * [B]();
    }

    int GetHash(double x) {                                            //вычисление ключа при B <= 30
        return static_cast<int>(fmod(x, B));
    }

    int GetHash(double x, int a, int c) {                              //вычисление ключа при B > 30
        return static_cast<int>(fmod((a * x + c), B));
    }

    void Insert(double value) {                                        //добавление элемента в хеш-таблицу
        int key;
        if (B <= 30) key = GetHash(value);
        else key = GetHash(value, a, c);
        Node* newNode = new Node{ key, value, NULL };
        if (!element[key]) {
            element[key] = newNode;
        }
        else {
            newNode->next = element[key];
            element[key] = newNode;
        }
    }

    int Search(double value) {                                         //поиск
        int key = GetHash(value);
        Node* current = element[key];
        while (current) {
            if (current->value == value)
                return key;
            current = current->next;
        }
        return -1;
    }

    int Search(double value, int a, int c) {
        int key = GetHash(value, a, c);
        Node* current = element[key];
        while (current) {
            if (current->value == value)
                return key;
            current = current->next;
        }
        return -1;
    }

    int GetCollisions() {
        int count = 0;
        for (int i = 0; i < B; i++) {
            if (element[i]) {
                Node* current = element[i]->next;
                while (current) {
                    count++;
                    current = current->next;
                }
            }
        }
        return count;
    }

    int GetLong() {                                                    //поиск самой длинной цепочки коллизий
        int max = 0;
        for (int i = 0; i < B; i++) {
            int length = 0;
            Node* current = element[i];
            while (current) {
                length++;
                current = current->next;
            }
            if (length > max) {
                max = length;
            }
        }
        return max;
    }

    double GetPercent() {                                              //подсчет процента заполненности таблицы
        int filled = 0;
        for (int i = 0; i < B; i++) {
            if (element[i])
                filled++;
        }
        return (static_cast<double>(filled) / B) * 100;
    }

    void Print() {                                                     //вывод
        cout << "’еш-таблица:" << endl;
        for (int i = 0; i < B; i++) {
            if (element[i]) {
                cout << i << ": [";
                Node* current = element[i];
                while (current) {
                    cout << current->value;
                    if (current->next)
                        cout << "; ";
                    current = current->next;
                }
                cout << "]" << endl;
            }
            else {
                cout << i << ": []" << endl;
            }
        }
    }

    ~Hash() {                                                     //дестуктор
        for (int i = 0; i < B; i++) {
            Node* current = element[i];
            while (current) {
                Node* tmp = current;
                current = current->next;
                delete tmp;
            }
        }
        delete[] element;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int B, a, c, n;
    double current, value;
    ifstream f("input1.txt");
    if (!f.is_open()) {
        cout << "ќшибка открыти€ файла" << endl;
        return 0;
    }
    cout << "¬ведите количество классов: ";
    cin >> B;
    if (B > 30 && B <= 50000) {
        cout << "’еш - функци€: h(x) = (ax + c) % B" << endl;
        cout << "¬ведите коэффициент a: " << endl;
        cin >> a;
        cout << "¬ведите коэффициент c: " << endl;
        cin >> c;
        Hash table(B, a, c);
        while (f >> value) {
            table.Insert(value);
        }
        f.close();
        cout << "’эш-таблица построена" << endl;
        cout << " олличество коллизий: " << table.GetCollisions() << endl;
        cout << "—ама€ длинна€ цепочка коллизий состоит из " << table.GetLong() << " элементов" << endl;
        cout << "“аблица заполнена на " << table.GetPercent() << " процентов" << endl;
        cout << "¬ведите число дл€ поиска: ";
        cin >> current;
        if (table.Search(current) == -1) cout << "Ёлемент " << current << " не найден" << endl;
        else cout << "Ёлемент " << current << " найден, ключ: " << table.Search(current, a, c) << endl;
    }
    else if (B > 0 && B <= 30) {
        cout << "’еш - функци€: h(x) = x % B" << endl;
        Hash table(B);
        while (f >> value) {
            table.Insert(value);
        }
        f.close();
        table.Print();
        cout << "¬ведите число дл€ поиска: ";
        cin >> current;
        if (table.Search(current) == -1) cout << "Ёлемент " << current << " не найден" << endl;
        else cout << "Ёлемент " << current << " найден, ключ: " << table.Search(current) << endl;
    }
    else if (B > 50000) {
        cout << "¬ведено слишком большое число" << endl;
        return 0;
    }
    else if (B <= 0) {
        cout << "¬ведено слишком маленькое число" << endl;
        return 0;
    }

    system("pause");
    return 0;
}
