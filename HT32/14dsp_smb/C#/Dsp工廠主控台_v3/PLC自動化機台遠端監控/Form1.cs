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
        Form2 f2 = new Form2();
        Form4 f4 = new Form4();
        Form6 f6 = new Form6();


        int while_flag = 1;
        public string [] rxbuf = new string [127];
        UInt16 rx_flag;
        string senval;
        public string[] senbuf = new string[100];

        int trun_y1;
        int up_y2;
        int down_y3;
        int motor_y4;
        int alarm_y5;
        int run_y7;
        int standby_y6;

        int trun_count = 0;
        int up_count = 0;
        int down_count = 0;
        int motor_count =0;

        byte trun_cflag = 0;
        byte up_cflag = 0;
        byte down_cflag = 0;
        byte motor_cflag = 0;
        byte alarm_flag = 0;


        double  st1_val;
        double  sa1_val;

        UInt16 ec_val;
        UInt16 ef_val;
        UInt16 ev_val;





        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            timer3.Start();
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
            Form2 f2 = new Form2();//產生Form2的物件，才可以使用它所提供的Method
         
            f2.Show(this);//
        }

        private void button10_Click(object sender, EventArgs e)
        {

            f4.Show();
        }

        private void button11_Click(object sender, EventArgs e)
        {
           
            Serial_Set("BT:0*");
         
        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            f2.Show();

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
            timer2.Start();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
          
            //----------plc動作------------------------------------------
            if (trun_y1 == 2)
            {
                lab_trun.Text = "旋轉中";
                if(trun_cflag == 0)
                {
                    trun_count += 1;
                    lab_trun_c.Text = Convert.ToString(trun_count);
                    trun_cflag = 1;
                }
            }
            else
            {
                lab_trun.Text = "停止動作" ;
                trun_cflag = 0;
            }

            //-------------------------------------
            if (up_y2 == 4)
            {
                lab_up.Text = "上升中";
                if (up_cflag == 0)
                {
                    up_count += 1;
                    lab_up_c.Text = Convert.ToString(trun_count);
                    up_cflag = 1;
                }
            }
            else
            {
                lab_up.Text = "停止動作";
                up_cflag = 0;
            }
            //--------------------------------------
            if (down_y3 == 8)
            {
                lab_down.Text = "下降中";
                if (down_cflag == 0)
                {
                    up_count += 1;
                    lab_down_c.Text = Convert.ToString(trun_count);
                    down_cflag = 1;
                }
            }
            else
            {
                lab_down.Text = "停止動作";
                down_cflag = 0;
            }
               
            //--------------------------------------
            if (motor_y4 == 1)
            {
                lab_motor.Text = "運轉中";               
            }
            else lab_motor.Text = "停止動作";
            //--------------機台狀態-------------------------------------
            
            
                if (sa1_val > 0.25)
                {
                
                if (alarm_y5 == 2 || st1_val > 34)
                    {
                        if (alarm_flag > 0)
                        {
                            alarm_flag = 0;
                            alarm_flag = 0;
                            alarm_flag = 0;
                        Serial_Set("BT:3*");
                        }
                            
                       groupBox4.BackColor = Color.Red;
                        lab_Machine_status.Text = "危險狀態";
                      
                    }
                    else if (run_y7 == 8)
                    {
                        groupBox4.BackColor = Color.Yellow;
                        lab_Machine_status.Text = "運轉中";
                         alarm_flag = 1;
                    }
               
                    else if (standby_y6 == 4)
                    {
                        groupBox4.BackColor = Color.Lime;
                        lab_Machine_status.Text = "待機中";
                        alarm_flag = 1;
                    }
                } 
                else
                {
                    groupBox4.BackColor = Color.DodgerBlue;
                    lab_Machine_status.Text = "關機狀態";
                }

               
                
            
            //-----------PLC次數--------------------------------
            if (up_count == 0) lab_up_c.Text = "0";
            if (down_count == 0) lab_down_c.Text = "0";
            if (trun_count == 0) lab_trun_c.Text = "0";

            //----------------環境------------------------
            if (ec_val > 1000) lab_ec.BackColor = Color.Red;
            else lab_ec.BackColor = Color.Aquamarine;
            if(ef_val>100) lab_ef.BackColor = Color.Red;
            else lab_ef.BackColor = Color.Aquamarine;
            if (ev_val > 100) lab_ev.BackColor = Color.Red;
            else lab_ev.BackColor = Color.Aquamarine;






        }
        private void Serial_Set(string a)
        {
            serialPort1.Write(char.ConvertFromUtf32(0x03)+ char.ConvertFromUtf32(0x03)+ char.ConvertFromUtf32(0x04));  //16進制數值轉字串
            serialPort1.Write(a);
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {

            }
            catch
            {

            }
            
            label20.Text = "";
            senval = "";
            if(serialPort1.BytesToRead != 0)  //緩衝區是否有東西
            {
                while(while_flag !=0)
                {
                    //rxbuf[rx_flag] = char.ConvertFromUtf32 (serialPort1.ReadByte  ()); //讀取緩衝區資料到texBox1
                    rxbuf[rx_flag] = char.ConvertFromUtf32(serialPort1.ReadByte());
                    senval += rxbuf[rx_flag];
                    if (rxbuf[rx_flag] == "*")
                    {
                        //Array.Clear (senbuf,0,senbuf.Length); // 清空
                        label20.Text = senval;
                        senbuf = senval.Split(':', ',','*'); // 切割
                        break;
                    }
                    rx_flag += 1;
                }
                    
            }
         
            for (int i = 0; i <= rx_flag; i++)
            {
                 if(rxbuf[i] == "s"&& rxbuf[2]=="1")
                {
 
                    if (rxbuf[i+1] =="t" )
                    {
                        //lab_st1.Text = "";
                        lab_st1.Text = senbuf[1];
                        
                        st1_val = Convert.ToDouble(senbuf[1]);
                    }
                    else if (rxbuf[i + 1] == "a")
                    {
                        //lab_sa1.Text = "";
                        lab_sa1.Text = senbuf[5];
                        sa1_val = Convert.ToDouble(senbuf[5]);
                    }
                    else if (rxbuf[i + 1] == "s")
                    {
                        lab_ss1.Text = "";
                        lab_ss1.Text = senbuf[7];
                    }
                    else if (rxbuf[i + 1] == "p")
                    {
                        //lab_sp1.Text = "";
                        try
                        {
                            int y7_y4 = byte.Parse(rxbuf[i + 4], System.Globalization.NumberStyles.HexNumber);//字串轉16進制數值
                            int y3_y0 = byte.Parse(rxbuf[i + 5], System.Globalization.NumberStyles.HexNumber);
                            trun_y1 = (y3_y0 & 2); //(數值AND);
                            up_y2   = (y3_y0 & 4);
                            down_y3 = (y3_y0 & 8);

                            motor_y4   = (y7_y4 & 1);
                            alarm_y5   = (y7_y4 & 2);
                            standby_y6 = (y7_y4 & 4);
                            run_y7     = (y7_y4 & 8);

                        }
                        catch
                        {

                        }

                    }
                    else if (rxbuf[i + 1] == "c")
                    {
                        /*lab_sc1_sok.Text = "";
                        lab_sc1_pok.Text = "";
                        lab_sc1_sno.Text = ""; 
                        lab_sc1_pno.Text = "";*/
                        lab_sc1_sok.Text = senbuf[9];
                        lab_sc1_pok.Text = senbuf[10];
                        lab_sc1_sno.Text = senbuf[11];
                        lab_sc1_pno.Text = senbuf[12];
                        
                    }
                }
                else if(rxbuf[i] == "e")
                {
                    if(rxbuf[i+1]=="t")
                    {
                        lab_et.Text = senbuf[1];
                    }
                    else if (rxbuf[i + 1] == "h")
                    {
                        lab_eh.Text = senbuf[3];
                    }
                    else if (rxbuf[i + 1] == "c")
                    {
                        lab_ec.Text = senbuf[5];
                        ec_val = Convert.ToUInt16(lab_ec.Text);
                    }
                    else if (rxbuf[i + 1] == "f")
                    {
                        lab_ef.Text = senbuf[7];
                        ef_val = Convert.ToUInt16(lab_ef.Text);
                    }
                    else if (rxbuf[i + 1] == "v")
                    {
                        lab_ev.Text = senbuf[9];
                        ev_val = Convert.ToUInt16(lab_ev.Text);
                    }
                    else if (rxbuf[i + 1] == "l")
                    {
                        lab_el.Text = senbuf[11];
                    }
                }
            }
          
            rx_flag = 0;
            lab_data.Text = DateTime.Now.ToShortDateString();
            lab_time.Text = DateTime.Now.ToShortTimeString();
       
        }
       



        private void button4_Click(object sender, EventArgs e)
        {
            Serial_Set("BT:3*");
            string z = "4";
            int value9 = byte.Parse(z, System.Globalization.NumberStyles.HexNumber);//字串轉16進制數值
            int a = (value9 & 1); //(數值AND)
            int b = (value9 & 4);
          

        } 
        private void button13_Click(object sender, EventArgs e)
        {
            
            Serial_Set("BT:4*");
            alarm_flag = 1;
        }

        private void label59_Click(object sender, EventArgs e)
        {

        }

        private void timer3_Tick(object sender, EventArgs e)
        {


          //---------------m1---------------------------------
            f2.lab_st1.Text = this.lab_st1.Text;
            f2.lab_sa1.Text = this.lab_sa1.Text;
            f2.lab_ss1.Text = this.lab_ss1.Text;

            f2.lab_sc1_sok.Text = this.lab_sc1_sok.Text;
            f2.lab_sc1_pok.Text = this.lab_sc1_pok.Text;
            f2.lab_sc1_sno.Text = this.lab_sc1_sno.Text;
            f2.lab_sc1_pno.Text = this.lab_sc1_pno.Text;
            f2.lab_st1.Text = this.lab_st1.Text;

            f2.lab_trun.Text = this.lab_trun.Text;
            f2.lab_trun_c.Text = this.lab_trun_c.Text;
            f2.lab_up.Text = this.lab_up.Text;
            f2.lab_up_c.Text = this.lab_up_c.Text;
            f2.lab_down.Text = this.lab_down.Text;
            f2.lab_down_c.Text = this.lab_down_c.Text;
            f2.lab_motor.Text = this.lab_motor.Text;

            f2.lab_m1_region.Text = this.textBox7.Text;
            f2.lab_m1_work.Text = this.textBox8.Text;
            f2.lab_m1_user.Text = this.textBox9.Text;

            f2.label29.Text = this.textBox10.Text;
            f2.lab_m1_status.Text = this.lab_Machine_status.Text;
            f2.groupBox1.BackColor = this.groupBox4.BackColor;

            //-------------------milieu-------------------------------
            f6.lab_et.Text = this.lab_et.Text;
            f6.lab_eh.Text = this.lab_eh.Text;
            f6.lab_ec.Text = this.lab_ec.Text;
            f6.lab_ec.BackColor = this.lab_ec.BackColor;
            f6.lab_ef.Text = this.lab_ef.Text;
            f6.lab_ef.BackColor = this.lab_ef.BackColor;
            f6.lab_ev.Text = this.lab_ev.Text;
            f6.lab_ev.BackColor = this.lab_ev.BackColor;
            f6.lab_el.Text = this.lab_el.Text;
             
            //-------------------machine3----------------------------
            f4.lab_m3_region.Text = this.textBox4.Text;
            f4.lab_m3_work.Text = this.textBox5.Text;
            f4.lab_m3_user.Text = this.textBox6.Text;
            //this.lab_m3_status.Text = f4.lab_m3_status.Text;

        }

        private void button3_Click(object sender, EventArgs e)
        {
            f6.Show();
        }
    }
}
