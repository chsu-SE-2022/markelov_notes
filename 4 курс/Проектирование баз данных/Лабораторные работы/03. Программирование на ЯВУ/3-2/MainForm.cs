using System;
using System.Configuration;
using System.Data;
using System.Globalization;
using System.Windows.Forms;
using Oracle.ManagedDataAccess.Client;

namespace PI43WinForms
{
    public class MainForm : Form
    {
        private readonly DataGridView _grid = new DataGridView();
        private readonly Button _btnSave = new Button();
        private readonly Button _btnApply = new Button();
        

        private DataTable _table;
        private string _currentSource = "CHEREPOVETS_STIP"; // откуда загружены данные в текущий момент

        public MainForm()
        {
            Text = "Череповец - адреса";
            Width = 900;
            Height = 600;
            StartPosition = FormStartPosition.CenterScreen;

            var panelButtons = new Panel { Dock = DockStyle.Top, Height = 44 };

            _btnApply.Text = "Разыграть лотерею";
            _btnApply.Width = 180;
            _btnApply.Left = 8;
            _btnApply.Top = 8;
            _btnApply.Click += (s, e) => RunLottery();

            _btnSave.Text = "Сохранить";
            _btnSave.Width = 120;
            _btnSave.Left = _btnApply.Right + 8;
            _btnSave.Top = 8;
            _btnSave.Click += async (s, e) => await SaveIntoCherepovetsAsync();

            panelButtons.Controls.AddRange(new Control[] { _btnApply, _btnSave });

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
                using (var conn = new OracleConnection(GetConnectionString()))
                {
                    await conn.OpenAsync();
                    await LoadTableAsync(conn, Qualify("CHEREPOVETS_STIP"));
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка инициализации: " + ex, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        

        private async System.Threading.Tasks.Task LoadTableAsync(OracleConnection conn, string tableName)
        {
            var sql = $"SELECT ФАМИЛИЯ, УЛИЦА, ДОМ, КВАРТИРА, СТИП FROM {tableName}";
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
            SetHeader("СТИП", "Стипендия");
        }

        private void RunLottery()
        {
            if (_table == null) return;

            int M = 0;
            int N = 0;
            int rowCount = 0;
            foreach (DataRow row in _table.Rows)
            {
                if (row.RowState == DataRowState.Deleted) continue;
                rowCount++;
                int d = ToInt(row["ДОМ"], 0);
                int k = ToInt(row["КВАРТИРА"], 0);
                if (d > M) M = d;
                if (k > N) N = k;
            }

            if (M <= 0 || N <= 0 || rowCount == 0)
            {
                MessageBox.Show("Недостаточно данных для лотереи (нет валидных значений дома/квартиры).", "Лотерея", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            var rnd = new Random();
            var arr = new int[M, N];
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    arr[i, j] = rnd.Next(0, 101);
                }
            }

            int m = rnd.Next(1, M + 1);
            int n = rnd.Next(1, N + 1);
            int X = arr[m - 1, n - 1];

            DataRow winner = null;
            foreach (DataRow row in _table.Rows)
            {
                if (row.RowState == DataRowState.Deleted) continue;
                if (ToInt(row["ДОМ"], 0) == m && ToInt(row["КВАРТИРА"], 0) == n)
                {
                    winner = row;
                    break;
                }
            }

            if (winner != null)
            {
                decimal curr = 0m;
                if (!(winner["СТИП"] == DBNull.Value || winner["СТИП"] == null))
                {
                    try { curr = Convert.ToDecimal(winner["СТИП"], CultureInfo.InvariantCulture); } catch { curr = 0m; }
                }
                winner["СТИП"] = curr + X;
                MessageBox.Show($"Выпал адрес: дом {m}, кв. {n}. Х = {X}. Победитель найден — его стипендия увеличена на Х.", "Лотерея", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                if (rowCount > 0)
                {
                    decimal add = Math.Round((decimal)X / rowCount, 2, MidpointRounding.AwayFromZero);
                    foreach (DataRow row in _table.Rows)
                    {
                        if (row.RowState == DataRowState.Deleted) continue;
                        decimal curr = 0m;
                        if (!(row["СТИП"] == DBNull.Value || row["СТИП"] == null))
                        {
                            try { curr = Convert.ToDecimal(row["СТИП"], CultureInfo.InvariantCulture); } catch { curr = 0m; }
                        }
                        row["СТИП"] = curr + add;
                    }
                }
                MessageBox.Show($"Выпал адрес: дом {m}, кв. {n}. Х = {X}. По этому адресу никто не числится — Х поделен между всеми студентами.", "Лотерея", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
                        using (var del = new OracleCommand($"DELETE FROM {Qualify("CHEREPOVETS_STIP")}", conn))
                        {
                            del.Transaction = tx;
                            await del.ExecuteNonQueryAsync();
                        }

                        using (var ins = new OracleCommand($"INSERT INTO {Qualify("CHEREPOVETS_STIP")} (ФАМИЛИЯ, УЛИЦА, ДОМ, КВАРТИРА, СТИП) VALUES (:fam, :ul, :dom, :kv, :stip)", conn))
                        {
                            ins.Transaction = tx;
                            ins.BindByName = true;
                            ins.Parameters.Add(":fam", OracleDbType.NVarchar2, 100);
                            ins.Parameters.Add(":ul", OracleDbType.NVarchar2, 200);
                            ins.Parameters.Add(":dom", OracleDbType.Varchar2);
                            ins.Parameters.Add(":kv", OracleDbType.Varchar2);
                            ins.Parameters.Add(":stip", OracleDbType.Decimal);

                            foreach (DataRow row in _table.Rows)
                            {
                                if (row.RowState == DataRowState.Deleted) continue;
                                ins.Parameters[":fam"].Value = row["ФАМИЛИЯ"] == DBNull.Value ? (object)DBNull.Value : row["ФАМИЛИЯ"]; 
                                ins.Parameters[":ul"].Value = row["УЛИЦА"] == DBNull.Value ? (object)DBNull.Value : row["УЛИЦА"]; 
                                ins.Parameters[":dom"].Value = row["ДОМ"] == DBNull.Value ? (object)DBNull.Value : row["ДОМ"]; 
                                ins.Parameters[":kv"].Value = row["КВАРТИРА"] == DBNull.Value ? (object)DBNull.Value : row["КВАРТИРА"]; 
                                ins.Parameters[":stip"].Value = row.Table.Columns.Contains("СТИП") && row["СТИП"] != DBNull.Value ? row["СТИП"] : (object)DBNull.Value; 
                                await ins.ExecuteNonQueryAsync();
                            }
                        }

                        tx.Commit();
                    }
                }
                MessageBox.Show("Данные сохранены в CHEREPOVETS_STIP.");
                _currentSource = "CHEREPOVETS_STIP";
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
