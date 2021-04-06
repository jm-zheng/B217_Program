using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;
using InterfaceLib;

namespace Win_Info_Status
{
    public partial class FrmInfoStatus : Form
    {
        public FrmInfoStatus()
        {
            InitializeComponent();
        }

        InterfaceLib.IMsg iRemoting = null;
        StructMsg.SkyVersion _SkyVersion;
        StructMsg.SkyConn_ip_port _SkyConn_ip_port;
        StructMsg.information _information;
        StructMsg.SkyNc_filename _SkyNc_filename;
        StructMsg.status _status;
        StructMsg.position _position;
        StructMsg.spindle_speed _spindle_speed;


        StructMsg.Pwd _Pwd;
        
        short ret = 0;
        
        private void Form1_Load(object sender, EventArgs e)
        {
            if (ChannelServices.RegisteredChannels.Length == 0)
            {
                ChannelServices.RegisterChannel(new TcpChannel());

                iRemoting = (IMsg)Activator.GetObject(typeof(IMsg), "tcp://localhost:9501/RemoteObjectURI9501");
            }
            
            _Pwd.ConnectionKey = "123";
            MS100.Enabled = true;
            S1.Enabled = true;

            //廠牌及機台名稱
            ret = iRemoting.SKY_conn_ip_port(_Pwd, ref _SkyConn_ip_port);
            if (ret == 0)
            {
                txtMan_F.Text = _SkyConn_ip_port.Manufacturer[0];
                txtName_F.Text = _SkyConn_ip_port.MachineName[0];
            }

            //基本資訊
            ret = iRemoting.GET_information(_Pwd, ref _information);
            if (ret == 0)
            {
                txtAxes_F.Text = _information.Axes.ToString();
                txtType_F.Text = _information.CncType;
                txtSeries_F.Text = _information.Series;
                txtNc_F.Text = _information.Nc_Ver;
            }

            //Key序號
            ret = iRemoting.SKY_version(_Pwd, ref _SkyVersion);
            if (ret == 0)
            {
                txtLic.Text = _SkyVersion.SerialNumber.ToString();
            }
        }

        private void S1_Tick(object sender, EventArgs e)
        {
            //主程
            _SkyNc_filename.RetType = -1;
            ret = iRemoting.SKY_nc_filename(_Pwd, ref _SkyNc_filename);
            if (ret == 0)
            {
                txtProg_F.Text = _SkyNc_filename.MainProg[0];
            }

            //狀態及模式
            ret = iRemoting.GET_status(_Pwd, ref _status);
            if (ret == 0)
            {
                txtStatus_F.Text = _status.Status;
                txtMode_F.Text = _status.Mode;
            }

            ret = iRemoting.GET_spindle_speed(_Pwd, ref _spindle_speed);
            if (ret == 0)
            {
                label17.Text = _spindle_speed.SpSpeed.ToString();
            }

        }

        private void MS100_Tick(object sender, EventArgs e)
        {
            ret = iRemoting.GET_position(_Pwd, ref _position);
            if (ret == 0)
            {
                txtMachX_F.Text = _position.Mach[0].ToString();
                txtMachY_F.Text = _position.Mach[1].ToString();
                txtMachZ_F.Text = _position.Mach[2].ToString();

                txtAbsX_F.Text = _position.Abs[0].ToString();
                txtAbsY_F.Text = _position.Abs[1].ToString();
                txtAbsZ_F.Text = _position.Abs[2].ToString();
            }
        }
    }
}
