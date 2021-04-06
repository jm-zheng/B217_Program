using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Win_Info_Status
{
    public partial class FrmMDI : Form
    {
        public FrmMDI()
        {
            InitializeComponent();
        }

        private void FrmMDI_Load(object sender, EventArgs e)
        {

        }

        private void cNC資訊與狀態ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FrmInfoStatus frm = new FrmInfoStatus();
            frm.MdiParent = this;
            frm.Show();
        }

        private void cNC座標資訊ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 串聯排列ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.Cascade);
        }

        private void 水平排列ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void 垂直並排ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileVertical);
        }
    }
}
