namespace Win_Info_Status
{
    partial class FrmMDI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.開啟ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.排列ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cNC資訊與狀態ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cNC座標資訊ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.串聯排列ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.水平排列ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.垂直並排ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.開啟ToolStripMenuItem,
            this.排列ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.MdiWindowListItem = this.開啟ToolStripMenuItem;
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(503, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 開啟ToolStripMenuItem
            // 
            this.開啟ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cNC資訊與狀態ToolStripMenuItem,
            this.cNC座標資訊ToolStripMenuItem});
            this.開啟ToolStripMenuItem.Name = "開啟ToolStripMenuItem";
            this.開啟ToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.開啟ToolStripMenuItem.Text = "開啟";
            // 
            // 排列ToolStripMenuItem
            // 
            this.排列ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.串聯排列ToolStripMenuItem,
            this.水平排列ToolStripMenuItem,
            this.垂直並排ToolStripMenuItem});
            this.排列ToolStripMenuItem.Name = "排列ToolStripMenuItem";
            this.排列ToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.排列ToolStripMenuItem.Text = "排列";
            // 
            // cNC資訊與狀態ToolStripMenuItem
            // 
            this.cNC資訊與狀態ToolStripMenuItem.Name = "cNC資訊與狀態ToolStripMenuItem";
            this.cNC資訊與狀態ToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.cNC資訊與狀態ToolStripMenuItem.Text = "CNC資訊與狀態";
            this.cNC資訊與狀態ToolStripMenuItem.Click += new System.EventHandler(this.cNC資訊與狀態ToolStripMenuItem_Click);
            // 
            // cNC座標資訊ToolStripMenuItem
            // 
            this.cNC座標資訊ToolStripMenuItem.Name = "cNC座標資訊ToolStripMenuItem";
            this.cNC座標資訊ToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.cNC座標資訊ToolStripMenuItem.Text = "CNC座標資訊";
            this.cNC座標資訊ToolStripMenuItem.Click += new System.EventHandler(this.cNC座標資訊ToolStripMenuItem_Click);
            // 
            // 串聯排列ToolStripMenuItem
            // 
            this.串聯排列ToolStripMenuItem.Name = "串聯排列ToolStripMenuItem";
            this.串聯排列ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.串聯排列ToolStripMenuItem.Text = "串聯排列";
            this.串聯排列ToolStripMenuItem.Click += new System.EventHandler(this.串聯排列ToolStripMenuItem_Click);
            // 
            // 水平排列ToolStripMenuItem
            // 
            this.水平排列ToolStripMenuItem.Name = "水平排列ToolStripMenuItem";
            this.水平排列ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.水平排列ToolStripMenuItem.Text = "水平排列";
            this.水平排列ToolStripMenuItem.Click += new System.EventHandler(this.水平排列ToolStripMenuItem_Click);
            // 
            // 垂直並排ToolStripMenuItem
            // 
            this.垂直並排ToolStripMenuItem.Name = "垂直並排ToolStripMenuItem";
            this.垂直並排ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.垂直並排ToolStripMenuItem.Text = "垂直並排";
            this.垂直並排ToolStripMenuItem.Click += new System.EventHandler(this.垂直並排ToolStripMenuItem_Click);
            // 
            // FrmMDI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(503, 415);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FrmMDI";
            this.Text = "FrmMDI";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.FrmMDI_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 開啟ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cNC資訊與狀態ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cNC座標資訊ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 排列ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 串聯排列ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 水平排列ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 垂直並排ToolStripMenuItem;
    }
}