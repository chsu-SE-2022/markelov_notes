#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include "DataDevices_i.h"
#include "Exception.h"
#include "Vector.h"
#include "MyForm.h"
using namespace std;

int lucky = 0, unlucky = 0, traffic = 0;
double times = 0;
string name;

string DataDevices::work = "Да";

Vector<DataDevices_i*> v;
Queue<WiFi_router> q_wifi;
Queue<Mobile_antenna> q_mob;
Queue<Modem> q_rout;
Queue<Switch> q_sw;
Queue<Hub> q_hub;
Queue<Flash> q_fl;
Queue<HDD> q_hdd;
Queue<SSD> q_ssd;

WiFi_router WiFi_1("CHSU_FREE", "0", security::NoProtection, 100, 70, 5);         //описание доступных WiFi-сетей
WiFi_router WiFi_2("CHSU_WORK", "1234567890", security::WPA3, 120, 50, 5);
WiFi_router WiFi_3("IPhone", "ghfdgldklkl", security::WPA2, 80, 40, 2.4);
WiFi_router WiFi_4("Xiaomi", "h5hjg54g5", security::WPA2, 70, 40, 2.4);
WiFi_router WiFi_5;

Mobile_antenna Mobile_1("MTS RUS", generation::_5G, 70, 100, 5);         //описание доступных мобильных сетей
Mobile_antenna Mobile_2("Beeline", generation::_2G, 50, 90, 5);
Mobile_antenna Mobile_3("MegaFon", generation::_4G, 80, 100, 5);
Mobile_antenna Mobile_4("Tele2", generation::_3G, 50, 80, 5);
Mobile_antenna Mobile_5;

Modem Router_1("Rostelecom", Optical, 200, 5, line::Ethernet);
Modem Router_2;
Modem Router_3(Router_1);

Switch Switch_1("iZet", Coaxial, 100, 3, 8);
Switch Switch_2;
Switch Switch_3(Switch_1);

Hub Hub_1("Beeline", Twisted, 150, 4, 32);
Hub Hub_2;
Hub Hub_3(Hub_1);

Flash USB_1("Kingston", 8, 3.1, 'A', 30);
Flash USB_2("WD");
Flash USB_3("Corsair", 2);
Flash USB_4;

HDD HDD_1("Kingston", 1024, connect_type::SATA, 100);
HDD HDD_2;
HDD HDD_3(HDD_1);

SSD SSD_1("WD", 512, connect_type2::_M2, 500);
SSD SSD_2;
SSD SSD_3(SSD_1);

template <class T>
String^ authorization(T& obj, Queue<T>& q) {
    traffic += obj.getTraffic();
    times += obj.getTime();
    q.add(obj);
    v.add(&obj);
    return obj.getInfo();
}

