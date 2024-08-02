#pragma once
#include "windows.h"
#include <iostream>
#include <math.h>

namespace Pyramid {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
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
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;



	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(872, 621);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(135, 32);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Построить пирамиду";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
			this->pictureBox1->Location = System::Drawing::Point(-1, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1020, 615);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 631);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Цвет:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(177, 631);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Масштаб:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(557, 631);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(119, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Количество оборотов:";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(682, 629);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			this->numericUpDown1->TabIndex = 8;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(366, 631);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(58, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Скорость:";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(239, 621);
			this->trackBar1->Maximum = 7;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(121, 45);
			this->trackBar1->TabIndex = 11;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(430, 621);
			this->trackBar2->Maximum = 7;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(121, 45);
			this->trackBar2->TabIndex = 12;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(87, 621);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(84, 32);
			this->button2->TabIndex = 13;
			this->button2->Text = L"Выбрать";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(51, 621);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(30, 32);
			this->pictureBox2->TabIndex = 14;
			this->pictureBox2->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1019, 663);
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Пирамида";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ gr = pictureBox1->CreateGraphics();
		System::Drawing::Color Col = colorDialog1->Color;
		Pen^ pen = gcnew Pen(Col, 4);
		int w = pictureBox1->Width;
		int h = pictureBox1->Height;
		int stop = 0;
		double coef, coef2;

		while (stop < numericUpDown1->Value) {

			if (trackBar1->Value == 0) coef = 0.25;
			if (trackBar1->Value == 1) coef = 0.5;
			if (trackBar1->Value == 2) coef = 0.75;
			if (trackBar1->Value == 3) coef = 1;
			if (trackBar1->Value == 4) coef = 1.25;
			if (trackBar1->Value == 5) coef = 1.5;
			if (trackBar1->Value == 6) coef = 1.75;
			if (trackBar1->Value == 7) coef = 2;

			if (trackBar2->Value == 0) coef2 = 0.25;
			if (trackBar2->Value == 1) coef2 = 0.5;
			if (trackBar2->Value == 2) coef2 = 0.75;
			if (trackBar2->Value == 3) coef2 = 1;
			if (trackBar2->Value == 4) coef2 = 1.25;
			if (trackBar2->Value == 5) coef2 = 1.5;
			if (trackBar2->Value == 6) coef2 = 1.75;
			if (trackBar2->Value == 7) coef2 = 2;

			int ax = -100, bx = -60, cx = 60, dx = 100, ex = 60, fx = -60;

			for (int i = 0; i <= 40; ax++, bx += 3, cx++, dx--, ex -= 3, fx--, i++) {

				double ay = sqrt((10000 - pow(ax, 2)) / 4);
				double by = sqrt((10000 - pow(bx, 2)) / 4);
				double cy = sqrt((10000 - pow(cx, 2)) / 4);
				double dy = sqrt((10000 - pow(dx, 2)) / 4);
				double ey = sqrt((10000 - pow(ex, 2)) / 4);
				double fy = sqrt((10000 - pow(fx, 2)) / 4);

				int A[] = { w / 2 + ax * coef, h / 2 + ay * coef };
				int B[] = { w / 2 + bx * coef, h / 2 + by * coef };
				int C[] = { w / 2 + cx * coef, h / 2 + cy * coef };
				int D[] = { w / 2 + dx * coef, h / 2 - dy * coef };
				int E[] = { w / 2 + ex * coef, h / 2 - ey * coef };
				int F[] = { w / 2 + fx * coef, h / 2 - fy * coef };
				int K[] = { w / 2, h / 2 - 150 * coef };

				gr->DrawLine(pen, A[0], A[1], K[0], K[1]);
				gr->DrawLine(pen, B[0], B[1], K[0], K[1]);
				gr->DrawLine(pen, C[0], C[1], K[0], K[1]);
				gr->DrawLine(pen, D[0], D[1], K[0], K[1]);
				gr->DrawLine(pen, E[0], E[1], K[0], K[1]);
				gr->DrawLine(pen, F[0], F[1], K[0], K[1]);

				gr->DrawLine(pen, A[0], A[1], B[0], B[1]);
				gr->DrawLine(pen, B[0], B[1], C[0], C[1]);
				gr->DrawLine(pen, C[0], C[1], D[0], D[1]);
				gr->DrawLine(pen, D[0], D[1], E[0], E[1]);
				gr->DrawLine(pen, E[0], E[1], F[0], F[1]);
				gr->DrawLine(pen, F[0], F[1], A[0], A[1]);
			
			Sleep(10 / coef2);
			pictureBox1->Refresh();
			}

			stop++;
		}
	}

	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	}	
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->colorDialog1->ShowDialog();
		Graphics^ gr2 = pictureBox2->CreateGraphics();
		System::Drawing::Color Col = colorDialog1->Color;
		gr2->Clear(Col);
	}
};
}