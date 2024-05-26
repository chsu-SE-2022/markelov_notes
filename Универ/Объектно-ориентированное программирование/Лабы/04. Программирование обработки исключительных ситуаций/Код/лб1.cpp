#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "WiFi.h"
#include "Queue.h"
#include "DataDevices.h"
#include "Wireless.h"
#include "Site.h"
#include "Mobile.h"
#include "Flash.h"
#include "Modem.h"
#include "Wired.h"
#include "Router.h"
#include "Exception.h"
using namespace std;

string DataDevices::work = "Да";
string Site::work = "Да";

void Wireless::openSite(Site& site) {  //функция класса WiFi, взаимодействующая с объектом класса Site
    cout << "Сообщение от оператора: Вы успешно зашли на сайт " << site.getName() << " через сеть " << getName() << endl;
    cout << "Сайт работает: " << site.getWork() << endl;
    cout << "Время загрузки сайта: " << site.getTime() << " мс" << endl << endl;
}

void Wired::openSite(Site& site) {  //функция класса WiFi, взаимодействующая с объектом класса Site
    cout << "Сообщение от провайдера: Вы успешно зашли на сайт " << site.getName() << " через роутер от " << getName() << endl;
    cout << "Сайт работает: " << site.getWork() << endl;
    cout << "Время загрузки сайта: " << site.getTime() << " мс" << endl << endl;
}

void Site::status(Wireless& wifi) {  //функция класса Site, взаимодействующая с объектом класса WiFi
    cout << "Сообщение от сайта: Подключение к сайту " << getName() << " осуществляется через сеть " << wifi.getName() << endl;
    cout << "Скорость сети: " << wifi.getSpeed() << " Мбит/с" << endl << endl;
}

void Site::status(Wired& network) {  //функция класса Site, взаимодействующая с объектом класса WiFi
    cout << "Сообщение от сайта: Подключение к сайту " << getName() << " осуществляется через роутер от " << network.getName() << endl;
    cout << "Скорость сети: " << network.getSpeed() << " Мбит/с" << endl << endl;
}

WiFi_router authorization(int number, int& traffic, double& time, string password, WiFi_router& Network, Queue<string>& q, Queue<string>& error, Queue<int>& q_num, int& correct) {
    if (password == Network.getPassword()) {      //если пароль верный, то выводится информация о сети
        WiFi_router Network_Connected(Network);
        q.add(Network.getName());
        q_num.add(number);
        correct++;
        cout << Network;
        traffic = Network.sum(traffic, Network.getTraffic());
        time = Network.sum(time, Network.getTime());
        return Network_Connected;
    }
    else {
        error.add(Network.getName());
        throw MyException("Пароль неверный!");   //если пароль неверный, выводится сообщение об ошибке
        WiFi_router Network_Disconnected(Network);
        return Network_Disconnected;
    }
}

