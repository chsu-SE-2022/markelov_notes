#pragma once
#include "windows.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_windows.h>
#include <iomanip>
#include <map>

namespace Device {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;
	using namespace msclr::interop;
	using namespace std;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::ComboBox^ comboBox4;
	private: System::Windows::Forms::ComboBox^ comboBox6;

	private: System::Windows::Forms::ComboBox^ comboBox7;
	private: System::Windows::Forms::ComboBox^ comboBox8;
	private: System::Windows::Forms::ComboBox^ comboBox9;
	private: System::Windows::Forms::ComboBox^ comboBox10;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;

	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Button^ button4;

	private: System::Windows::Forms::ComboBox^ comboBox11;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button5;

	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Button^ button7;


	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::RichTextBox^ richTextBox3;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Label^ label21;



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox8 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox9 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox10 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->comboBox11 = (gcnew System::Windows::Forms::ComboBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"Wi-Fi-роутеры", L"Мобильные антенны", L"Модемы",
					L"Коммутаторы", L"Хабы", L"Флешки", L"Жесткие диски", L"SSD"
			});
			this->comboBox1->Location = System::Drawing::Point(40, 51);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(310, 21);
			this->comboBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label1->Location = System::Drawing::Point(65, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(252, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Выберите класс устройств";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label2->Location = System::Drawing::Point(87, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(196, 24);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Выберите Wi-Fi сеть";
			this->label2->Visible = false;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"CHSU_FREE", L"CHSU_WORK", L"IPhone", L"Xiaomi",
					L"Неопределенная сеть"
			});
			this->comboBox2->Location = System::Drawing::Point(40, 137);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(310, 21);
			this->comboBox2->TabIndex = 3;
			this->comboBox2->Visible = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label3->Location = System::Drawing::Point(65, 98);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(253, 24);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Выберите мобильную сеть";
			this->label3->Visible = false;
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"MTS RUS", L"Beeline", L"MegaFon", L"Tele2", L"Неопределенный оператор" });
			this->comboBox3->Location = System::Drawing::Point(40, 137);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(310, 21);
			this->comboBox3->TabIndex = 5;
			this->comboBox3->Visible = false;
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Kingston", L"WD", L"Corsair", L"Неопознанное USB-устройство",
					L"Kingston"
			});
			this->comboBox4->Location = System::Drawing::Point(40, 137);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(310, 21);
			this->comboBox4->TabIndex = 6;
			this->comboBox4->Visible = false;
			// 
			// comboBox6
			// 
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Rostelecom", L"Неизвестный модем", L"Rostelecom" });
			this->comboBox6->Location = System::Drawing::Point(40, 137);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(310, 21);
			this->comboBox6->TabIndex = 7;
			this->comboBox6->Visible = false;
			// 
			// comboBox7
			// 
			this->comboBox7->FormattingEnabled = true;
			this->comboBox7->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"iZet", L"Неопознанный коммутатор", L"iZet" });
			this->comboBox7->Location = System::Drawing::Point(40, 137);
			this->comboBox7->Name = L"comboBox7";
			this->comboBox7->Size = System::Drawing::Size(310, 21);
			this->comboBox7->TabIndex = 9;
			this->comboBox7->Visible = false;
			// 
			// comboBox8
			// 
			this->comboBox8->FormattingEnabled = true;
			this->comboBox8->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Beeline", L"Неопознанный хаб", L"Beeline" });
			this->comboBox8->Location = System::Drawing::Point(40, 137);
			this->comboBox8->Name = L"comboBox8";
			this->comboBox8->Size = System::Drawing::Size(310, 21);
			this->comboBox8->TabIndex = 10;
			this->comboBox8->Visible = false;
			// 
			// comboBox9
			// 
			this->comboBox9->FormattingEnabled = true;
			this->comboBox9->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Kingston", L"Неопознанный жесткий диск", L"Kingston" });
			this->comboBox9->Location = System::Drawing::Point(40, 137);
			this->comboBox9->Name = L"comboBox9";
			this->comboBox9->Size = System::Drawing::Size(310, 21);
			this->comboBox9->TabIndex = 11;
			this->comboBox9->Visible = false;
			// 
			// comboBox10
			// 
			this->comboBox10->FormattingEnabled = true;
			this->comboBox10->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"WD", L"Неопознанный SSD-диск", L"WD" });
			this->comboBox10->Location = System::Drawing::Point(40, 137);
			this->comboBox10->Name = L"comboBox10";
			this->comboBox10->Size = System::Drawing::Size(310, 21);
			this->comboBox10->TabIndex = 12;
			this->comboBox10->Visible = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label4->Location = System::Drawing::Point(107, 98);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(165, 24);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Выберите модем";
			this->label4->Visible = false;
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(0, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(100, 23);
			this->label5->TabIndex = 51;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label6->Location = System::Drawing::Point(87, 98);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(212, 24);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Выберите коммутатор";
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label7->Location = System::Drawing::Point(121, 98);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(136, 24);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Выберите хаб";
			this->label7->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label8->Location = System::Drawing::Point(87, 98);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(215, 24);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Выберите USB-флешку";
			this->label8->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label9->Location = System::Drawing::Point(74, 98);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(228, 24);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Выберите жесткий диск";
			this->label9->Visible = false;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label10->Location = System::Drawing::Point(93, 98);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(190, 24);
			this->label10->TabIndex = 19;
			this->label10->Text = L"Выберите SSD-диск";
			this->label10->Visible = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(374, 49);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 20;
			this->button1->Text = L"ОК";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(374, 135);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 21;
			this->button2->Text = L"ОК";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label11->Location = System::Drawing::Point(115, 172);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(157, 24);
			this->label11->TabIndex = 22;
			this->label11->Text = L"Введите пароль";
			this->label11->Visible = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(40, 208);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(310, 20);
			this->textBox1->TabIndex = 23;
			this->textBox1->Visible = false;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(374, 206);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 24;
			this->button3->Text = L"ОК";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label12->ForeColor = System::Drawing::Color::Green;
			this->label12->Location = System::Drawing::Point(80, 248);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(238, 24);
			this->label12->TabIndex = 25;
			this->label12->Text = L"Подключение выполнено";
			this->label12->Visible = false;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label13->ForeColor = System::Drawing::Color::Red;
			this->label13->Location = System::Drawing::Point(112, 248);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(171, 24);
			this->label13->TabIndex = 26;
			this->label13->Text = L"Пароль неверный";
			this->label13->Visible = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(299, 291);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(51, 20);
			this->textBox2->TabIndex = 28;
			this->textBox2->Text = L"0";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(299, 329);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(51, 20);
			this->textBox3->TabIndex = 29;
			this->textBox3->Text = L"0";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label14->Location = System::Drawing::Point(74, 286);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(219, 24);
			this->label14->TabIndex = 30;
			this->label14->Text = L"Удачных подключений:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label15->Location = System::Drawing::Point(53, 324);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(240, 24);
			this->label15->TabIndex = 31;
			this->label15->Text = L"Неудачных подключений:";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(299, 370);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(51, 20);
			this->textBox4->TabIndex = 32;
			this->textBox4->Text = L"0";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label16->Location = System::Drawing::Point(116, 366);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(177, 24);
			this->label16->TabIndex = 33;
			this->label16->Text = L"Передано данных:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label17->Location = System::Drawing::Point(42, 407);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(251, 24);
			this->label17->TabIndex = 34;
			this->label17->Text = L"Общее время соединения:";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(299, 409);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(51, 20);
			this->textBox5->TabIndex = 35;
			this->textBox5->Text = L"0";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(156, 444);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 36;
			this->button4->Text = L"Сброс";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// comboBox11
			// 
			this->comboBox11->FormattingEnabled = true;
			this->comboBox11->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"В хронологическом порядке (от старых к новым)",
					L"В обратном хронологическому порядке (от новых к старым)", L"В алфавитном порядке (A-Z)", L"В обратном алфавитному порядке (Z-A)",
					L"Поиск"
			});
			this->comboBox11->Location = System::Drawing::Point(618, 51);
			this->comboBox11->Name = L"comboBox11";
			this->comboBox11->Size = System::Drawing::Size(318, 21);
			this->comboBox11->TabIndex = 38;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(505, 135);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(502, 164);
			this->richTextBox1->TabIndex = 39;
			this->richTextBox1->Text = L"";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(559, 305);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(196, 23);
			this->button5->TabIndex = 40;
			this->button5->Text = L"Вывести для выбранного класса";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label18->Location = System::Drawing::Point(631, 24);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(297, 24);
			this->label18->TabIndex = 37;
			this->label18->Text = L"Вывести историю подключений";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label19->Location = System::Drawing::Point(636, 75);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(286, 24);
			this->label19->TabIndex = 42;
			this->label19->Text = L"Введите название устройства";
			this->label19->Visible = false;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(618, 109);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(318, 20);
			this->textBox6->TabIndex = 43;
			this->textBox6->Visible = false;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(942, 107);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(65, 23);
			this->button7->TabIndex = 44;
			this->button7->Text = L"ОК";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(505, 378);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(502, 217);
			this->richTextBox2->TabIndex = 47;
			this->richTextBox2->Text = L"";
			this->richTextBox2->Visible = false;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label20->Location = System::Drawing::Point(631, 342);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(279, 24);
			this->label20->TabIndex = 48;
			this->label20->Text = L"Выберите файл для передачи";
			this->label20->Visible = false;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(559, 628);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(196, 23);
			this->button9->TabIndex = 49;
			this->button9->Text = L"Загрузить файл";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Visible = false;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// richTextBox3
			// 
			this->richTextBox3->Location = System::Drawing::Point(12, 473);
			this->richTextBox3->Name = L"richTextBox3";
			this->richTextBox3->Size = System::Drawing::Size(461, 178);
			this->richTextBox3->TabIndex = 50;
			this->richTextBox3->Text = L"";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(761, 305);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(196, 23);
			this->button6->TabIndex = 52;
			this->button6->Text = L"Вывести всю историю";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(942, 107);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(65, 23);
			this->button8->TabIndex = 53;
			this->button8->Text = L"ОК";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Visible = false;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(761, 628);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(196, 23);
			this->button10->TabIndex = 54;
			this->button10->Text = L"Передать данные";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Visible = false;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label21->ForeColor = System::Drawing::Color::Green;
			this->label21->Location = System::Drawing::Point(670, 598);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(175, 24);
			this->label21->TabIndex = 55;
			this->label21->Text = L"Данные переданы";
			this->label21->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1019, 663);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->richTextBox3);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->comboBox11);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->comboBox10);
			this->Controls->Add(this->comboBox9);
			this->Controls->Add(this->comboBox8);
			this->Controls->Add(this->comboBox7);
			this->Controls->Add(this->comboBox6);
			this->Controls->Add(this->comboBox4);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Устройства передачи данных";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	public: int getIndex1() {
		return comboBox1->SelectedIndex;
	}
	public: int getIndex2(int index) {
		switch (index) {
		case 0: return comboBox2->SelectedIndex;
			break;
		case 1: return comboBox3->SelectedIndex;
			break;
		case 2: return comboBox6->SelectedIndex;
			break;
		case 3: return comboBox7->SelectedIndex;
			break;
		case 4: return comboBox8->SelectedIndex;
			break;
		case 5: return comboBox4->SelectedIndex;
			break;
		case 6: return comboBox9->SelectedIndex;
			break;
		case 7: return comboBox10->SelectedIndex;
			break;
		}
	}
	public: int getIndex3() {
		return comboBox11->SelectedIndex;
	}
	public: void setLucky(String^ value) {
		this->textBox2->Text = value;
	}
	public: void setUnlucky(String^ value) {
		this->textBox3->Text = value;
	}
	public: void setTraffic(String^ value) {
		this->textBox4->Text = value;
	}
	public: void setTime(String^ value) {
		this->textBox5->Text = value;
	}
	public: void setText(String^ value) {
		this->richTextBox1->AppendText(value + "\n");
	}
	public: void setClear() {
		this->richTextBox1->Clear();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		button2->Visible = true;
		this->textBox1->Visible = false;
		this->label11->Visible = false;
		this->label12->Visible = false;
		this->label13->Visible = false;
		this->button3->Visible = false;
		button9->Visible = false;
		label20->Visible = false;
		richTextBox2->Visible = false;
		switch (comboBox1->SelectedIndex) {
		case 0: {
			label2->Visible = true;
			comboBox2->Visible = true;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = false;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = false;
			label7->Visible = false;
			comboBox7->Visible = false;
			label8->Visible = false;
			comboBox8->Visible = false;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			break;
		case 1: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = true;
			comboBox3->Visible = true;
			label4->Visible = false;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = false;
			label7->Visible = false;
			comboBox7->Visible = false;
			label8->Visible = false;
			comboBox8->Visible = false;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			break;
		case 2: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = true;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = true;
			label6->Visible = false;
			label7->Visible = false;
			comboBox7->Visible = false;
			label8->Visible = false;
			comboBox8->Visible = false;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			  break;
		case 3: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = false;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = true;
			label7->Visible = false;
			comboBox7->Visible = true;
			label8->Visible = false;
			comboBox8->Visible = false;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			  break;
		case 4: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = false;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = false;
			label7->Visible = true;
			comboBox7->Visible = false;
			label8->Visible = false;
			comboBox8->Visible = true;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			  break;
		case 5: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = false;
			comboBox4->Visible = true;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = false;
			label7->Visible = false;
			comboBox7->Visible = false;
			label8->Visible = true;
			comboBox8->Visible = false;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			  break;
		case 6: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = false;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = false;
			label7->Visible = false;
			comboBox7->Visible = false;
			label8->Visible = false;
			comboBox8->Visible = false;
			label9->Visible = true;
			comboBox9->Visible = true;
			label10->Visible = false;
			comboBox10->Visible = false;
		}
			  break;
		case 7: {
			label2->Visible = false;
			comboBox2->Visible = false;
			label3->Visible = false;
			comboBox3->Visible = false;
			label4->Visible = false;
			comboBox4->Visible = false;
			label5->Visible = false;
			comboBox6->Visible = false;
			label6->Visible = false;
			label7->Visible = false;
			comboBox7->Visible = false;
			label8->Visible = false;
			comboBox8->Visible = false;
			label9->Visible = false;
			comboBox9->Visible = false;
			label10->Visible = true;
			comboBox10->Visible = true;
		}
			  break;
		}
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
	setlocale(LC_ALL, "Russian");
	OpenFileDialog^ openFile = gcnew OpenFileDialog();
	openFile->Filter = "Текстовые файлы (*.txt)|*.txt";
	String^ fileName;
	if (System::Windows::Forms::DialogResult::OK == openFile->ShowDialog()) fileName = openFile->FileName;
	label21->Visible = false;
	button10->Visible = true;
	try {
		StreamReader^ file = gcnew StreamReader(fileName, Encoding::GetEncoding("windows-1251"));
		richTextBox2->Text = file->ReadToEnd();
	}
	catch (Exception^ e)
	{
		richTextBox2->Text = "Ошибка открытия файла!";
	}
}
};
}