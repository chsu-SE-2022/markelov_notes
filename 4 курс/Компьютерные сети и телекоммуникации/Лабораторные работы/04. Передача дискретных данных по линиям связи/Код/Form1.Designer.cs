namespace WinFormsApp1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            richTextBox1 = new RichTextBox();
            PING = new Button();
            textBox1 = new TextBox();
            numericUpDown1 = new NumericUpDown();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            ((System.ComponentModel.ISupportInitialize)numericUpDown1).BeginInit();
            SuspendLayout();
            // 
            // richTextBox1
            // 
            richTextBox1.Location = new Point(34, 141);
            richTextBox1.Margin = new Padding(3, 4, 3, 4);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(866, 437);
            richTextBox1.TabIndex = 0;
            richTextBox1.Text = "";
            // 
            // PING
            // 
            PING.Location = new Point(814, 62);
            PING.Margin = new Padding(3, 4, 3, 4);
            PING.Name = "PING";
            PING.Size = new Size(86, 31);
            PING.TabIndex = 1;
            PING.Text = "PING";
            PING.UseVisualStyleBackColor = true;
            PING.Click += button1_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(34, 66);
            textBox1.Margin = new Padding(3, 4, 3, 4);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(614, 27);
            textBox1.TabIndex = 2;
            // 
            // numericUpDown1
            // 
            numericUpDown1.Location = new Point(654, 65);
            numericUpDown1.Margin = new Padding(3, 4, 3, 4);
            numericUpDown1.Name = "numericUpDown1";
            numericUpDown1.Size = new Size(152, 27);
            numericUpDown1.TabIndex = 3;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(654, 36);
            label1.Name = "label1";
            label1.Size = new Size(149, 20);
            label1.TabIndex = 4;
            label1.Text = "Количество пакетов";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(34, 36);
            label2.Name = "label2";
            label2.Size = new Size(131, 20);
            label2.TabIndex = 5;
            label2.Text = "Ссылка на ресурс";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(34, 117);
            label3.Name = "label3";
            label3.Size = new Size(78, 20);
            label3.TabIndex = 6;
            label3.Text = "Результат:";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(914, 600);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(numericUpDown1);
            Controls.Add(textBox1);
            Controls.Add(PING);
            Controls.Add(richTextBox1);
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)numericUpDown1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private RichTextBox richTextBox1;
        private Button button1;
        private TextBox textBox1;
        private NumericUpDown numericUpDown1;
        private Button PING;
        private Label label1;
        private Label label2;
        private Label label3;
    }
}