template<typename T>
T authorization(int number, int& traffic, double& time, T& Network, Queue<string>& q, Queue<string>& error, Queue<int>& q_num, int& correct) {
    T Network_Connected(Network);
    q.add(Network.DataDevices::getName());
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
        WiFi_router WiFi_1("CHSU_FREE", "0", security::NoProtection, 100, 70, 5);         //описание доступных WiFi-сетей
        WiFi_router WiFi_2("CHSU_WORK", "1234567890", security::WPA3, 120, 50, 5);
        WiFi_router WiFi_3("IPhone", "ghfdgldklkl", security::WPA2, 80, 40, 2.4);
        WiFi_router WiFi_4("Xiaomi", "h5hjg54g5", security::WPA2, 70, 40, 2.4);
        WiFi_router WiFi_5;
        WiFi_router WiFi_6(WiFi_1);
        WiFi_router WiFi_7(2.4, "Rostelecom");
        WiFi_router WiFi_8(100, 60, "Beeline");
        WiFi_router WiFi_9("iZet");

        Mobile_antenna Mobile_1("MTS RUS", generation::_5G, 70, 100, 5);         //описание доступных мобильных сетей
        Mobile_antenna Mobile_2("Beeline", generation::_2G, 50, 90, 5);
        Mobile_antenna Mobile_3("MegaFon", generation::_4G, 80, 100, 5);
        Mobile_antenna Mobile_4("Tele2", generation::_3G, 50, 80, 5);
        Mobile_antenna Mobile_5;
        Mobile_antenna Mobile_6(Mobile_1);
        Mobile_antenna Mobile_7("Yota");
        Mobile_antenna Mobile_8("Tinkoff Mobile", generation::_3G);
        Mobile_antenna Mobile_9("Мотив", generation::GPRS, 30);

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

        Router Router_1("Rostelecom", Optical, 200, 5);
        Router Router_2;
        Router Router_3(Router_1);

        cout << "Доступные Wi-Fi сети: " << endl;              //вывод доступных Wi-Fi сетей на экран
        cout << "1. " << WiFi_1.getName() << endl;
        cout << "2. " << WiFi_2.getName() << endl;
        cout << "3. " << WiFi_3.getName() << endl;
        cout << "4. " << WiFi_4.getName() << endl;
        cout << "5. " << WiFi_5.getName() << endl;
        cout << "6. " << WiFi_6.getName() << endl;
        cout << "7. " << WiFi_7.getName() << endl;
        cout << "8. " << WiFi_8.getName() << endl;
        cout << "9. " << WiFi_9.getName() << endl << endl;

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
        cout << "24. " << Modem_1.Mobile_antenna::getName() << endl;
        cout << "25. " << Modem_2.Mobile_antenna::getName() << endl;
        cout << "26. " << Modem_3.Mobile_antenna::getName() << endl;
        cout << "27. " << Modem_4.Mobile_antenna::getName() << endl;
        cout << "28. " << Modem_5.Mobile_antenna::getName() << endl;
        cout << "29. " << Modem_6.Mobile_antenna::getName() << endl << endl;

        cout << "Подключенные роутеры: " << endl;              //вывод доступных мобильных сетей на экран
        cout << "30. " << Router_1.getName() << endl;
        cout << "31. " << Router_2.getName() << endl;
        cout << "32. " << Router_3.getName() << endl << endl;

        cout << "0. " << "Вывести историю подключения к сетям" << endl;

        if (count == 0) {
            cout << endl << "Рекомендации: " << endl;
            cout << "Выбирая между сетями " << WiFi_1.getName() << " и " << WiFi_2.getName() << " рекомендуем выбрать сеть ";
            if (WiFi_1 > WiFi_2) cout << WiFi_1.getName();
            else if (WiFi_1 < WiFi_2) cout << WiFi_2.getName();
            cout << ", т.к. её скорость выше" << endl;
            if (WiFi_5 == WiFi_9) cout << "Скорость у сетей " << WiFi_5.getName() << " и " << WiFi_9.getName() << " одинакова" << endl;
            if (WiFi_3 == WiFi_4) cout << "Скорость у сетей " << WiFi_3.getName() << " и " << WiFi_4.getName() << " одинакова" << endl;
            cout << "С помощью сетей " << WiFi_7.getName() << " и " << WiFi_8.getName() << " можно передать " << WiFi_7 + WiFi_8 << " Мб данных" << endl;
        }

        cout << endl << "Введите номер сети/устройства: ";       //выбор сети/устройства
        cin >> number;
        count++;
        try {
            if (number < 0 || number > 32) throw MyException("Такой сети (устройства) нет!");   //если введен номер несуществуещей сети/устройства, выводится сообщение об ошибке
        }
        catch (MyException& ex) {
            cout << "Такой сети (устройства) нет!" << endl << endl;
            continue;
        }
        if (number == 0 && !q.empty()) {
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
            try {
                if (num < 1 || num > 6) throw MyException("Такого варианта нет!");
            }
            catch (MyException& ex) {
                cout << "Такого варианта нет!" << endl << endl;
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
                cout << "1. " << WiFi_1.getName() << endl;
                cout << "2. " << WiFi_2.getName() << endl;
                cout << "3. " << WiFi_3.getName() << endl;
                cout << "4. " << WiFi_4.getName() << endl;
                cout << "5. " << WiFi_5.getName() << endl;
                cout << "6. " << WiFi_6.getName() << endl;
                cout << "7. " << WiFi_7.getName() << endl;
                cout << "8. " << WiFi_8.getName() << endl;
                cout << "9. " << WiFi_9.getName() << endl;
                cout << "10. " << Mobile_1.getName() << endl;
                cout << "11. " << Mobile_2.getName() << endl;
                cout << "12. " << Mobile_3.getName() << endl;
                cout << "13. " << Mobile_4.getName() << endl;
                cout << "14. " << Mobile_5.getName() << endl;
                cout << "15. " << Mobile_6.getName() << endl;
                cout << "16. " << Mobile_7.getName() << endl;
                cout << "17. " << Mobile_8.getName() << endl;
                cout << "18. " << Mobile_9.getName() << endl;
                cout << "19. " << USB_1.getName() << endl;
                cout << "20. " << USB_2.getName() << endl;
                cout << "21. " << USB_3.getName() << endl;
                cout << "22. " << USB_4.getName() << endl;
                cout << "23. " << USB_5.getName() << endl;
                cout << "24. " << Modem_1.Mobile_antenna::getName() << endl;
                cout << "25. " << Modem_2.Mobile_antenna::getName() << endl;
                cout << "26. " << Modem_3.Mobile_antenna::getName() << endl;
                cout << "27. " << Modem_4.Mobile_antenna::getName() << endl;
                cout << "28. " << Modem_5.Mobile_antenna::getName() << endl;
                cout << "29. " << Modem_6.Mobile_antenna::getName() << endl;
                cout << "30. " << Router_1.getName() << endl;
                cout << "31. " << Router_2.getName() << endl;
                cout << "32. " << Router_3.getName() << endl;

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
        WiFi_router Network_Connected;
        Mobile_antenna Mobile_Connected;
        Modem Modem_Connected;
        Router Router_Connected;
        correct = 0;
        try {
            switch (number) {
            case 1: Network_Connected = authorization(number, traffic, time, password, WiFi_1, q, error, q_num, correct);
                break;                                                                 
            case 2: Network_Connected = authorization(number, traffic, time, password, WiFi_2, q, error, q_num, correct);
                break;                                                                
            case 3: Network_Connected = authorization(number, traffic, time, password, WiFi_3, q, error, q_num, correct);
                break;                                                                
            case 4: Network_Connected = authorization(number, traffic, time, password, WiFi_4, q, error, q_num, correct);
                break;                                                                
            case 5: Network_Connected = authorization(number, traffic, time, password, WiFi_5, q, error, q_num, correct);
                break;                                                                
            case 6: Network_Connected = authorization(number, traffic, time, password, WiFi_6, q, error, q_num, correct);
                break;                                                                
            case 7: Network_Connected = authorization(number, traffic, time, password, WiFi_7, q, error, q_num, correct);
                break;                                                                
            case 8: Network_Connected = authorization(number, traffic, time, password, WiFi_8, q, error, q_num, correct);
                break;                                                                
            case 9: Network_Connected = authorization(number, traffic, time, password, WiFi_9, q, error, q_num, correct);
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
            case 30: Router_Connected = authorization(number, traffic, time, Router_1, q, error, q_num, correct);
                break;
            case 31: Router_Connected = authorization(number, traffic, time, Router_2, q, error, q_num, correct);
                break;
            case 32: Router_Connected = authorization(number, traffic, time, Router_3, q, error, q_num, correct);
                break;
            }
        }
        catch (const MyException& ex) {
            cout << "Пароль неверный!" << endl << endl;
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

            try {
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
                default: throw MyException("Такого сайта нет!");
                    break;
                }
            }
            catch (const MyException& ex) {
                cout << "Такого сайта нет!" << endl << endl;
            }
        }
    }
    system("pause");
    return 0;
}