System::Void Device::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
    Device::MyForm^ myForm = this;
    String^ info;
    label21->Visible = false;
    button10->Visible = false;
    if (Device::MyForm::getIndex1() * 10 + Device::MyForm::getIndex2(Device::MyForm::getIndex1()) >= 10) {
        lucky++;
        button9->Visible = true;
        label20->Visible = true;
        richTextBox2->Visible = true;
        label12->Visible = true;
    }
    setLucky(System::Convert::ToString(lucky));
    switch (Device::MyForm::getIndex1() * 10 + Device::MyForm::getIndex2(Device::MyForm::getIndex1())) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4: {
        textBox1->Visible = true;
        label11->Visible = true;
        button3->Visible = true;
    }
          break;
    case 10: info = authorization(Mobile_1, q_mob);
        richTextBox3->Text = info + "\nИнформация записана в файл Mobile.txt";
          break;
    case 11: info = authorization(Mobile_2, q_mob);
        richTextBox3->Text = info + "\nИнформация записана в файл Mobile.txt";
           break;
    case 12: info = authorization(Mobile_3, q_mob);
        richTextBox3->Text = info + "\nИнформация записана в файл Mobile.txt";
           break;
    case 13: info = authorization(Mobile_4, q_mob);
        richTextBox3->Text = info + "\nИнформация записана в файл Mobile.txt";
           break;
    case 14: info = authorization(Mobile_5, q_mob);
        richTextBox3->Text = info + "\nИнформация записана в файл Mobile.txt";
           break;
    case 20: info = authorization(Router_1, q_rout);
        richTextBox3->Text = info + "\nИнформация записана в файл Modem.txt";
           break;
    case 21: info = authorization(Router_2, q_rout);
        richTextBox3->Text = info + "\nИнформация записана в файл Modem.txt";
           break;
    case 22: info = authorization(Router_3, q_rout);
        richTextBox3->Text = info + "\nИнформация записана в файл Modem.txt";
           break;
    case 30: info = authorization(Switch_1, q_sw);
        richTextBox3->Text = info + "\nИнформация записана в файл Switch.txt";
           break;
    case 31: info = authorization(Switch_2, q_sw);
        richTextBox3->Text = info + "\nИнформация записана в файл Switch.txt";
           break;
    case 32: info = authorization(Switch_3, q_sw);
        richTextBox3->Text = info + "\nИнформация записана в файл Switch.txt";
           break;
    case 40: info = authorization(Hub_1, q_hub);
        richTextBox3->Text = info + "\nИнформация записана в файл Hub.txt";
           break;
    case 41: info = authorization(Hub_2, q_hub);
        richTextBox3->Text = info + "\nИнформация записана в файл Hub.txt";
           break;
    case 42: info = authorization(Hub_3, q_hub);
        richTextBox3->Text = info + "\nИнформация записана в файл Hub.txt";
           break;
    case 50: info = authorization(USB_1, q_fl);
        richTextBox3->Text = info + "\nИнформация записана в файл Flash.txt";
           break;
    case 51: info = authorization(USB_2, q_fl);
        richTextBox3->Text = info + "\nИнформация записана в файл Flash.txt";
           break;
    case 52: info = authorization(USB_3, q_fl);
        richTextBox3->Text = info + "\nИнформация записана в файл Flash.txt";
           break;
    case 53: info = authorization(USB_4, q_fl);
        richTextBox3->Text = info + "\nИнформация записана в файл Flash.txt";
           break;
    case 60: info = authorization(HDD_1, q_hdd);
        richTextBox3->Text = info + "\nИнформация записана в файл HDD.txt";
           break;
    case 61: info = authorization(HDD_2, q_hdd);
        richTextBox3->Text = info + "\nИнформация записана в файл HDD.txt";
           break;
    case 62: info = authorization(HDD_3, q_hdd);
        richTextBox3->Text = info + "\nИнформация записана в файл HDD.txt";
           break;
    case 70: info = authorization(SSD_1, q_ssd);
        richTextBox3->Text = info + "\nИнформация записана в файл SSD.txt";
           break;
    case 71: info = authorization(SSD_2, q_ssd);
        richTextBox3->Text = info + "\nИнформация записана в файл SSD.txt";
           break;
    case 72: info = authorization(SSD_3, q_ssd);
        richTextBox3->Text = info + "\nИнформация записана в файл SSD.txt";
           break;
    }
    Device::MyForm::setTraffic(System::Convert::ToString(traffic));
    Device::MyForm::setTime(System::Convert::ToString(times));
}

