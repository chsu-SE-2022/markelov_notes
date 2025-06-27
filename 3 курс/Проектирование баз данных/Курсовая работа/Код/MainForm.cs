using System;
using System.Data;
using System.Data.OleDb;
using System.Windows.Forms;
using System.Linq;
using System.Collections.Generic;

namespace CheTransApp
{
    public partial class MainForm : Form
    {
        private string connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=CheTrans.accdb;";
        private string userRole;

        private readonly string[] tableNames = new string[]
        {
            "Время работы",
            "График по времени суток",
            "График по дням недели",
            "График по месяцам",
            "Интервальное расписание",
            "Класс транспорта",
            "Маршруты",
            "Места оплаты",
            "Направления движения",
            "Населенные пункты",
            "Остановки",
            "Перевозчики",
            "Способы оплаты",
            "Тарифы",
            "Тип маршрута",
            "Тип пола",
            "Тип топлива",
            "Тип транспорта",
            "Типы расписаний",
            "Точное расписание",
            "Транспортные средства",
            "Улицы"
        };

        public MainForm(string role)
        {
            InitializeComponent();
            userRole = role;
            InitUI();
            btnAdd.Click += btnAdd_Click;
            btnEdit.Click += btnEdit_Click;
            btnShowTable.Click += btnShowTable_Click;
            btnDelete.Click += btnDelete_Click;
        }

        private void InitUI()
        {
            if (userRole == "Пассажир")
            {
                comboBoxQueries.Visible = true;
                btnShowQuery.Visible = true;
                comboBoxTables.Visible = false;
                btnShowTable.Visible = false;
                btnAdd.Visible = btnEdit.Visible = btnDelete.Visible = false;
                
                dataGridView1.ReadOnly = true;
                dataGridView1.AllowUserToAddRows = false;
                dataGridView1.AllowUserToDeleteRows = false;
                dataGridView1.AllowUserToOrderColumns = false;
                dataGridView1.AllowUserToResizeColumns = false;
                dataGridView1.AllowUserToResizeRows = false;
                dataGridView1.MultiSelect = false;
                dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                
                comboBoxQueries.Items.Clear();
                comboBoxQueries.Items.AddRange(new string[] {
                    "Список всех маршрутов с конечными",
                    "Список всех автобусов с конечными",
                    "Список всех трамваев с конечными",
                    "Список всех городских маршрутов",
                    "Список всех пригородных маршрутов",
                    "Список всех маршрутов с тарифами",
                    "Список всех маршрутов со способами оплаты",
                    "Список всех маршрутов с местами оплаты",
                    "Список всех перевозчиков",
                    "Список всех остановок с улицами и населенными пунктами",
                    "Список всех маршрутов по транспортным средствам",
                    "Список всех маршрутов по перевозчикам",
                    "Список всех маршрутов по времени работы",
                    "Список всех маршрутов с интервальным расписанием",
                    "Список всех маршрутов, работающих летом",
                    "Список всех маршрутов с низкопольным транспортом",
                    "Список всех маршрутов с транспортом на газу",
                    "Список всех маршрутов с транспортом на электричестве",
                    "Список всех маршрутов с кондиционерами",
                    "Список всех маршрутов с USB-зарядками",
                    "Список всех маршрутов с пандусами",
                    "Список всех маршрутов с Wi-Fi",
                    "Список всех маршрутов с валидаторами",
                    "Список всех маршрутов с кондукторами",
                    "Список всех маршрутов, работающих по воскресеньям",
                    "Список всех маршрутов, работающих после 22:00",
                    "Список всех маршрутов, работающих до 06:00",
                    "Список неработающих маршрутов",
                    "Список всех маршрутов, где доступна бесплатная пересадка",
                    "Список всех маршрутов, где доступны проездные"
                });
                if (comboBoxQueries.Items.Count > 0)
                    comboBoxQueries.SelectedIndex = 0;
            }
            else
            {
                comboBoxQueries.Visible = false;
                btnShowQuery.Visible = false;
                comboBoxTables.Visible = true;
                btnShowTable.Visible = true;
                btnAdd.Visible = btnEdit.Visible = btnDelete.Visible = true;
                comboBoxTables.Items.Clear();
                comboBoxTables.Items.AddRange(tableNames);
                if (comboBoxTables.Items.Count > 0)
                    comboBoxTables.SelectedIndex = 0;
                comboBoxTables.SelectedIndexChanged -= comboBoxTables_SelectedIndexChanged;
            }
        }

        private void comboBoxTables_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (userRole == "Пассажир")
            {
                btnShowQuery_Click(sender, e);
            }
        }

        private void btnShowTable_Click(object sender, EventArgs e)
        {
            string table = comboBoxTables.SelectedItem as string;
            if (!string.IsNullOrEmpty(table))
            {
                string query = $"SELECT * FROM [{table}]";
                dataGridView1.DataSource = ExecuteQuery(query);
            }
        }

        private void btnShowQuery_Click(object sender, EventArgs e)
        {
            int idx = comboBoxQueries.SelectedIndex;
            if (idx >= 0 && idx < Queries.QueryList.Count)
                dataGridView1.DataSource = ExecuteQuery(Queries.QueryList[idx]);
        }

        public DataTable ExecuteQuery(string query)
        {
            using (OleDbConnection conn = new OleDbConnection(connectionString))
            {
                conn.Open();
                OleDbDataAdapter adapter = new OleDbDataAdapter(query, conn);
                DataTable dt = new DataTable();
                adapter.Fill(dt);
                return dt;
            }
        }

