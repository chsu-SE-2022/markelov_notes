#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_windows.h>
#include <msclr\marshal_atl.h>

namespace лб1_2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
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


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RichTextBox^ richTextBox3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::RichTextBox^ richTextBox4;
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->richTextBox4 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label1->Location = System::Drawing::Point(104, 9);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(242, 39);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Исходный код";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label2->Location = System::Drawing::Point(912, 9);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(319, 39);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Обработанный код";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->button1->Location = System::Drawing::Point(527, 682);
			this->button1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(256, 64);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Обработать код";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(16, 65);
			this->richTextBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(456, 707);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(835, 65);
			this->richTextBox2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(456, 707);
			this->richTextBox2->TabIndex = 6;
			this->richTextBox2->Text = L"";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->button2->Location = System::Drawing::Point(527, 586);
			this->button2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(256, 64);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Выбрать файл";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label3->Location = System::Drawing::Point(521, 506);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(167, 29);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Строк в коде:";
			// 
			// richTextBox3
			// 
			this->richTextBox3->Location = System::Drawing::Point(717, 507);
			this->richTextBox3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->richTextBox3->Name = L"richTextBox3";
			this->richTextBox3->ReadOnly = true;
			this->richTextBox3->Size = System::Drawing::Size(64, 27);
			this->richTextBox3->TabIndex = 9;
			this->richTextBox3->Text = L"";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label4->Location = System::Drawing::Point(600, 106);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(108, 29);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Ошибки";
			// 
			// richTextBox4
			// 
			this->richTextBox4->Location = System::Drawing::Point(493, 149);
			this->richTextBox4->Margin = System::Windows::Forms::Padding(4);
			this->richTextBox4->Name = L"richTextBox4";
			this->richTextBox4->ReadOnly = true;
			this->richTextBox4->Size = System::Drawing::Size(323, 31);
			this->richTextBox4->TabIndex = 11;
			this->richTextBox4->Text = L"";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1308, 788);
			this->Controls->Add(this->richTextBox4);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->richTextBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Распознавание строк";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		int Automat(char c, int s) {
			switch (s) {
			case 0: { //начало новой строки, увеличивается счетчик
				if (c == '\n') return 12;
				else if (c == '/') return 4;
				else if (c == ' ') return 3;
				else return 1;
			}
				  break;
			case 1: { //обнаружен другой символ кода
				if (c == ' ') return 2;
				else if (c == '\n') return 0;
				else if (c == '/') return 4;
				else return 1;
			}
				  break;
			case 2: { //обнаружен 1 пробел
				if (c == ' ') return 3;
				else if (c == '\n') return 0;
				else if (c == '/') return 4;
				else return 1;
			}
				  break;
			case 3: { //обнаружен 2 пробел подряд, он пропускается
				if (c == ' ') return 3;
				else if (c == '\n') return 0;
				else if (c == '/') return 4;
				else return 1;
			}
				  break;
			case 4: { //обнаружен 1 слеш
				if (c == ' ') return 2;
				else if (c == '\n') return 0;
				else if (c == '/') return 5;
				else if (c == '*') return 7;
				else return 1;
			}
				  break;
			case 5: { //обнаружен 2 слеш подряд, начался однострочный комментарий
				if (c == '\n') return 0;
				else return 6;
			}
				  break;
			case 6: { //пропуск символов однострочного комментария
				if (c == '\n') return 0;
				else return 6;
			}
				  break;
			case 7: { //обнаружена звездочка после слеша, начался многострочный комментарий
				if (c == '*') return 9;
				else if (c == '\n') return 11;
				else return 8;
			}
				  break;
			case 8: { //пропуск символов многострочного комментария
				if (c == '*') return 9;
				else if (c == '\n') return 11;
				else return 8;
			}
				  break;
			case 9: { //обнаружена звездочка в многострочном комментарии
				if (c == '*') return 9;
				else if (c == '\n') return 11;
				else if (c == '/') return 10;
				else return 8;
			}
				  break;
			case 10: { //обнаружен слеш после звездочки в многострочном комментарии, комментарий закончен
				if (c == '\n') return 0;
				else if (c == '/') return 4;
				else if (c == ' ') return 2;
				else return 1;
			}
				   break;
			case 11: { //обнаружен перенос строки в многострочном комментарии, увеличивается счетчик
				if (c == '\n') return 11;
				else if (c == '*') return 9;
				else return 8;
			}
				   break;
			case 12: { //обнаружен 2 перенос строки подряд, он пропускается
				if (c == '\n') return 12;
				else if (c == '/') return 4;
				else if (c == ' ') return 3;
				else return 1;
			}
			}
		}

#pragma endregion
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	setlocale(LC_ALL, "Russian");
	richTextBox2->Text = "";
	if (richTextBox1->Text == "") richTextBox2->Text = "Код не введен!";
	int n = 0, k1 = 0, k2 = 0, count = 0;
	char c;
	String^ str1 = "";
	String^ str00 = richTextBox1->Text;
	str00 += "\n";
	string str = "";
	string str0 = marshal_as<string>(str00);
	int s = 0;
	for (int i = 0; i < str0.length(); i++) {
		c = str0[i];
		s = Automat(c, s);
		if (s == 0 || s == 1 || s == 2 || s == 4) str += c; //запись символа кода в строку
		if (s == 5 || s == 7) str.erase(str.length() - 1, 1); //стирание предыдущего символа (при // и /*)
		if (s == 0 || s == 11) {
			if (str != "" && str != "\n") {
				count++; //увеличение счетчика при переносе строки
				str1 = count + "\t" + marshal_as<String^>(str);
				richTextBox2->Text += str1;
			}
			str = "";
		}
	}
	str1 = count + "";
	richTextBox3->Text = str1;
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	setlocale(LC_ALL, "Russian");
	OpenFileDialog^ openFile = gcnew OpenFileDialog();
	openFile->Filter = "Текстовые файлы (*.txt)|*.txt";
	String^ fileName;
	if (System::Windows::Forms::DialogResult::OK == openFile->ShowDialog()) fileName = openFile->FileName;
	try {
		StreamReader^ file = gcnew StreamReader(fileName, Encoding::GetEncoding("windows-1251"));
		richTextBox1->Text = file->ReadToEnd();
	}
	catch (Exception^ e)
	{
		richTextBox2->Text = "Ошибка открытия файла!";
	}
}
};
};