System::Void Device::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
    String^ info;
    switch (Device::MyForm::getIndex1() * 10 + Device::MyForm::getIndex2(Device::MyForm::getIndex1())) {
    case 0: {
        try {
            if (WiFi_1.getPassword() == marshal_as<string>(textBox1->Text)) {
                label12->Visible = true;
                label13->Visible = false;
                button9->Visible = true;
                label20->Visible = true;
                richTextBox2->Visible = true;
                lucky++;
                setLucky(System::Convert::ToString(lucky));
                info = authorization(WiFi_1, q_wifi);
                richTextBox3->Text = info + "\nИнформация записана в файл WiFi.txt";
            }
            else {
                throw MyException("Пароль неверный!");
                
            }
        }
        catch (MyException& ex) {
            label12->Visible = false;
            label13->Visible = true;
            button9->Visible = false;
            label20->Visible = false;
            richTextBox2->Visible = false;
            unlucky++;
            setUnlucky(System::Convert::ToString(unlucky));

        }
    }
          break;
    case 1: {
        try {
            if (WiFi_2.getPassword() == marshal_as<string>(textBox1->Text)) {
                label12->Visible = true;
                label13->Visible = false;
                button9->Visible = true;
                label20->Visible = true;
                richTextBox2->Visible = true;
                lucky++;
                setLucky(System::Convert::ToString(lucky));
                info = authorization(WiFi_2, q_wifi);
                richTextBox3->Text = info + "\nИнформация записана в файл WiFi.txt";
            }
            else {
                throw MyException("Пароль неверный!");

            }
        }
        catch (MyException& ex) {
            label12->Visible = false;
            label13->Visible = true;
            button9->Visible = false;
            label20->Visible = false;
            richTextBox2->Visible = false;
            unlucky++;
            setUnlucky(System::Convert::ToString(unlucky));
        }
    }
          break;
    case 2: {
        try {
            if (WiFi_3.getPassword() == marshal_as<string>(textBox1->Text)) {
                label12->Visible = true;
                label13->Visible = false;
                button9->Visible = true;
                label20->Visible = true;
                richTextBox2->Visible = true;
                lucky++;
                setLucky(System::Convert::ToString(lucky));
                info = authorization(WiFi_3, q_wifi);
                richTextBox3->Text = info + "\nИнформация записана в файл WiFi.txt";
            }
            else {
                throw MyException("Пароль неверный!");

            }
        }
        catch (MyException& ex) {
            label12->Visible = false;
            label13->Visible = true;
            button9->Visible = false;
            label20->Visible = false;
            richTextBox2->Visible = false;
            unlucky++;
            setUnlucky(System::Convert::ToString(unlucky));
        }
    }
          break;
    case 3: {
        try {
            if (WiFi_4.getPassword() == marshal_as<string>(textBox1->Text)) {
                label12->Visible = true;
                label13->Visible = false;
                button9->Visible = true;
                label20->Visible = true;
                richTextBox2->Visible = true;
                lucky++;
                setLucky(System::Convert::ToString(lucky));
                info = authorization(WiFi_4, q_wifi);
                richTextBox3->Text = info + "\nИнформация записана в файл WiFi.txt";
            }
            else {
                throw MyException("Пароль неверный!");

            }
        }
        catch (MyException& ex) {
            label12->Visible = false;
            label13->Visible = true;
            button9->Visible = false;
            label20->Visible = false;
            richTextBox2->Visible = false;
            unlucky++;
            setUnlucky(System::Convert::ToString(unlucky));
        }
    }
          break;
    case 4: {
        try {
            if (WiFi_5.getPassword() == marshal_as<string>(textBox1->Text)) {
                label12->Visible = true;
                label13->Visible = false;
                button9->Visible = true;
                label20->Visible = true;
                richTextBox2->Visible = true;
                lucky++;
                setLucky(System::Convert::ToString(lucky));
                info = authorization(WiFi_5, q_wifi);
                richTextBox3->Text = info + "\nИнформация записана в файл WiFi.txt";
            }
            else {
                throw MyException("Пароль неверный!");

            }
        }
        catch (MyException& ex) {
            label12->Visible = false;
            label13->Visible = true;
            button9->Visible = false;
            label20->Visible = false;
            richTextBox2->Visible = false;
            unlucky++;
            setUnlucky(System::Convert::ToString(unlucky));
        }
    }
          break;
    }
    Device::MyForm::setTraffic(System::Convert::ToString(traffic));
    Device::MyForm::setTime(System::Convert::ToString(times));
}

System::Void Device::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {
    lucky = 0;
    unlucky = 0;
    traffic = 0;
    times = 0;
    setLucky(System::Convert::ToString(lucky));
    setUnlucky(System::Convert::ToString(unlucky));
    Device::MyForm::setTraffic(System::Convert::ToString(traffic));
    Device::MyForm::setTime(System::Convert::ToString(times));
}

