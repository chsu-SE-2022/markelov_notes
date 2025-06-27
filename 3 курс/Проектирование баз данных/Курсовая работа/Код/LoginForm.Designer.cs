namespace CheTransApp
{
    partial class LoginForm
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.Button btnPassenger;
        private System.Windows.Forms.Button btnAdmin;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.btnPassenger = new System.Windows.Forms.Button();
            this.btnAdmin = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnPassenger
            // 
            this.btnPassenger.Location = new System.Drawing.Point(30, 30);
            this.btnPassenger.Name = "btnPassenger";
            this.btnPassenger.Size = new System.Drawing.Size(200, 30);
            this.btnPassenger.TabIndex = 0;
            this.btnPassenger.Text = "Войти как пассажир";
            this.btnPassenger.UseVisualStyleBackColor = true;
            this.btnPassenger.Click += new System.EventHandler(this.btnPassenger_Click);
            // 
            // btnAdmin
            // 
            this.btnAdmin.Location = new System.Drawing.Point(30, 80);
            this.btnAdmin.Name = "btnAdmin";
            this.btnAdmin.Size = new System.Drawing.Size(200, 30);
            this.btnAdmin.TabIndex = 1;
            this.btnAdmin.Text = "Войти как администратор";
            this.btnAdmin.UseVisualStyleBackColor = true;
            this.btnAdmin.Click += new System.EventHandler(this.btnAdmin_Click);
            // 
            // LoginForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(264, 141);
            this.Controls.Add(this.btnAdmin);
            this.Controls.Add(this.btnPassenger);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LoginForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Авторизация";
            this.ResumeLayout(false);
        }
    }
} 