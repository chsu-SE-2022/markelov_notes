using System;
using System.Configuration;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Windows.Forms;
using Oracle.ManagedDataAccess.Client;

namespace PI43WinForms
{
    public class MainForm : Form
    {
        private readonly DataGridView _grid = new DataGridView();
        private readonly Button _btnSave = new Button();
        private readonly Button _btnApply = new Button();
        private readonly Button _btnRestore = new Button();
        private readonly Label _lblText = new Label();
        private readonly Button _btnHelp = new Button();

        private DataTable _table;
        private string _currentSource = "CHEREPOVETS"; // откуда загружены данные в текущий момент

        public MainForm()
        {
            Text = "Череповец - адреса";
            Width = 900;
            Height = 600;
            StartPosition = FormStartPosition.CenterScreen;

            var panelTop = new Panel { Dock = DockStyle.Top, Height = 72 };
            _lblText.Text = "[Заглушка текста — будет заменено позже]";
            _lblText.AutoSize = false;
            _lblText.Dock = DockStyle.Fill;
            _lblText.Padding = new Padding(8);

            var panelButtons = new Panel { Dock = DockStyle.Top, Height = 44 };

            _btnApply.Text = "Применить изменения";
            _btnApply.Width = 180;
            _btnApply.Left = 8;
            _btnApply.Top = 8;
            _btnApply.Click += (s, e) => ApplyBusinessRules();

            _btnRestore.Text = "Восстановить исходные данные";
            _btnRestore.Width = 230;
            _btnRestore.Left = _btnApply.Right + 8;
            _btnRestore.Top = 8;
            _btnRestore.Click += async (s, e) => await LoadFromBackupAsync();

            _btnSave.Text = "Сохранить";
            _btnSave.Width = 120;
            _btnSave.Left = _btnRestore.Right + 8;
            _btnSave.Top = 8;
            _btnSave.Click += async (s, e) => await SaveIntoCherepovetsAsync();

            _btnHelp.Text = "Справка";
            _btnHelp.Width = 100;
            _btnHelp.Left = _btnSave.Right + 8;
            _btnHelp.Top = 8;
            _btnHelp.Click += (s, e) => new HelpForm().ShowDialog(this);

            panelButtons.Controls.AddRange(new Control[] { _btnApply, _btnRestore, _btnSave, _btnHelp });
            panelTop.Controls.Add(_lblText);

            _grid.Dock = DockStyle.Fill;
            _grid.AllowUserToAddRows = false;
            _grid.AllowUserToDeleteRows = false;
            _grid.ReadOnly = true;
            _grid.EditMode = DataGridViewEditMode.EditProgrammatically;
            _grid.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;

            Controls.Add(_grid);
            Controls.Add(panelButtons);

            Load += async (s, e) => await InitializeAndLoadAsync();
        }

        private string GetConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["OracleXE"].ConnectionString;
        }