System::Void Device::MyForm::button5_Click(System::Object^ sender, System::EventArgs^ e) {
    Device::MyForm^ myForm = this;
    if (Device::MyForm::getIndex3() == 4) {
        textBox6->Visible = true;
        label19->Visible = true;
        button7->Visible = true;
        button8->Visible = false;
    }
    else {
        textBox6->Visible = false;
        label19->Visible = false;
        button7->Visible = false;
    }
    ofstream result;
    result.open("result.txt");
    string s;
    switch (Device::MyForm::getIndex1() * 10 + Device::MyForm::getIndex3()) {
    case 0: {
        if (q_wifi.getSize() <= 20) {
            s << q_wifi;
            richTextBox1->Text = marshal_as<String^>(s);
        }
            else result << q_wifi;
        }
          break;
    case 1: q_wifi.print_NewOld(result, myForm);
        break;
    case 2: q_wifi.print_AZ(result, myForm);
        break;
    case 3: q_wifi.print_ZA(result, myForm);
        break;
    case 10: {
        if (q_mob.getSize() <= 20) {
            s << q_mob;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_mob;
    }
           break;
    case 11: q_mob.print_NewOld(result, myForm);
        break;
    case 12: q_mob.print_AZ(result, myForm);
        break;
    case 13: q_mob.print_ZA(result, myForm);
        break;
    case 20: {
        if (q_rout.getSize() <= 20) {
            s << q_rout;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_wifi;
    }
           break;
    case 21: q_rout.print_NewOld(result, myForm);
        break;
    case 22: q_rout.print_AZ(result, myForm);
        break;
    case 23: q_rout.print_ZA(result, myForm);
        break;
    case 30: {
        if (q_sw.getSize() <= 20) {
            s << q_sw;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_sw;
    }
           break;
    case 31: q_sw.print_NewOld(result, myForm);
        break;
    case 32: q_sw.print_AZ(result, myForm);
        break;
    case 33: q_sw.print_ZA(result, myForm);
        break;
    case 40: {
        if (q_hub.getSize() <= 20) {
            s << q_hub;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_hub;
    }
           break;
    case 41: q_hub.print_NewOld(result, myForm);
        break;
    case 42: q_hub.print_AZ(result, myForm);
        break;
    case 43: q_hub.print_ZA(result, myForm);
        break;
    case 50: {
        if (q_fl.getSize() <= 20) {
            s << q_wifi;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_fl;
    }
           break;
    case 51: q_fl.print_NewOld(result, myForm);
        break;
    case 52: q_fl.print_AZ(result, myForm);
        break;
    case 53: q_fl.print_ZA(result, myForm);
        break;
    case 60: {
        if (q_hdd.getSize() <= 20) {
            s << q_hdd;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_hdd;
    }
           break;
    case 61: q_hdd.print_NewOld(result, myForm);
        break;
    case 62: q_hdd.print_AZ(result, myForm);
        break;
    case 63: q_hdd.print_ZA(result, myForm);
        break;
    case 70: {
        if (q_ssd.getSize() <= 20) {
            s << q_ssd;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << q_ssd;
    }
           break;
    case 71: q_ssd.print_NewOld(result, myForm);
        break;
    case 72: q_ssd.print_AZ(result, myForm);
        break;
    case 73: q_ssd.print_ZA(result, myForm);
        break;
    }
    result.close();
}

System::Void Device::MyForm::button6_Click(System::Object^ sender, System::EventArgs^ e) {
    Device::MyForm^ myForm = this;
    ofstream result;
    result.open("result.txt");
    string s;
    if (Device::MyForm::getIndex3() == 4) {
        textBox6->Visible = true;
        label19->Visible = true;
        button7->Visible = false;
        button8->Visible = true;
    }
    else {
        textBox6->Visible = false;
        label19->Visible = false;
        button8->Visible = false;
    }
    switch (Device::MyForm::getIndex3()) {
    case 0: {
        if (v.getSize() == 0) {
            richTextBox1->Text = "Подключений не было";
        }
        else if (v.getSize() <= 20) {
            s << v;
            richTextBox1->Text = marshal_as<String^>(s);
        }
        else result << v;
    }
          break;
    case 1: v.print_NewOld(result, myForm);
        break;
    case 2: v.print_AZ(result, myForm);
        break;
    case 3: v.print_ZA(result, myForm);
        break;
    }
    result.close();
}

System::Void Device::MyForm::button7_Click(System::Object^ sender, System::EventArgs^ e) {
    Device::MyForm^ myForm = this;
    switch (Device::MyForm::getIndex1()) {
    case 0: {
        q_wifi.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 1: {
        q_mob.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 2: {
        q_rout.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 3: {
        q_sw.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 4: {
        q_hub.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 5: {
        q_fl.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 6: {
        q_hdd.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    case 7: {
        q_ssd.search(marshal_as<string>(textBox6->Text), myForm);
    }
          break;
    }
}

System::Void Device::MyForm::button8_Click(System::Object^ sender, System::EventArgs^ e) {
    Device::MyForm^ myForm = this;
    v.search(marshal_as<string>(textBox6->Text), myForm);
}

System::Void Device::MyForm::button10_Click(System::Object^ sender, System::EventArgs^ e) {
    Device::MyForm^ myForm = this;
    v.broadcast(richTextBox2->Text, myForm);   
    label21->Visible = true;
}