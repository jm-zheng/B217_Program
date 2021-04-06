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
        public Form4()
        {
            InitializeComponent();
            label19.Text = "10";
            label18.Text = "200";
            label17.Text = "32.5";
            label16.Text = "08:27";
            label31.Text = "B217";
            label32.Text = "23號螺桿";
            label33.Text = "鄭錦明";
        }

        private void Form4_Load(object sender, EventArgs e)
        {
            if (ChannelServices.RegisteredChannels.Length == 0)
            {
                ChannelServices.RegisterChannel(new TcpChannel());

                iRemoting = (IMsg)Activator.GetObject(typeof(IMsg), "tcp://localhost:9501/RemoteObjectURI9501");
            }

            _Pwd.ConnectionKey = "123";
            MS_100.Enabled = true;
            S_1.Enabled = true;
        }

        private void MS_100_Tick(object sender, EventArgs e)
        {
            ret = iRemoting.GET_position(_Pwd, ref _position);
            if (ret == 0)
            {
                label9.Text = _position.Mach[0].ToString();
                label8.Text = _position.Mach[1].ToString();
                label7.Text = _position.Mach[2].ToString();

              
            }

        }

        private void S_1_Tick(object sender, EventArgs e)
        {
            //狀態及模式
            ret = iRemoting.GET_status(_Pwd, ref _status);
            if (ret == 0)
            {
                label10.Text = _status.Mode;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form1 f = new Form1();
            f.Visible = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
