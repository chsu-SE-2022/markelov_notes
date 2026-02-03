#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_windows.h>
#include <msclr\marshal_atl.h>




namespace лб1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
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
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label47;
	private: System::Windows::Forms::Label^ label48;
	private: System::Windows::Forms::Label^ label49;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(470, 279);
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox4->Location = System::Drawing::Point(330, 545);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(614, 29);
			this->textBox4->TabIndex = 21;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox3->Location = System::Drawing::Point(330, 608);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(614, 29);
			this->textBox3->TabIndex = 20;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox1->Location = System::Drawing::Point(330, 576);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(614, 29);
			this->textBox1->TabIndex = 19;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->label3->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label3->Location = System::Drawing::Point(432, 337);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(375, 26);
			this->label3->TabIndex = 18;
			this->label3->Text = L"(через ОДИН пробел, без запятых)";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->button2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button2->Location = System::Drawing::Point(330, 414);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(273, 94);
			this->button2->TabIndex = 17;
			this->button2->Text = L"Запустить автоматический режим";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label2->Location = System::Drawing::Point(515, 511);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(241, 31);
			this->label2->TabIndex = 16;
			this->label2->Text = L"Результат работы";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label1->Location = System::Drawing::Point(528, 306);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(211, 31);
			this->label1->TabIndex = 15;
			this->label1->Text = L"Введите строки";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox2->Location = System::Drawing::Point(330, 376);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(614, 29);
			this->textBox2->TabIndex = 14;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->button1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button1->Location = System::Drawing::Point(671, 414);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(273, 94);
			this->button1->TabIndex = 13;
			this->button1->Text = L"Запустить пошаговый режим";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label47->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label47->Location = System::Drawing::Point(53, 543);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(271, 31);
			this->label47->TabIndex = 66;
			this->label47->Text = L"Правильные строки:";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label48->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label48->Location = System::Drawing::Point(23, 572);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(301, 31);
			this->label48->TabIndex = 67;
			this->label48->Text = L"Неправильные строки:";
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label49->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label49->Location = System::Drawing::Point(284, 605);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(40, 31);
			this->label49->TabIndex = 68;
			this->label49->Text = L"S:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label4->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label4->Location = System::Drawing::Point(515, 79);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(241, 31);
			this->label4->TabIndex = 69;
			this->label4->Text = L"A = {X, S, S0, F, δ}";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label5->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label5->Location = System::Drawing::Point(515, 122);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(125, 31);
			this->label5->TabIndex = 70;
			this->label5->Text = L"X = {0, 1}";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label6->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label6->Location = System::Drawing::Point(515, 165);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(257, 31);
			this->label6->TabIndex = 71;
			this->label6->Text = L"S = {S0, S1, S2, S3}";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label7->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label7->Location = System::Drawing::Point(515, 212);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(128, 31);
			this->label7->TabIndex = 72;
			this->label7->Text = L"S0 = {S0}";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label8->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label8->Location = System::Drawing::Point(515, 258);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(112, 31);
			this->label8->TabIndex = 73;
			this->label8->Text = L"F = {S3}";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label9->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label9->Location = System::Drawing::Point(1011, 12);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(37, 31);
			this->label9->TabIndex = 74;
			this->label9->Text = L"δ:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label10->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label10->Location = System::Drawing::Point(1011, 55);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(169, 31);
			this->label10->TabIndex = 75;
			this->label10->Text = L"(S0, 0) → S1";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label11->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label11->Location = System::Drawing::Point(1011, 98);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(169, 31);
			this->label11->TabIndex = 76;
			this->label11->Text = L"(S0, 1) → S0";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label12->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label12->Location = System::Drawing::Point(1011, 145);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(169, 31);
			this->label12->TabIndex = 77;
			this->label12->Text = L"(S1, 0) → S3";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label13->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label13->Location = System::Drawing::Point(1011, 191);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(169, 31);
			this->label13->TabIndex = 78;
			this->label13->Text = L"(S1, 1) → S2";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label14->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label14->Location = System::Drawing::Point(1011, 238);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(169, 31);
			this->label14->TabIndex = 79;
			this->label14->Text = L"(S2, 0) → S3";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label15->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label15->Location = System::Drawing::Point(1011, 285);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(169, 31);
			this->label15->TabIndex = 80;
			this->label15->Text = L"(S2, 1) → S2";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label16->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label16->Location = System::Drawing::Point(1011, 332);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(169, 31);
			this->label16->TabIndex = 81;
			this->label16->Text = L"(S3, 0) → S1";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label17->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label17->Location = System::Drawing::Point(1011, 376);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(169, 31);
			this->label17->TabIndex = 82;
			this->label17->Text = L"(S3, 1) → S0";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->label18->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label18->Location = System::Drawing::Point(515, 20);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(179, 46);
			this->label18->TabIndex = 83;
			this->label18->Text = L"(1*01*0)*";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1260, 640);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label49);
			this->Controls->Add(this->label48);
			this->Controls->Add(this->label47);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Распознавание строк";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		int Automat(int x[], int s[], int k, int count) {
			switch (s[k]) {
			case 0: {
				if (x[k] == 0) s[k + 1] = 1;
				else s[k + 1] = 0;
			}
				  break;
			case 1: {
				if (x[k] == 0) s[k + 1] = 3;
				else s[k + 1] = 2;
			}
				  break;
			case 2: {
				if (x[k] == 0) s[k + 1] = 3;
				else s[k + 1] = 2;
			}
				  break;
			case 3: {
				if (x[k] == 0) s[k + 1] = 1;
				else s[k + 1] = 0;
			}
				  break;
			}
			if (s[k + 1] == 1) count++;
			else if (s[k + 1] == 3) count--;
			return count;
		}

