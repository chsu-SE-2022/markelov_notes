using System;
using System.Windows.Forms;

namespace CheTransApp
{
    public partial class LoginForm : Form
    {
        public string UserRole { get; private set; } = "Пассажир";

        public LoginForm()
        {
            InitializeComponent();
        }

        private void btnPassenger_Click(object sender, EventArgs e)
        {
            UserRole = "Пассажир";
            DialogResult = DialogResult.OK;
        }

        private void btnAdmin_Click(object sender, EventArgs e)
        {
            using (var passwordForm = new AdminPasswordForm())
            {
                if (passwordForm.ShowDialog() == DialogResult.OK)
                {
                    UserRole = "Администратор";
                    DialogResult = DialogResult.OK;
                }
            }
        }
    }
} 