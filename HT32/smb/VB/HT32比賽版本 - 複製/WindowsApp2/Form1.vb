Public Class Form1
    'Public RXD$
    Dim RXD$
    Dim asd(256) As String
    Dim asdflag As Integer
    Dim smb_data As String = ""
    Dim abc As SQL_TypeDef = New SQL_TypeDef
    Dim ttt As SQL_TypeDef = New SQL_TypeDef
    Dim y4_y7data As Integer
    Dim y0_y3data As Integer
    Dim y0_data As Integer
    Dim y1_data As Integer
    Dim y2_data As Integer
    Dim y3_data As Integer
    Dim y4_data As Integer
    Dim y5_data As Integer
    Dim Pc1_data As Integer
    Dim Pc1_1_Data As Integer
    Dim Pc2_data As Integer
    Dim Pc2_1_data As Integer
    Dim PLC_D_1_data As Integer
    Dim PLC_D_2_data As Integer
    Dim Pc4_data As Decimal
    Dim ecTEXT As Integer
    Dim evTEXT As Integer
    Dim PLC_D_3_data As Integer
    Dim PLC_D_4_data As Integer
    Dim PLC_D_3_3_data As Integer
    Dim PLC_D_4_4_data As Integer
    Dim PLC_D_3_3_1data As Integer
    Dim PLC_D_3_3_2data As Integer
    Dim ps4
    Dim Pc3_data As Decimal
    Dim Pc3_1_data As Decimal
    Dim Carousel_BT = 0
    Dim a_val As Single
    Dim stop_flag As Integer


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
        Next
        MySQL_Init(ttt, 6, "127.0.0.1", "root", "123456", "factory") 'MySQL連線網址、帳號、密碼、表單名稱
        MySQL_Connection() '開啟連線
        Timer2.Interval = 5000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer2.Enabled = True '啟動Timer1
        Timer4.Interval = 300 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer4.Enabled = True '啟動Timer1

        Timer3.Interval = 10000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer3.Enabled = True '啟動Timer1
    End Sub
    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        Form6.Show()
        Form6.et.Text = et.Text
        Form6.eh.Text = eh.Text
        Form6.ec.Text = ec.Text
        Form6.ef.Text = ef.Text
        Form6.ev.Text = ev.Text
        Form6.el.Text = el.Text
    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click, Button8.Click
        '''''''''''''''''''傳送資料到DataGridView1
        Form2.TextBox1.Text = TextBox1.Text
        Form2.Show()
        TextBox1.Text = Form2.TextBox1.Text
        Me.DataGridView1.Rows.Add(name1.Text, number1.Text, Manager1.Text, SS1.Text, SC1.Text, ST1.Text, SA1.Text, SA1.Text, motor1.Text)
        Me.DataGridView1.Rows.Add(nama2.Text, number2.Text, manager2.Text, SS2.Text, SC2.Text, ST2.Text, SA2.Text, status2.Text)
        Me.DataGridView1.Rows.Add(nama3.Text, number3.Text, manager3.Text, SS3.Text, SC3.Text, ST3.Text, SA3.Text, status3.Text)
        Timer1.Enabled = True
        MySQL_Connection()

    End Sub

    Private Sub DataGridView1_CellContentClick(sender As Object, e As DataGridViewCellEventArgs) Handles DataGridView1.CellContentClick

    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim aaa ''收進來的空白及換行宣告
        Dim bbb ''''''''收進來的換行宣告
        Dim ccc
        Dim qw() As String ''''''''''''''宣告執行收到資訊的第一行分割
        Dim kc() As String ''''''''''''''宣告執行收到資訊的第二行分割
        Dim jk() As String ''''''''''''''宣告執行收到資訊的第三行分割
        Dim zx() As String ''''''''''''''宣告執行收到資訊的第四行分割
        Dim mn() As String ''''''''''''''宣告執行收到資訊的第五行分割
        Dim ee() As String
        Dim jkf() As String
        Dim kfc() As String
        Dim ee2() As String
        Dim jkf2() As String

        If SerialPort1.BytesToRead Then
            For index = 1 To SerialPort1.BytesToRead
                asdflag += 1
                asd(asdflag) = Chr(SerialPort1.ReadByte)
                If asd(asdflag) = "*" Then
                    Exit For
                End If
            Next
        End If
        If asd(asdflag) = "*" Then
            Label16.Text = ""
            For index = 1 To asdflag
                Label16.Text &= asd(index) & ""
            Next

            ''''''''''''''''''''''收serial port的資料*為結尾碼收到*從新收資料一次
            'smb_data$ = SerialPort1.ReadExisting
            'If smb_data$ <> "" Then
            '    Label16.Text = ""
            '    For index = 1 To smb_data$.Length
            '        Label16.Text &= Mid(smb_data$, index, 1) & ""
            '    Next
            aaa = Chr(&HD) & Chr(&HA) ''收進來的空白及換行
            bbb = Chr(&HA) '''''''''''''收進來的換行
            ccc = Chr(&HD)
            Try
                If Mid(Label16.Text, 1, 2) = "BT" Then
                    asdflag = 0
                Else
                    qw = Split(Label16.Text, aaa) ''''''''''''''執行收到資訊的第一行分割
                    kc = Split(Label16.Text, bbb) ''''''''''''''執行收到資訊的第二行分割
                    jk = Split(Label16.Text, bbb) ''''''''''''''執行收到資訊的第三行分割
                    zx = Split(Label16.Text, bbb) ''''''''''''''執行收到資訊的第四行分割
                    mn = Split(Label16.Text, bbb) ''''''''''''''執行收到資訊的第五行分割
                    jkf = Split(Label16.Text, aaa)
                    kfc = Split(Label16.Text, aaa)
                    For i As Integer = 0 To 5
                        '''''''''''''''''st開頭'''''''''''''''
                        '  If Mid(Label16.Text, 1, 3) = "st1" Then


                        If i = 0 Then
                            qw = Split(qw(i), ":")
                            If Mid(Label16.Text, 1, 3) = "st1" Then
                                If qw(0) = "st1" Then
                                    ST1.Text = qw(1)
                                    name1.Text = "A場區"
                                    number1.Text = ComboBox2.Text
                                    Manager1.Text = "9527"

                                End If
                            End If
                            If Mid(Label16.Text, 1, 3) = "st2" Then
                                If qw(0) = "st2" Then
                                    ST2.Text = qw(1)
                                    nama2.Text = "B場區"
                                    number2.Text = ComboBox2.Text
                                    manager2.Text = "9528"
                                    status2.Text = "正常狀態"

                                End If

                                If ST2.Text >= "29.5" Then
                                    status2.Text = "危險狀態"
                                    GroupBox5.BackColor = Color.Red
                                ElseIf ST2.Text >= "28.5" & ST2.Text <= "29.0" Then
                                    GroupBox5.BackColor = Color.Orange
                                    status2.Text = "警告狀態"
                                Else
                                    status2.Text = "正常狀態"
                                    GroupBox5.BackColor = Color.LightGreen
                                End If
                            End If
                            If Mid(Label16.Text, 1, 3) = "st2" Then
                                If qw(0) = "st3" Then
                                    ST3.Text = qw(1)
                                    nama3.Text = "C場域"
                                    number3.Text = ComboBox2.Text
                                    manager3.Text = "9529"
                                    motor3.Text = "運轉中"
                                    status3.Text = "正常狀態"
                                    GroupBox6.BackColor = Color.LightGreen
                                End If
                            End If
                            If qw(0) = "et" Then
                                et.Text = qw(1)
                                If et.Text >= "32.00" Then
                                    et.BackColor = Color.Red
                                ElseIf et.Text >= "28.5" < "32.0" Then
                                    et.BackColor = Color.Orange
                                Else
                                    et.BackColor = Color.LightGreen
                                End If
                            End If
                        End If
                        ''''''''''''''''''''''st結尾'''''''''''''''''''''''''''''''''''''''
                        ''''''''''''''''''''''sp'''''''''''''''''''''''''''''''''''''''
                        If i = 1 Then
                            kc = Split(kc(i), ":")
                            If Mid(Label16.Text, 12, 3) = "sp1" Then
                                If kc(0) = "sp1" Then
                                    motor1.Text = kc(1)
                                    motor1.Text = ""
                                    y4_y7data = Asc(Mid(kc(1), 1, 1))
                                    y0_y3data = Asc(Mid(kc(1), 2, 1))
                                    y4_y7data = y4_y7data - &H30
                                    y0_y3data = y0_y3data - &H30
                                    y0_data = (y0_y3data And &H1)
                                    If y0_data = 1 Then
                                        turn1.Text = "旋轉中"
                                    Else
                                        turn1.Text = "停止動作"
                                    End If
                                    y1_data = (y0_y3data And &H2)
                                    If y1_data = 2 Then
                                        turn1.Text = "旋轉中"

                                    Else
                                        turn1.Text = "停止動作"
                                    End If
                                    y2_data = (y0_y3data And &H4)
                                    If y2_data = 4 Then
                                        down1.Text = "下降中"
                                    Else
                                        down1.Text = "停止動作"
                                    End If
                                    y3_data = (y0_y3data And &H8)
                                    If y3_data = 8 Then
                                        up1.Text = "上升中"
                                    Else
                                        up1.Text = "停止動作"
                                    End If
                                    y4_data = (y4_y7data And &H1)
                                    If y4_data = 1 Then
                                        motor1.Text = "運轉中"
                                    Else
                                        motor1.Text = "停止動作"
                                    End If
                                    y5_data = (y4_y7data And &H2)
                                    Label52.Text = y5_data
                                    'If y5_data = 2 Then
                                    '    status1.BackColor = Color.Red
                                    '    status1.Text = "危險狀態"
                                    '    GroupBox1.BackColor = Color.Red
                                    'Else
                                    '    status1.Text = "正常狀態"
                                    'End If
                                End If
                            End If
                            '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
                            If kc(0) = "sp2" Then
                                motor2.Text = kc(1)
                                motor2.Text = ""
                            End If
                            If kc(0) = "eh" Then
                                eh.Text = kc(1)
                            End If
                        End If ''''結尾if
                        If i = 2 Then
                            jk = Split(jk(i), ":")
                            If Mid(Label16.Text, 19, 3) = "sa1" Then
                                If jk(0) = "sa1" Then
                                    SA1.Text = jk(1)
                                    a_val = Hex(Asc(jk(1)))

                                End If
                            End If
                            If jk(0) = "sa2" Then
                                SA2.Text = jk(1)
                            End If
                            If jk(0) = "sa3" Then
                                SA3.Text = jk(1)
                            End If
                            If jk(0) = "ec" Then
                                ec.Text = jk(1)
                                ecTEXT = CInt(jk(1))

                            End If



                        End If

                        If i = 3 Then
                            zx = Split(zx(i), ":")
                            If Mid(Label16.Text, 29, 3) = "ss1" Then
                                If zx(0) = "ss1" Then
                                    SS1.Text = zx(1)
                                End If
                            End If
                            If zx(0) = "ss2" Then
                                SS2.Text = zx(1)
                            End If
                            If zx(0) = "ss3" Then
                                SS3.Text = zx(1)
                            End If
                            If zx(0) = "ef" Then
                                ef.Text = zx(1)
                            End If
                        End If ''''結尾if



                        If i = 4 Then
                            mn = Split(mn(i), ":")
                            If Mid(Label16.Text, 36, 3) = "sc1" Then
                                If mn(0) = "sc1" Then
                                    ee = Split(mn(1), ",")
                                    jkf = Split(ee(0), ":")
                                    SC1.Text = jkf(0)
                                    noc1.Text = ee(2)
                                    PD1.Text = Pc3_data
                                    Label29.Text = Pc4_data
                                    PLC_D_1_data = Asc(Mid(ee(1), 1, 1))
                                    PLC_D_2_data = Asc(Mid(ee(1), 2, 1))
                                    ' Pc1_data = (Asc(PLC_D_1_data))
                                    If PLC_D_1_data > &H30 < &H40 Then
                                        Pc1_data = PLC_D_1_data - &H30
                                        Pc1_1_Data = (Pc1_data << 4)
                                    End If
                                    'Pc2_data = (Asc(PLC_D_2_data))
                                    If PLC_D_2_data > &H30 < &H40 Then
                                        Pc2_data = PLC_D_2_data - &H30
                                    ElseIf PLC_D_2_data >= &H41 Then
                                        Pc2_data = PLC_D_2_data - &H31
                                    End If
                                    Pc3_data = (Pc1_1_Data + Pc2_data)

                                    PLC_D_3_data = Asc(Mid(ee(3), 1, 1))
                                    PLC_D_4_data = Asc(Mid(ee(3), 2, 1))
                                    If PLC_D_3_data > &H30 < &H40 Then
                                        PLC_D_3_3_1data = PLC_D_3_data - &H30
                                        PLC_D_3_3_2data = (PLC_D_3_3_1data << 4)
                                    End If
                                    'Pc2_data = (Asc(PLC_D_2_data))
                                    If PLC_D_4_data > &H30 < &H40 Then
                                        PLC_D_4_4_data = PLC_D_4_data - &H30
                                    ElseIf PLC_D_4_data >= &H41 Then
                                        PLC_D_4_4_data = PLC_D_4_data - &H31
                                    End If
                                    Pc4_data = (PLC_D_3_3_2data + PLC_D_4_4_data)
                                End If
                            End If
                            If mn(0) = "sc2" Then
                                SC2.Text = mn(1)
                                ee2 = Split(mn(1), ",")
                                jkf2 = Split(ee2(0), ":")
                                SC2.Text = jkf2(0)
                            End If
                            If mn(0) = "sc3" Then
                                SC3.Text = mn(1)
                            End If
                            If mn(0) = "ev" Then
                                ev.Text = mn(1)
                                evTEXT = CInt(mn(1))
                            End If ''''結尾

                        End If
                        If i = 5 Then
                            If qw(0) = "et" Then
                                jkf = Split(jkf(i), ":")
                                If jkf(0) = "el" Then
                                    el.Text = jkf(1)
                                End If
                            End If ''''結尾
                        End If
                    Next
                    asdflag = 0
                End If
            Catch
                asdflag = 0
            End Try
        End If
        Label20.Text = Format(Now, "hh:mm:ss") '指定TimeString為時間格式AMPM hh:mm:ss
    End Sub
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If SerialPort1.IsOpen = True Then
        End If
    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        Try
            SerialPort1.PortName = ComboBox1.Items(ComboBox1.SelectedIndex)
            SerialPort1.Open()
            Timer1.Enabled = True
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try
        Timer1.Interval = 100 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer1.Enabled = True '啟動Timer1
        Label18.Text = DateString.ToString() '設定日期時間
    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        Form3.Show()
    End Sub

    Private Sub Button9_Click(sender As Object, e As EventArgs) Handles Button9.Click
        SerialPort1.Write("BT:0*")
    End Sub

    Private Sub Button10_Click(sender As Object, e As EventArgs) Handles Button10.Click
        SerialPort1.Write("BT:3*")
    End Sub

    Private Sub Button11_Click(sender As Object, e As EventArgs) Handles Button11.Click
        SerialPort1.Write("BT:4*")
        '  stop_flag = 0
    End Sub

    Private Sub Button12_Click(sender As Object, e As EventArgs) Handles Button12.Click
        Form5.Show()
    End Sub

    Private Sub Timer3_Tick(sender As Object, e As EventArgs) Handles Timer3.Tick
        Me.DataGridView1.Rows.Add(et.Text, eh.Text, ec.Text, ef.Text, ev.Text, el.Text)
        ttt.Form = "setting"
        ttt.Column(1) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(0).Value
        ttt.Column(2) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(1).Value
        ttt.Column(3) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(2).Value
        ttt.Column(4) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(3).Value
        ttt.Column(5) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(4).Value
        ttt.Column(6) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(5).Value
        MySQL_Add(ttt, 6)
    End Sub

    Private Sub Label43_Click(sender As Object, e As EventArgs) Handles Label43.Click

    End Sub

    Private Sub GroupBox5_Enter(sender As Object, e As EventArgs) Handles GroupBox5.Enter

    End Sub

    Private Sub manager2_Click(sender As Object, e As EventArgs) Handles manager2.Click

    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click

        TextBox1.Text = TextBox4.Text / 2
        TextBox2.Text = TextBox4.Text / 2
    End Sub

    Private Sub Timer4_Tick(sender As Object, e As EventArgs) Handles Timer4.Tick

        If ST1.Text > "32.00" Or y5_data = 2 Then
            status1.Text = "危險狀態"
            If stop_flag = 0 Then
                stop_flag = 1
                SerialPort1.Write("BT:3*")
            End If
            GroupBox1.BackColor = Color.Red

        ElseIf ST1.Text >= "28.5" And ST1.Text <= "32.00" And SA1.Text >= "0.10" Then
            GroupBox1.BackColor = Color.Orange
            status1.Text = "警告狀態"
        ElseIf SA1.Text < "0.10" Then
            status1.Text = "待機狀態"
            GroupBox1.BackColor = Color.Yellow
        Else
            status1.Text = "正常狀態"
            stop_flag = 0
            GroupBox1.BackColor = Color.LightGreen
        End If


        If ecTEXT > 1000 Then
            ec.BackColor = Color.Red
        ElseIf ecTEXT < 600 Then
            ec.BackColor = Color.LightGreen
        Else
            ec.BackColor = Color.Orange
        End If

        If evTEXT > 100 Then
            ev.BackColor = Color.Red
        ElseIf evTEXT < 50 Then
            ev.BackColor = Color.LightGreen
        Else
            ev.BackColor = Color.Orange
        End If



        'If y5_data = 2 Then
        '    status1.BackColor = Color.Red
        '    status1.Text = "危險狀態"
        '    GroupBox1.BackColor = Color.Red
        'Else
        '    status1.Text = "正常狀態"
        'End If








    End Sub

    Private Sub Timer5_Tick(sender As Object, e As EventArgs) Handles Timer5.Tick
        Form2.Show()
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click

        Label54.Text = "輪播中"
        Timer5.Interval = 10000 '設Timer1的時間間隔為1000毫秒，也就是1秒
            Timer5.Enabled = True '啟動Timer1
        Form2.Show()



    End Sub
End Class
