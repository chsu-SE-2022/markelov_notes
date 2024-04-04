#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "WiFi.h"
#include "Queue.h"
#include "Site.h"
#include "Mobile.h"
#include "Flash.h"
#include "Modem.h"
using namespace std;

string WiFi::work = "Да";
string Site::work = "Да";

void WiFi::openSite(Site& site) {  //функция класса WiFi, взаимодействующая с объектом класса Site
    cout << "Сообщение от провайдера: Вы успешно зашли на сайт " << site.getName() << " через сеть " << getName() << endl;
    cout << "Сайт работает: " << site.getWork() << endl;
    cout << "Время загрузки сайта: " << site.getTime() << " мс" << endl << endl;

}

void Site::status(WiFi& wifi) {  //функция класса Site, взаимодействующая с объектом класса WiFi
    cout << "Сообщение от сайта: Подключение к сайту " << getName() << " осуществляется через сеть " << wifi.getName() << endl;
    cout << "Скорость сети: " << wifi.getSpeed() << " Мбит/с" << endl << endl;
}

void NetworkError(int err) {    //функция вывода ошибок
    switch (err) {
    case 1: cout << "Такой сети нет!" << endl << endl;
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
        q.add(Network.getName());
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
        error.add(Network.getName());
        return Network_Disconnected;
    }
}

template<typename T>
T authorization(int number, int& traffic, double& time, T& Network, Queue<string>& q, Queue<string>& error, Queue<int>& q_num, int& correct) {
    T Network_Connected(Network);
    q.add(Network.WiFi::getName());
    q_num.add(number);
    correct++;
    cout << Network;
    traffic = Network.sum(traffic, Network.getTraffic());
    time = Network.sum(time, Network.getTime());
    return Network_Connected;
}

