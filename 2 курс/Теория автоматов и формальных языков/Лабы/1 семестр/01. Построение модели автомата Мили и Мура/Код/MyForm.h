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
	/// —водка дл€ MyForm
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
		/// ќсвободить все используемые ресурсы.
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
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Label^ label27;


	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label37;
	private: System::Windows::Forms::Label^ label38;
	private: System::Windows::Forms::Label^ label39;
	private: System::Windows::Forms::Label^ label40;
	private: System::Windows::Forms::Label^ label41;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::Label^ label43;
	private: System::Windows::Forms::Label^ label44;
	private: System::Windows::Forms::Label^ label45;
	private: System::Windows::Forms::Label^ label46;
	private: System::Windows::Forms::Label^ label47;
	private: System::Windows::Forms::Label^ label48;
	private: System::Windows::Forms::Label^ label49;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
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
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(403, 185);
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox4->Location = System::Drawing::Point(330, 545);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(614, 29);
			this->textBox4->TabIndex = 21;
			this->textBox4->ReadOnly = true;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox3->Location = System::Drawing::Point(330, 608);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(614, 29);
			this->textBox3->TabIndex = 20;
			this->textBox3->ReadOnly = true;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->textBox1->Location = System::Drawing::Point(330, 576);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(614, 29);
			this->textBox1->TabIndex = 19;
			this->textBox1->ReadOnly = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->label3->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label3->Location = System::Drawing::Point(360, 337);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(545, 26);
			this->label3->TabIndex = 18;
			this->label3->Text = L"(числа через ќƒ»Ќ пробел, без зап€тых и буквы х)";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->button2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button2->Location = System::Drawing::Point(671, 414);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(273, 94);
			this->button2->TabIndex = 17;
			this->button2->Text = L"«апустить автоматический режим";
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
			this->label2->Size = System::Drawing::Size(233, 31);
			this->label2->TabIndex = 16;
			this->label2->Text = L"ѕротокол работы";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label1->Location = System::Drawing::Point(380, 306);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(500, 31);
			this->label1->TabIndex = 15;
			this->label1->Text = L"¬ведите входную последовательность";
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
			this->button1->Location = System::Drawing::Point(330, 414);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(273, 94);
			this->button1->TabIndex = 13;
			this->button1->Text = L"«апустить пошаговый режим";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label4->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label4->Location = System::Drawing::Point(12, 209);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(199, 24);
			this->label4->TabIndex = 22;
			this->label4->Text = L"S0 Ц ожидание карты";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label5->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label5->Location = System::Drawing::Point(12, 233);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(179, 24);
			this->label5->TabIndex = 23;
			this->label5->Text = L"S1 Ц прин€та карта";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label6->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label6->Location = System::Drawing::Point(12, 257);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(190, 24);
			this->label6->TabIndex = 24;
			this->label6->Text = L"S2 Ц пин-код прин€т";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label7->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label7->Location = System::Drawing::Point(12, 281);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(259, 24);
			this->label7->TabIndex = 25;
			this->label7->Text = L"S3 Ц выбр. оп. сн€ти€ денег";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label8->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label8->Location = System::Drawing::Point(12, 305);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(283, 24);
			this->label8->TabIndex = 26;
			this->label8->Text = L"S4 Ц выбр. оп. внесени€ денег";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label9->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label9->Location = System::Drawing::Point(12, 329);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(255, 24);
			this->label9->TabIndex = 27;
			this->label9->Text = L"S5 Ц выбр. оп. оплаты услуг";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label10->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label10->Location = System::Drawing::Point(12, 353);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(264, 24);
			this->label10->TabIndex = 28;
			this->label10->Text = L"S6 Ц введ. сумма дл€ сн€ти€";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label11->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label11->Location = System::Drawing::Point(12, 377);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(185, 24);
			this->label11->TabIndex = 29;
			this->label11->Text = L"S7 Ц внесена сумма";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label12->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label12->Location = System::Drawing::Point(12, 401);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(189, 24);
			this->label12->TabIndex = 30;
			this->label12->Text = L"S8 Ц выбрана услуга";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label13->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label13->Location = System::Drawing::Point(12, 425);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(186, 24);
			this->label13->TabIndex = 31;
			this->label13->Text = L"S9 Ц опер. подтвер.";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label14->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label14->Location = System::Drawing::Point(12, 449);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(213, 24);
			this->label14->TabIndex = 32;
			this->label14->Text = L"S10 Ц опер. выполнена";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label15->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label15->Location = System::Drawing::Point(12, 473);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(224, 24);
			this->label15->TabIndex = 33;
			this->label15->Text = L"S11 Ц карта возвращена";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label16->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label16->Location = System::Drawing::Point(421, 280);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(172, 24);
			this->label16->TabIndex = 46;
			this->label16->Text = L"х11 Ц подтв. опер.";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label17->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label17->Location = System::Drawing::Point(421, 256);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(178, 24);
			this->label17->TabIndex = 45;
			this->label17->Text = L"х10 Ц выбор услуги";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label18->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label18->Location = System::Drawing::Point(421, 232);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(198, 24);
			this->label18->TabIndex = 44;
			this->label18->Text = L"х9 Ц внесение суммы";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label19->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label19->Location = System::Drawing::Point(421, 208);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(260, 24);
			this->label19->TabIndex = 43;
			this->label19->Text = L"х8 Ц ввод суммы дл€ сн€ти€";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label20->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label20->Location = System::Drawing::Point(421, 184);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(270, 24);
			this->label20->TabIndex = 42;
			this->label20->Text = L"х7 Ц нажата кн. \"Ќа гл. экран\"";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label21->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label21->Location = System::Drawing::Point(421, 160);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(259, 24);
			this->label21->TabIndex = 41;
			this->label21->Text = L"х6 Ц выбор оп. оплаты услуг";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label22->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label22->Location = System::Drawing::Point(421, 136);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(292, 24);
			this->label22->TabIndex = 40;
			this->label22->Text = L"х5 Ц выбор. оп. внесени€ денег";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label23->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label23->Location = System::Drawing::Point(421, 112);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(263, 24);
			this->label23->TabIndex = 39;
			this->label23->Text = L"х4 Ц выбор оп. сн€ти€ денег";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label24->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label24->Location = System::Drawing::Point(421, 88);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(259, 24);
			this->label24->TabIndex = 38;
			this->label24->Text = L"х3 Ц ввод верного пин-кода";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label25->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label25->Location = System::Drawing::Point(421, 64);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(281, 24);
			this->label25->TabIndex = 37;
			this->label25->Text = L"х2 Ц ввод неверного пин-кода";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label26->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label26->Location = System::Drawing::Point(421, 40);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(195, 24);
			this->label26->TabIndex = 36;
			this->label26->Text = L"х1 - вставлена карта";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label27->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label27->Location = System::Drawing::Point(421, 16);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(203, 24);
			this->label27->TabIndex = 35;
			this->label27->Text = L"x0 Ц приложена карта";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label30->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label30->Location = System::Drawing::Point(984, 40);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(227, 24);
			this->label30->TabIndex = 51;
			this->label30->Text = L"отобр. экрана \"ѕин-код\"";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label31->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label31->Location = System::Drawing::Point(984, 16);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(262, 24);
			this->label31->TabIndex = 50;
			this->label31->Text = L"у0 Ц сообщ. \" арта считана\",";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label32->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label32->Location = System::Drawing::Point(708, 64);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(222, 24);
			this->label32->TabIndex = 49;
			this->label32->Text = L"х14 - выход из системы";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label33->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label33->Location = System::Drawing::Point(708, 40);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(267, 24);
			this->label33->TabIndex = 48;
			this->label33->Text = L"х13 - запрос на возвр. карты";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label34->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label34->Location = System::Drawing::Point(708, 16);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(223, 24);
			this->label34->TabIndex = 47;
			this->label34->Text = L"х12 Ц проведение опер.";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label28->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label28->Location = System::Drawing::Point(984, 88);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(227, 24);
			this->label28->TabIndex = 53;
			this->label28->Text = L"отобр. экрана \"ѕин-код\"";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label29->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label29->Location = System::Drawing::Point(984, 64);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(264, 24);
			this->label29->TabIndex = 52;
			this->label29->Text = L"у1 Ц сообщ. \" арта прин€та\",";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label35->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label35->Location = System::Drawing::Point(985, 112);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(276, 24);
			this->label35->TabIndex = 54;
			this->label35->Text = L"у2 Ц сообщ. \"ѕин-код неверн.\"";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label36->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label36->Location = System::Drawing::Point(985, 136);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(273, 24);
			this->label36->TabIndex = 55;
			this->label36->Text = L"у3 Ц сообщ. \"ѕин-код верный\"";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label37->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label37->Location = System::Drawing::Point(985, 160);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(262, 24);
			this->label37->TabIndex = 56;
			this->label37->Text = L"у4 Ц сообщ. \"ќпер. выбрана\"";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label38->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label38->Location = System::Drawing::Point(985, 184);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(262, 24);
			this->label38->TabIndex = 57;
			this->label38->Text = L"у4 Ц сообщ. \"ќпер. выбрана\"";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label39->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label39->Location = System::Drawing::Point(985, 209);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(275, 24);
			this->label39->TabIndex = 58;
			this->label39->Text = L"у5 - у7, у13 Ц отобр. гл. экрана";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label40->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label40->Location = System::Drawing::Point(984, 233);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(226, 24);
			this->label40->TabIndex = 59;
			this->label40->Text = L"у8 Ц отобр. экрана опер.";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label41->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label41->Location = System::Drawing::Point(985, 257);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(223, 24);
			this->label41->TabIndex = 60;
			this->label41->Text = L"у9 Ц вывод введ. суммы";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label42->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label42->Location = System::Drawing::Point(984, 281);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(231, 24);
			this->label42->TabIndex = 61;
			this->label42->Text = L"у10 Ц вывод внес. суммы";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label43->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label43->Location = System::Drawing::Point(984, 306);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(234, 24);
			this->label43->TabIndex = 62;
			this->label43->Text = L"у11 Ц вывод выбр. услуги";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label44->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label44->Location = System::Drawing::Point(984, 330);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(244, 24);
			this->label44->TabIndex = 63;
			this->label44->Text = L"у12 Ц вывод рез-тов опер.";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label45->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label45->Location = System::Drawing::Point(984, 354);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(279, 24);
			this->label45->TabIndex = 64;
			this->label45->Text = L"у14 Ц сообщ. \"«аберите карту\"";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label46->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label46->Location = System::Drawing::Point(985, 378);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(267, 24);
			this->label46->TabIndex = 65;
			this->label46->Text = L"у15 - у16 Ц вывод нач. экрана";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label47->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label47->Location = System::Drawing::Point(284, 545);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(40, 31);
			this->label47->TabIndex = 66;
			this->label47->Text = L"’:";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label48->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label48->Location = System::Drawing::Point(284, 574);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(40, 31);
			this->label48->TabIndex = 67;
			this->label48->Text = L"Y:";
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1260, 640);
			this->Controls->Add(this->label49);
			this->Controls->Add(this->label48);
			this->Controls->Add(this->label47);
			this->Controls->Add(this->label46);
			this->Controls->Add(this->label45);
			this->Controls->Add(this->label44);
			this->Controls->Add(this->label43);
			this->Controls->Add(this->label42);
			this->Controls->Add(this->label41);
			this->Controls->Add(this->label40);
			this->Controls->Add(this->label39);
			this->Controls->Add(this->label38);
			this->Controls->Add(this->label37);
			this->Controls->Add(this->label36);
			this->Controls->Add(this->label35);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label34);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label27);
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
			this->Name = L"MyForm";
			this->Text = L"јвтомат ћили";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

		}

		void Mili(int x[], int y[], int s[], int i, int j, int& err) {
			switch (s[i]) {
			case 0: {
				if (x[i] == 0) {
					s[i + 1] = 1;
					y[i] = 0;
				}
				else if (x[i] == 1) {
					s[i + 1] = 1;
					y[i] = 1;
				}
				else err++;
			}
				break;
			case 1: {
				if (x[i] == 2) {
					s[i + 1] = 1;
					y[i] = 2;
				}
				else if (x[i] == 3) {
					s[i + 1] = 2;
					y[i] = 3;
				}
				else err++;
			}
				  break;
			case 2: {
				if (x[i] == 4) {
					s[i + 1] = 3;
					y[i] = 4;
				}
				else if (x[i] == 5) {
					s[i + 1] = 4;
					y[i] = 4;
				}
				else if (x[i] == 6) {
					s[i + 1] = 5;
					y[i] = 4;
				}
				else if (x[i] == 13) {
					s[i + 1] = 11;
					y[i] = 14;
				}
				else if (x[i] == 14) {
					s[i + 1] = 0;
					y[i] = 15;
				}
				else err++;
			}
				  break;
			case 3: {
				if (x[i] == 7) {
					s[i + 1] = 2;
					y[i] = 5;
				}
				else if (x[i] == 8) {
					s[i + 1] = 6;
					y[i] = 8;
				}
				else err++;
			}
				  break;
			case 4: {
				if (x[i] == 7) {
					s[i + 1] = 2;
					y[i] = 6;
				}
				else if (x[i] == 9) {
					s[i + 1] = 7;
					y[i] = 8;
				}
				else err++;
			}
				  break;
			case 5: {
				if (x[i] == 7) {
					s[i + 1] = 2;
					y[i] = 7;
				}
				else if (x[i] == 10) {
					s[i + 1] = 8;
					y[i] = 8;
				}
				else err++;
			}
				  break;
			case 6: {
				if (x[i] == 11) {
					s[i + 1] = 9;
					y[i] = 9;
				}
				else err++;
			}
				  break;
			case 7: {
				if (x[i] == 11) {
					s[i + 1] = 9;
					y[i] = 10;
				}
				else err++;
			}
				  break;
			case 8: {
				if (x[i] == 11) {
					s[i + 1] = 9;
					y[i] = 11;
				}
				else err++;
			}
				  break;
			case 9: {
				if (x[i] == 12) {
					s[i + 1] = 10;
					y[i] = 12;
				}
				else err++;
			}
				  break;
			case 10: {
				if (x[i] == 7) {
					s[i + 1] = 2;
					y[i] = 13;
				}
				else err++;
			}
				   break;
			case 11: {
				if (x[i] == 14) {
					s[i + 1] = 0;
					y[i] = 16;
				}
				else err++;
			}
				   break;
			}
		}

