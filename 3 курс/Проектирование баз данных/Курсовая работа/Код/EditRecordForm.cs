using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace CheTransApp
{
    public partial class EditRecordForm : Form
    {
        private readonly string tableName;
        private readonly Dictionary<string, object> recordData;
        private readonly bool isEdit;
        private readonly OleDbConnection connection;
        private readonly List<Control> controls = new List<Control>();
        private readonly List<string> autoIncrementFields = new List<string> { "Код времени работы", "Код времени суток", "Код графика", "Код расписания", "Код класса транспорта", "Код маршрута", "Код места оплаты", "Код направления", "Код населенного пункта", "Код остановки", "Код перевозчика", "Код способа оплаты", "Код тарифа", "Код типа маршрута", "Код типа пола", "Код типа топлива", "Код транспорта", "Код типа расписания", "Код улицы", "Код ТС" };
        private readonly List<string> tableNames = new List<string> {
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
        // Явное описание внешних ключей для каждой таблицы: поле -> связанная таблица
        private readonly Dictionary<string, Dictionary<string, string>> explicitForeignKeys = new Dictionary<string, Dictionary<string, string>>
        {
            { "Время работы", new Dictionary<string, string> {
                { "Маршрут", "Маршруты" },
                { "График по месяцам", "График по месяцам" },
                { "График по дням недели", "График по дням недели" },
                { "Тип расписания", "Типы расписаний" }
            }},
            { "Интервальное расписание", new Dictionary<string, string> {
                { "Время работы", "Время работы" },
                { "Время суток", "График по времени суток" }
            }},
            { "Точное расписание", new Dictionary<string, string> {
                { "Время работы", "Время работы" },
                { "Направление", "Направления движения" }
            }},
            { "Маршруты", new Dictionary<string, string> {
                { "Тип транспорта", "Тип транспорта" },
                { "Тип маршрута", "Тип маршрута" },
                { "Начальная", "Остановки" },
                { "Конечная", "Остановки" },
                { "Перевозчик", "Перевозчики" },
                { "Транспортные средства", "Транспортные средства" },
                { "Тариф", "Тарифы" },
                { "Способы оплаты", "Способы оплаты" },
                { "Места оплаты", "Места оплаты" }
            }},
            { "Остановки", new Dictionary<string, string> {
                { "Улица", "Улицы" }
            }},
            { "Улицы", new Dictionary<string, string> {
                { "Населенный пункт", "Населенные пункты" }
            }},
            { "Транспортные средства", new Dictionary<string, string> {
                { "Класс транспорта", "Класс транспорта" },
                { "Тип пола", "Тип пола" },
                { "Тип топлива", "Тип топлива" }
            }},
            // Добавьте остальные таблицы и их внешние ключи по необходимости
        };

        public Dictionary<string, object> ResultData { get; private set; }

        public EditRecordForm(string tableName, Dictionary<string, object> recordData = null, OleDbConnection connection = null)
        {
            this.tableName = tableName;
            this.recordData = recordData;
            this.isEdit = recordData != null;
            this.connection = connection;
            this.Text = (isEdit ? "Изменить" : "Добавить") + $" запись: {tableName}";
            BuildForm();
        }

        private void BuildForm()
        {
            // Получаем схему таблицы
            DataTable schema = GetTableSchema();
            int y = 15;
            foreach (DataRow row in schema.Rows)
            {
                string columnName = row["COLUMN_NAME"].ToString();
                string dataType = row["DATA_TYPE"].ToString();
                bool isAutoInc = autoIncrementFields.Contains(columnName);
                if (isAutoInc && !isEdit) continue; // Не показываем автоинкрементные поля при добавлении

                Label lbl = new Label { Location = new Point(15, y + 3), AutoSize = true };
                
                // Определяем текст для подписи
                string labelText = columnName;
                if (tableName == "Интервальное расписание" && columnName == "Время работы")
                {
                    labelText = "Маршрут";
                }
                else if (tableName == "Точное расписание" && columnName == "Время работы")
                {
                    labelText = "Маршрут";
                }
                lbl.Text = labelText;

                Control ctrl;
                if (dataType.Contains("Boolean"))
                {
                    ctrl = new CheckBox { Location = new Point(180, y), Width = 200 };
                    if (isEdit && recordData.ContainsKey(columnName))
                        ((CheckBox)ctrl).Checked = Convert.ToBoolean(recordData[columnName]);
                }
                else if (dataType.Contains("Date"))
                {
                    ctrl = new DateTimePicker { Location = new Point(180, y), Width = 200, Format = DateTimePickerFormat.Custom, CustomFormat = "dd.MM.yyyy HH:mm" };
                    if (isEdit && recordData.ContainsKey(columnName))
                        ((DateTimePicker)ctrl).Value = Convert.ToDateTime(recordData[columnName]);
                }
                else if (IsExplicitForeignKey(tableName, columnName))
                {
                    ComboBox cb = new ComboBox { Location = new Point(180, y), Width = 200, DropDownStyle = ComboBoxStyle.DropDownList };
                    var items = GetForeignKeyItemsByExplicit(tableName, columnName);
                    cb.DataSource = new BindingSource(items, null);
                    cb.DisplayMember = "Value";
                    cb.ValueMember = "Key";
                    if (isEdit && recordData.ContainsKey(columnName))
                        cb.SelectedValue = recordData[columnName];
                    ctrl = cb;
                }
                else
                {
                    ctrl = new TextBox { Location = new Point(180, y), Width = 200 };
                    if (isEdit && recordData.ContainsKey(columnName))
                        ((TextBox)ctrl).Text = recordData[columnName]?.ToString();
                }
                ctrl.Name = "ctrl_" + columnName;

                // Делаем автоинкрементные поля недоступными для редактирования при изменении записи
                if (isAutoInc && isEdit)
                {
                    ctrl.Enabled = false; // Отключаем элемент управления
                }

                controls.Add(ctrl);
                this.Controls.Add(lbl);
                this.Controls.Add(ctrl);
                y += 35;
            }
            Button btnOk = new Button { Text = "Сохранить", Location = new Point(60, y), DialogResult = DialogResult.OK };
            Button btnCancel = new Button { Text = "Отмена", Location = new Point(180, y), DialogResult = DialogResult.Cancel };
            btnOk.Click += BtnOk_Click;
            this.Controls.Add(btnOk);
            this.Controls.Add(btnCancel);
            this.ClientSize = new Size(400, y + 50);
        }

        private DataTable GetTableSchema()
        {
            using (var cmd = new OleDbCommand($"SELECT * FROM [{tableName}] WHERE 1=0", connection))
            using (var adapter = new OleDbDataAdapter(cmd))
            {
                DataTable dt = new DataTable();
                adapter.Fill(dt);
                DataTable schema = new DataTable();
                schema.Columns.Add("COLUMN_NAME", typeof(string));
                schema.Columns.Add("DATA_TYPE", typeof(string));
                foreach (DataColumn col in dt.Columns)
                {
                    var row = schema.NewRow();
                    row["COLUMN_NAME"] = col.ColumnName;
                    row["DATA_TYPE"] = col.DataType.Name;
                    schema.Rows.Add(row);
                }
                return schema;
            }
        }

        private bool IsExplicitForeignKey(string table, string column)
        {
            return explicitForeignKeys.ContainsKey(table) && explicitForeignKeys[table].ContainsKey(column);
        }

        private Dictionary<int, string> GetForeignKeyItemsByExplicit(string table, string column)
        {
            string refTable = explicitForeignKeys[table][column];
            var items = new Dictionary<int, string>();

            // Определяем кастомные подписи для некоторых таблиц
            List<string> customLabels = null;
            if (refTable == "Способы оплаты")
            {
                customLabels = new List<string> {
                    "Только наличные", "Наличные и банковская карта", "Наличные и любые карты", "Все способы"
                };
            }
            else if (refTable == "Места оплаты")
            {
                customLabels = new List<string> {
                    "Кондуктор", "Валидатор+Водитель", "Валидатор+Автомат", "Кондутор+Валидатор", "Водитель", "Автовокзал", "Автовокзал+Онлайн", "Кодуктор+Автовокзал", "Кондуктор+Автовокзал+Онлайн", "Водитель+Автовокзал", "Водитель+Автовокзал+Онлайн"
                };
            }
            else if (refTable == "Тарифы")
            {
                customLabels = new List<string> {
                    "Городской с бесплатной пересадкой", "Городской без бесплатной пересадки", "Для коротких маршрутов", "Пригородный"
                };
            }

            int index = 0;
            using (var cmd = new OleDbCommand($"SELECT * FROM [{refTable}]", connection))
            using (var reader = cmd.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = Convert.ToInt32(reader[0]);
                    string value;

                    if (customLabels != null && index < customLabels.Count)
                    {
                         value = customLabels[index];
                    }
                    else if (refTable == "График по месяцам")
                        value = GetMonthScheduleName(reader);
                    else if (refTable == "График по дням недели")
                        value = GetWeekScheduleName(reader);
                    else if (refTable == "Время работы")
                         value = GetWorkTimeRouteNumber(reader);
                    else if (refTable == "График по времени суток")
                         value = GetTimeOfDayName(reader);
                    else if (refTable == "Транспортные средства")
                         value = "Вариант " + reader[0].ToString(); // Используем ID с префиксом "Вариант " для транспортных средств
                    else
                        value = reader[GetDisplayField(refTable)]?.ToString();

                    items[key] = value;
                    index++;
                }
            }
            return items;
        }

        private string GetMonthScheduleName(IDataRecord reader)
        {
            // Индексы: 1-12 — месяцы
            bool[] months = new bool[12];
            for (int i = 0; i < 12; i++)
                months[i] = Convert.ToBoolean(reader[i + 1]);
            if (months.All(x => x)) return "Круглогодично";
            if (months[5] && months[6] && months[7] && months.Take(5).All(x => !x) && months.Skip(8).All(x => !x)) return "В летний период";
            if (months[8] && months[9] && months[10] && months[11] && months[0] && months[1] && months[2] && months[3] && months[4] && !months[5] && !months[6] && !months[7]) return "В течение учебного года";
            if (months[11] && months[0] && months[1] && months.Skip(2).All(x => !x)) return "В зимний период";
            // Индивидуально — перечислить месяцы
            string[] monthNames = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
            var active = monthNames.Where((m, i) => months[i]).ToArray();
            return string.Join(", ", active);
        }

        private string GetWeekScheduleName(IDataRecord reader)
        {
            // Индексы: 1-7 — дни недели
            bool[] days = new bool[7];
            for (int i = 0; i < 7; i++)
                days[i] = Convert.ToBoolean(reader[i + 1]);
            if (days.All(x => x)) return "Ежедневно";
            if (days.Take(6).All(x => x) && !days[6]) return "С понедельника по субботу";
            if (days.Take(5).All(x => x) && !days[5] && !days[6]) return "По будням";
            if (!days[0] && !days[1] && !days[2] && !days[3] && !days[4] && days[5] && days[6]) return "По выходным";
            if (!days[0] && !days[1] && !days[2] && !days[3] && !days[4] && days[5] && !days[6]) return "По субботам";
            if (!days[0] && !days[1] && !days[2] && !days[3] && !days[4] && !days[5] && days[6]) return "По воскресеньям";
            // Индивидуально — перечислить дни
            string[] dayNames = { "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" };
            var active = dayNames.Where((d, i) => days[i]).ToArray();
            return string.Join(", ", active);
        }

        private string GetWorkTimeRouteNumber(IDataRecord reader)
        {
            // Читаем поле Маршрут (второе поле после ключа)
            object routeId = reader[1]; 
            if (routeId == DBNull.Value) return "";
            int id = Convert.ToInt32(routeId);
            
            // Ищем номер маршрута в таблице Маршруты по ID
            using (var cmd = new OleDbCommand($"SELECT [Номер маршрута] FROM [Маршруты] WHERE [Код маршрута] = ?", connection))
            {
                cmd.Parameters.AddWithValue("@id", id);
                var result = cmd.ExecuteScalar();
                return result?.ToString() ?? "";
            }
        }

        private string GetTimeOfDayName(IDataRecord reader)
        {
            // Читаем Время начала и Время окончания интервала
            DateTime startTime = Convert.ToDateTime(reader["Начало интервала"]);
            DateTime endTime = Convert.ToDateTime(reader["Конец интервала"]);

            // Определяем название по времени
            if (startTime.TimeOfDay == new TimeSpan(5, 0, 0) && endTime.TimeOfDay == new TimeSpan(10, 0, 0))
                return "05:00-10:00";
            if (startTime.TimeOfDay == new TimeSpan(10, 0, 0) && endTime.TimeOfDay == new TimeSpan(15, 0, 0))
                return "10:00-15:00";
            if (startTime.TimeOfDay == new TimeSpan(15, 0, 0) && endTime.TimeOfDay == new TimeSpan(19, 0, 0))
                return "15:00-19:00";
            if (startTime.TimeOfDay == new TimeSpan(19, 0, 0) && endTime.TimeOfDay == new TimeSpan(0, 0, 0))
                return "19:00-00:00";
            if (startTime.TimeOfDay == new TimeSpan(0, 0, 0) && endTime.TimeOfDay == new TimeSpan(23, 59, 59))
                return "Весь день";

            return $"{startTime:HH:mm} - {endTime:HH:mm}"; // По умолчанию показываем интервал
        }

        private string GetDisplayField(string table)
        {
            // Простая эвристика: ищем первое текстовое поле, иначе первое поле после ключа
            using (var cmd = new OleDbCommand($"SELECT * FROM [{table}] WHERE 1=0", connection))
            using (var adapter = new OleDbDataAdapter(cmd))
            {
                DataTable dt = new DataTable();
                adapter.Fill(dt);
                foreach (DataColumn col in dt.Columns)
                {
                    if (col.DataType == typeof(string) && !col.ColumnName.StartsWith("Код "))
                        return col.ColumnName;
                }
                // fallback: второе поле
                if (dt.Columns.Count > 1)
                    return dt.Columns[1].ColumnName;
                return dt.Columns[0].ColumnName;
            }
        }

        private void BtnOk_Click(object sender, EventArgs e)
        {
            ResultData = new Dictionary<string, object>();
            foreach (var ctrl in controls)
            {
                string col = ctrl.Name.Substring(5);
                object val = null;
                if (ctrl is TextBox tb)
                    val = tb.Text;
                else if (ctrl is CheckBox cb)
                    val = cb.Checked;
                else if (ctrl is DateTimePicker dtp)
                    val = dtp.Value;
                else if (ctrl is ComboBox cmb)
                    val = ((KeyValuePair<int, string>)cmb.SelectedItem).Key;
                ResultData[col] = val;
            }
            this.DialogResult = DialogResult.OK;
        }
    }
} 