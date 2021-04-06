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
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;

using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;





namespace PLC自動化機台遠端監控
{
    public partial class Form4 : Form
    {
        short ret = 0;
        IMsg iRemoting = null;
        StructMsg.Pwd _Pwd;
        StructMsg.status _status;
        StructMsg.position _position;
        StructMsg.Utilization_Today _Util_Today;
        StructMsg.Utilization _Util;
        StructMsg.time _time;

        //-------------------------------------
        delegate void SetTextCallback(string text);//用來更新UIText 的Callback
        MqttClient client;//MqttClient
        string clientId;//連線時所用的ClientID

        string m3_sensor;
        string js_date, js_time, js_m3_rgion, js_m3_work, js_m3_user, js_m3_staus,
               js_m3_open, js_m3_mode, js_m3_m_x, js_m3_m_y, js_m3_m_z;

        private void button2_Click_1(object sender, EventArgs e)
        {
            lab_m3_region.Text = "a區域";
            lab_m3_status.Text = "123";
            lab_m3_work.Text = "3號工件";
            lab_m3_user.Text = "鄭錦明";
            lab_m3_mode.Text = "3";
            lab_m3_m_x.Text = "258";
            lab_m3_m_y.Text = "354";
            lab_m3_m_z.Text = "489";
            lab_m3_open.Text = "開機";

        }

        private void m3_status_timer_Tick(object sender, EventArgs e)
        {
            ret = iRemoting.GET_position(_Pwd, ref _position);
            if (ret == 0)
            {
                lab_m3_m_x.Text = _position.Mach[0].ToString();
                lab_m3_m_y.Text = _position.Mach[1].ToString();
                lab_m3_m_z.Text = _position.Mach[2].ToString();


            }
            ret = iRemoting.GET_status(_Pwd, ref _status);
            if (ret == 0)
            {
                lab_m3_status.Text = _status.Status;
                lab_m3_mode.Text = _status.Mode;
            }
            short asd = iRemoting.GET_time(_Pwd, ref _time);
            if (asd == 0)
            {
                lab_m3_open.Text = _time.Power[0].ToString() + " : " +
               _time.Power[1].ToString() + " : " + _time.Power[2].ToString();

            }
        }

        public Form4()
        {
            InitializeComponent();
            
            
          
        }

        private void Form4_Load(object sender, EventArgs e)
        {
            if (ChannelServices.RegisteredChannels.Length == 0)
            {
                ChannelServices.RegisterChannel(new TcpChannel());

                iRemoting = (IMsg)Activator.GetObject(typeof(IMsg), "tcp://localhost:9501/RemoteObjectURI9501");
            }

            _Pwd.ConnectionKey = "123";
           //  m3_status_timer.Enabled = true;
           // m3_mqtt_timer.Enabled = true;

            //--------------------------------------------------------
            client = new MqttClient("liantw.com");//MQTTServer在本機
            //client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;//當接收到訊息時處理函式
            clientId = Guid.NewGuid().ToString();//取得唯一碼
            client.Connect(clientId);//建立連線

        }

       


        private void button2_Click(object sender, EventArgs e)
        {
            
           
           
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            m3_mqtt_timer.Start();

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

       

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void m3_mqtt_timer_Tick(object sender, EventArgs e)
        {
            dataGridView1.Rows.Add(DateTime.Now.ToShortDateString(), DateTime.Now.ToShortTimeString(), lab_m3_region.Text, lab_m3_work.Text, lab_m3_user.Text, lab_m3_status.Text);
            dataGridView2.Rows.Add(lab_m3_open.Text, lab_m3_mode.Text, lab_m3_m_x.Text, lab_m3_m_y.Text, lab_m3_m_z.Text);

            string Topic = "machine3";
            js_date = "\"date\":\"" + DateTime.Now.ToShortDateString();
            js_time = "\",\"time\":\"" + DateTime.Now.ToShortTimeString();
            js_m3_rgion = "\",\"m3_rgion\":\"" + lab_m3_region.Text;
            js_m3_work = "\",\"m3_work\":\"" + lab_m3_work.Text;
            js_m3_user = "\",\"m3_user\":\"" + lab_m3_user.Text;
            js_m3_staus = "\",\"m3_status\":\"" + lab_m3_status.Text;
            js_m3_open = "\",\"m3_open\":\"" + lab_m3_open.Text;
            js_m3_mode = "\",\"m3_mode\":\"" + lab_m3_mode.Text;
            js_m3_m_x = "\",\"m3_m_x\":\"" + lab_m3_m_x.Text;
            js_m3_m_y = "\",\"m3_m_y\":\"" + lab_m3_m_y.Text;
            js_m3_m_z = "\",\"m3_m_z\":\"" + lab_m3_m_z.Text;
            //發佈主題、內容及設定傳送品質 QoS 0 ( 0, 1, 2 )

            m3_sensor = "{" + js_date + js_time + js_m3_rgion + js_m3_work + js_m3_user + js_m3_staus +
               js_m3_open + js_m3_mode + js_m3_m_x + js_m3_m_y + js_m3_m_z + "\"}";

            client.Publish(Topic, Encoding.UTF8.GetBytes(m3_sensor), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, true);
        }

  
    }
}
