using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 智慧機上盒
{
    public partial class Form1 : Form
    {

        int while_flag = 1;
        public string[] rxbuf = new string[127];
        UInt16 rx_flag;
        string senval;
        public string[] senbuf = new string[100];


        int hand_y0;
        int conveyor_y2;
        int processing_y4;
        int detection_y6;
        int alarm_y12;
        int run_y10;
        int standby_y11;

        int hand_count = 0;
        int conveyor_count = 0;
        int processing_count = 0;
        int detection_count = 0;

        byte hand_cflag = 0;
        byte conveyor_cflag = 0;
        byte processing_cflag = 0;
        byte detection_cflag = 0;

        byte alarm_flag = 0;

        double st1_val;
        double sa1_val;
        int sa1_ad;

        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

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

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void groupBox5_Enter(object sender, EventArgs e)
        {

        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:1*");
        }

        private void Label9_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = Convert.ToString(comboBox1.SelectedItem);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            timer1.Start() ;
            timer2.Start();
            timer3.Start();
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                label2.Text = "";
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
                            label2.Text = senval;
                            senbuf = senval.Split(':', ',', '*'); // 切割
                            break;
                        }
                        rx_flag += 1;
                    }

                }

                if (senbuf[0] == "st1")
                {
                    label19.Text = senbuf[1];
                    st1_val = Convert.ToDouble(senbuf[1]);
                }
                if (senbuf[2] == "sp1")
                {
                    int y7_y4 = byte.Parse(senbuf[3], System.Globalization.NumberStyles.HexNumber);//字串轉16進制數值
                    int y3_y0 = byte.Parse(senbuf[4], System.Globalization.NumberStyles.HexNumber);
                    int y10_y13 = byte.Parse(senbuf[6], System.Globalization.NumberStyles.HexNumber);


                    hand_y0 = (y3_y0 & 1);
                    conveyor_y2 = (y3_y0 & 4);
                    processing_y4 = (y7_y4 & 1);
                    detection_y6 = (y7_y4 & 4);
                    standby_y11 = (y10_y13 & 2);
                    run_y10 = (y10_y13 & 1);
                    alarm_y12 = (y10_y13 & 4);

                }
                if (senbuf[7] == "sa1")
                {
                    label20.Text = senbuf[8];
                    sa1_val = Convert.ToDouble(senbuf[8]);
                    sa1_ad = Convert.ToByte(senbuf[9]);
                }
                if (senbuf[10] == "ss1")
                {
                    label17.Text = "";
                    label17.Text = senbuf[11];
                }
                if (senbuf[12] == "sc1")
                {
                    label18.Text = "";
                    label18.Text = senbuf[13];
                }

                rx_flag = 0;
                lab_data.Text = DateTime.Now.ToShortDateString();
                lab_time.Text = DateTime.Now.ToShortTimeString();
            }
            catch
            {

            }

         }


        private void timer2_Tick(object sender, EventArgs e)
        {
            //PLC動作
            if(hand_y0 == 1)
            {
                label25.Text = "動作中";
                if (hand_cflag == 0)
                {
                    hand_count += 1;
                    label11.Text = Convert.ToString(hand_count);
                    hand_cflag = 1;
                }
            }
            else
            {
                hand_cflag = 0;
                label25.Text = "停止動作";
            }
            //-----------------------------------------
            if (conveyor_y2 == 4)
            {
                label26.Text = "動作中";
                if (conveyor_cflag == 0)
                {
                    conveyor_count += 1;
                    label30.Text = Convert.ToString(hand_count);
                    conveyor_cflag = 1;
                }
            }
            else
            {
                conveyor_cflag = 0;
                label26.Text = "停止動作";
            }

            //--------------------------------------------
            if (processing_y4 == 1)
            {
                label27.Text = "動作中";
                if (processing_cflag == 0)
                {
                    processing_count += 1;
                    label31.Text = Convert.ToString(processing_count);
                    processing_cflag = 1;
                }
            }
            else
            {
                processing_cflag = 0;
                label27.Text = "停止動作";
            }

            //----------------------------------------------------------
            if (detection_y6 == 4)
            {
                label28.Text = "動作中";
                if (detection_cflag == 0)
                {
                    detection_count += 1;
                    label32.Text = Convert.ToString(detection_count);
                    detection_cflag = 1;
                }
            }
            else
            {
                detection_cflag = 0;
                label28.Text = "停止動作";
            }
            //--------------------------------------

            if (sa1_val > 0.1)
            {

                if (alarm_y12 == 4 || st1_val > 34)
                {
                    if (alarm_flag > 0)
                    {
                        alarm_flag = 0;
                        alarm_flag = 0;
                        alarm_flag = 0;
                        Serial_Set("BT:0*");
                    }
                    groupBox2.BackColor = Color.Red;
                    label12.Text = "危險狀態";
                }
                else if (run_y10 == 1)
                {
                    groupBox2.BackColor = Color.Lime;
                    label12.Text = "運轉中";
                    alarm_flag = 1;
                }

                else if (standby_y11 == 2)
                {
                    groupBox2.BackColor = Color.Yellow;
                    label12.Text = "待機中";
                    alarm_flag = 1;
                }
            }

        }
        private void Serial_Set(string a)
        {
            serialPort1.Write(char.ConvertFromUtf32(0x05) + char.ConvertFromUtf32(0x05) + char.ConvertFromUtf32(0x05));  //16進制數值轉字串
            serialPort1.Write(a);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:2*");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:3*");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:4*");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:5*");
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            dataGridView1.Rows.Add(DateTime.Now.ToShortDateString(), DateTime.Now.ToShortTimeString(),textBox1.Text,textBox2.Text,textBox3.Text,label12.Text,label17.Text,label18.Text,label19.Text,label20.Text,label11.Text,label30.Text,label31.Text,label32.Text);
        }
    }
}