        private async System.Threading.Tasks.Task InitializeAndLoadAsync()
        {
            try
            {
                await LoadPreferCherepovetsElseBackupAsync();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка инициализации: " + ex, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private async System.Threading.Tasks.Task LoadPreferCherepovetsElseBackupAsync()
        {
            using (var conn = new OracleConnection(GetConnectionString()))
            {
                await conn.OpenAsync();
                var count = await ExecuteCountAsync(conn, Qualify("CHEREPOVETS"));
                if (count > 0)
                {
                    await LoadTableAsync(conn, Qualify("CHEREPOVETS"));
                }
                else
                {
                    await LoadTableAsync(conn, Qualify("CHEREPOVETS_BACKUP"));
                }
            }
        }

        private async System.Threading.Tasks.Task<int> ExecuteCountAsync(OracleConnection conn, string tableName)
        {
            using (var cmd = new OracleCommand($"SELECT COUNT(*) FROM {tableName}", conn))
            {
                var obj = await cmd.ExecuteScalarAsync();
                if (obj == null || obj == DBNull.Value) return 0;
                if (obj is decimal dec) return Convert.ToInt32(dec, CultureInfo.InvariantCulture);
                if (obj is int i) return i;
                return Convert.ToInt32(Convert.ToDecimal(Convert.ToString(obj, CultureInfo.InvariantCulture), CultureInfo.InvariantCulture));
            }
        }

        private async System.Threading.Tasks.Task LoadTableAsync(OracleConnection conn, string tableName)
        {
            var sql = $"SELECT ФАМИЛИЯ, УЛИЦА, ДОМ, КВАРТИРА FROM {tableName}";
            using (var da = new OracleDataAdapter(sql, conn))
            {
                var t = new DataTable(tableName);
                da.Fill(t);
                _table = t;
                _currentSource = tableName;
                _grid.DataSource = _table;
                SetColumnHeaders();
            }
        }

        private void SetColumnHeaders()
        {
            void SetHeader(string name, string header)
            {
                if (_grid.Columns.Contains(name)) _grid.Columns[name].HeaderText = header;
            }
            SetHeader("ФАМИЛИЯ", "Фамилия");
            SetHeader("УЛИЦА", "Улица");
            SetHeader("ДОМ", "Дом");
            SetHeader("КВАРТИРА", "Квартира");
        }

        private void ApplyBusinessRules()
        {
            if (_table == null) return;

            foreach (DataRow row in _table.Rows)
            {
                if (row.RowState == DataRowState.Deleted) continue;

                var street = Convert.ToString(row["УЛИЦА"], CultureInfo.InvariantCulture);
                if (string.Equals(street, "Энгельса", StringComparison.Ordinal))
                {
                    bool isEmptyDom = IsNullEmptyOrZero(row["ДОМ"]);
                    bool isEmptyKv = IsNullEmptyOrZero(row["КВАРТИРА"]);

                    // БОМЖей собираем только с Энгельса: если оба пустые — Дом=22, Квартира=NULL
                    if (isEmptyDom && isEmptyKv)
                    {
                        row["ДОМ"] = 22;
                        row["КВАРТИРА"] = DBNull.Value;
                        row["УЛИЦА"] = "Милютина"; // тоже переименовываем улицу
                        continue;
                    }

                    // Остальные записи по Энгельса: переименовать улицу и сместить дом -50
                    row["УЛИЦА"] = "Милютина";
                    int dom = ToInt(row["ДОМ"], 0);
                    if (dom != 0)
                    {
                        row["ДОМ"] = dom - 50;
                    }
                }
                // На остальных улицах ничего не делаем, даже если дом/квартира пустые
            }
        }

        private async System.Threading.Tasks.Task LoadFromBackupAsync()
        {
            try
            {
                using (var conn = new OracleConnection(GetConnectionString()))
                {
                    await conn.OpenAsync();
                    await LoadTableAsync(conn, Qualify("CHEREPOVETS_BACKUP"));
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка загрузки из BACKUP: " + ex.Message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private async System.Threading.Tasks.Task SaveIntoCherepovetsAsync()
        {
            if (_table == null)
            {
                MessageBox.Show("Нет данных для сохранения.");
                return;
            }

            try
            {
                using (var conn = new OracleConnection(GetConnectionString()))
                {
                    await conn.OpenAsync();
                    using (var tx = conn.BeginTransaction())
                    {
                        using (var del = new OracleCommand($"DELETE FROM {Qualify("CHEREPOVETS")}", conn))
                        {
                            del.Transaction = tx;
                            await del.ExecuteNonQueryAsync();
                        }

                        using (var ins = new OracleCommand($"INSERT INTO {Qualify("CHEREPOVETS")} (ФАМИЛИЯ, УЛИЦА, ДОМ, КВАРТИРА) VALUES (:fam, :ul, :dom, :kv)", conn))
                        {
                            ins.Transaction = tx;
                            ins.BindByName = true;
                            ins.Parameters.Add(":fam", OracleDbType.NVarchar2, 100);
                            ins.Parameters.Add(":ul", OracleDbType.NVarchar2, 200);
                            ins.Parameters.Add(":dom", OracleDbType.Varchar2);
                            ins.Parameters.Add(":kv", OracleDbType.Varchar2);

                            foreach (DataRow row in _table.Rows)
                            {
                                if (row.RowState == DataRowState.Deleted) continue;
                                ins.Parameters[":fam"].Value = row["ФАМИЛИЯ"] == DBNull.Value ? (object)DBNull.Value : row["ФАМИЛИЯ"]; 
                                ins.Parameters[":ul"].Value = row["УЛИЦА"] == DBNull.Value ? (object)DBNull.Value : row["УЛИЦА"]; 
                                ins.Parameters[":dom"].Value = row["ДОМ"] == DBNull.Value ? (object)DBNull.Value : row["ДОМ"]; 
                                ins.Parameters[":kv"].Value = row["КВАРТИРА"] == DBNull.Value ? (object)DBNull.Value : row["КВАРТИРА"]; 
                                await ins.ExecuteNonQueryAsync();
                            }
                        }

                        tx.Commit();
                    }
                }
                MessageBox.Show("Данные сохранены в CHEREPOVETS.");
                _currentSource = "CHEREPOVETS";
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка сохранения: " + ex.Message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private static int ToInt(object v, int def = 0)
        {
            if (v == null || v == DBNull.Value) return def;
            if (v is int i) return i;
            if (v is decimal d) return Convert.ToInt32(d, CultureInfo.InvariantCulture);
            var s = Convert.ToString(v, CultureInfo.InvariantCulture);
            if (int.TryParse(s, NumberStyles.Any, CultureInfo.InvariantCulture, out var r)) return r;
            if (double.TryParse(s, NumberStyles.Any, CultureInfo.InvariantCulture, out var rd)) return Convert.ToInt32(rd);
            return def;
        }

        private static bool IsNullEmptyOrZero(object v)
        {
            if (v == null || v == DBNull.Value) return true;
            var s = Convert.ToString(v, CultureInfo.InvariantCulture);
            if (string.IsNullOrWhiteSpace(s)) return true;
            // Нолик в любом виде считаем пустым
            if (int.TryParse(s, NumberStyles.Any, CultureInfo.InvariantCulture, out var ri)) return ri == 0;
            if (decimal.TryParse(s, NumberStyles.Any, CultureInfo.InvariantCulture, out var rd)) return rd == 0m;
            return false;
        }

        private static string Qualify(string table)
        {
            // Добавляет схему из AppSettings["OracleSchema"], если она задана
            var schema = ConfigurationManager.AppSettings["OracleSchema"];
            if (!string.IsNullOrWhiteSpace(schema))
            {
                return $"{schema.Trim()}.{table}";
            }
            return table;
        }
    }
}
