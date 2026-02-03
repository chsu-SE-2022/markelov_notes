using System;
using System.Windows.Forms;

namespace PI43WinForms
{
    public class HelpForm : Form
    {
        public HelpForm()
        {
            Text = "Справка";
            Width = 860;
            Height = 720;
            StartPosition = FormStartPosition.CenterParent;

            var layout = new TableLayoutPanel
            {
                Dock = DockStyle.Fill,
                ColumnCount = 1,
                RowCount = 2
            };
            layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100f));
            layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

            var browser = new WebBrowser
            {
                Dock = DockStyle.Fill,
                AllowWebBrowserDrop = false,
                IsWebBrowserContextMenuEnabled = false,
                ScriptErrorsSuppressed = true,
                WebBrowserShortcutsEnabled = false
            };

            string html = @"<!DOCTYPE html>
<html lang='ru'>
<head>
  <meta charset='utf-8'>
  <title>Справка</title>
  <style>
    html, body { height: 100%; }
    body { font-family: 'Segoe UI', Arial, sans-serif; color: #1f2937; margin: 0; }
    .container { box-sizing: border-box; padding: 28px 36px; }
    h1 { font-size: 24px; margin: 0 0 8px; color: #0f172a; }
    .subtitle { color: #475569; margin-bottom: 18px; }
    h2 { font-size: 18px; margin: 26px 0 12px; color: #0f172a; }
    p { line-height: 1.6; margin: 8px 0; }
    ol { margin: 10px 0 10px 22px; }
    li { margin: 6px 0; }
    .card { background: #ffffff; border: 1px solid #e5e7eb; border-radius: 10px; box-shadow: 0 4px 14px rgba(0,0,0,0.06); }
    .header { padding: 18px 22px; border-bottom: 1px solid #e5e7eb; background: linear-gradient(180deg,#fff,#fafafa); border-top-left-radius: 10px; border-top-right-radius: 10px; }
    .content { padding: 22px; }
    .note { background: #f1f5f9; border-left: 4px solid #3b82f6; padding: 12px 14px; border-radius: 6px; color: #0f172a; margin: 16px 0; }
    .muted { color: #64748b; }
    .em { font-weight: 600; }
    .mono { font-family: ui-monospace, SFMono-Regular, Menlo, Consolas, monospace; }
  </style>
  </head>
  <body>
    <div class='container'>
      <div class='card'>
        <div class='header'>
          <h1>Постановление мэрии г. Череповца № 967</h1>
          <div class='subtitle'>от 09.12.1999</div>
        </div>
        <div class='content'>
          <p>С целью сохранения памяти об истории Череповца и вкладе первого городского головы <span class='em'>И. А. Милютина</span> в развитие города мэрия постановляет:</p>
          <ol>
            <li><span class='em'>Присвоить</span> улице Энгельса название <span class='em'>улица Милютина</span>.</li>
            <li>В связи со сносом домов № 1–50 по улице Энгельса одновременно с изменением названия улицы <span class='em'>изменить нумерацию на 50</span> (по принципу: 51 – 1, 52 – 2 и т. д.).</li>
            <li>С целью улучшения социальной и криминогенной обстановки в Индустриальном районе организовать работу приюта по адресу <span class='em'>ул. Энгельса, 72 (ул. Милютина, 22)</span>. Всех жителей, прописанных на улице Энгельса (Милютина) и не имеющих постоянное место жительства, поселить в приют.</li>
            <li>Сотрудникам ФМС России внести изменения адресов регистрации жителей Череповца в муниципальную базу данных «Череповец» с помощью специализированного программного обеспечения «Череповец – адреса» в соответствии с Руководством пользователя в приложении 1 настоящего постановления.</li>
            <li>Студентам направления «Программная инженерия» Череповецкого государственного университета разработать программное обеспечение «Череповец – адреса», позволяющее в автоматизированном порядке внести изменения адресов в базу данных «Череповец».</li>
          </ol>

          <div class='note'>
            Указ вступает в силу <span class='em'>с 1 января 2000 года</span>.
          </div>

          <h2>Приложение 1. Руководство пользователя</h2>
          <ol>
            <li><span class='em'>1 января 2000 года в 00:00</span> запустить программу и нажать на кнопку <span class='mono'>«Применить изменения»</span>.</li>
            <li>Проверить корректность внесенных изменений в таблице.</li>
            <li>Если изменения корректны — нажать на кнопку <span class='mono'>«Сохранить»</span>.</li>
            <li>Если изменения некорректны — обратиться к техническому специалисту.</li>
            <li>Если изменения были внесены преждевременно — немедленно нажать на <span class='mono'>«Восстановить исходные данные»</span>, затем на <span class='mono'>«Сохранить»</span>.</li>
          </ol>
        </div>
      </div>
    </div>
  </body>
</html>";

            browser.DocumentText = html;

            var btnClose = new Button
            {
                Text = "Закрыть",
                Anchor = AnchorStyles.Right,
                AutoSize = true,
                Padding = new Padding(10, 6, 10, 6),
                Margin = new Padding(8)
            };
            btnClose.Click += (s, e) => Close();

            var bottom = new FlowLayoutPanel
            {
                FlowDirection = FlowDirection.RightToLeft,
                Dock = DockStyle.Fill,
                Padding = new Padding(0, 8, 8, 8)
            };
            bottom.Controls.Add(btnClose);

            layout.Controls.Add(browser, 0, 0);
            layout.Controls.Add(bottom, 0, 1);
            Controls.Add(layout);
        }
    }
}
