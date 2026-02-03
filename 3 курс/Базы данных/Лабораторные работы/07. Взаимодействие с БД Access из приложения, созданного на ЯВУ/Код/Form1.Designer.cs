namespace бд_форм
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;
		private Button btnSave; // Кнопка Сохранить
		private Button btnSortBySurname; // Кнопка сортировки
		private Button btnShowNamesAndBirthdays; // Кнопка вывода фамилий и ДР
		private Button btnOlderThan20; // Кнопка вывода студентов старше 20 лет
		private Button btnMathAStudents; // Кнопка вывода отличников по математике
		private Button btnAllStudents; // Кнопка вывода отличников по всем предметам
		private Button btnReset; // Кнопка сброса
		private System.Windows.Forms.DataGridView dataGridView1;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            dataGridView1 = new DataGridView();
            btnSave = new Button();
            btnSortBySurname = new Button();
            btnShowNamesAndBirthdays = new Button();
            btnOlderThan20 = new Button();
            btnMathAStudents = new Button();
            btnAllStudents = new Button();
            btnReset = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToOrderColumns = true;
            dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridView1.ColumnHeadersHeight = 29;
            dataGridView1.Location = new Point(10, 10);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 51;
            dataGridView1.Size = new Size(773, 300);
            dataGridView1.TabIndex = 0;
            // 
            // btnSave
            // 
            btnSave.Location = new Point(10, 320);
            btnSave.Name = "btnSave";
            btnSave.Size = new Size(100, 30);
            btnSave.TabIndex = 1;
            btnSave.Text = "Сохранить";
            btnSave.Click += btnSave_Click;
            // 
            // btnSortBySurname
            // 
            btnSortBySurname.Location = new Point(116, 320);
            btnSortBySurname.Name = "btnSortBySurname";
            btnSortBySurname.Size = new Size(100, 30);
            btnSortBySurname.TabIndex = 2;
            btnSortBySurname.Text = "Сортировка";
            btnSortBySurname.Click += btnSortBySurname_Click;
            // 
            // btnShowNamesAndBirthdays
            // 
            btnShowNamesAndBirthdays.Location = new Point(222, 320);
            btnShowNamesAndBirthdays.Name = "btnShowNamesAndBirthdays";
            btnShowNamesAndBirthdays.Size = new Size(124, 30);
            btnShowNamesAndBirthdays.TabIndex = 3;
            btnShowNamesAndBirthdays.Text = "Фамилии и ДР";
            btnShowNamesAndBirthdays.Click += btnShowNamesAndBirthdays_Click;
            // 
            // btnOlderThan20
            // 
            btnOlderThan20.Location = new Point(352, 320);
            btnOlderThan20.Name = "btnOlderThan20";
            btnOlderThan20.Size = new Size(89, 30);
            btnOlderThan20.TabIndex = 3;
            btnOlderThan20.Text = "Старше 20";
            btnOlderThan20.Click += btnOlderThan20_Click;
            // 
            // btnMathAStudents
            // 
            btnMathAStudents.Location = new Point(447, 320);
            btnMathAStudents.Name = "btnMathAStudents";
            btnMathAStudents.Size = new Size(135, 30);
            btnMathAStudents.TabIndex = 4;
            btnMathAStudents.Text = "5 по математике";
            btnMathAStudents.Click += btnMathAStudents_Click;
            // 
            // btnAllStudents
            // 
            btnAllStudents.Location = new Point(588, 320);
            btnAllStudents.Name = "btnAllStudents";
            btnAllStudents.Size = new Size(89, 30);
            btnAllStudents.TabIndex = 5;
            btnAllStudents.Text = "5 по всем предметам";
            btnAllStudents.Click += btnAllStudents_Click;
            // 
            // btnReset
            // 
            btnReset.Location = new Point(683, 320);
            btnReset.Name = "btnReset";
            btnReset.Size = new Size(100, 30);
            btnReset.TabIndex = 6;
            btnReset.Text = "Сброс";
            btnReset.Click += btnReset_Click;
            // 
            // Form1
            // 
            ClientSize = new Size(797, 361);
            Controls.Add(dataGridView1);
            Controls.Add(btnSave);
            Controls.Add(btnSortBySurname);
            Controls.Add(btnShowNamesAndBirthdays);
            Controls.Add(btnOlderThan20);
            Controls.Add(btnMathAStudents);
            Controls.Add(btnAllStudents);
            Controls.Add(btnReset);
            Name = "Form1";
            Text = "Работа с базой данных студентов";
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
        }
    }
}
