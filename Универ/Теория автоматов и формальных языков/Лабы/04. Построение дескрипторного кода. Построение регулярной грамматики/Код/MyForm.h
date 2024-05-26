#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <array>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_windows.h>
#include <msclr\marshal_atl.h>

namespace лб7_8 {

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

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RichTextBox^ richTextBox3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::DataGridView^ dataGridView3;
	private: System::Windows::Forms::DataGridView^ dataGridView4;
	private: System::Windows::Forms::DataGridView^ dataGridView5;
	private: System::Windows::Forms::DataGridView^ dataGridView6;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id10;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Разделители;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Псевдокод10;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
	private: System::Windows::Forms::RichTextBox^ richTextBox4;
	private: System::Windows::Forms::RichTextBox^ richTextBox5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id20;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ЗнакиОпераций;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Псевдокод20;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id30;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Константы;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Псевдокод30;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id40;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ КлючевыеСлова;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Псевдокод40;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id50;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Идентификаторы;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Псевдокод50;


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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->id10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Разделители = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Псевдокод10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->id20 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ЗнакиОпераций = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Псевдокод20 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->id30 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Константы = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Псевдокод30 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
			this->id40 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->КлючевыеСлова = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Псевдокод40 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView5 = (gcnew System::Windows::Forms::DataGridView());
			this->id50 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Идентификаторы = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Псевдокод50 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView6 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->richTextBox4 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox5 = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView6))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label1->Location = System::Drawing::Point(58, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(193, 31);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Исходный код";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label2->Location = System::Drawing::Point(367, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(253, 31);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Обработанный код";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->button1->Location = System::Drawing::Point(1171, 133);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(192, 52);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Обработать код";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(12, 53);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(303, 323);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(338, 53);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(303, 323);
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
			this->button2->Location = System::Drawing::Point(1171, 75);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(192, 52);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Выбрать файл";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label3->Location = System::Drawing::Point(1167, 28);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(133, 24);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Строк в коде:";
			// 
			// richTextBox3
			// 
			this->richTextBox3->Location = System::Drawing::Point(1314, 29);
			this->richTextBox3->Name = L"richTextBox3";
			this->richTextBox3->ReadOnly = true;
			this->richTextBox3->Size = System::Drawing::Size(49, 23);
			this->richTextBox3->TabIndex = 9;
			this->richTextBox3->Text = L"";
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->id10, this->Разделители,
					this->Псевдокод10
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 393);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(270, 235);
			this->dataGridView1->TabIndex = 10;
			// 
			// id10
			// 
			this->id10->HeaderText = L"10";
			this->id10->Name = L"id10";
			this->id10->Width = 30;
			// 
			// Разделители
			// 
			this->Разделители->HeaderText = L"Разделители";
			this->Разделители->Name = L"Разделители";
			this->Разделители->ReadOnly = true;
			// 
			// Псевдокод10
			// 
			this->Псевдокод10->HeaderText = L"Псевдокод";
			this->Псевдокод10->Name = L"Псевдокод10";
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			this->button3->Location = System::Drawing::Point(1171, 191);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(192, 52);
			this->button3->TabIndex = 12;
			this->button3->Text = L"Найти лексемы";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->id20, this->ЗнакиОпераций,
					this->Псевдокод20
			});
			this->dataGridView2->Location = System::Drawing::Point(288, 393);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->Size = System::Drawing::Size(270, 235);
			this->dataGridView2->TabIndex = 13;
			// 
			// id20
			// 
			this->id20->HeaderText = L"20";
			this->id20->Name = L"id20";
			this->id20->Width = 30;
			// 
			// ЗнакиОпераций
			// 
			this->ЗнакиОпераций->HeaderText = L"Знаки операций";
			this->ЗнакиОпераций->Name = L"ЗнакиОпераций";
			this->ЗнакиОпераций->ReadOnly = true;
			// 
			// Псевдокод20
			// 
			this->Псевдокод20->HeaderText = L"Псевдокод";
			this->Псевдокод20->Name = L"Псевдокод20";
			// 
			// dataGridView3
			// 
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->id30, this->Константы,
					this->Псевдокод30
			});
			this->dataGridView3->Location = System::Drawing::Point(564, 393);
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->Size = System::Drawing::Size(270, 235);
			this->dataGridView3->TabIndex = 14;
			// 
			// id30
			// 
			this->id30->HeaderText = L"30";
			this->id30->Name = L"id30";
			this->id30->Width = 30;
			// 
			// Константы
			// 
			this->Константы->HeaderText = L"Константы";
			this->Константы->Name = L"Константы";
			this->Константы->ReadOnly = true;
			// 
			// Псевдокод30
			// 
			this->Псевдокод30->HeaderText = L"Псевдокод";
			this->Псевдокод30->Name = L"Псевдокод30";
			// 
			// dataGridView4
			// 
			this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView4->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->id40, this->КлючевыеСлова,
					this->Псевдокод40
			});
			this->dataGridView4->Location = System::Drawing::Point(840, 393);
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->Size = System::Drawing::Size(270, 235);
			this->dataGridView4->TabIndex = 15;
			// 
			// id40
			// 
			this->id40->HeaderText = L"40";
			this->id40->Name = L"id40";
			this->id40->Width = 30;
			// 
			// КлючевыеСлова
			// 
			this->КлючевыеСлова->HeaderText = L"Ключевые слова";
			this->КлючевыеСлова->Name = L"КлючевыеСлова";
			this->КлючевыеСлова->ReadOnly = true;
			// 
			// Псевдокод40
			// 
			this->Псевдокод40->HeaderText = L"Псевдокод";
			this->Псевдокод40->Name = L"Псевдокод40";
			// 
			// dataGridView5
			// 
			this->dataGridView5->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView5->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->id50, this->Идентификаторы,
					this->Псевдокод50
			});
			this->dataGridView5->Location = System::Drawing::Point(1116, 393);
			this->dataGridView5->Name = L"dataGridView5";
			this->dataGridView5->Size = System::Drawing::Size(270, 235);
			this->dataGridView5->TabIndex = 16;
			// 
			// id50
			// 
			this->id50->HeaderText = L"50";
			this->id50->Name = L"id50";
			this->id50->Width = 30;
			// 
			// Идентификаторы
			// 
			this->Идентификаторы->HeaderText = L"Идентификаторы";
			this->Идентификаторы->Name = L"Идентификаторы";
			this->Идентификаторы->ReadOnly = true;
			// 
			// Псевдокод50
			// 
			this->Псевдокод50->HeaderText = L"Псевдокод";
			this->Псевдокод50->Name = L"Псевдокод50";
			// 
			// dataGridView6
			// 
			this->dataGridView6->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView6->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->dataGridViewTextBoxColumn5 });
			this->dataGridView6->Location = System::Drawing::Point(660, 12);
			this->dataGridView6->Name = L"dataGridView6";
			this->dataGridView6->Size = System::Drawing::Size(479, 115);
			this->dataGridView6->TabIndex = 17;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->HeaderText = L"Ошибки";
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->ReadOnly = true;
			this->dataGridViewTextBoxColumn5->Width = 435;
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->button4->Location = System::Drawing::Point(1171, 324);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(192, 52);
			this->button4->TabIndex = 18;
			this->button4->Text = L"Сброс";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// richTextBox4
			// 
			this->richTextBox4->Location = System::Drawing::Point(660, 157);
			this->richTextBox4->Name = L"richTextBox4";
			this->richTextBox4->ReadOnly = true;
			this->richTextBox4->Size = System::Drawing::Size(232, 219);
			this->richTextBox4->TabIndex = 19;
			this->richTextBox4->Text = L"";
			// 
			// richTextBox5
			// 
			this->richTextBox5->Location = System::Drawing::Point(909, 157);
			this->richTextBox5->Name = L"richTextBox5";
			this->richTextBox5->ReadOnly = true;
			this->richTextBox5->Size = System::Drawing::Size(230, 219);
			this->richTextBox5->TabIndex = 20;
			this->richTextBox5->Text = L"";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label4->Location = System::Drawing::Point(724, 130);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(110, 24);
			this->label4->TabIndex = 21;
			this->label4->Text = L"Псевдокод";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label5->Location = System::Drawing::Point(930, 130);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(191, 24);
			this->label5->TabIndex = 22;
			this->label5->Text = L"Дескрипторный код";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1396, 640);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->richTextBox5);
			this->Controls->Add(this->richTextBox4);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->dataGridView6);
			this->Controls->Add(this->dataGridView5);
			this->Controls->Add(this->dataGridView4);
			this->Controls->Add(this->dataGridView3);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->richTextBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Распознавание строк";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView6))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		bool search(DataGridView^ dataGridView, String^ symbol) {
			for (int i = 0; i < dataGridView->RowCount; i++) {
				if (dataGridView->Rows[i]->Cells->Count > 0) {
					Object^ Cell = dataGridView->Rows[i]->Cells[1]->Value;
					if (Cell != nullptr) {
						String^ searchSymbol = Cell->ToString();
						if (searchSymbol == symbol) {
							Object^ num = dataGridView->Rows[i]->Cells[0]->Value;
							id = num->ToString();
							num = dataGridView->Rows[i]->Cells[2]->Value;
							psevdo = num->ToString();
							return true;
						}
					}
				}
			}
			if (symbol == "") return true;
			else return false;
		}

		int Automat1(char c, int s) {
			switch (s) {
			case 0: { //начало новой строки, увеличивается счетчик
				if (c == '\n') return 11;
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
				else return 8;
			}
				  break;
			case 8: { //пропуск символов многострочного комментария
				if (c == '*') return 9;
				else return 8;
			}
				  break;
			case 9: { //обнаружена звездочка в многострочном комментарии
				if (c == '*') return 9;
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
			case 11: { //обнаружен 2 перенос строки подряд, он пропускается
				if (c == '\n') return 11;
				else if (c == '/') return 4;
				else if (c == ' ') return 3;
				else return 1;
			}
			}
		}

		void Automat2(char c, int& s, string& str, int& i, bool& f) {
			switch (s) {
			case 0: {
				switch (c) {
					//пробел, перенос
				case ' ':
				case '\n': break;
					//запрещенные символы
				case '@':
				case '`':
				case '№':
				case '$':
				case '^': {
					str += c;
					f = true;
				}
						break;
						//разделители
				case '{':
				case '}':
				case '(':
				case ')':
				case '[':
				case ']':
				case ';':
				case ',':
				case ':': {
					str += c;
					s = 1;
					f = true;
				}
						break;
						//знаки
				case '+': {
					str += c;
					s = 2;
				}
						break;
				case '-': {
					str += c;
					s = 3;
				}
						break;
				case '<': {
					str += c;
					s = 4;
				}
						break;
				case '>': {
					str += c;
					s = 5;
				}
						break;
				case '=':
				case '*':
				case '/':
				case '%':
				case '!': {
					str += c;
					s = 6;
				}
						break;
				case '&': {
					str += c;
					s = 8;
				}
						break;
				case '|': {
					str += c;
					s = 9;
				}
						break;
						//константы
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': {
					str += c;
					s = 10;
				}
						break;
						/*case '\'': {
							del += c;
							s = 14;
						}
								 break;
						case '"': {
							del += c;
							s = 17;
						}
								break;*/
						//ключевые слова
				case 'a': {
					str += c;
					s = 14;
				}
						break;
				case 'b': {
					str += c;
					s = 18;
				}
						break;
				case 'c': {
					str += c;
					s = 24;
				}
						break;
				case 'd': {
					str += c;
					s = 40;
				}
						break;
				case 'e': {
					str += c;
					s = 53;
				}
						break;
				case 'f': {
					str += c;
					s = 65;
				}
						break;
				case 'g': {
					str += c;
					s = 77;
				}
						break;
				case 'i': {
					str += c;
					s = 80;
				}
						break;
				case 'l': {
					str += c;
					s = 85;
				}
						break;
				case 'm': {
					str += c;
					s = 88;
				}
						break;
				case 'n': {
					str += c;
					s = 94;
				}
						break;
				case 'o': {
					str += c;
					s = 108;
				}
						break;
				case 'p': {
					str += c;
					s = 115;
				}
						break;
				case 'r': {
					str += c;
					s = 131;
				}
						break;
				case 's': {
					str += c;
					s = 136;
				}
						break;
				case 't': {
					str += c;
					s = 158;
				}
						break;
				case 'u': {
					str += c;
					s = 171;
				}
						break;
				case 'v': {
					str += c;
					s = 183;
				}
						break;
				case 'w': {
					str += c;
					s = 191;
				}
						break;
				case 'h':
				case 'j':
				case 'k':
				case 'q':
				case 'x':
				case 'y':
				case 'z':
				case '_': {
					str += c;
					s = 999;
				}
				}
				if (c >= 'A' && c <= 'Z') {
					str += c;
					s = 999;
				}
			}
				  break;
			case 1:
				break;
			case 2: {
				switch (c) {
				case '+':
				case '=': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 3: {
				switch (c) {
				case '-':
				case '=': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 4: {
				switch (c) {
				case '<':
				case '=': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 5: {
				switch (c) {
				case '>':
				case '=': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 6: {
				switch (c) {
				case '=': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 7:
				break;
			case 8: {
				switch (c) {
				case '&': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 9: {
				switch (c) {
				case '|': {
					str += c;
					s = 7;
					f = true;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				  break;
			case 10: {
				switch (c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': {
					str += c;
				}
						break;
				case '.': {
					str += c;
					s = 11;
				}
						break;
				case 'e':
				case 'E': {
					str += c;
					s = 12;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				   break;
			case 11: {
				switch (c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': {
					str += c;
				}
						break;
				case 'e':
				case 'E': {
					str += c;
					s = 12;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				   break;
			case 12: {
				switch (c) {
				case '+':
				case '-': {
					str += c;
					s = 13;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				   break;
			case 13: {
				switch (c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': {
					str += c;
				}
						break;
				default: {
					i--;
					f = true;
				}
					   break;
				}
			}
				   break;
			case 14: {
				switch (c) {
				case 'u': {
					str += c;
					s = 15;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 15: {
				switch (c) {
				case 't': {
					str += c;
					s = 16;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 16: {
				switch (c) {
				case 'o': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 17: {
				if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
					str += c;
					s = 999;
				}
				else {
					i--;
					f = true;
				}
			}
				   break;
			case 18: {
				switch (c) {
				case 'o': {
					str += c;
					s = 19;
				}
						break;
				case 'r': {
					str += c;
					s = 21;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 19: {
				switch (c) {
				case 'o': {
					str += c;
					s = 20;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 20: {
				switch (c) {
				case 'l': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 21: {
				switch (c) {
				case 'e': {
					str += c;
					s = 22;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 22: {
				switch (c) {
				case 'a': {
					str += c;
					s = 23;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 23: {
				switch (c) {
				case 'k': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 24: {
				switch (c) {
				case 'a': {
					str += c;
					s = 25;
				}
						break;
				case 'h': {
					str += c;
					s = 29;
				}
						break;
				case 'l': {
					str += c;
					s = 31;
				}
						break;
				case 'o': {
					str += c;
					s = 34;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 25: {
				switch (c) {
				case 's': {
					str += c;
					s = 26;
				}
						break;
				case 't': {
					str += c;
					s = 27;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 26: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 27: {
				switch (c) {
				case 'c': {
					str += c;
					s = 28;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 28: {
				switch (c) {
				case 'h': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 29: {
				switch (c) {
				case 'a': {
					str += c;
					s = 30;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 30: {
				switch (c) {
				case 'r': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 31: {
				switch (c) {
				case 'a': {
					str += c;
					s = 32;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 32: {
				switch (c) {
				case 's': {
					str += c;
					s = 33;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 33: {
				switch (c) {
				case 's': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 34: {
				switch (c) {
				case 'n': {
					str += c;
					s = 35;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 35: {
				switch (c) {
				case 'c': {
					str += c;
					s = 36;
				}
						break;
				case 's': {
					str += c;
					s = 39;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 36: {
				switch (c) {
				case 'e': {
					str += c;
					s = 37;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 37: {
				switch (c) {
				case 'p': {
					str += c;
					s = 38;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 38: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 39: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 40: {
				switch (c) {
				case 'e': {
					str += c;
					s = 41;
				}
						break;
				case 'o': {
					str += c;
					s = 49;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 41: {
				switch (c) {
				case 'f': {
					str += c;
					s = 42;
				}
						break;
				case 'l': {
					str += c;
					s = 46;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 42: {
				switch (c) {
				case 'a': {
					str += c;
					s = 43;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 43: {
				switch (c) {
				case 'u': {
					str += c;
					s = 44;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 44: {
				switch (c) {
				case 'l': {
					str += c;
					s = 45;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 45: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 46: {
				switch (c) {
				case 'e': {
					str += c;
					s = 47;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 47: {
				switch (c) {
				case 't': {
					str += c;
					s = 48;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 48: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 49: {
				switch (c) {
				case 'u': {
					str += c;
					s = 50;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 17;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 50: {
				switch (c) {
				case 'b': {
					str += c;
					s = 51;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 51: {
				switch (c) {
				case 'l': {
					str += c;
					s = 52;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 52: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 53: {
				switch (c) {
				case 'l': {
					str += c;
					s = 54;
				}
						break;
				case 'n': {
					str += c;
					s = 56;
				}
						break;
				case 'x': {
					str += c;
					s = 58;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 54: {
				switch (c) {
				case 's': {
					str += c;
					s = 55;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 55: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 56: {
				switch (c) {
				case 'u': {
					str += c;
					s = 57;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 57: {
				switch (c) {
				case 'm': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 58: {
				switch (c) {
				case 'p': {
					str += c;
					s = 59;
				}
						break;
				case 't': {
					str += c;
					s = 62;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 59: {
				switch (c) {
				case 'o': {
					str += c;
					s = 60;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 60: {
				switch (c) {
				case 'r': {
					str += c;
					s = 61;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 61: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 62: {
				switch (c) {
				case 'e': {
					str += c;
					s = 63;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 63: {
				switch (c) {
				case 'r': {
					str += c;
					s = 64;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 64: {
				switch (c) {
				case 'n': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 65: {
				switch (c) {
				case 'a': {
					str += c;
					s = 66;
				}
						break;
				case 'l': {
					str += c;
					s = 69;
				}
						break;
				case 'o': {
					str += c;
					s = 72;
				}
						break;
				case 'r': {
					str += c;
					s = 73;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 66: {
				switch (c) {
				case 'l': {
					str += c;
					s = 67;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 67: {
				switch (c) {
				case 's': {
					str += c;
					s = 68;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 68: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 69: {
				switch (c) {
				case 'o': {
					str += c;
					s = 70;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 70: {
				switch (c) {
				case 'a': {
					str += c;
					s = 71;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 71: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 72: {
				switch (c) {
				case 'r': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 73: {
				switch (c) {
				case 'i': {
					str += c;
					s = 74;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 74: {
				switch (c) {
				case 'e': {
					str += c;
					s = 75;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 75: {
				switch (c) {
				case 'n': {
					str += c;
					s = 76;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 76: {
				switch (c) {
				case 'd': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 77: {
				switch (c) {
				case 'o': {
					str += c;
					s = 78;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 78: {
				switch (c) {
				case 't': {
					str += c;
					s = 79;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 79: {
				switch (c) {
				case 'o': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 80: {
				switch (c) {
				case 'f': {
					str += c;
					s = 17;
				}
						break;
				case 'n': {
					str += c;
					s = 81;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 81: {
				switch (c) {
				case 'l': {
					str += c;
					s = 82;
				}
						break;
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 82: {
				switch (c) {
				case 'i': {
					str += c;
					s = 83;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 83: {
				switch (c) {
				case 'n': {
					str += c;
					s = 84;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 84: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 85: {
				switch (c) {
				case 'o': {
					str += c;
					s = 86;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 86: {
				switch (c) {
				case 'n': {
					str += c;
					s = 87;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 87: {
				switch (c) {
				case 'g': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 88: {
				switch (c) {
				case 'u': {
					str += c;
					s = 89;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 89: {
				switch (c) {
				case 't': {
					str += c;
					s = 90;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 90: {
				switch (c) {
				case 'a': {
					str += c;
					s = 91;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 91: {
				switch (c) {
				case 'b': {
					str += c;
					s = 92;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 92: {
				switch (c) {
				case 'l': {
					str += c;
					s = 93;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 93: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 94: {
				switch (c) {
				case 'a': {
					str += c;
					s = 95;
				}
						break;
				case 'e': {
					str += c;
					s = 102;
				}
						break;
				case 'u': {
					str += c;
					s = 103;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 95: {
				switch (c) {
				case 'm': {
					str += c;
					s = 96;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 96: {
				switch (c) {
				case 'e': {
					str += c;
					s = 97;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 97: {
				switch (c) {
				case 's': {
					str += c;
					s = 98;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 98: {
				switch (c) {
				case 'p': {
					str += c;
					s = 99;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 99: {
				switch (c) {
				case 'a': {
					str += c;
					s = 100;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 100: {
				switch (c) {
				case 'c': {
					str += c;
					s = 101;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
				   break;
			case 101: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 102: {
				switch (c) {
				case 'w': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 103: {
				switch (c) {
				case 'l': {
					str += c;
					s = 104;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 104: {
				switch (c) {
				case 'l': {
					str += c;
					s = 105;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 105: {
				switch (c) {
				case 'p': {
					str += c;
					s = 106;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 106: {
				switch (c) {
				case 't': {
					str += c;
					s = 107;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 107: {
				switch (c) {
				case 'r': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 108: {
				switch (c) {
				case 'p': {
					str += c;
					s = 109;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 109: {
				switch (c) {
				case 'e': {
					str += c;
					s = 110;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 110: {
				switch (c) {
				case 'r': {
					str += c;
					s = 111;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 111: {
				switch (c) {
				case 'a': {
					str += c;
					s = 112;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 112: {
				switch (c) {
				case 't': {
					str += c;
					s = 113;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 113: {
				switch (c) {
				case 'o': {
					str += c;
					s = 114;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 114: {
				switch (c) {
				case 'r': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 115: {
				switch (c) {
				case 'r': {
					str += c;
					s = 116;
				}
						break;
				case 'u': {
					str += c;
					s = 127;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 116: {
				switch (c) {
				case 'i': {
					str += c;
					s = 117;
				}
						break;
				case 'o': {
					str += c;
					s = 121;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 117: {
				switch (c) {
				case 'v': {
					str += c;
					s = 118;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 118: {
				switch (c) {
				case 'a': {
					str += c;
					s = 119;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 119: {
				switch (c) {
				case 't': {
					str += c;
					s = 120;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 120: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 121: {
				switch (c) {
				case 't': {
					str += c;
					s = 122;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 122: {
				switch (c) {
				case 'e': {
					str += c;
					s = 123;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 123: {
				switch (c) {
				case 'c': {
					str += c;
					s = 124;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 124: {
				switch (c) {
				case 't': {
					str += c;
					s = 125;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 125: {
				switch (c) {
				case 'e': {
					str += c;
					s = 126;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 126: {
				switch (c) {
				case 'd': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 127: {
				switch (c) {
				case 'b': {
					str += c;
					s = 128;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 128: {
				switch (c) {
				case 'l': {
					str += c;
					s = 129;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 129: {
				switch (c) {
				case 'i': {
					str += c;
					s = 130;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 130: {
				switch (c) {
				case 'c': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 131: {
				switch (c) {
				case 'e': {
					str += c;
					s = 132;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 132: {
				switch (c) {
				case 't': {
					str += c;
					s = 133;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 133: {
				switch (c) {
				case 'u': {
					str += c;
					s = 134;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 134: {
				switch (c) {
				case 'r': {
					str += c;
					s = 135;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 135: {
				switch (c) {
				case 'n': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 136: {
				switch (c) {
				case 'h': {
					str += c;
					s = 137;
				}
						break;
				case 'i': {
					str += c;
					s = 140;
				}
						break;
				case 't': {
					str += c;
					s = 147;
				}
						break;
				case 'w': {
					str += c;
					s = 154;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 137: {
				switch (c) {
				case 'o': {
					str += c;
					s = 138;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 138: {
				switch (c) {
				case 'r': {
					str += c;
					s = 139;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 139: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 140: {
				switch (c) {
				case 'g': {
					str += c;
					s = 141;
				}
						break;
				case 'z': {
					str += c;
					s = 144;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 141: {
				switch (c) {
				case 'n': {
					str += c;
					s = 142;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 142: {
				switch (c) {
				case 'e': {
					str += c;
					s = 143;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 143: {
				switch (c) {
				case 'd': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 144: {
				switch (c) {
				case 'e': {
					str += c;
					s = 145;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 145: {
				switch (c) {
				case 'o': {
					str += c;
					s = 146;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 146: {
				switch (c) {
				case 'f': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 147: {
				switch (c) {
				case 'a': {
					str += c;
					s = 148;
				}
						break;
				case 'r': {
					str += c;
					s = 151;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 148: {
				switch (c) {
				case 't': {
					str += c;
					s = 149;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 149: {
				switch (c) {
				case 'i': {
					str += c;
					s = 150;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 150: {
				switch (c) {
				case 'c': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 151: {
				switch (c) {
				case 'u': {
					str += c;
					s = 152;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 152: {
				switch (c) {
				case 'c': {
					str += c;
					s = 153;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 153: {
				switch (c) {
				case 't': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 154: {
				switch (c) {
				case 'i': {
					str += c;
					s = 155;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 155: {
				switch (c) {
				case 't': {
					str += c;
					s = 156;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 156: {
				switch (c) {
				case 'c': {
					str += c;
					s = 157;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 157: {
				switch (c) {
				case 'h': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 158: {
				switch (c) {
				case 'e': {
					str += c;
					s = 159;
				}
						break;
				case 'h': {
					str += c;
					s = 165;
				}
						break;
				case 'r': {
					str += c;
					s = 169;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 159: {
				switch (c) {
				case 'm': {
					str += c;
					s = 160;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 160: {
				switch (c) {
				case 'p': {
					str += c;
					s = 161;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 161: {
				switch (c) {
				case 'l': {
					str += c;
					s = 162;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 162: {
				switch (c) {
				case 'a': {
					str += c;
					s = 163;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 163: {
				switch (c) {
				case 't': {
					str += c;
					s = 164;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 164: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 165: {
				switch (c) {
				case 'i': {
					str += c;
					s = 166;
				}
						break;
				case 'r': {
					str += c;
					s = 167;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 166: {
				switch (c) {
				case 's': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 167: {
				switch (c) {
				case 'o': {
					str += c;
					s = 168;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 168: {
				switch (c) {
				case 'w': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 169: {
				switch (c) {
				case 'u': {
					str += c;
					s = 170;
				}
						break;
				case 'y': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 170: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 171: {
				switch (c) {
				case 'n': {
					str += c;
					s = 172;
				}
						break;
				case 's': {
					str += c;
					s = 180;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 172: {
				switch (c) {
				case 'i': {
					str += c;
					s = 173;
				}
						break;
				case 's': {
					str += c;
					s = 175;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 173: {
				switch (c) {
				case 'o': {
					str += c;
					s = 174;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 174: {
				switch (c) {
				case 'n': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 175: {
				switch (c) {
				case 'i': {
					str += c;
					s = 176;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 176: {
				switch (c) {
				case 'g': {
					str += c;
					s = 177;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 177: {
				switch (c) {
				case 'n': {
					str += c;
					s = 178;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 178: {
				switch (c) {
				case 'e': {
					str += c;
					s = 179;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 179: {
				switch (c) {
				case 'd': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 180: {
				switch (c) {
				case 'i': {
					str += c;
					s = 181;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 181: {
				switch (c) {
				case 'n': {
					str += c;
					s = 182;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 182: {
				switch (c) {
				case 'g': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 183: {
				switch (c) {
				case 'i': {
					str += c;
					s = 184;
				}
						break;
				case 'o': {
					str += c;
					s = 189;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 184: {
				switch (c) {
				case 'r': {
					str += c;
					s = 185;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 185: {
				switch (c) {
				case 't': {
					str += c;
					s = 186;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 186: {
				switch (c) {
				case 'u': {
					str += c;
					s = 187;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 187: {
				switch (c) {
				case 'a': {
					str += c;
					s = 188;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 188: {
				switch (c) {
				case 'l': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 189: {
				switch (c) {
				case 'i': {
					str += c;
					s = 190;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 190: {
				switch (c) {
				case 'd': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 191: {
				switch (c) {
				case 'h': {
					str += c;
					s = 192;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 192: {
				switch (c) {
				case 'i': {
					str += c;
					s = 193;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 193: {
				switch (c) {
				case 'l': {
					str += c;
					s = 194;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
			case 194: {
				switch (c) {
				case 'e': {
					str += c;
					s = 17;
				}
						break;
				default: {
					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
						str += c;
						s = 999;
					}
					else {
						s = 999;
						i--;
						f = true;
					}
				}
					   break;
				}
			}
					break;
					//идентификатор
			case 999: {
				if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
					str += c;
				}
				else {
					i--;
					f = true;
				}
			}
			}
		}

		public: String^ prog = ""; 
		public: String^ id = "";
		public: String^ psevdo = "";
		public: int err = 0, s1 = 0, count_r = 0, count_z = 0, count_const = 0, count_key = 0, count_id = 0;

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
			s = Automat1(c, s);
			if (s == 0 || s == 1 || s == 2 || s == 4) str += c; //запись символа кода в строку
			if (s == 5 || s == 7) str.erase(str.length() - 1, 1); //стирание предыдущего символа (при // и /*)
			if (s == 0) {
				if (str != "" && str != "\n") {
					count++; //увеличение счетчика при переносе строки
					str1 = count + "\t" + marshal_as<String^>(str);
					prog += marshal_as<String^>(str);
					richTextBox2->Text += str1;
				}
				str = "";
			}
		}
		if (s == 8 || s == 9) {
			String^ symbol = "Обнаружен незакрытый комментарий";
			cli::array<String^>^ row = gcnew cli::array<String^> { symbol };
			dataGridView6->Rows->Add(row);
		}
		str1 = count + "";
		richTextBox3->Text = str1;
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		prog = "";
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
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ str0 = prog;
		String^ symbol;
		String^ count;
		String^ pk;
		string str00 = marshal_as<string>(str0), str = "";
		bool f = false;
		char c;
		int s = 0;
		for (int i = 0; i < str00.length(); i++) {
			c = str00[i];
			Automat2(c, s, str, i, f);
			if (c == ' ' || c == '\n') richTextBox4->Text += Char::ToString(c);
			if (s == 0) { //ошибки
				if (f) {
					symbol = "Неверный символ: ";
					symbol += marshal_as<String^>(str);
					cli::array<String^>^ row = gcnew cli::array<String^> { symbol };
					dataGridView6->Rows->Add(row);
					symbol = "";
					str = "";
					f = false;
				}
			}
			if (s == 1) { //разделители
				if (f) {
					symbol += marshal_as<String^>(str);
					if (!search(dataGridView1, symbol)) {
						count_r++;
						count = Convert::ToString(count_r);
						pk = symbol;
						cli::array<String^>^ row = gcnew cli::array<String^> { count, symbol, pk };
						dataGridView1->Rows->Add(row);
						richTextBox4->Text += pk;
						richTextBox5->Text += "(10, " + count + "), ";
					}
					else {
						richTextBox4->Text += psevdo;
						richTextBox5->Text += "(10, " + id + "), ";
					}
					symbol = "";
					str = "";
					f = false;
					s = 0;
					count = "";
				}
			}
			if (s >= 2 && s <= 9) { //знаки
				if (f) {
					for (int i = 0; i < str.length(); i++)
						symbol += Char::ToString(str[i]);
					if (!search(dataGridView2, symbol)) {
						count_z++;
						count = Convert::ToString(count_z);
						pk = symbol;
						cli::array<String^>^ row = gcnew cli::array<String^> { count, symbol, pk };
						dataGridView2->Rows->Add(row);
						richTextBox4->Text += pk;
						richTextBox5->Text += "(20, " + count + "), ";
					}
					else {
						richTextBox4->Text += psevdo;
						richTextBox5->Text += "(20, " + id + "), ";
					}
					symbol = "";
					str = "";
					f = false;
					s = 0;
					count = "";
				}
			}
			if (s >= 10 && s <= 13) { //константы
				if (f) {
					for (int i = 0; i < str.length(); i++)
						symbol += Char::ToString(str[i]);
					if (symbol[symbol->Length - 1] == '.' || symbol[symbol->Length - 1] == 'E' || symbol[symbol->Length - 1] == 'e' || symbol[symbol->Length - 1] == '+' || symbol[symbol->Length - 1] == '-') {
						symbol = "Неверная константа: " + symbol;
						cli::array<String^>^ row = gcnew cli::array<String^> { symbol };
						dataGridView6->Rows->Add(row);
					}
					else if (!search(dataGridView3, symbol)) {
						count_const++;
						count = Convert::ToString(count_const);
						pk = symbol;
						cli::array<String^>^ row = gcnew cli::array<String^> { count, symbol, pk };
						dataGridView3->Rows->Add(row);
						richTextBox4->Text += pk;
						richTextBox5->Text += "(30, " + count + "), ";
					}
					else {
						richTextBox4->Text += psevdo;
						richTextBox5->Text += "(30, " + id + "), ";
					}
					symbol = "";
					str = "";
					f = false;
					s = 0;
					count = "";
				}
			}
			if (s == 17) { //ключевые слова
				if (f) {
					for (int i = 0; i < str.length(); i++)
						symbol += Char::ToString(str[i]);
					if (!search(dataGridView4, symbol)) {
						count_key++;
						count = Convert::ToString(count_key);
						pk = symbol;
						cli::array<String^>^ row = gcnew cli::array<String^> { count, symbol, pk };
						dataGridView4->Rows->Add(row);
						richTextBox4->Text += pk;
						richTextBox5->Text += "(40, " + count + "), ";
					}
					else {
						richTextBox4->Text += psevdo;
						richTextBox5->Text += "(40, " + id + "), ";
					}
					symbol = "";
					str = "";
					f = false;
					s = 0;
					count = "";
					pk = "";
				}
			}
			if (s == 999) { //идентификаторы
				if (f) {
					for (int i = 0; i < str.length(); i++)
						symbol += Char::ToString(str[i]);
					if (!search(dataGridView5, symbol)) {
						count_id++;
						count = Convert::ToString(count_id);
						pk = "id" + count;
						cli::array<String^>^ row = gcnew cli::array<String^> { count, symbol, pk };
						dataGridView5->Rows->Add(row);
						richTextBox4->Text += pk;
						richTextBox5->Text += "(50, " + count + "), ";
					}
					else {
						richTextBox4->Text += psevdo;
						richTextBox5->Text += "(50, " + id + "), ";
					}
					symbol = "";
					str = "";
					f = false;
					s = 0;
					count = "";
				}
			}
		}
		if (richTextBox5->Text != "") richTextBox5->Text = richTextBox5->Text->Substring(0, richTextBox5->Text->Length - 1);
		string pcode = marshal_as<string>(richTextBox4->Text);
		s = 0;
		for (int i = 0; i < pcode.length(); i++) {
			Automat1(pcode[i], s);
		}
		richTextBox4->Text = marshal_as<String^>(pcode);
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		richTextBox1->Clear();
		richTextBox2->Clear();
		richTextBox3->Clear();
		dataGridView1->Rows->Clear();
		dataGridView2->Rows->Clear();
		dataGridView3->Rows->Clear();
		dataGridView4->Rows->Clear();
		dataGridView5->Rows->Clear();
		dataGridView6->Rows->Clear();
		prog = "";
		count_r = 0, count_z = 0, count_const = 0, count_key = 0, count_id = 0;
	}
};
}