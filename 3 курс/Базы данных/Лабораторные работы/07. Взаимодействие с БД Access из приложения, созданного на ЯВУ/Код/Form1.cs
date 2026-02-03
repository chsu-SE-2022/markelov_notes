using System;
using System.Data.OleDb;
using System.Windows.Forms;

namespace бд_форм
{
    public partial class Form1 : Form
    {
        // Строка подключения к базе данных Access
        private string connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=лб7.accdb;Persist Security Info=False;";

        // Инициализация формы
        public Form1()
        {
            InitializeComponent();
            LoadData();
        }

        // Загрузка данных из БД
        private void LoadData(string query = "SELECT * FROM ПИ33")
        {
            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                connection.Open();

                OleDbDataAdapter adapter = new OleDbDataAdapter(query, connection);

                System.Data.DataTable table = new System.Data.DataTable();
                adapter.Fill(table);

                dataGridView1.DataSource = table;
            }
        }

        // Сохранение изменений в БД
        private void SaveChanges()
        {
            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                connection.Open();

                OleDbDataAdapter adapter = new OleDbDataAdapter("SELECT * FROM ПИ33", connection);
                OleDbCommandBuilder builder = new OleDbCommandBuilder(adapter);

				System.Data.DataTable table = (System.Data.DataTable)dataGridView1.DataSource;
                adapter.Update(table);

                MessageBox.Show("Изменения сохранены");
			}
        }

		// Кнопка Сохранить
		private void btnSave_Click(object sender, EventArgs e)
		{
            SaveChanges();
		}

        // Сортировка по фамилии
        private void btnSortBySurname_Click(object sender, EventArgs e)
        {
            string query = "SELECT * FROM ПИ33 ORDER BY Фамилия";
            LoadData(query);
        }

		// Вывести фамилии и даты рождения
		private void btnShowNamesAndBirthdays_Click(object sender, EventArgs e)
		{
			string query = "SELECT Фамилия, ДР FROM ПИ33";
			LoadData(query);
		}

		// Старше 20 лет
		private void btnOlderThan20_Click(object sender, EventArgs e)
		{
			string query = "SELECT * FROM ПИ33 WHERE ДР <= DateAdd('yyyy', -20, Date())";
			LoadData(query);
		}

		// Отличники по математике
		private void btnMathAStudents_Click(object sender, EventArgs e)
		{
			string query = "SELECT * FROM ПИ33 WHERE Мат = 5";
			LoadData(query);
		}

		// Отличники по всем предметам
		private void btnAllStudents_Click(object sender, EventArgs e)
		{
			string query = "SELECT * FROM ПИ33 WHERE Мат = 5 AND Инф = 5 AND ИнЯз = 5";
			LoadData(query);
		}

		// Сброс
		private void btnReset_Click(object sender, EventArgs e)
		{
			LoadData();
		}
	}
}

