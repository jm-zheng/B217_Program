<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form4
    Inherits System.Windows.Forms.Form

    'Form 覆寫 Dispose 以清除元件清單。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    '為 Windows Form 設計工具的必要項
    Private components As System.ComponentModel.IContainer

    '注意: 以下為 Windows Form 設計工具所需的程序
    '可以使用 Windows Form 設計工具進行修改。
    '請勿使用程式碼編輯器進行修改。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.DataGridView1 = New System.Windows.Forms.DataGridView()
        Me.Column8 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column9 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column1 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column2 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column3 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column4 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column5 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column6 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column16 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column17 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column7 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Timer2 = New System.Windows.Forms.Timer(Me.components)
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Column15 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column14 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column13 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column12 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column11 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Column10 = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.DataGridView2 = New System.Windows.Forms.DataGridView()
        Me.Label67 = New System.Windows.Forms.Label()
        Me.TextBox3 = New System.Windows.Forms.TextBox()
        Me.GroupBox13 = New System.Windows.Forms.GroupBox()
        Me.manager3 = New System.Windows.Forms.Label()
        Me.Label46 = New System.Windows.Forms.Label()
        Me.status3 = New System.Windows.Forms.Label()
        Me.number3 = New System.Windows.Forms.Label()
        Me.Label55 = New System.Windows.Forms.Label()
        Me.Label57 = New System.Windows.Forms.Label()
        Me.Label58 = New System.Windows.Forms.Label()
        Me.nama3 = New System.Windows.Forms.Label()
        Me.Button8 = New System.Windows.Forms.Button()
        Me.GroupBox14 = New System.Windows.Forms.GroupBox()
        Me.ST3 = New System.Windows.Forms.Label()
        Me.Label72 = New System.Windows.Forms.Label()
        Me.SC3 = New System.Windows.Forms.Label()
        Me.Label49 = New System.Windows.Forms.Label()
        Me.SA3 = New System.Windows.Forms.Label()
        Me.Label51 = New System.Windows.Forms.Label()
        Me.Label53 = New System.Windows.Forms.Label()
        Me.SS3 = New System.Windows.Forms.Label()
        Me.GroupBox15 = New System.Windows.Forms.GroupBox()
        Me.down3 = New System.Windows.Forms.Label()
        Me.Label78 = New System.Windows.Forms.Label()
        Me.motor3 = New System.Windows.Forms.Label()
        Me.up3 = New System.Windows.Forms.Label()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.Label40 = New System.Windows.Forms.Label()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.turn = New System.Windows.Forms.Label()
        Me.PictureBox3 = New System.Windows.Forms.PictureBox()
        Me.GroupBox6 = New System.Windows.Forms.GroupBox()
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.DataGridView2, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox13.SuspendLayout()
        Me.GroupBox14.SuspendLayout()
        Me.GroupBox15.SuspendLayout()
        CType(Me.PictureBox3, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox6.SuspendLayout()
        Me.SuspendLayout()
        '
        'DataGridView1
        '
        Me.DataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.DataGridView1.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.Column8, Me.Column9, Me.Column1, Me.Column2, Me.Column3, Me.Column4, Me.Column5, Me.Column6, Me.Column16, Me.Column17, Me.Column7})
        Me.DataGridView1.Location = New System.Drawing.Point(442, 215)
        Me.DataGridView1.Name = "DataGridView1"
        Me.DataGridView1.RowTemplate.Height = 24
        Me.DataGridView1.Size = New System.Drawing.Size(1134, 369)
        Me.DataGridView1.TabIndex = 14
        '
        'Column8
        '
        Me.Column8.HeaderText = "日期"
        Me.Column8.Name = "Column8"
        '
        'Column9
        '
        Me.Column9.HeaderText = "時間"
        Me.Column9.Name = "Column9"
        '
        'Column1
        '
        Me.Column1.HeaderText = "區域顯示"
        Me.Column1.Name = "Column1"
        '
        'Column2
        '
        Me.Column2.HeaderText = "機台名稱"
        Me.Column2.Name = "Column2"
        '
        'Column3
        '
        Me.Column3.HeaderText = "管理者"
        Me.Column3.Name = "Column3"
        '
        'Column4
        '
        Me.Column4.HeaderText = "震動指數"
        Me.Column4.Name = "Column4"
        '
        'Column5
        '
        Me.Column5.HeaderText = "物件數量"
        Me.Column5.Name = "Column5"
        '
        'Column6
        '
        Me.Column6.HeaderText = "機台溫度"
        Me.Column6.Name = "Column6"
        '
        'Column16
        '
        Me.Column16.HeaderText = "機台電流"
        Me.Column16.Name = "Column16"
        '
        'Column17
        '
        Me.Column17.HeaderText = "輸送帶馬達"
        Me.Column17.Name = "Column17"
        '
        'Column7
        '
        Me.Column7.HeaderText = "狀態顯示"
        Me.Column7.Name = "Column7"
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        '
        'Timer2
        '
        '
        'Button1
        '
        Me.Button1.Font = New System.Drawing.Font("新細明體", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(136, Byte))
        Me.Button1.Location = New System.Drawing.Point(21, 394)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 37)
        Me.Button1.TabIndex = 15
        Me.Button1.Text = "首頁"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Column15
        '
        Me.Column15.HeaderText = "光照度"
        Me.Column15.Name = "Column15"
        '
        'Column14
        '
        Me.Column14.HeaderText = "TVOC"
        Me.Column14.Name = "Column14"
        '
        'Column13
        '
        Me.Column13.HeaderText = "甲醛"
        Me.Column13.Name = "Column13"
        '
        'Column12
        '
        Me.Column12.HeaderText = "CO2"
        Me.Column12.Name = "Column12"
        '
        'Column11
        '
        Me.Column11.HeaderText = "濕度"
        Me.Column11.Name = "Column11"
        '
        'Column10
        '
        Me.Column10.HeaderText = "溫度"
        Me.Column10.Name = "Column10"
        '
        'DataGridView2
        '
        Me.DataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.DataGridView2.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.Column10, Me.Column11, Me.Column12, Me.Column13, Me.Column14, Me.Column15})
        Me.DataGridView2.Location = New System.Drawing.Point(442, 22)
        Me.DataGridView2.Name = "DataGridView2"
        Me.DataGridView2.RowTemplate.Height = 24
        Me.DataGridView2.Size = New System.Drawing.Size(639, 187)
        Me.DataGridView2.TabIndex = 13
        '
        'Label67
        '
        Me.Label67.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(128, Byte), Integer))
        Me.Label67.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label67.Location = New System.Drawing.Point(7, 23)
        Me.Label67.Name = "Label67"
        Me.Label67.Size = New System.Drawing.Size(88, 23)
        Me.Label67.TabIndex = 5
        Me.Label67.Text = "工單件數"
        '
        'TextBox3
        '
        Me.TextBox3.Location = New System.Drawing.Point(101, 17)
        Me.TextBox3.Name = "TextBox3"
        Me.TextBox3.Size = New System.Drawing.Size(100, 27)
        Me.TextBox3.TabIndex = 6
        '
        'GroupBox13
        '
        Me.GroupBox13.Controls.Add(Me.nama3)
        Me.GroupBox13.Controls.Add(Me.Label58)
        Me.GroupBox13.Controls.Add(Me.Label57)
        Me.GroupBox13.Controls.Add(Me.Label55)
        Me.GroupBox13.Controls.Add(Me.number3)
        Me.GroupBox13.Controls.Add(Me.status3)
        Me.GroupBox13.Controls.Add(Me.Label46)
        Me.GroupBox13.Controls.Add(Me.manager3)
        Me.GroupBox13.Location = New System.Drawing.Point(217, 49)
        Me.GroupBox13.Name = "GroupBox13"
        Me.GroupBox13.Size = New System.Drawing.Size(190, 150)
        Me.GroupBox13.TabIndex = 7
        Me.GroupBox13.TabStop = False
        Me.GroupBox13.Text = "機台履歷"
        '
        'manager3
        '
        Me.manager3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.manager3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.manager3.Location = New System.Drawing.Point(102, 83)
        Me.manager3.Name = "manager3"
        Me.manager3.Size = New System.Drawing.Size(81, 23)
        Me.manager3.TabIndex = 1
        '
        'Label46
        '
        Me.Label46.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label46.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label46.Location = New System.Drawing.Point(16, 111)
        Me.Label46.Name = "Label46"
        Me.Label46.Size = New System.Drawing.Size(80, 23)
        Me.Label46.TabIndex = 1
        Me.Label46.Text = "狀態顯示"
        '
        'status3
        '
        Me.status3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.status3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.status3.Location = New System.Drawing.Point(102, 113)
        Me.status3.Name = "status3"
        Me.status3.Size = New System.Drawing.Size(81, 23)
        Me.status3.TabIndex = 1
        Me.status3.Text = "待機狀態"
        '
        'number3
        '
        Me.number3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.number3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.number3.Location = New System.Drawing.Point(102, 54)
        Me.number3.Name = "number3"
        Me.number3.Size = New System.Drawing.Size(81, 23)
        Me.number3.TabIndex = 1
        '
        'Label55
        '
        Me.Label55.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label55.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label55.Location = New System.Drawing.Point(16, 83)
        Me.Label55.Name = "Label55"
        Me.Label55.Size = New System.Drawing.Size(80, 23)
        Me.Label55.TabIndex = 1
        Me.Label55.Text = "管理者"
        '
        'Label57
        '
        Me.Label57.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label57.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label57.Location = New System.Drawing.Point(16, 54)
        Me.Label57.Name = "Label57"
        Me.Label57.Size = New System.Drawing.Size(80, 23)
        Me.Label57.TabIndex = 1
        Me.Label57.Text = "機台名稱"
        '
        'Label58
        '
        Me.Label58.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label58.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label58.Location = New System.Drawing.Point(16, 23)
        Me.Label58.Name = "Label58"
        Me.Label58.Size = New System.Drawing.Size(80, 23)
        Me.Label58.TabIndex = 1
        Me.Label58.Text = "區域顯示"
        '
        'nama3
        '
        Me.nama3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.nama3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.nama3.Location = New System.Drawing.Point(102, 23)
        Me.nama3.Name = "nama3"
        Me.nama3.Size = New System.Drawing.Size(81, 23)
        Me.nama3.TabIndex = 1
        '
        'Button8
        '
        Me.Button8.Location = New System.Drawing.Point(314, 17)
        Me.Button8.Name = "Button8"
        Me.Button8.Size = New System.Drawing.Size(92, 29)
        Me.Button8.TabIndex = 8
        Me.Button8.Text = "紀錄資料"
        Me.Button8.UseVisualStyleBackColor = True
        '
        'GroupBox14
        '
        Me.GroupBox14.Controls.Add(Me.SS3)
        Me.GroupBox14.Controls.Add(Me.Label53)
        Me.GroupBox14.Controls.Add(Me.Label51)
        Me.GroupBox14.Controls.Add(Me.SA3)
        Me.GroupBox14.Controls.Add(Me.Label49)
        Me.GroupBox14.Controls.Add(Me.SC3)
        Me.GroupBox14.Controls.Add(Me.Label72)
        Me.GroupBox14.Controls.Add(Me.ST3)
        Me.GroupBox14.Location = New System.Drawing.Point(7, 208)
        Me.GroupBox14.Name = "GroupBox14"
        Me.GroupBox14.Size = New System.Drawing.Size(200, 150)
        Me.GroupBox14.TabIndex = 9
        Me.GroupBox14.TabStop = False
        Me.GroupBox14.Text = "感測狀態"
        '
        'ST3
        '
        Me.ST3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.ST3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.ST3.Location = New System.Drawing.Point(98, 88)
        Me.ST3.Name = "ST3"
        Me.ST3.Size = New System.Drawing.Size(96, 23)
        Me.ST3.TabIndex = 1
        '
        'Label72
        '
        Me.Label72.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label72.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label72.Location = New System.Drawing.Point(12, 120)
        Me.Label72.Name = "Label72"
        Me.Label72.Size = New System.Drawing.Size(80, 23)
        Me.Label72.TabIndex = 1
        Me.Label72.Text = "機台電流"
        '
        'SC3
        '
        Me.SC3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.SC3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.SC3.Location = New System.Drawing.Point(98, 55)
        Me.SC3.Name = "SC3"
        Me.SC3.Size = New System.Drawing.Size(96, 23)
        Me.SC3.TabIndex = 1
        '
        'Label49
        '
        Me.Label49.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label49.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label49.Location = New System.Drawing.Point(12, 88)
        Me.Label49.Name = "Label49"
        Me.Label49.Size = New System.Drawing.Size(80, 23)
        Me.Label49.TabIndex = 1
        Me.Label49.Text = "機台溫度"
        '
        'SA3
        '
        Me.SA3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.SA3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.SA3.Location = New System.Drawing.Point(98, 120)
        Me.SA3.Name = "SA3"
        Me.SA3.Size = New System.Drawing.Size(96, 23)
        Me.SA3.TabIndex = 1
        '
        'Label51
        '
        Me.Label51.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label51.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label51.Location = New System.Drawing.Point(12, 55)
        Me.Label51.Name = "Label51"
        Me.Label51.Size = New System.Drawing.Size(80, 23)
        Me.Label51.TabIndex = 1
        Me.Label51.Text = "物件數量"
        '
        'Label53
        '
        Me.Label53.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label53.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label53.Location = New System.Drawing.Point(12, 23)
        Me.Label53.Name = "Label53"
        Me.Label53.Size = New System.Drawing.Size(80, 23)
        Me.Label53.TabIndex = 1
        Me.Label53.Text = "震動指數"
        '
        'SS3
        '
        Me.SS3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.SS3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.SS3.Location = New System.Drawing.Point(98, 23)
        Me.SS3.Name = "SS3"
        Me.SS3.Size = New System.Drawing.Size(96, 23)
        Me.SS3.TabIndex = 1
        '
        'GroupBox15
        '
        Me.GroupBox15.Controls.Add(Me.turn)
        Me.GroupBox15.Controls.Add(Me.Label12)
        Me.GroupBox15.Controls.Add(Me.Label40)
        Me.GroupBox15.Controls.Add(Me.Label13)
        Me.GroupBox15.Controls.Add(Me.up3)
        Me.GroupBox15.Controls.Add(Me.motor3)
        Me.GroupBox15.Controls.Add(Me.Label78)
        Me.GroupBox15.Controls.Add(Me.down3)
        Me.GroupBox15.Location = New System.Drawing.Point(213, 208)
        Me.GroupBox15.Name = "GroupBox15"
        Me.GroupBox15.Size = New System.Drawing.Size(201, 150)
        Me.GroupBox15.TabIndex = 10
        Me.GroupBox15.TabStop = False
        Me.GroupBox15.Text = "機台狀況"
        '
        'down3
        '
        Me.down3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.down3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.down3.Location = New System.Drawing.Point(113, 84)
        Me.down3.Name = "down3"
        Me.down3.Size = New System.Drawing.Size(77, 23)
        Me.down3.TabIndex = 5
        '
        'Label78
        '
        Me.Label78.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label78.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label78.Location = New System.Drawing.Point(9, 117)
        Me.Label78.Name = "Label78"
        Me.Label78.Size = New System.Drawing.Size(98, 23)
        Me.Label78.TabIndex = 1
        Me.Label78.Text = "輸送帶馬達"
        '
        'motor3
        '
        Me.motor3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.motor3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.motor3.Location = New System.Drawing.Point(113, 115)
        Me.motor3.Name = "motor3"
        Me.motor3.Size = New System.Drawing.Size(77, 23)
        Me.motor3.TabIndex = 1
        '
        'up3
        '
        Me.up3.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.up3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.up3.Location = New System.Drawing.Point(113, 53)
        Me.up3.Name = "up3"
        Me.up3.Size = New System.Drawing.Size(77, 23)
        Me.up3.TabIndex = 5
        '
        'Label13
        '
        Me.Label13.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label13.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label13.Location = New System.Drawing.Point(9, 23)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(98, 23)
        Me.Label13.TabIndex = 4
        Me.Label13.Text = "直進旋轉"
        '
        'Label40
        '
        Me.Label40.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label40.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label40.Location = New System.Drawing.Point(9, 84)
        Me.Label40.Name = "Label40"
        Me.Label40.Size = New System.Drawing.Size(98, 23)
        Me.Label40.TabIndex = 6
        Me.Label40.Text = "品檢下降"
        '
        'Label12
        '
        Me.Label12.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.Label12.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label12.Location = New System.Drawing.Point(9, 53)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(98, 23)
        Me.Label12.TabIndex = 6
        Me.Label12.Text = "品檢上升"
        '
        'turn
        '
        Me.turn.BackColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.turn.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.turn.Location = New System.Drawing.Point(113, 23)
        Me.turn.Name = "turn"
        Me.turn.Size = New System.Drawing.Size(77, 23)
        Me.turn.TabIndex = 3
        '
        'PictureBox3
        '
        Me.PictureBox3.ErrorImage = Global.WindowsApp2.My.Resources.Resources.list_11939741650
        Me.PictureBox3.Image = Global.WindowsApp2.My.Resources.Resources.list_11939741650
        Me.PictureBox3.Location = New System.Drawing.Point(8, 57)
        Me.PictureBox3.Name = "PictureBox3"
        Me.PictureBox3.Size = New System.Drawing.Size(203, 145)
        Me.PictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox3.TabIndex = 11
        Me.PictureBox3.TabStop = False
        '
        'GroupBox6
        '
        Me.GroupBox6.BackColor = System.Drawing.Color.Yellow
        Me.GroupBox6.Controls.Add(Me.PictureBox3)
        Me.GroupBox6.Controls.Add(Me.GroupBox15)
        Me.GroupBox6.Controls.Add(Me.GroupBox14)
        Me.GroupBox6.Controls.Add(Me.Button8)
        Me.GroupBox6.Controls.Add(Me.GroupBox13)
        Me.GroupBox6.Controls.Add(Me.TextBox3)
        Me.GroupBox6.Controls.Add(Me.Label67)
        Me.GroupBox6.Font = New System.Drawing.Font("新細明體", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(136, Byte))
        Me.GroupBox6.Location = New System.Drawing.Point(13, 22)
        Me.GroupBox6.Margin = New System.Windows.Forms.Padding(4)
        Me.GroupBox6.Name = "GroupBox6"
        Me.GroupBox6.Padding = New System.Windows.Forms.Padding(4)
        Me.GroupBox6.Size = New System.Drawing.Size(422, 365)
        Me.GroupBox6.TabIndex = 16
        Me.GroupBox6.TabStop = False
        Me.GroupBox6.Text = "機台3"
        '
        'Form4
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1143, 580)
        Me.Controls.Add(Me.GroupBox6)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.DataGridView1)
        Me.Controls.Add(Me.DataGridView2)
        Me.Name = "Form4"
        Me.Text = "Form4"
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.DataGridView2, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox13.ResumeLayout(False)
        Me.GroupBox14.ResumeLayout(False)
        Me.GroupBox15.ResumeLayout(False)
        CType(Me.PictureBox3, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox6.ResumeLayout(False)
        Me.GroupBox6.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents DataGridView1 As DataGridView
    Friend WithEvents Column8 As DataGridViewTextBoxColumn
    Friend WithEvents Column9 As DataGridViewTextBoxColumn
    Friend WithEvents Column1 As DataGridViewTextBoxColumn
    Friend WithEvents Column2 As DataGridViewTextBoxColumn
    Friend WithEvents Column3 As DataGridViewTextBoxColumn
    Friend WithEvents Column4 As DataGridViewTextBoxColumn
    Friend WithEvents Column5 As DataGridViewTextBoxColumn
    Friend WithEvents Column6 As DataGridViewTextBoxColumn
    Friend WithEvents Column16 As DataGridViewTextBoxColumn
    Friend WithEvents Column17 As DataGridViewTextBoxColumn
    Friend WithEvents Column7 As DataGridViewTextBoxColumn
    Friend WithEvents Timer1 As Timer
    Friend WithEvents Timer2 As Timer
    Friend WithEvents SerialPort1 As IO.Ports.SerialPort
    Friend WithEvents Button1 As Button
    Friend WithEvents Column15 As DataGridViewTextBoxColumn
    Friend WithEvents Column14 As DataGridViewTextBoxColumn
    Friend WithEvents Column13 As DataGridViewTextBoxColumn
    Friend WithEvents Column12 As DataGridViewTextBoxColumn
    Friend WithEvents Column11 As DataGridViewTextBoxColumn
    Friend WithEvents Column10 As DataGridViewTextBoxColumn
    Friend WithEvents DataGridView2 As DataGridView
    Friend WithEvents Label67 As Label
    Friend WithEvents TextBox3 As TextBox
    Friend WithEvents GroupBox13 As GroupBox
    Friend WithEvents nama3 As Label
    Friend WithEvents Label58 As Label
    Friend WithEvents Label57 As Label
    Friend WithEvents Label55 As Label
    Friend WithEvents number3 As Label
    Friend WithEvents status3 As Label
    Friend WithEvents Label46 As Label
    Friend WithEvents manager3 As Label
    Friend WithEvents Button8 As Button
    Friend WithEvents GroupBox14 As GroupBox
    Friend WithEvents SS3 As Label
    Friend WithEvents Label53 As Label
    Friend WithEvents Label51 As Label
    Friend WithEvents SA3 As Label
    Friend WithEvents Label49 As Label
    Friend WithEvents SC3 As Label
    Friend WithEvents Label72 As Label
    Friend WithEvents ST3 As Label
    Friend WithEvents GroupBox15 As GroupBox
    Friend WithEvents turn As Label
    Friend WithEvents Label12 As Label
    Friend WithEvents Label40 As Label
    Friend WithEvents Label13 As Label
    Friend WithEvents up3 As Label
    Friend WithEvents motor3 As Label
    Friend WithEvents Label78 As Label
    Friend WithEvents down3 As Label
    Friend WithEvents PictureBox3 As PictureBox
    Friend WithEvents GroupBox6 As GroupBox
End Class
