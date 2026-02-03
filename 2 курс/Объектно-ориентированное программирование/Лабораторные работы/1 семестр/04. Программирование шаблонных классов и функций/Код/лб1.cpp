#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Header.h"
#include "Queue.h"
using namespace std;

string WiFi::work;

void NetworkError(int err) {    //функция вывода ошибок
    switch (err) {
    case 1: cout << "Такой WiFi-сети нет!";
        break;
    case 2: cout << "Пароль неверный!" << endl;
        break;
    case 3: cout << "Такого варианта нет!" << endl;
        break;
    }
}

void authorization(int& count, int& capacity, int number, int& traffic, double& time, string password, WiFi& Network, Queue<string>& q, Queue<string>& error, Queue<int>& q_num) {
    if (count == capacity - 1) capacity += 100;
    if (password == Network.getPassword()) {      //если пароль верный, то выводится информация о сети
        q.add(Network.getLogin());
        q_num.add(number);
        count++;
        cout << Network;
        traffic = Network.sum(traffic, Network.getTraffic());
        time = Network.sum(time, Network.getTime());
    }
    else {
        NetworkError(2);         //если пароль неверный, выводится сообщение об ошибке
        error.add(Network.getLogin());
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int number, count = 0, capacity = 100, traffic = 0;
    double time = 0;
    string password, name;
    Queue<string> q, error;
    Queue<int> q_num;

    while (true) {
        WiFi Network_1("CHSU_FREE", "0", security::NoProtection, 100, 70, 5);         //описание доступных WiFi-сетей
        WiFi Network_2("CHSU_WORK", "1234567890", security::WPA3, 120, 50, 5);
        WiFi Network_3("IPhone", "ghfdgldklkl", security::WPA2, 80, 40, 2.4);
        WiFi Network_4("Xiaomi", "h5hjg54g5", security::WPA2, 70, 40, 2.4);
        WiFi Network_5;
        WiFi Network_6(Network_1);
        WiFi Network_7(2.4, "Rostelecom");
        WiFi Network_8(100, 60, "Beeline");
        WiFi Network_9("iZet");

        cout << "Доступные сети: " << endl;              //вывод доступных сетей на экран
        cout << "1. " << Network_1.getLogin() << endl;
        cout << "2. " << Network_2.getLogin() << endl;
        cout << "3. " << Network_3.getLogin() << endl;
        cout << "4. " << Network_4.getLogin() << endl;
        cout << "5. " << Network_5.getLogin() << endl;
        cout << "6. " << Network_6.getLogin() << endl;
        cout << "7. " << Network_7.getLogin() << endl;
        cout << "8. " << Network_8.getLogin() << endl;
        cout << "9. " << Network_9.getLogin() << endl << endl;
        cout << "0. " << "Вывести историю подключения к сетям" << endl;

        if (count == 0) {
            cout << endl << "Рекомендации: " << endl;
            cout << "Выбирая между сетями " << Network_1.getLogin() << " и " << Network_2.getLogin() << " рекомендуем выбрать сеть ";
            if (Network_1 > Network_2) cout << Network_1.getLogin();
            else if (Network_1 < Network_2) cout << Network_2.getLogin();
            cout << ", т.к. её скорость выше" << endl;
            if (Network_5 == Network_9) cout << "Скорость у сетей " << Network_5.getLogin() << " и " << Network_9.getLogin() << " одинакова" << endl;
            if (Network_3 == Network_4) cout << "Скорость у сетей " << Network_3.getLogin() << " и " << Network_4.getLogin() << " одинакова" << endl;
            cout << "С помощью сетей " << Network_7.getLogin() << " и " << Network_8.getLogin() << " можно передать " << Network_7 + Network_8 << " Мб данных" << endl;
        }

        cout << endl << "Введите номер сети, к которой хотите подключиться: ";       //выбор сети
        cin >> number;
        if (number < 0 || number > 9) {     //если введен номер несуществуещей сети, выводится сообщение об ошибке
            NetworkError(1);
            return -1;
        }
        else if (number == 0 && !q.empty()) {
            int num;
            if (q >= error) cout << endl << "Было совершено " << q.getSize() << " удачных подключений и " << error.getSize() << " неудачных" << endl;
            if (q < error) cout << endl << "Было совершено " << error.getSize() << " неудачных подключений и " << q.getSize() << " удачных" << endl;
            cout << "Всего было передано " << traffic << " Мб данных" << endl;
            cout << "Общее время соединения: " << time << " сек" << endl;
            cout << endl << "Порядок вывода:" << endl;              //вывод доступных сетей на экран
            cout << "1. " << "В хронологическом (от старых подключений к новым)" << endl;
            cout << "2. " << "В хронологическом (от новых подключений к старым)" << endl;
            cout << "3. " << "В алфавитном (A - Z)" << endl;
            cout << "4. " << "В обратном алфавитному (Z - A)" << endl;
            cout << "5. " << "Поиск по названию" << endl;
            cout << "6. " << "Поиск по номеру" << endl;
            cout << endl << "Выберите порядок: ";
            cin >> num;
            if (num < 1 || num > 6) {
                NetworkError(3);
                return -1;
            }
            if (num >= 1 && num <= 4) cout << endl << "История подключений: " << endl;
            switch (num) {
            case 1: cout << q;
                break;
            case 2: q.print_NewOld();
                break;
            case 3: q.print_AZ();
                break;
            case 4: q.print_ZA();
                break;
            case 5: {
                cout << endl << "Введите название сети: ";
                cin >> name;
                cin.get();
                q.search(name);
            }
                  break;
            case 6: {
                cout << endl << "Доступные сети: " << endl;              //вывод доступных сетей на экран
                cout << "1. " << Network_1.getLogin() << endl;
                cout << "2. " << Network_2.getLogin() << endl;
                cout << "3. " << Network_3.getLogin() << endl;
                cout << "4. " << Network_4.getLogin() << endl;
                cout << "5. " << Network_5.getLogin() << endl;
                cout << "6. " << Network_6.getLogin() << endl;
                cout << "7. " << Network_7.getLogin() << endl;
                cout << "8. " << Network_8.getLogin() << endl;
                cout << "9. " << Network_9.getLogin() << endl;
                cout << endl << "Введите номер сети: ";
                int number2;
                cin >> number2;
                cin.get();
                q_num.search(number2);
            }
                  break;
            }
            return 0;
        }
        else if (number == 0 && q.empty()) {
            cout << "Подключений не было" << endl;
            return 0;
        }

        cout << "Введите пароль: ";     //ввод пароля
        cin >> password;
        cin.get();
        switch (number) {
        case 1: authorization(count, capacity, number, traffic, time, password, Network_1, q, error, q_num);
            break;
        case 2: authorization(count, capacity, number, traffic, time, password, Network_2, q, error, q_num);
            break;
        case 3: authorization(count, capacity, number, traffic, time, password, Network_3, q, error, q_num);
            break;
        case 4: authorization(count, capacity, number, traffic, time, password, Network_4, q, error, q_num);
            break;
        case 5: authorization(count, capacity, number, traffic, time, password, Network_5, q, error, q_num);
            break;
        case 6: authorization(count, capacity, number, traffic, time, password, Network_6, q, error, q_num);
            break;
        case 7: authorization(count, capacity, number, traffic, time, password, Network_7, q, error, q_num);
            break;
        case 8: authorization(count, capacity, number, traffic, time, password, Network_8, q, error, q_num);
            break;
        case 9: authorization(count, capacity, number, traffic, time, password, Network_9, q, error, q_num);
            break;
        }
    }
    system("pause");
    return 0;
}