#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "WiFi.h"
#include "Queue.h"
#include "Site.h"
using namespace std;

string WiFi::work = "Да";
string Site::work = "Да";

void WiFi::openSite(Site& site) {  //функция класса WiFi, взаимодействующая с объектом класса Site
    cout << "Сообщение от провайдера: Вы успешно зашли на сайт " << site.getName() << " через Wi-Fi сеть " << getLogin() << endl;
    cout << "Сайт работает: " << site.getWork() << endl;
    cout << "Время загрузки сайта: " << site.getTime() << " мс" << endl << endl;

}

void Site::statusWiFi(WiFi& wifi) {  //функция класса Site, взаимодействующая с объектом класса WiFi
    cout << "Сообщение от сайта: Подключение к сайту " << getName() << " осуществляется через Wi-Fi сеть " << wifi.getLogin() << endl;
    cout << "Протокол безопасности сети: " << wifi.getProtection() << endl << endl;
}

void NetworkError(int err) {    //функция вывода ошибок
    switch (err) {
    case 1: cout << "Такой WiFi-сети нет!" << endl << endl;
        break;
    case 2: cout << "Пароль неверный!" << endl << endl;
        break;
    case 3: cout << "Такого варианта нет!" << endl << endl;
        break;
    case 4: cout << "Такого сайта нет!" << endl << endl;
    }
}

WiFi authorization(int number, int& traffic, double& time, string password, WiFi& Network, Queue<string>& q, Queue<string>& error, Queue<int>& q_num, int& correct) {
    if (password == Network.getPassword()) {      //если пароль верный, то выводится информация о сети
        WiFi Network_Connected(Network);
        q.add(Network.getLogin());
        q_num.add(number);
        correct++;
        cout << Network;
        traffic = Network.sum(traffic, Network.getTraffic());
        time = Network.sum(time, Network.getTime());
        return Network_Connected;
    }
    else {
        NetworkError(2);         //если пароль неверный, выводится сообщение об ошибке
        WiFi Network_Disconnected(Network);
        error.add(Network.getLogin());
        return Network_Disconnected;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int number, number_site, count = 0, traffic = 0, correct = 0;
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

        Site Site_1("Google", "Поисковик", "www.google.com", protocol::https);
        Site Site_2("Яндекс", "Поисковик", "www.ya.ru", protocol::https);
        Site Site_3("ВКонтакте", "Социальная сеть", "www.vk.com", protocol::https);
        Site Site_4("YouTube", "Видеохостинг", "www.youtube.com", protocol::https);
        Site Site_5;
        Site Site_6(Site_1);
        Site Site_7("example.com");
        Site Site_8("www.edu.chsu.ru", protocol::http);
        Site Site_9("ЧГУ", "www.chsu.ru", protocol::https);

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
        count++;
        if (number < 0 || number > 9) {     //если введен номер несуществуещей сети, выводится сообщение об ошибке
            NetworkError(1);
            continue;
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
                continue;
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
        WiFi Network_Connected;
        correct = 0;
        switch (number) {
        case 1: Network_Connected = authorization(number, traffic, time, password, Network_1, q, error, q_num, correct);
            break;
        case 2: Network_Connected = authorization(number, traffic, time, password, Network_2, q, error, q_num, correct);
            break;
        case 3: Network_Connected = authorization(number, traffic, time, password, Network_3, q, error, q_num, correct);
            break;
        case 4: Network_Connected = authorization(number, traffic, time, password, Network_4, q, error, q_num, correct);
            break;
        case 5: Network_Connected = authorization(number, traffic, time, password, Network_5, q, error, q_num, correct);
            break;
        case 6: Network_Connected = authorization(number, traffic, time, password, Network_6, q, error, q_num, correct);
            break;
        case 7: Network_Connected = authorization(number, traffic, time, password, Network_7, q, error, q_num, correct);
            break;
        case 8: Network_Connected = authorization(number, traffic, time, password, Network_8, q, error, q_num, correct);
            break;
        case 9: Network_Connected = authorization(number, traffic, time, password, Network_9, q, error, q_num, correct);
            break;
        }
        while (correct == 1) {
            cout << "Доступные сайты: " << endl;              //вывод доступных сетей на экран
            cout << "1. " << Site_1 << endl;
            cout << "2. " << Site_2 << endl;
            cout << "3. " << Site_3 << endl;
            cout << "4. " << Site_4 << endl;
            cout << "5. " << Site_5 << endl;
            cout << "6. " << Site_6 << endl;
            cout << "7. " << Site_7 << endl;
            cout << "8. " << Site_8 << endl;
            cout << "9. " << Site_9 << endl << endl;
            cout << "0. Отключиться от Wi-Fi сети " << Network_Connected.getLogin() << endl << endl;
            cout << "Выберите сайт: ";
            cin >> number_site;
            switch (number_site) {
            case 1: {
                Network_Connected.openSite(Site_1); 
                Site_1.statusWiFi(Network_Connected);
            }                     
                break;            
            case 2: {             
                Network_Connected.openSite(Site_2);
                Site_2.statusWiFi(Network_Connected);
            }                     
                break;            
            case 3: {             
                Network_Connected.openSite(Site_3);
                Site_3.statusWiFi(Network_Connected);
            }                     
                break;            
            case 4: {             
                Network_Connected.openSite(Site_4);
                Site_4.statusWiFi(Network_Connected);
            }                     
                break;            
            case 5: {             
                Network_Connected.openSite(Site_5);
                Site_5.statusWiFi(Network_Connected);
            }                     
                break;            
            case 6: {             
                Network_Connected.openSite(Site_6);
                Site_6.statusWiFi(Network_Connected);
            }                     
                break;            
            case 7: {             
                Network_Connected.openSite(Site_7);
                Site_7.statusWiFi(Network_Connected);
            }                     
                break;            
            case 8: {             
                Network_Connected.openSite(Site_8);
                Site_8.statusWiFi(Network_Connected);
            }
                break;
            case 9: {
                Network_Connected.openSite(Site_9);
                Site_9.statusWiFi(Network_Connected);
            }
                break;
            case 0: {
                cout << "Вы отключились от Wi-Fi сети " << Network_Connected.getLogin() << endl << endl;
                correct--; 
            }
                break;
            default: NetworkError(4);
                   break;
            }
        }
    }
    system("pause");
    return 0;
}