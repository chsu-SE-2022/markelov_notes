#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

string WiFi::work;

void NetworkError(int err) {    //функция вывода ошибок
    switch (err) {
    case 1: cout << "Такой WiFi-сети нет!";
        break;
    case 2: cout << "Пароль неверный!" << endl;
        break;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int number;
    string password, name;
 
    WiFi Network_1("CHSU FREE", "0", security::NoProtection, 100, 70, 5);         //описание доступных WiFi-сетей
    WiFi Network_2("CHSU WORK", "1234567890", security::WPA3, 120, 50, 5);
    WiFi Network_3("iPhone", "ghfdgldklkl", security::WPA2, 80, 40, 2.4);
    WiFi Network_4("Xiaomi", "h5hjg54g5", security::WPA2, 70, 40, 2.4);
    WiFi Network_5;
    WiFi Network_6(Network_1);
    WiFi Network_7(2.4, "Rostelecom");
    WiFi Network_8(100, "Beeline");

    cout << "Доступные сети: " << endl;              //вывод доступных сетей на экран
    cout << "1. " << Network_1.getLogin() << endl;
    cout << "2. " << Network_2.getLogin() << endl;
    cout << "3. " << Network_3.getLogin() << endl;
    cout << "4. " << Network_4.getLogin() << endl;
    cout << "5. " << Network_5.getLogin() << endl;
    cout << "6. " << Network_6.getLogin() << endl;
    cout << "7. " << Network_7.getLogin() << endl;
    cout << "8. " << Network_8.getLogin() << endl;
    cout << endl;

    cout << "Введите номер сети, к которой хотите подключиться: ";       //выбор сети
    cin >> number;     
    if (number < 1 || number > 8) {     //если введен номер несуществуещей сети, выводится сообщение об ошибке
        NetworkError(1);
        return 0; 
    }

    cout << "Введите пароль: ";     //ввод пароля
    cin >> password;
    switch (number) {

    case 1: {
        if (password == Network_1.getPassword()) Network_1.networkInfo(); //если пароль верный, то выводится информация о сети
        else {
            NetworkError(2); //если пароль неверный, выводится сообщение об ошибке
            return 0;
        }
    }
          break;

    case 2: {
        if (password == Network_2.getPassword()) Network_2.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;

    case 3: {
        if (password == Network_3.getPassword()) Network_3.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;

    case 4: {
        if (password == Network_4.getPassword()) Network_4.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;
    case 5: {
        if (password == Network_5.getPassword()) Network_5.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;
    case 6: {
        if (password == Network_6.getPassword()) Network_6.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;
    case 7: {
        if (password == Network_7.getPassword()) Network_7.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;
    case 8: {
        if (password == Network_8.getPassword()) Network_8.networkInfo();
        else {
            NetworkError(2);
            return 0;
        }
    }
          break;
    }
    system("pause");
    return 0;
}