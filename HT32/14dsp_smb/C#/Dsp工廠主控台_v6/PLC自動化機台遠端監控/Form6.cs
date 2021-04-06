using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

using MySql;


namespace PLC自動化機台遠端監控
{
    public partial class Form6 : Form
    {
        string e_sensor;
        string js_date, js_time, js_et, js_eh, js_ec, js_ef,
              js_ev, js_el;

        delegate void SetTextCallback(string text);//用來更新UIText 的Callback

        private void button1_Click(object sender, EventArgs e)
        {
           
        }

        MqttClient client;//MqttClient
        string clientId;//連線時所用的ClientID

        SQLTypedef mysql_e = new SQLTypedef();

        public Form6()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form6_Load(object sender, EventArgs e)
        {
            timer1.Start();
            mysql_function.MYSQL_Init(ref mysql_e, 22, "127.0.0.1", "root", "123456", "factory");

            client = new MqttClient("liantw.com");//MQTTServer在本機
                                                  // client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;//當接收到訊息時處理函式
            clientId = Guid.NewGuid().ToString();//取得唯一碼
            client.Connect(clientId);//建立連線
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
           dataGridView1.Rows.Add(DateTime.Now.ToShortDateString(), DateTime.Now.ToShortTimeString(),lab_et.Text,lab_eh.Text,lab_ec.Text,lab_ef.Text,lab_ev.Text,lab_el.Text);
            mysql_e.FROM = "setting";
            mysql_e.DATE_YMD = mysql_e.TIME = DateTime.Now;
            mysql_e.COLUMN[1] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[2].Value);
            mysql_e.COLUMN[2] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[3].Value);
            mysql_e.COLUMN[3] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[4].Value);
            mysql_e.COLUMN[4] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[5].Value);
            mysql_e.COLUMN[5] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[6].Value);
            mysql_e.COLUMN[6] = Convert.ToString(dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[7].Value);

            mysql_function.MYSQL_ADD(mysql_e, 6);

            js_date = "\"date\":\"" + DateTime.Now.ToShortDateString();
            js_time = "\",\"time\":\"" + DateTime.Now.ToShortTimeString();
            js_et = "\",\"et\":\"" + lab_et.Text;
            js_eh = "\",\"eh\":\"" + lab_eh.Text;
            js_ec = "\",\"ec\":\"" + lab_ec.Text;
            js_ef = "\",\"ef\":\"" + lab_ef.Text;
            js_ev = "\",\"ev\":\"" + lab_ev.Text;
            js_el = "\",\"el\":\"" + lab_el.Text;

            e_sensor = "{" + js_date + js_time + js_et + js_eh + js_ec + js_ef + js_ev + js_el + "\"}";

            //設定完整的發佈路徑
            string Topic = "milieu";

            //發佈主題、內容及設定傳送品質 QoS 0 ( 0, 1, 2 )
            client.Publish(Topic, Encoding.UTF8.GetBytes(e_sensor), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, true);

        }
    }
}
