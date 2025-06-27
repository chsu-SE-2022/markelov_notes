using System;
using System.Windows.Forms;

namespace CheTransApp
{
    public partial class AdminPasswordForm : Form
    {
        public bool IsPasswordCorrect { get; private set; } = false;

        public AdminPasswordForm()
        {
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (txtPassword.Text == "1234")
            {
                IsPasswordCorrect = true;
                DialogResult = DialogResult.OK;
            }
            else
            {
                MessageBox.Show("Неверный пароль!");
                txtPassword.Clear();
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        private void txtPassword_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Enter)
            {
                btnOK_Click(sender, e);
                e.Handled = true;
            }
        }
    }
} 