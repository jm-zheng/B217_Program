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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                foreach (string PortName in System.IO.Ports.SerialPort.GetPortNames())   //foreach 陳述式：foreach   (   型別   識別項   in   運算式   )   內嵌陳述式
                    comboBox1.Items.Add(PortName);
            }
            catch (Exception)
            {

            }
        }
        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button12_Click(object sender, EventArgs e)
        {
            Form2 f = new Form2();//產生Form2的物件，才可以使用它所提供的Method
            f.Show(this);//
        }

        private void button10_Click(object sender, EventArgs e)
        {
            Form4 f = new Form4();
            f.Visible = true;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            serialPort1.Write("BT:0*");
            
            label29.Text = "0";     //機台1
            label31.Text = "A-1";  
            label32.Text = "PP/PS板";
            label33.Text = "0001";
            label34.Text = "運轉中";
            groupBox4.BackColor = Color.Lime;

            label38.Text = "0";     //機台2
            label46.Text = "A-2";   
            label45.Text = "傘形齒輪";
            label44.Text = "0002";
            label43.Text = "待機狀態";

            label48.Text = "0";     //CNC機台
            label56.Text = "A-3";   
            label55.Text = "螺絲";
            label54.Text = "0003";
            label53.Text = "運轉中";
            groupBox8.BackColor = Color.Lime;

            //============================= 環境感測
            label12.Text = "27"; 
            label14.Text = "50";
            label15.Text = "456";
            label16.Text = "0";
            label17.Text = "1";
            label19.Text = "1127";

            label4.Text = DateTime.Now.ToShortDateString();
            label5.Text = DateTime.Now.ToShortTimeString();
        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            Form2 f = new Form2();//產生Form2的物件，才可以使用它所提供的Method
            f.Show(this);//
        }

        private void button9_Click(object sender, EventArgs e)
        {
            Form3 f = new Form3();//產生Form2的物件，才可以使用它所提供的Method
            f.Show(this);//
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void label4_Click(object sender, EventArgs e)
        {
            Console.Write(DateTime.Now.ToShortDateString());
        }

        private void label5_Click(object sender, EventArgs e)
        {
            Console.Write(DateTime.Now.ToShortTimeString());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = Convert.ToString(comboBox1.SelectedItem);
            serialPort1.Open();
            timer1.Start(); //啟動計時器
        }

        private void timer2_Tick(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Interval = 1;
            if (serialPort1.BytesToRead != 0)  //緩衝區是否有東西
            {
                label20.Text = serialPort1.ReadLine(); //讀取緩衝區資料到texBox1
            }
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            serialPort1.Write("BT:3*");
        }

        private void button13_Click(object sender, EventArgs e)
        {
            serialPort1.Write("BT:4*");
        }
    }
}