#pragma endregion
		private: System::Void ProcessTextFromRichTextBox() {
			button1_Click(nullptr, nullptr);
		}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		setlocale(LC_ALL, "Russian");
		String^ sx = textBox2->Text;
		string str_x = marshal_as<string>(sx), str_s = "", str_true = "", str_false = "";
		for (int i = 0; i < str_x.length() + 1; i++) {
			if (str_x[i] == ' ') {
				textBox4->Text = "Ошибка! Введено больше одной строки";
				textBox1->Text = "";
				textBox3->Text = "";
				return;
			}
			if (str_x[i] != '0' && str_x[i] != '1' && str_x[i] != ' ' && str_x[i] != '\0') {
				textBox4->Text = "Ошибка! В строке содержатся символы, не входящие в алфавит";
				textBox1->Text = "";
				textBox3->Text = "";
				return;
			}
		}
		int i = 0, j = 0;
		string str_result = "";
		int count = 0;
		int* x = new int[str_x.length() + 1];
		int* s = new int[str_x.length() + 1];
		s[0] = 0;
		j = 0;
		while (str_x[i] != ' ' && str_x[i] != '\0') {
			if (str_x[i] == '0') x[j] = 0;
			else x[j] = 1;
			i++;
			j++;
		}
		for (int k = 0; k < j; k++) {
			count = Automat(x, s, k, count);
		}
		for (int k = 0; k < j; k++) {
			if (x[k] == 0) str_result += "0";
			else str_result += "1";
		}
		for (int k = 0; k <= j; k++) {
			if (s[k] == 0) str_s += "S0 ";
			else if (s[k] == 1) str_s += "S1 ";
			else if (s[k] == 2) str_s += "S2 ";
			else if (s[k] == 3) str_s += "S3 ";
		}
		str_result += " ";
		if (count == 0) str_true += str_result;
		else str_false += str_result;
		delete[] x;
		delete[] s;
		i++;
		String^ str_t = marshal_as<String^>(str_true);
		String^ str_f = marshal_as<String^>(str_false);
		String^ str_automat = marshal_as<String^>(str_s);
		textBox4->Text = str_t;
		textBox1->Text = str_f;
		textBox3->Text = str_automat;
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		setlocale(LC_ALL, "Russian");
		int n = 0;
		String^ sx = textBox2->Text;
		string str_x = marshal_as<string>(sx), str_true = "", str_false = "";
		for (int i = 0; i < str_x.length() + 1; i++) {
			if (str_x[i] == ' ' || str_x[i] == '\0') n++;
			if (str_x[0] == ' ' || (str_x[i] == ' ' && str_x[i - 1] == ' ')) {
				textBox4->Text = "Ошибка! Введен лишний пробел";
				textBox1->Text = "";
				textBox3->Text = "";
				return;
			}
			if (str_x[i] != '0' && str_x[i] != '1' && str_x[i] != ' ' && str_x[i] != '\0') {
				textBox4->Text = "Ошибка! В строке содержатся символы, не входящие в алфавит";
				textBox1->Text = "";
				textBox3->Text = "";
				return;
			}
		}
		int i = 0, j = 0;
		for (int m = 1; m <= n; m++) {
			string str_result = "";
			int count = 0;
			int* x = new int[str_x.length() + 1];
			int* s = new int[str_x.length() + 1];
			s[0] = 0;
			j = 0;
			while (str_x[i] != ' ' && str_x[i] != '\0') {
				if (str_x[i] == '0') x[j] = 0;
				else x[j] = 1;
				i++;
				j++;
			}
			for (int k = 0; k < j; k++) {
				count = Automat(x, s, k, count);
			}
			for (int k = 0; k < j; k++) {
				if (x[k] == 0) str_result += "0";
				else str_result += "1";
			}
			str_result += " ";
			if (count == 0) str_true += str_result;
			else str_false += str_result;
			delete[] x;
			delete[] s;
			i++;
		}
		String^ str_t = marshal_as<String^>(str_true);
		String^ str_f = marshal_as<String^>(str_false);
		textBox4->Text = str_t;
		textBox1->Text = str_f;
		textBox3->Text = "";
	}
};
}