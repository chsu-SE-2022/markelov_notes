using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace NetworkCalc
{
    public class MainForm : Form
    {
        ComboBox cbType;
        NumericUpDown numLen;
        Button btnAdd;
        Button btnClear;
        Button btnCalc;
        DataGridView gridSegments;
        DataGridView gridPdv;
        DataGridView gridPvv;
        TextBox txtResult;
        NumericUpDown numMaxPdv;
        NumericUpDown numMaxPvv;

        readonly BindingSource segmentsSrc = new();
        readonly BindingSource pdvSrc = new();
        readonly BindingSource pvvSrc = new();

        public MainForm()
        {
            Text = "Ethernet Calc";
            Width = 1200;
            Height = 750;
            MinimumSize = new Size(1000, 600);

            var left = new GroupBox { Text = "Конфигурация", Dock = DockStyle.Fill, MinimumSize = new Size(560, 0) };
            var right = new GroupBox { Text = "Результат", Dock = DockStyle.Fill };
            SuspendLayout();
            var split = new SplitContainer { Dock = DockStyle.Fill, Orientation = Orientation.Vertical, SplitterWidth = 6, FixedPanel = FixedPanel.None };
            split.Panel1.Controls.Add(left);
            split.Panel2.Controls.Add(right);
            Controls.Add(split);

            cbType = new ComboBox { DropDownStyle = ComboBoxStyle.DropDownList, Width = 220 };
            cbType.DataSource = Enum.GetValues(typeof(SegmentType));
            numLen = new NumericUpDown { Minimum = 1, Maximum = 10000, Value = 10, Width = 120 };
            btnAdd = new Button { Text = "Добавить сегмент", AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink };
            btnClear = new Button { Text = "Очистить", AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink };
            btnCalc = new Button { Text = "Рассчитать", AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink };

            // Top-left settings built as two rows: controls then buttons
            var inputs = new TableLayoutPanel { Dock = DockStyle.Top, AutoSize = true, ColumnCount = 4, Padding = new Padding(8) };
            inputs.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
            inputs.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
            inputs.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
            inputs.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
            inputs.Controls.Add(new Label { Text = "Тип сегмента:", AutoSize = true, Margin = new Padding(0, 8, 6, 0) }, 0, 0);
            inputs.Controls.Add(cbType, 1, 0);
            inputs.Controls.Add(new Label { Text = "Длина, м:", AutoSize = true, Margin = new Padding(10, 8, 6, 0) }, 2, 0);
            inputs.Controls.Add(numLen, 3, 0);

            var buttons = new FlowLayoutPanel { Dock = DockStyle.Top, AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink, FlowDirection = FlowDirection.LeftToRight, WrapContents = false, Padding = new Padding(8, 0, 8, 8) };
            buttons.Controls.Add(btnAdd);
            buttons.Controls.Add(btnClear);
            buttons.Controls.Add(btnCalc);

            var topPanel = new Panel { Dock = DockStyle.Fill, AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink };
            topPanel.Controls.Add(buttons);
            topPanel.Controls.Add(inputs);

            gridSegments = new DataGridView { Dock = DockStyle.Fill, ReadOnly = true, AutoGenerateColumns = false, AllowUserToAddRows = false, Margin = new Padding(0) };
            gridSegments.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(Segment.Type), HeaderText = "Тип", Width = 160 });
            gridSegments.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(Segment.LengthMeters), HeaderText = "Длина, м", Width = 80 });
            // Left layout: 2 rows (top autosize, bottom grid fill)
            var leftLayout = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 1, RowCount = 2, Padding = new Padding(0), AutoScroll = true };
            leftLayout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
            leftLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
            leftLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
            leftLayout.Controls.Add(topPanel, 0, 0);
            leftLayout.Controls.Add(gridSegments, 0, 1);
            left.Controls.Add(leftLayout);

            var rightTop = new Panel { Dock = DockStyle.Fill, AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink, Padding = new Padding(8) };

            numMaxPdv = new NumericUpDown { Minimum = 1, Maximum = 5000, Value = 575, Width = 100 };
            numMaxPvv = new NumericUpDown { Minimum = 1, Maximum = 500, Value = 49, Width = 100 };
            var fl2 = new FlowLayoutPanel { Dock = DockStyle.Fill, FlowDirection = FlowDirection.LeftToRight, WrapContents = true, AutoSize = true };
            fl2.Controls.Add(new Label { Text = "Критический PDV, бит:", AutoSize = true, Margin = new Padding(0, 8, 0, 0) });
            fl2.Controls.Add(numMaxPdv);
            fl2.Controls.Add(new Label { Text = "Макс. сокращение PVV, бит:", AutoSize = true, Margin = new Padding(10, 8, 0, 0) });
            fl2.Controls.Add(numMaxPvv);
            rightTop.Controls.Add(fl2);

            var tabs = new TabControl { Dock = DockStyle.Fill };
            var tabTables = new TabPage("Таблицы PDV/PVV");
            var tabOut = new TabPage("Вывод");
            tabs.TabPages.Add(tabOut);
            tabs.TabPages.Add(tabTables);
            // Right layout: 2 rows (top autosize settings, bottom tabs fill)
            var rightLayout = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 1, RowCount = 2 };
            rightLayout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
            rightLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
            rightLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
            rightLayout.Controls.Add(rightTop, 0, 0);
            rightLayout.Controls.Add(tabs, 0, 1);
            right.Controls.Add(rightLayout);

            txtResult = new TextBox { Dock = DockStyle.Fill, Multiline = true, ReadOnly = true, ScrollBars = ScrollBars.Vertical };
            tabOut.Controls.Add(txtResult);

            var splitTables = new SplitContainer { Dock = DockStyle.Fill, Orientation = Orientation.Horizontal };
            tabTables.Controls.Add(splitTables);

            gridPdv = new DataGridView { Dock = DockStyle.Fill, AutoGenerateColumns = false, AllowUserToAddRows = false };
            gridPdv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PdvEntry.Type), HeaderText = "Тип", ReadOnly = true });
            gridPdv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PdvEntry.MaxLengthMeters), HeaderText = "Макс. длина" });
            gridPdv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PdvEntry.LeftBaseBits), HeaderText = "База левого" });
            gridPdv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PdvEntry.MidBaseBits), HeaderText = "База промежуточного" });
            gridPdv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PdvEntry.RightBaseBits), HeaderText = "База правого" });
            gridPdv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PdvEntry.PerMeterBits), HeaderText = "Бит/м" });

            gridPvv = new DataGridView { Dock = DockStyle.Fill, AutoGenerateColumns = false, AllowUserToAddRows = false };
            gridPvv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PvvEntry.Type), HeaderText = "Тип", ReadOnly = true });
            gridPvv.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = nameof(PvvEntry.RepeaterShrinkBits), HeaderText = "PVV сокращение/повторитель, бит" });

            splitTables.Panel1.Controls.Add(gridPdv);
            splitTables.Panel2.Controls.Add(gridPvv);

            segmentsSrc.DataSource = new List<Segment>();
            gridSegments.DataSource = segmentsSrc;
            pdvSrc.DataSource = Defaults.Pdv();
            gridPdv.DataSource = pdvSrc;
            pvvSrc.DataSource = Defaults.Pvv();
            gridPvv.DataSource = pvvSrc;

            btnAdd.Click += (_, __) => AddSegment();
            btnClear.Click += (_, __) => { segmentsSrc.DataSource = new List<Segment>(); gridSegments.DataSource = segmentsSrc; };
            btnCalc.Click += (_, __) => Calculate();

            ResumeLayout();
            // Set initial split ratio so left takes ~65% of form width after window shows
            Shown += (_, __) =>
            {
                split.SplitterDistance = (int)(ClientSize.Width * 0.65);
            };

            // Shortcut: Ctrl+L to maximize left (~85%)
            KeyPreview = true;
            KeyDown += (s, e) =>
            {
                if (e.Control && e.KeyCode == Keys.L)
                {
                    split.SplitterDistance = (int)(ClientSize.Width * 0.85);
                    e.Handled = true;
                }
            };
        }

        void AddSegment()
        {
            var segs = (List<Segment>)segmentsSrc.DataSource;
            var seg = new Segment { Type = (SegmentType)cbType.SelectedItem, LengthMeters = (int)numLen.Value };
            var pdv = ((List<PdvEntry>)pdvSrc.List).First(p => p.Type == seg.Type);
            if (seg.LengthMeters > pdv.MaxLengthMeters)
            {
                MessageBox.Show("Длина сегмента превышает максимум для выбранного типа.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            segs.Add(seg);
            segmentsSrc.ResetBindings(false);
        }

        void Calculate()
        {
            var segs = ((List<Segment>)segmentsSrc.DataSource).ToList();
            if (segs.Count < 2)
            {
                MessageBox.Show("Добавьте как минимум начальный и конечный сегменты.");
                return;
            }

            var pdvTable = ((List<PdvEntry>)pdvSrc.List).ToDictionary(x => x.Type, x => x);
            var pvvTable = ((List<PvvEntry>)pvvSrc.List).ToDictionary(x => x.Type, x => x);

            double oneWayBits = 0;
            oneWayBits += pdvTable[segs.First().Type].LeftBaseBits;
            for (int i = 1; i < segs.Count - 1; i++) oneWayBits += pdvTable[segs[i].Type].MidBaseBits;
            oneWayBits += pdvTable[segs.Last().Type].RightBaseBits;
            foreach (var s in segs) oneWayBits += pdvTable[s.Type].PerMeterBits * s.LengthMeters;

            double roundTripBits = 2 * oneWayBits;

            int repeaters = Math.Max(0, segs.Count - 1);
            double totalPvv = 0;
            for (int i = 0; i < repeaters; i++)
            {
                var t = segs[Math.Min(i + 1, segs.Count - 1)].Type;
                totalPvv += pvvTable[t].RepeaterShrinkBits;
            }

            bool pdvOk = roundTripBits <= (double)numMaxPdv.Value;
            bool pvvOk = totalPvv <= (double)numMaxPvv.Value;

            var lines = new List<string>();
            lines.Add($"Удвоенная задержка распространения (PDV): {roundTripBits:F2} бит");
            lines.Add($"Суммарное сокращение PVV повторителями: {totalPvv:F0} бит");
            lines.Add($"Работоспособность: {(pdvOk && pvvOk ? "Сеть работоспособна" : "Сеть НЕ работоспособна")}");
            lines.Add("");
            lines.Add("Подробности PDV:");
            lines.Add($"  Левый базовый: {pdvTable[segs.First().Type].LeftBaseBits}");
            lines.Add($"  Промежуточные базовые: {Enumerable.Range(1, Math.Max(0, segs.Count-2)).Sum(i=>pdvTable[segs[i].Type].MidBaseBits):F2}");
            lines.Add($"  Правый базовый: {pdvTable[segs.Last().Type].RightBaseBits}");
            lines.Add($"  По длинам: {segs.Sum(s=>pdvTable[s.Type].PerMeterBits * s.LengthMeters):F2}");

            txtResult.Text = string.Join(Environment.NewLine, lines);
        }
    }
}
