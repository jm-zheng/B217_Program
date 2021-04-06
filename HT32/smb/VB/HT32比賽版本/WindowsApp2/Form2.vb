Public Class Form2
    Dim abc As SQL_TypeDef = New SQL_TypeDef
    Dim MyExcel As New Microsoft.Office.Interop.Excel.Application()

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Enabled = True
        Timer2.Enabled = True
        If Form1.Label54.Text = "輪播中" Then
            Timer3.Interval = 10000 '設Timer1的時間間隔為1000毫秒，也就是1秒
            Timer3.Enabled = True '啟動Timer1
            Form1.Hide()
        End If
        Form6.Close()

        Try
            MySQL_Init(abc, 15, "127.0.0.1", "root", "123456", "factory")

            MySQL_Connection()
            SerialPort1.Open()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick

        Timer1.Interval = 1000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer1.Enabled = True '啟動Timer1
        name1.Text = Form1.name1.Text
        number1.Text = Form1.number1.Text
        Manager1.Text = Form1.Manager1.Text
        SS1.Text = Form1.SS1.Text
        SC1.Text = Form1.SC1.Text
        ST1.Text = Form1.ST1.Text
        SA1.Text = Form1.SA1.Text
        motor1.Text = Form1.motor1.Text
        status1.Text = Form1.status1.Text
        turn1.Text = Form1.turn1.Text
        up1.Text = Form1.up1.Text
        down1.Text = Form1.down1.Text
        TextBox1.Text = Form1.TextBox1.Text
        noc1.Text = Form1.noc1.Text
        If ST1.Text >= "30.0" Or Form1.Label52.Text = 2 Then
            status1.Text = "危險狀態"
            GroupBox1.BackColor = Color.Red
        ElseIf ST1.Text >= "28.5" And ST1.Text <= "29.5" And SA1.Text >= "0.10" Then
            GroupBox1.BackColor = Color.Orange
            status1.Text = "警告狀態"
        ElseIf SA1.Text < "0.10" Then
            status1.Text = "待機狀態"
            GroupBox1.BackColor = Color.Yellow
        Else
            status1.Text = "正常狀態"
            GroupBox1.BackColor = Color.LightGreen
        End If

    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick

        Timer2.Interval = 1000 '設Timer1的時間間隔為1000毫秒，也就是1秒

        Me.DataGridView2.Rows.Add(Form1.motor1.Text, Form1.turn1.Text, Form1.up1.Text, Form1.down1.Text, Form1.PD1.Text, Form1.Label29.Text, Form1.noc1.Text)
        Me.DataGridView1.Rows.Add(Form1.Label18.Text, Form1.Label20.Text, Form1.name1.Text, Form1.number1.Text, Form1.Manager1.Text, Form1.SS1.Text, Form1.SC1.Text, Form1.ST1.Text, Form1.SA1.Text, Form1.status1.Text)
        abc.Form = "machine1"
        abc.Column(1) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(2).Value
        abc.Column(2) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(3).Value
        abc.Column(3) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(4).Value
        abc.Column(4) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(5).Value
        abc.Column(5) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(6).Value
        abc.Column(6) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(7).Value
        abc.Column(7) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(8).Value
        abc.Column(8) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(9).Value
        abc.Column(9) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(0).Value
        abc.Column(10) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(1).Value
        abc.Column(11) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(2).Value
        abc.Column(12) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(3).Value
        abc.Column(13) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(4).Value
        abc.Column(14) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(5).Value
        abc.Column(15) = DataGridView2.Rows(DataGridView2.Rows.Count - 2).Cells(6).Value
        MySQL_Add(abc, 15)
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Form1.Show()
    End Sub

    Private Sub BackgroundWorker1_DoWork(sender As Object, e As System.ComponentModel.DoWorkEventArgs) Handles BackgroundWorker1.DoWork

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        MyExcel.Application.Workbooks.Add()
        MyExcel.Visible = True
        Dim Cols As Integer
        For Cols = 1 To DataGridView1.Columns.Count
            MyExcel.Cells(1, Cols) = DataGridView1.Columns(Cols - 1).HeaderText
        Next
        '往excel表裡添加資料()
        Dim i As Integer
        For i = 0 To DataGridView1.RowCount - 2
            Dim j As Integer
            For j = 0 To DataGridView1.ColumnCount - 1
                If Me.DataGridView1(j, i).Value Is System.DBNull.Value Then

                    MyExcel.Cells(i + 2, j + 1) = ""
                Else
                    MyExcel.Cells(i + 2, j + 1) = DataGridView1(j, i).Value.ToString

                End If
            Next j
        Next i
        Cols = 0


        MyExcel.Application.Workbooks.Add()
        MyExcel.Visible = True
        Dim Cols2 As Integer
        For Cols2 = 1 To DataGridView2.Columns.Count
            MyExcel.Cells(1, Cols2) = DataGridView2.Columns(Cols2 - 1).HeaderText
        Next
        '往excel表裡添加資料()
        Dim x As Integer
        For x = 0 To DataGridView2.RowCount - 2
            Dim j As Integer
            For j = 0 To DataGridView2.ColumnCount - 1
                If Me.DataGridView2(j, x).Value Is System.DBNull.Value Then

                    MyExcel.Cells(x + 2, j + 1) = ""
                Else
                    MyExcel.Cells(x + 2, j + 1) = DataGridView2(j, x).Value.ToString

                End If
            Next j
        Next x
        Cols2 = 0
    End Sub

    Private Sub Timer3_Tick(sender As Object, e As EventArgs) Handles Timer3.Tick

        Form3.Show()
    End Sub
End Class