template<typename T>
void login(T& Network, Site& website) {
    Network.openSite(website);
    website.status(Network);
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

        Mobile Mobile_1("MTS RUS", generation::_5G, 70, 100, 5);         //описание доступных мобильных сетей
        Mobile Mobile_2("Beeline", generation::_2G, 50, 90, 5);
        Mobile Mobile_3("MegaFon", generation::_4G, 80, 100, 5);
        Mobile Mobile_4("Tele2", generation::_3G, 50, 80, 5);
        Mobile Mobile_5;
        Mobile Mobile_6(Mobile_1);
        Mobile Mobile_7("Yota");
        Mobile Mobile_8("Tinkoff Mobile", generation::_3G);
        Mobile Mobile_9("Мотив", generation::GPRS, 30);

        Site Site_1("Google", "Поисковик", "www.google.com", protocol::https);
        Site Site_2("Яндекс", "Поисковик", "www.ya.ru", protocol::https);
        Site Site_3("ВКонтакте", "Социальная сеть", "www.vk.com", protocol::https);
        Site Site_4("YouTube", "Видеохостинг", "www.youtube.com", protocol::https);
        Site Site_5;
        Site Site_6(Site_1);
        Site Site_7("example.com");
        Site Site_8("www.edu.chsu.ru", protocol::http);
        Site Site_9("ЧГУ", "www.chsu.ru", protocol::https);

        Flash USB_1("Kingston", 8, 3.1, 'A');
        Flash USB_2("WD");
        Flash USB_3("Corsair", 2);
        Flash USB_4;
        Flash USB_5(USB_1);

        Modem Modem_1("MegaFon", _4G, 80, 100, 5, 3.0, 'A', 1, 1);
        Modem Modem_2("Yota");
        Modem Modem_3("Rostelecom", _3G);
        Modem Modem_4("Beeline", _2G, 'A');
        Modem Modem_5;
        Modem Modem_6(Modem_1);


        cout << "Доступные Wi-Fi сети: " << endl;              //вывод доступных Wi-Fi сетей на экран
        cout << "1. " << Network_1.getName() << endl;
        cout << "2. " << Network_2.getName() << endl;
        cout << "3. " << Network_3.getName() << endl;
        cout << "4. " << Network_4.getName() << endl;
        cout << "5. " << Network_5.getName() << endl;
        cout << "6. " << Network_6.getName() << endl;
        cout << "7. " << Network_7.getName() << endl;
        cout << "8. " << Network_8.getName() << endl;
        cout << "9. " << Network_9.getName() << endl << endl;

        cout << "Доступные мобильные сети: " << endl;              //вывод доступных мобильных сетей на экран
        cout << "10. " << Mobile_1.getName() << endl;
        cout << "11. " << Mobile_2.getName() << endl;
        cout << "12. " << Mobile_3.getName() << endl;
        cout << "13. " << Mobile_4.getName() << endl;
        cout << "14. " << Mobile_5.getName() << endl;
        cout << "15. " << Mobile_6.getName() << endl;
        cout << "16. " << Mobile_7.getName() << endl;
        cout << "17. " << Mobile_8.getName() << endl;
        cout << "18. " << Mobile_9.getName() << endl << endl;

        cout << "Подключенные USB-устройства: " << endl;              //вывод доступных мобильных сетей на экран
        cout << "19. " << USB_1.getName() << endl;
        cout << "20. " << USB_2.getName() << endl;
        cout << "21. " << USB_3.getName() << endl;
        cout << "22. " << USB_4.getName() << endl;
        cout << "23. " << USB_5.getName() << endl << endl;

        cout << "Подключенные USB-модемы: " << endl;              //вывод доступных мобильных сетей на экран
        cout << "24. " << Modem_1.WiFi::getName() << endl;
        cout << "25. " << Modem_2.WiFi::getName() << endl;
        cout << "26. " << Modem_3.WiFi::getName() << endl;
        cout << "27. " << Modem_4.WiFi::getName() << endl;
        cout << "28. " << Modem_5.WiFi::getName() << endl;
        cout << "29. " << Modem_6.WiFi::getName() << endl << endl;

        cout << "0. " << "Вывести историю подключения к сетям" << endl;

        if (count == 0) {
            cout << endl << "Рекомендации: " << endl;
            cout << "Выбирая между сетями " << Network_1.getName() << " и " << Network_2.getName() << " рекомендуем выбрать сеть ";
            if (Network_1 > Network_2) cout << Network_1.getName();
            else if (Network_1 < Network_2) cout << Network_2.getName();
            cout << ", т.к. её скорость выше" << endl;
            if (Network_5 == Network_9) cout << "Скорость у сетей " << Network_5.getName() << " и " << Network_9.getName() << " одинакова" << endl;
            if (Network_3 == Network_4) cout << "Скорость у сетей " << Network_3.getName() << " и " << Network_4.getName() << " одинакова" << endl;
            cout << "С помощью сетей " << Network_7.getName() << " и " << Network_8.getName() << " можно передать " << Network_7 + Network_8 << " Мб данных" << endl;
        }

        cout << endl << "Введите номер сети/устройства: ";       //выбор сети/устройства
        cin >> number;
        count++;
        if (number < 0 || number > 29) {     //если введен номер несуществуещей сети/устройства, выводится сообщение об ошибке
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
                cout << "1. " << Network_1.getName() << endl;
                cout << "2. " << Network_2.getName() << endl;
                cout << "3. " << Network_3.getName() << endl;
                cout << "4. " << Network_4.getName() << endl;
                cout << "5. " << Network_5.getName() << endl;
                cout << "6. " << Network_6.getName() << endl;
                cout << "7. " << Network_7.getName() << endl;
                cout << "8. " << Network_8.getName() << endl;
                cout << "9. " << Network_9.getName() << endl;
                cout << "10. " << Mobile_1.getName() << endl;
                cout << "11. " << Mobile_2.getName() << endl;
                cout << "12. " << Mobile_3.getName() << endl;
                cout << "13. " << Mobile_4.getName() << endl;
                cout << "14. " << Mobile_5.getName() << endl;
                cout << "15. " << Mobile_6.getName() << endl;
                cout << "16. " << Mobile_7.getName() << endl;
                cout << "17. " << Mobile_8.getName() << endl;
                cout << "18. " << Mobile_9.getName() << endl;
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

        if (number >= 1 && number <= 9) {
            cout << "Введите пароль: ";     //ввод пароля
            cin >> password;
            cin.get();
        }
        WiFi Network_Connected;
        Mobile Mobile_Connected;
        Modem Modem_Connected;
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
        case 10: Mobile_Connected = authorization(number, traffic, time, Mobile_1, q, error, q_num, correct);
            break;
        case 11: Mobile_Connected = authorization(number, traffic, time, Mobile_2, q, error, q_num, correct);
            break;
        case 12: Mobile_Connected = authorization(number, traffic, time, Mobile_3, q, error, q_num, correct);
            break;
        case 13: Mobile_Connected = authorization(number, traffic, time, Mobile_4, q, error, q_num, correct);
            break;
        case 14: Mobile_Connected = authorization(number, traffic, time, Mobile_5, q, error, q_num, correct);
            break;
        case 15: Mobile_Connected = authorization(number, traffic, time, Mobile_6, q, error, q_num, correct);
            break;
        case 16: Mobile_Connected = authorization(number, traffic, time, Mobile_7, q, error, q_num, correct);
            break;
        case 17: Mobile_Connected = authorization(number, traffic, time, Mobile_8, q, error, q_num, correct);
            break;
        case 18: Mobile_Connected = authorization(number, traffic, time, Mobile_9, q, error, q_num, correct);
            break;
        case 19: cout << USB_1;
            break;
        case 20: cout << USB_2;
            break;
        case 21: cout << USB_3;
            break;
        case 22: cout << USB_4;
            break;
        case 23: cout << USB_5;
            break;
        case 24: Modem_Connected = authorization(number, traffic, time, Modem_1, q, error, q_num, correct);
            break;
        case 25: Modem_Connected = authorization(number, traffic, time, Modem_2, q, error, q_num, correct);
            break;
        case 26: Modem_Connected = authorization(number, traffic, time, Modem_3, q, error, q_num, correct);
            break;
        case 27: Modem_Connected = authorization(number, traffic, time, Modem_4, q, error, q_num, correct);
            break;
        case 28: Modem_Connected = authorization(number, traffic, time, Modem_5, q, error, q_num, correct);
            break;
        case 29: Modem_Connected = authorization(number, traffic, time, Modem_6, q, error, q_num, correct);
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
            if (number <= 9) cout << "0. Отключиться от Wi-Fi сети " << Network_Connected.getName() << endl << endl;
            else cout << "0. Отключиться от мобильной сети " << Mobile_Connected.getName() << endl << endl;
            cout << "Выберите сайт: ";
            cin >> number_site;

            switch (number_site) {
            case 1: {
                if (number <= 9) login(Network_Connected, Site_1);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_1);
                else login(Modem_Connected, Site_1);
            }
                  break;
            case 2: {
                if (number <= 9) login(Network_Connected, Site_2);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_2);
                else login(Modem_Connected, Site_2);
            }
                  break;
            case 3: {
                if (number <= 9) login(Network_Connected, Site_3);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_3);
                else login(Modem_Connected, Site_3);
            }
                  break;
            case 4: {
                if (number <= 9) login(Network_Connected, Site_4);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_4);
                else login(Modem_Connected, Site_4);
            }
                  break;
            case 5: {
                if (number <= 9) login(Network_Connected, Site_5);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_5);
                else login(Modem_Connected, Site_5);
            }
                  break;
            case 6: {
                if (number <= 9) login(Network_Connected, Site_6);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_6);
                else login(Modem_Connected, Site_6);
            }
                  break;
            case 7: {
                if (number <= 9) login(Network_Connected, Site_7);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_7);
                else login(Modem_Connected, Site_7);
            }
                  break;
            case 8: {
                if (number <= 9) login(Network_Connected, Site_8);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_8);
                else login(Modem_Connected, Site_8);
            }
                  break;
            case 9: {
                if (number <= 9) login(Network_Connected, Site_9);
                else if (number > 9 && number <= 18) login(Mobile_Connected, Site_9);
                else login(Modem_Connected, Site_9);
            }
                  break;
            case 0: {
                if (number <= 9) cout << "Вы отключились от Wi-Fi сети " << Network_Connected.getName() << endl << endl;
                else cout << "Вы отключились от мобильной сети " << Mobile_Connected.getName() << endl << endl;
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