#pragma endregion
		int click = 0;
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	setlocale(LC_ALL, "Russian");
	int n = 0;
	String^ sx = textBox2->Text;
	string str_x = marshal_as<string>(sx), str_y = "", str_s = "";
	for (int i = 0; i < str_x.length(); i++)
		if (i != 0)
			if ((str_x[i] == ' ' || str_x[i] == '\0') && str_x[i - 1] != ' ') n++;
	int k = 0, j = 0, err = 0;
	int* x = new int[n + 1];
	int* y = new int[n + 1];
	int* s = new int[n + 2];
	for (int i = 0; i < str_x.length(); i++) {
		k *= 10;
		if (str_x[i] == '0' && err == 0) k = k;
		else if (str_x[i] == '1' && err == 0) k++;
		else if (str_x[i] == '2' && err == 0) k += 2;
		else if (str_x[i] == '3' && err == 0) k += 3;
		else if (str_x[i] == '4' && err == 0) k += 4;
		else if (str_x[i] == '5' && err == 0) k += 5;
		else if (str_x[i] == '6' && err == 0) k += 6;
		else if (str_x[i] == '7' && err == 0) k += 7;
		else if (str_x[i] == '8' && err == 0) k += 8;
		else if (str_x[i] == '9' && err == 0) k += 9;
		else if (str_x[i] == ' ' && err == 0 && i != 0) {
			if (str_x[i - 1] == ' ') {
				if (err == 0) err++;
			}
			if (str_x[i + 1] != '\0') {
				k /= 10;
				x[j] = k;
				j++;
				k = 0;
			}
			else k /= 10;
		}
		else {
			if (err == 0) err++;
		}
	}
	x[j] = k;
	s[0] = 0;
	if (err == 0 && click <= j)
		for (int i = 0; i <= click; i++) {
			Mili(x, y, s, i, click, err);
		}
	else err++;
	if (err == 0) {
		for (int i = 0; i <= j + 1; i++) {
			if (s[i] == 0) str_s += "0 ";
			else if (s[i] == 1) str_s += "1 ";
			else if (s[i] == 2) str_s += "2 ";
			else if (s[i] == 3) str_s += "3 ";
			else if (s[i] == 4) str_s += "4 ";
			else if (s[i] == 5) str_s += "5 ";
			else if (s[i] == 6) str_s += "6 ";
			else if (s[i] == 7) str_s += "7 ";
			else if (s[i] == 8) str_s += "8 ";
			else if (s[i] == 9) str_s += "9 ";
			else if (s[i] == 10) str_s += "10 ";
			else if (s[i] == 11) str_s += "11 ";
		}
		for (int i = 0; i <= j; i++) {
			if (y[i] == 0) str_y += "0 ";
			else if (y[i] == 1) str_y += "1 ";
			else if (y[i] == 2) str_y += "2 ";
			else if (y[i] == 3) str_y += "3 ";
			else if (y[i] == 4) str_y += "4 ";
			else if (y[i] == 5) str_y += "5 ";
			else if (y[i] == 6) str_y += "6 ";
			else if (y[i] == 7) str_y += "7 ";
			else if (y[i] == 8) str_y += "8 ";
			else if (y[i] == 9) str_y += "9 ";
			else if (y[i] == 10) str_y += "10 ";
			else if (y[i] == 11) str_y += "11 ";
			else if (y[i] == 12) str_y += "12 ";
			else if (y[i] == 13) str_y += "13 ";
			else if (y[i] == 14) str_y += "14 ";
			else if (y[i] == 15) str_y += "15 ";
			else if (y[i] == 16) str_y += "16 ";
		}
	}
	String^ ss = marshal_as<String^>(str_s);
	String^ sy = marshal_as<String^>(str_y);
	if (err == 0) {
		textBox4->Text = sx;
		textBox1->Text = sy;
		textBox3->Text = ss;
	}
	else {
		textBox4->Text = "ќшибка!";
		textBox1->Text = "";
		textBox3->Text = "";
	}
	click++;
	delete[] x;
	delete[] y;
	delete[] s;
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	setlocale(LC_ALL, "Russian");
	int n = 0;
	String^ sx = textBox2->Text;
	string str_x = marshal_as<string>(sx), str_y = "", str_s = "";
	for (int i = 0; i < str_x.length(); i++)
		if (i != 0)
			if ((str_x[i] == ' ' || str_x[i] == '\0') && str_x[i - 1] != ' ') n++;
	int k = 0, j = 0, err = 0;
	int* x = new int[n + 1];
	int* y = new int[n + 1];
	int* s = new int[n + 2];
	for (int i = 0; i < str_x.length(); i++) {
		k *= 10;
		if (str_x[i] == '0' && err == 0) k = k;
		else if (str_x[i] == '1' && err == 0) k++;
		else if (str_x[i] == '2' && err == 0) k += 2;
		else if (str_x[i] == '3' && err == 0) k += 3;
		else if (str_x[i] == '4' && err == 0) k += 4;
		else if (str_x[i] == '5' && err == 0) k += 5;
		else if (str_x[i] == '6' && err == 0) k += 6;
		else if (str_x[i] == '7' && err == 0) k += 7;
		else if (str_x[i] == '8' && err == 0) k += 8;
		else if (str_x[i] == '9' && err == 0) k += 9;
		else if (str_x[i] == ' ' && err == 0 && i != 0) {
			if (str_x[i - 1] == ' ') {
				if (err == 0) err++;
			}
			if (str_x[i + 1] != '\0') {
				k /= 10;
				x[j] = k;
				j++;
				k = 0;
			}
			else k /= 10;
		}
		else {
			if (err == 0) err++;
		}
	}
	x[j] = k;
	s[0] = 0;
	if (err == 0)
		for (int i = 0; i <= j; i++) {
			Mili(x, y, s, i, j, err);
		}
	if (err == 0) {
		for (int i = 0; i <= j + 1; i++) {
			if (s[i] == 0) str_s += "0 ";
			else if (s[i] == 1) str_s += "1 ";
			else if (s[i] == 2) str_s += "2 ";
			else if (s[i] == 3) str_s += "3 ";
			else if (s[i] == 4) str_s += "4 ";
			else if (s[i] == 5) str_s += "5 ";
			else if (s[i] == 6) str_s += "6 ";
			else if (s[i] == 7) str_s += "7 ";
			else if (s[i] == 8) str_s += "8 ";
			else if (s[i] == 9) str_s += "9 ";
			else if (s[i] == 10) str_s += "10 ";
			else if (s[i] == 11) str_s += "11 ";
		}
		for (int i = 0; i <= j; i++) {
			if (y[i] == 0) str_y += "0 ";
			else if (y[i] == 1) str_y += "1 ";
			else if (y[i] == 2) str_y += "2 ";
			else if (y[i] == 3) str_y += "3 ";
			else if (y[i] == 4) str_y += "4 ";
			else if (y[i] == 5) str_y += "5 ";
			else if (y[i] == 6) str_y += "6 ";
			else if (y[i] == 7) str_y += "7 ";
			else if (y[i] == 8) str_y += "8 ";
			else if (y[i] == 9) str_y += "9 ";
			else if (y[i] == 10) str_y += "10 ";
			else if (y[i] == 11) str_y += "11 ";
			else if (y[i] == 12) str_y += "12 ";
			else if (y[i] == 13) str_y += "13 ";
			else if (y[i] == 14) str_y += "14 ";
			else if (y[i] == 15) str_y += "15 ";
			else if (y[i] == 16) str_y += "16 ";
		}
	}
	String^ ss = marshal_as<String^>(str_s);
	String^ sy = marshal_as<String^>(str_y);
	if (err == 0) {
		textBox4->Text = sx;
		textBox1->Text = sy;
		textBox3->Text = ss;
	}
	else { 
		textBox4->Text = "ќшибка!"; 
		textBox1->Text = "";
		textBox3->Text = "";
	}
	delete[] x;
	delete[] y;
	delete[] s;
}


};
}