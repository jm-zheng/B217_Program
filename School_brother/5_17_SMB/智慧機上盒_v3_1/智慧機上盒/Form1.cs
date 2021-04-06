using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

/*using MySql;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;*/

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

        string all_sensor;

        /*SQLTypedef mysql_name = new SQLTypedef();

        delegate void SetTextCallback(string text);//用來更新UIText 的Callback
        MqttClient client;//MqttClient
        string clientId;//連線時所用的ClientID*/

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
            /*mysql_function.MYSQL_Init(ref mysql_name, 22, "127.0.0.1", "root", "123456", "5/17game");
            client = new MqttClient("liantw.com");//MQTTServer在本機
                                                  // client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;//當接收到訊息時處理函式
            clientId = Guid.NewGuid().ToString();//取得唯一碼
            client.Connect(clientId);//建立連線*/
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

            if (sa1_ad > 10)
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
            else
            {
                groupBox2.BackColor = Color.DodgerBlue;
                label12.Text = "關機";
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
           dataGridView1.Rows.Add(DateTime.Now.ToShortDateString(), DateTime.Now.ToShortTimeString(),textBox1.Text,textBox2.Text,textBox3.Text,label12.Text,label17.Text,label18.Text,label19.Text,label20.Text,label25.Text,label26.Text,label27.Text,label28.Text,label11.Text,label30.Text,label31.Text,label32.Text);
            /*mysql_name.FROM = "5/17game";
            mysql_name.DATE_YMD = mysql_name.TIME = DateTime.Now;

            mysql_name.COLUMN[1] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[2].Value);
            mysql_name.COLUMN[2] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[3].Value);
            mysql_name.COLUMN[3] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[4].Value);
            mysql_name.COLUMN[4] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[5].Value);
            mysql_name.COLUMN[5] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[6].Value);
            mysql_name.COLUMN[6] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[7].Value);
            mysql_name.COLUMN[7] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[8].Value);
            mysql_name.COLUMN[8] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[9].Value);
            mysql_name.COLUMN[9] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[10].Value);
            mysql_name.COLUMN[10] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[11].Value);
            mysql_name.COLUMN[11] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[12].Value);
            mysql_name.COLUMN[12] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[13].Value);
            mysql_name.COLUMN[13] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[14].Value);
            mysql_name.COLUMN[14] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[15].Value);
            mysql_name.COLUMN[15] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[16].Value);
            mysql_name.COLUMN[16] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[17].Value);
            mysql_function.MYSQL_ADD(mysql_name, 16);

           all_sensor = DateTime.Now.ToShortDateString() + "," + DateTime.Now.ToShortTimeString() + "," + textBox1.Text + "," + textBox2.Text + "," + textBox3.Text + "," + label12.Text + "," + label17.Text + "," + label18.Text + "," + label19.Text + "," + label20.Text + "," + label25.Text +"," + label26.Text+","+label27.Text+","+label28.Text+"," + label11.Text + "," + label30.Text + "," + label31.Text + "," + label32.Text ;
           string Topic = "5/17game";
            //發佈主題、內容及設定傳送品質 QoS 0 ( 0, 1, 2 )
            client.Publish(Topic, Encoding.UTF8.GetBytes(all_sensor), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, true);
            // button4.Text = "hello";*/

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:0*");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            timer3.Start();
        }

        private void label11_Click(object sender, EventArgs e)
        {

        }
    }
}
