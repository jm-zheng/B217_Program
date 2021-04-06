Public Class Form3
    Dim abc As SQL_TypeDef = New SQL_TypeDef
    Private Sub Form3_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Enabled = True
        Timer2.Enabled = True

        If Form1.Label54.Text = "輪播中" Then
            Form2.Close()
            Timer3.Interval = 10000 '設Timer1的時間間隔為1000毫秒，也就是1秒
            Timer3.Enabled = True '啟動Timer1
        End If



        Try
            MySQL_Init(abc, 9, "127.0.0.1", "root", "123456", "factory")
            MySQL_Connection()
            SerialPort1.Open()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick
        Timer2.Interval = 5000 '設Timer1的時間間隔為1000毫秒，也就是1秒

        Me.DataGridView1.Rows.Add(Form1.Label18.Text, Form1.Label20.Text, Form1.nama2.Text, Form1.number2.Text, Form1.manager2.Text, Form1.SS2.Text, Form1.SC2.Text, Form1.ST2.Text, Form1.SA2.Text, motor2.Text, status2.Text)
        abc.Form = "machine2"
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

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick

        Timer1.Interval = 1000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer1.Enabled = True '啟動Timer1
        name2.Text = Form1.nama2.Text
        number2.Text = Form1.number2.Text
        manager2.Text = Form1.manager2.Text
        SS2.Text = Form1.SS2.Text
        SC2.Text = Form1.SC2.Text
        ST2.Text = Form1.ST2.Text
        SA2.Text = Form1.SA2.Text

        status2.Text = Form1.status2.Text
        TextBox1.Text = Form1.TextBox2.Text
        If ST2.Text >= "29.5" Then
            status2.Text = "異常狀態"
            GroupBox1.BackColor = Color.Red
        ElseIf ST2.Text >= "28.5" & ST2.Text <= "29.0" Then
            GroupBox1.BackColor = Color.Orange
            status2.Text = "警告狀態"
        Else
            status2.Text = "正常狀態"
            GroupBox1.BackColor = Color.LightGreen
        End If

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Form1.Show()
    End Sub

    Private Sub Timer3_Tick(sender As Object, e As EventArgs) Handles Timer3.Tick
        Form6.Show()
    End Sub
End Class