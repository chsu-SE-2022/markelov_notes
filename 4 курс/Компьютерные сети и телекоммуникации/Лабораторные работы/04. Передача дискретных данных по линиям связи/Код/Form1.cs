using System.Text;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Text = "ICMP Ping";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                string hostname = textBox1.Text;
                int n = Convert.ToInt32(numericUpDown1.Value);
                string data = "";
                byte[] buffer = Encoding.ASCII.GetBytes(data);
                uint timeout = 120;

                richTextBox1.Text = "";
                IcmpPing.Reply? firstReply = null;

                for (int i = 0; i < n; i++)
                {
                    IcmpPing.Reply reply = IcmpPing.Send(hostname, timeout, buffer);

                    if (firstReply == null)
                    {
                        firstReply = reply;
                        richTextBox1.Text += "Обмен пакетами с " + hostname + " [" + reply.Address.ToString() + "]" + ":" + '\n';
                    }

                    if (reply.Status == System.Net.NetworkInformation.IPStatus.Success)
                    {
                        richTextBox1.Text += "Ответ от " + reply.Address.ToString() + ": число байт=" + reply.DataSize + " время=" + reply.RoundtripTime + "мс TTL=" + reply.Ttl + '\n';
                    }
                    else
                    {
                        richTextBox1.Text += "Ответ от " + reply.Address.ToString() + ": статус=" + reply.Status + '\n';
                    }
                }

                if (firstReply != null)
                {
                    richTextBox1.Text += "Успешность проверки доступности хоста: " + firstReply.Status + '\n';
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Ошибка");
            }

        }
    }
}