        private string GetQueryByIndex(int index)
        {
            // Здесь разместить 30 SQL-запросов, возвращать нужный по индексу
            switch (index)
            {
                case 0: return "SELECT * FROM Перевозчики";
                case 1: return "SELECT * FROM Маршруты";
                // ... и так далее
                default: return "";
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            string table = comboBoxTables.SelectedItem as string;
            if (string.IsNullOrEmpty(table)) return;
            using (var conn = new OleDbConnection(connectionString))
            {
                conn.Open();
                using (var form = new EditRecordForm(table, null, conn))
                {
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        // Сформировать INSERT
                        var data = form.ResultData;
                        var columns = string.Join(", ", data.Keys.Select(k => $"[{k}]"));
                        var values = string.Join(", ", data.Keys.Select(k => "?"));
                        string sql = $"INSERT INTO [{table}] ({columns}) VALUES ({values})";
                        using (var cmd = new OleDbCommand(sql, conn))
                        {
                            foreach (var kv in data)
                                cmd.Parameters.AddWithValue("", kv.Value ?? DBNull.Value);
                            cmd.ExecuteNonQuery();
                        }
                        // Обновить таблицу
                        dataGridView1.DataSource = null;
                        dataGridView1.DataSource = ExecuteQuery($"SELECT * FROM [{table}]");
                        dataGridView1.Refresh();
                    }
                }
            }
        }

        private void btnEdit_Click(object sender, EventArgs e)
        {
            string table = comboBoxTables.SelectedItem as string;
            if (string.IsNullOrEmpty(table) || dataGridView1.SelectedRows.Count == 0) return;
            var row = dataGridView1.SelectedRows[0];
            var data = new Dictionary<string, object>();
            foreach (DataGridViewCell cell in row.Cells)
                data[cell.OwningColumn.HeaderText] = cell.Value;
            using (var conn = new OleDbConnection(connectionString))
            {
                conn.Open();
                using (var form = new EditRecordForm(table, data, conn))
                {
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        // Сформировать UPDATE
                        var newData = form.ResultData;
                        var setClause = string.Join(", ", newData.Keys.Select(k => $"[{k}]=?"));
                        // Найти имя ключевого поля
                        string keyField = data.Keys.FirstOrDefault(k => k.StartsWith("Код "));
                        if (string.IsNullOrEmpty(keyField)) return;
                        string sql = $"UPDATE [{table}] SET {setClause} WHERE [{keyField}]=?";
                        using (var cmd = new OleDbCommand(sql, conn))
                        {
                            foreach (var kv in newData)
                            {
                                // Находим порядок параметра, соответствующий полю в SET-выражении
                                // Это важно, так как порядок параметров должен совпадать с порядком полей в SET
                                var key = kv.Key;
                                // Добавляем параметр для значения поля
                                cmd.Parameters.AddWithValue("", kv.Value ?? DBNull.Value);
                            }
                            // Добавляем параметр для условия WHERE (первичный ключ)
                            cmd.Parameters.AddWithValue("", data[keyField]);
                            cmd.ExecuteNonQuery();
                        }
                        // Обновить таблицу
                        dataGridView1.DataSource = null;
                        dataGridView1.DataSource = ExecuteQuery($"SELECT * FROM [{table}]");
                        dataGridView1.Refresh();
                    }
                }
            }
        }

        // Обработчик кнопки Удалить
        private void btnDelete_Click(object sender, EventArgs e)
        {
            string table = comboBoxTables.SelectedItem as string;
            if (string.IsNullOrEmpty(table) || dataGridView1.SelectedRows.Count == 0) return;

            // Запрос подтверждения
            DialogResult result = MessageBox.Show(
                "Вы уверены, что хотите удалить выбранную запись?",
                "Подтверждение удаления",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Warning);

            if (result == DialogResult.Yes)
            {
                var row = dataGridView1.SelectedRows[0];
                var data = new Dictionary<string, object>();
                foreach (DataGridViewCell cell in row.Cells)
                    data[cell.OwningColumn.HeaderText] = cell.Value;

                // Найти имя ключевого поля
                string keyField = data.Keys.FirstOrDefault(k => k.StartsWith("Код "));
                if (string.IsNullOrEmpty(keyField)) return;

                // Получить значение первичного ключа
                object keyValue = data[keyField];
                if (keyValue == null || keyValue == DBNull.Value) return; // Невозможно удалить без ключа

                // Сформировать DELETE запрос
                string sql = $"DELETE FROM [{table}] WHERE [{keyField}]=?";

                using (var conn = new OleDbConnection(connectionString))
                {
                    try
                    {
                        conn.Open();
                        using (var cmd = new OleDbCommand(sql, conn))
                        {
                            cmd.Parameters.AddWithValue("", keyValue);
                            int rowsAffected = cmd.ExecuteNonQuery();

                            if (rowsAffected > 0)
                            {
                                // Обновить таблицу после успешного удаления
                                dataGridView1.DataSource = null;
                                dataGridView1.DataSource = ExecuteQuery($"SELECT * FROM [{table}]");
                                dataGridView1.Refresh();
                                MessageBox.Show("Запись успешно удалена.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            }
                            else
                            {
                                MessageBox.Show("Не удалось удалить запись.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show($"Ошибка при удалении записи: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }
    }
} 