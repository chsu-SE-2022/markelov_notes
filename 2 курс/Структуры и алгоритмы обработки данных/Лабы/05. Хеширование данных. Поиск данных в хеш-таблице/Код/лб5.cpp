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
    Hash(int B) {                                                      //����������� ��� B <= 30
        this->B = B;
        element = new Node * [B]();
    }

    Hash(int B, int a, int c) {                                        //����������� ��� B > 30
        this->B = B;
        this->a = a;
        this->c = c;
        element = new Node * [B]();
    }

    int GetHash(double x) {                                            //���������� ����� ��� B <= 30
        return static_cast<int>(fmod(x, B));
    }

    int GetHash(double x, int a, int c) {                              //���������� ����� ��� B > 30
        return static_cast<int>(fmod((a * x + c), B));
    }

    void Insert(double value) {                                        //���������� �������� � ���-�������
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

    int Search(double value) {                                         //�����
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

    int GetLong() {                                                    //����� ����� ������� ������� ��������
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

    double GetPercent() {                                              //������� �������� ������������� �������
        int filled = 0;
        for (int i = 0; i < B; i++) {
            if (element[i])
                filled++;
        }
        return (static_cast<double>(filled) / B) * 100;
    }

    void Print() {                                                     //�����
        cout << "���-�������:" << endl;
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

    ~Hash() {                                                     //���������
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
        cout << "������ �������� �����" << endl;
        return 0;
    }
    cout << "������� ���������� �������: ";
    cin >> B;
    if (B > 30 && B <= 50000) {
        cout << "��� - �������: h(x) = (ax + c) % B" << endl;
        cout << "������� ����������� a: " << endl;
        cin >> a;
        cout << "������� ����������� c: " << endl;
        cin >> c;
        Hash table(B, a, c);
        while (f >> value) {
            table.Insert(value);
        }
        f.close();
        cout << "���-������� ���������" << endl;
        cout << "����������� ��������: " << table.GetCollisions() << endl;
        cout << "����� ������� ������� �������� ������� �� " << table.GetLong() << " ���������" << endl;
        cout << "������� ��������� �� " << table.GetPercent() << " ���������" << endl;
        cout << "������� ����� ��� ������: ";
        cin >> current;
        if (table.Search(current) == -1) cout << "������� " << current << " �� ������" << endl;
        else cout << "������� " << current << " ������, ����: " << table.Search(current, a, c) << endl;
    }
    else if (B > 0 && B <= 30) {
        cout << "��� - �������: h(x) = x % B" << endl;
        Hash table(B);
        while (f >> value) {
            table.Insert(value);
        }
        f.close();
        table.Print();
        cout << "������� ����� ��� ������: ";
        cin >> current;
        if (table.Search(current) == -1) cout << "������� " << current << " �� ������" << endl;
        else cout << "������� " << current << " ������, ����: " << table.Search(current) << endl;
    }
    else if (B > 50000) {
        cout << "������� ������� ������� �����" << endl;
        return 0;
    }
    else if (B <= 0) {
        cout << "������� ������� ��������� �����" << endl;
        return 0;
    }

    system("pause");
    return 0;
}
