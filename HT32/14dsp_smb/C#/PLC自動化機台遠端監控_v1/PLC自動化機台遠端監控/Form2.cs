using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PLC自動化機台遠端監控
{
    public partial class Form2 : Form
    {
        int x =0;

        public Form2()
        {
            InitializeComponent();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            

            timer1.Start(); //啟動計時器
            groupBox1.BackColor = Color.Red; //溫度異常 背景顏色(紅)

            label22.Text = "0";
            label29.Text = "586";

            //==============機台履歷
            label31.Text = "A-1";
            label32.Text = "PP/PS板";
            label33.Text = "0001";
            label34.Text = "運轉中";
            //==============機台狀況
            label10.Text = "運轉中";
            label9.Text = "運轉中";
            label8.Text = "運轉中";
            label7.Text = "運轉中";
            //==============感測狀況
            label19.Text = "10";
            label18.Text = x.ToString();
            label17.Text = "70";
            label16.Text = "220";
            //==============機台動作次數
            label27.Text = x.ToString();
            label26.Text = x.ToString();
            label25.Text = x.ToString();
            label24.Text = x.ToString();

           
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Interval = 1000; //設Timer1的時間間隔為1000毫秒，也就是1秒
            
            dataGridView1.Rows.Add(DateTime.Now.ToShortDateString(), DateTime.Now.ToShortTimeString(), label31.Text, label32.Text, label33.Text, label19.Text, label18.Text, label17.Text, label16.Text);
            dataGridView2.Rows.Add(label10.Text, label9.Text, label8.Text, label7.Text,label27.Text, label26.Text, label25.Text, label24.Text);

            x += 1;
            label18.Text = x.ToString();
            label27.Text = x.ToString();
            label26.Text = x.ToString();
            label25.Text = x.ToString();
            label24.Text = x.ToString();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            
            
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form1 f = new Form1();
            f.Visible = true;
        }
    }
}
