using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using MySql;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;



namespace PLC自動化機台遠端監控
{
    public partial class Form2 : Form
    {
        SQLTypedef mysql_name = new SQLTypedef();
       
        string all_sensor;
        string js_date, js_time, js_st1, js_sa1, js_ss1, js_sc1_sok, js_sc1_pok, js_sc1_sno, js_sc1_pno;
        string js_trun, js_up, js_down, js_motor, js_trun_c, js_up_c, js_down_c, js_m1_rgion, js_m1_work, js_m1_user, js_m1_staus;


        delegate void SetTextCallback(string text);//用來更新UIText 的Callback
        MqttClient client;//MqttClient
        string clientId;//連線時所用的ClientID

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
            timer2.Start();




            // MessageBox.Show("必需輸入發佈主題!");


        }

        public void timer1_Tick(object sender, EventArgs e)
        {
            //設Timer1的時間間隔為1000毫秒，也就是1秒
           
            

            dataGridView1.Rows.Add(DateTime.Now.ToShortDateString(), DateTime.Now.ToShortTimeString(), lab_m1_region.Text, lab_m1_work.Text, lab_m1_user.Text, lab_ss1.Text, lab_st1.Text ,lab_sa1.Text, lab_sc1_sok.Text, lab_sc1_sno.Text);
            dataGridView2.Rows.Add(lab_m1_status.Text,lab_up.Text, lab_down.Text, lab_trun.Text, lab_motor.Text,lab_trun_c.Text, lab_up_c.Text, lab_down_c.Text, lab_sc1_pok.Text,lab_sc1_pno.Text);

            mysql_name.FROM = "5/17game";
            mysql_name.DATE_YMD = mysql_name.TIME = DateTime.Now;

            //dataGridView1.Rows[dataGridView1.Rows.Count-2].Cells[4]

            mysql_name.COLUMN[1] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[2].Value);
            mysql_name.COLUMN[2] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[3].Value);
            mysql_name.COLUMN[3] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[4].Value);
            mysql_name.COLUMN[4] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[5].Value);
            mysql_name.COLUMN[5] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[6].Value);
            mysql_name.COLUMN[6] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[7].Value);
            mysql_name.COLUMN[7] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[8].Value);
            mysql_name.COLUMN[8] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[9].Value);
            mysql_name.COLUMN[9] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[0].Value);
            mysql_name.COLUMN[10] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[1].Value);
            mysql_name.COLUMN[11] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[2].Value);
            mysql_name.COLUMN[12] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[3].Value);
            mysql_name.COLUMN[13] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[4].Value);
            mysql_name.COLUMN[14] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[5].Value);
            mysql_name.COLUMN[15] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[6].Value);
            mysql_name.COLUMN[16] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[7].Value);
            mysql_name.COLUMN[17] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[8].Value);
            mysql_name.COLUMN[18] = Convert.ToString(dataGridView2.Rows[dataGridView2.Rows.Count - 2].Cells[9].Value);


            mysql_function.MYSQL_ADD(mysql_name, 18);




        }
        

        private void timer2_Tick(object sender, EventArgs e)
        {

            js_date = "\"date\":\"" + DateTime.Now.ToShortDateString();
            js_time = "\",\"time\":\"" + DateTime.Now.ToShortTimeString();
            js_m1_rgion = "\",\"m1_rgion\":\"" + lab_m1_region.Text;
            js_m1_work = "\",\"m1_work\":\"" + lab_m1_work.Text;
            js_m1_user = "\",\"m1_user\":\"" + lab_m1_user.Text;
            js_m1_staus = "\",\"m1_status\":\"" + lab_m1_status.Text;
            js_st1 = "\",\"st1\":\"" + lab_st1.Text;
            js_sa1 = "\",\"sa1\":\"" + lab_sa1.Text;
            js_ss1 = "\",\"ss1\":\"" + lab_ss1.Text;
            js_sc1_sok = "\",\"sc1_sok\":\"" + lab_sc1_sok.Text;
            js_sc1_pok = "\",\"sc1_pok\":\"" + lab_sc1_pok.Text;
            js_sc1_sno = "\",\"sc1_sno\":\"" + lab_sc1_sno.Text;
            js_sc1_pno = "\",\"sc1_pno\":\"" + lab_sc1_pno.Text;
            js_trun = "\",\"sp1_trun\":\"" + lab_trun.Text;
            js_up = "\",\"sp1_up\":\"" + lab_up.Text;
            js_down = "\",\"sp1_down\":\"" + lab_down.Text;
            js_motor = "\",\"sp1_motor\":\"" + lab_motor.Text;
            js_trun_c = "\",\"sp1_trun_c\":\"" + lab_trun_c.Text;
            js_up_c = "\",\"sp1_up_c\":\"" + lab_up_c.Text;
            js_down_c = "\",\"sp1_down_c\":\"" + lab_down_c.Text;

            all_sensor = "{" + js_date + js_time + js_m1_rgion + js_m1_work + js_m1_user + js_m1_staus +
                            js_st1 + js_sa1 + js_ss1 + js_sc1_sok + js_sc1_pok + js_sc1_sno + js_sc1_pno +
                            js_trun + js_up + js_down + js_motor + js_trun_c + js_up_c + js_down_c + "\"}";

            /*"{"+ js_date + js_time + js_m1_rgion+ js_m1_work+ js_m1_staus+ 
                            js_st1+ js_sa1 + js_ss1+ js_sc1_sok + js_sc1_pok+ js_sc1_sno+ js_sc1_pno+
                            js_trun+ js_up+ js_down+ js_motor+ js_trun_c+ js_up_c+js_down_c+"\"}";*/


            //設定完整的發佈路徑
            string Topic = "machine1";

            //發佈主題、內容及設定傳送品質 QoS 0 ( 0, 1, 2 )
            client.Publish(Topic, Encoding.UTF8.GetBytes(all_sensor), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, true);
           // button4.Text = "hello";
            label8.Text = all_sensor;





            // dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[0].Value

        }

        private void button4_Click(object sender, EventArgs e)
        {
            

            
        }

        private void label15_Click(object sender, EventArgs e)
        {

        }

        public void Form2_Load(object sender, EventArgs e)
        {
            
            mysql_function.MYSQL_Init(ref mysql_name, 22,"127.0.0.1","root","123456","factory");

            
            client = new MqttClient("liantw.com");//MQTTServer在本機
           // client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;//當接收到訊息時處理函式
            clientId = Guid.NewGuid().ToString();//取得唯一碼
            client.Connect(clientId);//建立連線
            

        }
        
    }
}
