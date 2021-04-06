using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lora_etag_0527
{
    public partial class Form1 : Form
    {
        int while_flag = 1;
        public string[] rxbuf = new string[127];
        UInt16 rx_flag;
        string senval;
        public string[] senbuf = new string[100];

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

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = Convert.ToString(comboBox1.SelectedItem);
            serialPort1.Open();
            timer1.Start(); //啟動計時器
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = "";
            senval = "";
            if (serialPort1.BytesToRead != 0)  //緩衝區是否有東西
            {
                while (while_flag != 0)
                {
                    //rxbuf[rx_flag] = char.ConvertFromUtf32 (serialPort1.ReadByte  ()); //讀取緩衝區資料到texBox1
                    rxbuf[rx_flag] = char.ConvertFromUtf32(serialPort1.ReadByte());
                    senval += rxbuf[rx_flag];
                    if (rxbuf[rx_flag] == "*")
                    {
                        //Array.Clear (senbuf,0,senbuf.Length); // 清空
                        label1.Text = senval;
                        senbuf = senval.Split(':', ',', '*'); // 切割
                        break;
                    }
                    rx_flag += 1;
                }

            }

            for (int i = 0; i <= rx_flag; i++)
            {
                if (rxbuf[i] == "e")
                {

                    if (rxbuf[i + 1] == "t")
                    {
                        label2.Text = senbuf[1];
                    }
                    else if (rxbuf[i + 1] == "h")
                    {
                        label3.Text = senbuf[3];
                    }
                    else if (rxbuf[i + 1] == "c")
                    {
                        label4.Text = senbuf[5];
                        //ec_val = Convert.ToUInt16(lab_ec.Text);
                    }
                    else if (rxbuf[i + 1] == "f")
                    {
                        label5.Text = senbuf[7];
                       // ef_val = Convert.ToUInt16(lab_ef.Text);
                    }
                    else if (rxbuf[i + 1] == "v")
                    {
                        label6.Text = senbuf[9];
                        //ev_val = Convert.ToUInt16(lab_ev.Text);
                    }
                    else if (rxbuf[i + 1] == "l")
                    {
                        label7.Text = senbuf[11];
                    }
                       
                }

            }
            rx_flag = 0;

        }
    }
}
