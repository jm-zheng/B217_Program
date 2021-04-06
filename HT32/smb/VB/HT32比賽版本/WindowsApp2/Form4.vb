Public Class Form4
    Dim abc As SQL_TypeDef = New SQL_TypeDef
    Private Sub Form4_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Enabled = True
        Timer2.Enabled = True
        Try
            MySQL_Init(abc, 9, "127.0.0.1", "root", "123456", "factory")
            MySQL_Connection()
            SerialPort1.Open()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Timer1.Interval = 1000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer1.Enabled = True '啟動Timer1
        nama3.Text = Form1.nama3.Text
        number3.Text = Form1.number3.Text
        manager3.Text = Form1.manager3.Text
        SS3.Text = Form1.SS3.Text
        SC3.Text = Form1.SC3.Text
        ST3.Text = Form1.ST3.Text
        SA3.Text = Form1.SA3.Text
        motor3.Text = Form1.motor3.Text
        status3.Text = Form1.status3.Text
        turn.Text = Form1.turn3.Text
        up3.Text = Form1.up3.Text
        down3.Text = Form1.down3.Text
        If ST3.Text >= "29.5" Then
            status3.Text = "異常狀態"
            GroupBox6.BackColor = Color.Red
        ElseIf ST3.Text >= "29.5" & ST3.Text <= "32.5" Then
            GroupBox6.BackColor = Color.Orange
            status3.Text = "警告狀態"
        Else
            status3.Text = "正常狀態"
            GroupBox6.BackColor = Color.LightGreen
        End If
    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick
        Timer2.Interval = 5000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Me.DataGridView2.Rows.Add(Form1.et.Text, Form1.eh.Text, Form1.ec.Text, Form1.ef.Text, Form1.ev.Text, Form1.el.Text)
        Me.DataGridView1.Rows.Add(Form1.Label18.Text, Form1.Label20.Text, Form1.name1.Text, Form1.number1.Text, Form1.Manager1.Text, Form1.SS1.Text, Form1.SC1.Text, Form1.ST1.Text, Form1.SA1.Text, Form1.motor1.Text, Form1.status1.Text)
        abc.Form = "machine3"
        abc.Column(1) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(2).Value
        abc.Column(2) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(3).Value
        abc.Column(3) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(4).Value
        abc.Column(4) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(5).Value
        abc.Column(5) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(6).Value
        abc.Column(6) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(7).Value
        abc.Column(7) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(8).Value
        abc.Column(8) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(9).Value
        abc.Column(9) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(10).Value

        MySQL_Add(abc, 9)

    End Sub
End Class