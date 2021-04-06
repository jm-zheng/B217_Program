using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using InterfaceLib;
using MySql;

using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;



namespace PLC自動化機台遠端監控
{
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }

        private void Form4_Load(object sender, EventArgs e)
        {
            label19.Text = "10";
            label18.Text = "200";
            label17.Text = "32.5";
            label16.Text = "08:27";
            label31.Text = "B217";
            label32.Text = "23號螺桿";
            label33.Text = "鄭錦明";
            label34.Text = "STOP";
            label7.Text = "187.49";
            label8.Text = "273.54";
            label9.Text = "65.30";
            label10.Text = "MID";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form1 f = new Form1();
            f.Visible = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SQLTypedef SQLtest = new SQLTypedef();  //宣告MYSQL
            Class1.MYSQL_Init(ref SQLtest, 15, "127.0.0.1", "root", "usbw", "test"); //連線字串
            SQLtest.FROM = "test1";  //資料表名稱
            SQLtest.DATE_YMD = SQLtest.TIME = DateTime.Now; //時間
            SQLtest.COLUMN[1] = label10.Text;
            SQLtest.COLUMN[2] = label9.Text;
            SQLtest.COLUMN[3] = label8.Text;
            SQLtest.COLUMN[4] = label7.Text;
            SQLtest.COLUMN[5] = label31.Text;
            SQLtest.COLUMN[6] = label32.Text;
            SQLtest.COLUMN[7] = label33.Text;
            SQLtest.COLUMN[8] = label34.Text;
            SQLtest.COLUMN[9] = label16.Text;
            SQLtest.COLUMN[10] = label18.Text;
            SQLtest.COLUMN[11] = label17.Text;
            SQLtest.COLUMN[12] = label19.Text;
            Class1.MYSQL_ADD(SQLtest, 12);  //丟上資料庫
        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
