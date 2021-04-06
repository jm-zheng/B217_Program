Option Explicit On
Imports System.IO
Imports System
'Imports Microsoft.Office.Interop.Excel
Public Class Frist
    Dim Chouse As Object = 0
    Dim Rx_Data(128) As Object
    Dim Rx_N As Integer = 0
    Dim Rx_Case As Integer = 0
    Dim Button1_Times As Integer = 0
    'Dim Vmoney = 0
    Dim VAll1 = 0
    Dim VAll2 = 0
    Dim VP1 As Double = 0
    Dim VP2 = 0 '

    Dim t1 = 0, t2 = 0, t3 = 0, state_return = 0
    Dim Data_Length As Integer
    Dim PM1_PowerRate!
    Dim PM2_PowerRate!


    Dim Record_Sw = 0
    Public V3_Conut1 = 1
    Public V3_Conut2 = 1
    Public V3_Conut3 = 1
    Public V3_Conut4 = 1
    Dim BT = 0
    Dim RSSINum = 0
    Dim LGNum = 0
    Dim RxLR() As Byte = {0, &H50, &H50, &H1, &HBB}
    Dim S1() As Byte = {0, 1, 3, 1, 1, &H7F, &H1}
    Dim S2() As Byte = {0, 1, 2, 1, 1, &H7F, &H2}
    '4th data
    Const B217Lux = 8000
    Dim Mode = 1
    Dim RSSINode() As Byte = {0, &HDD, &H0, &HFF, &HFD, &H5A}
    Dim LightSensor() As Byte = {0, &HCC, 1, &H59}
    Dim LightCorrect() As Byte = {0, 1, 2, 0, &HC, &HA, 0}

    Dim PP1_PowerRate!
    Dim PP2_PowerRate!
    '*****************節能
    Dim energy_conservation_1 As Object
    Dim co2 As Object
    Dim money_1 As Object
    Dim energy_conservation_2 As Object
    '----------不累積電度
    Dim Nocumulativepower_1 As Object
    Dim Nocumulativepower_2 As Object
    '----------節能百分比
    Dim energy_percentage_1 As Object
    Dim energy_percentage_2 As Object
    '----------------碳足跡-------------------------
    Dim co2_1 As Object
    Dim co2_2 As Object
    '--------------時間資料--------------------------
    Dim Time_PowerRate(24)()

    '--------------調光變數--------------------------
    Dim light As Integer = 50

    Public T5_Station1 = Chr(&H1) + Chr(&H3)
    Public T5_Station2 = Chr(&H1) + Chr(&H2)

    Public T5_Channel1_Relay = Chr(&H0) + Chr(&H10)
    Public T5_Channel2_Relay = Chr(&H0) + Chr(&H8)

    Public T5_Channel1_PWM = Chr(&H0) + Chr(&H4)
    Public T5_Channel2_PWM = Chr(&H0) + Chr(&H8)
    Public TXD As String
    Public Const KWHPRICE As Single = 2.1

    '-------------宣告Excel的定義------------------
    'Dim NowNum = 0
    'Dim SClass = 0
    'Dim OutsetTime As Date
    'Public DataArray(0 To 6, 0 To 300) As String

    ''用於存放Microsoft Excel 引用的變數。
    'Public xlApp As Application
    'Public xlBook As Workbook
    'Public xlSheet As Worksheet
    'Public xlRange As Range
    'Public T5_StationAll1 = Chr(&HFF)
    'Public T5_StationAll2 = Chr(&HFF)
    
    '------------------End----------------------------

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click

        If Button1_Times = 0 Then
            SerialPort1.PortName = ComboBox5.SelectedItem
            SerialPort1.DataBits = ComboBox2.Text
            SerialPort1.Parity = ComboBox3.SelectedIndex
            SerialPort1.StopBits = ComboBox4.Text
            SerialPort1.Open()
            Button1_Times += 1
            Timer2.Enabled = True
            Timer3.Enabled = True
            'Record.Enabled = True
            Button1.Text = "取消連結"
        ElseIf Button1_Times = 1 Then
            SerialPort1.Close()
            Button1_Times = 0
            Timer2.Enabled = False
            Timer3.Enabled = False
            Record.Enabled = False
            Button1.Text = "啟動連結"
        End If
    End Sub

    Private Sub a_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        'SerialPort1.Open()
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox5.Items.Add(sp)
        Next
        ' ComboBox5.Text = ComboBox5.Items.Insert
        ComboBox1.Text = ComboBox1.Items.Item(0)
        ComboBox2.Text = ComboBox2.Items.Item(3)
        ComboBox3.Text = ComboBox3.Items.Item(0)
        ComboBox4.Text = ComboBox4.Items.Item(0)
        ComboBox5.Text = ComboBox5.Items.Item(0)
        'Button2.Checked=

        '-----------------------------------Excel----------------------------------------

        'On Error Resume Next
        ''#一部電腦僅執行一個Excel Application, 就算中突開啟Excel也不會影響程式執行
        ''#在工作管理員中只會看見一個EXCEL.exe在執行，不會浪費電腦資源
        ''#引用正在執行的Excel Application
        'xlApp = GetObject(, "Excel.Application")
        ''#若發生錯誤表示電腦沒有Excel正在執行，需重新建立一個新的應用程式
        'If Err.Number() <> 0 Then
        '    Err.Clear()
        '    '#執行一個新的Excel Application
        '    xlApp = CreateObject("Excel.Application")
        '    If Err.Number() <> 0 Then
        '        MsgBox("電腦沒有安裝Excel")
        '        End
        '    End If
        'End If
        '-------------------------------------End----------------------------------------
    End Sub

    Private Sub ComboBox5_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles ComboBox5.Click
        ComboBox5.Items.Clear()
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox5.Items.Add(sp)
        Next

    End Sub

    Private Sub T5_2CH_1()
        t1 = 0
        Label9.Text = "已連結"
        Label9.ForeColor = Color.Lime
        If Rx_Data(7) = &H10 Then
            Label15.Text = "ON"
            Label15.ForeColor = Color.Red
            Label16.Text = "OFF"
            Label16.ForeColor = Color.White
        ElseIf Rx_Data(7) = &H8 Then
            Label16.Text = "ON"
            Label16.ForeColor = Color.Red
            Label15.Text = "OFF"
            Label15.ForeColor = Color.White
        ElseIf Rx_Data(7) = &H18 Then
            Label16.Text = "ON"
            Label16.ForeColor = Color.Red
            Label15.Text = "ON"
            Label15.ForeColor = Color.Red
        Else
            Label15.Text = "OFF"
            Label15.ForeColor = Color.White
            Label16.Text = "OFF"
            Label16.ForeColor = Color.White
        End If

        Label17.Text = Rx_Data(8) / 10
        Label18.Text = Val(Rx_Data(9)) / 10
        Label23.Text = Rx_Data(10) / 100
        VP1 += ((110 * Label23.Text) / 7200)
        '***********不累積電度
        Nocumulativepower_1 = ((110 * Label23.Text) / 7200)
        Label56.Text = Format(Nocumulativepower_1, "0.000")
        '*************Power Plug1 Calculate
        PP1_PowerRate = VP1 * KWHPRICE
        Label52.Text = Format(PP1_PowerRate, "#0.00000")
        Label6.Text = Format(VP1, "0.000")
        '*************co2_1單位
        co2_1 = Format(Label7.Text, "0.00000")
        Label7.Text = Label6.Text * 0.638
        Timer2.Enabled = True
    End Sub
    Private Sub T5_2CH_2()
        t2 = 0
        Label10.Text = "已連結"
        Label10.ForeColor = Color.Lime
        If Rx_Data(7) = &H10 Then
            Label19.Text = "ON"
            Label19.ForeColor = Color.Red
            label100.Text = "OFF"
            label100.ForeColor = Color.White
        ElseIf Rx_Data(7) = &H8 Then
            label100.Text = "ON"
            label100.ForeColor = Color.Red
            Label19.Text = "OFF"
            Label19.ForeColor = Color.White
        ElseIf Rx_Data(7) = &H18 Then
            Label19.Text = "ON"
            Label19.ForeColor = Color.Red
            label100.Text = "ON"
            label100.ForeColor = Color.Red
        Else
            Label19.Text = "OFF"
            Label19.ForeColor = Color.White
            label100.Text = "OFF"
            label100.ForeColor = Color.White
        End If
        Label21.Text = Rx_Data(8) / 10
        Label22.Text = Rx_Data(9) / 10
        Label25.Text = ((Rx_Data(10) / 100) * 2 - 0.88)
        VP2 += ((110 * Label25.Text) / 7200)
        '***********不累積電度
        Nocumulativepower_2 = ((110 * Label25.Text) / 7200)
        Label66.Text = Format(Nocumulativepower_2, "0.000")
        '*************Power Plug1 Calculate
        PP2_PowerRate = VP2 * KWHPRICE
        Label55.Text = Format(PP2_PowerRate, "#0.00000")
        Label26.Text = Format(VP2, "0.000")
        '*************co2_2單位
        co2_2 = Format(Label36.Text, "0.00000")
        Label36.Text = Label26.Text * 0.638
        Timer2.Enabled = True
    End Sub
    '------------rssi的函式-----------------------------
    Private Sub RSSIandLight()

        t3 = 0
        Label79.Text = "已連結"
        Label79.ForeColor = Color.Lime
        '-------A區
        Label76.Text = Rx_Data(15) '----rssi
        Dim a = (Rx_Data(4) << 8) And &HFFFF + Rx_Data(5)
        Label60.Text = -14.225 + 0.0328 * (((Rx_Data(4) << 8) And &HFFFF) + Rx_Data(5))  '----light
        '-------B區

        Label77.Text = Rx_Data(28) '----rssi
        Label73.Text = -7.77 + 0.049 * (((Rx_Data(6) << 8) And &HFFFF) + Rx_Data(7)) '----light

        If Chouse = 1 Then
            LightTimer.Enabled = True
        ElseIf Chouse = 2 Then
            RSSITimer.Enabled = True
        Else
            Timer2.Enabled = True
        End If
        ' Timer2.Enabled = True

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        t1 += 1
        t2 += 1
        t3 += 1
        If t1 > 6 Then
            Label9.Text = "尚未連結"
            Label9.ForeColor = Color.Red
        End If
        If t2 > 6 Then
            Label10.Text = "尚未連結"
            Label10.ForeColor = Color.Red
        End If
        If t3 > 6 Then
            Label79.Text = "尚未連結"
            Label79.ForeColor = Color.Red
        End If

    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        state_return += 1
        Select Case state_return
            Case 1
                '確定Station1整體狀態
                SerialPort1.Write(S1, 1, 6)
            Case 2
                '確定Station2整體狀態
                SerialPort1.Write(S2, 1, 6)
            Case 3
                SerialPort1.Write(RxLR, 1, 4)
                state_return = 0
            Case 4

        End Select

    End Sub

    Private Sub Timer3_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer3.Tick
        If Rx_Case = 0 Then
            If SerialPort1.BytesToRead() Then
                Timer2.Enabled = False
                UART_Rx()
            End If


        ElseIf Rx_Case = 1 And Rx_N > 2 Then
            If Rx_Data(0) = &H1 And Rx_Data(1) = &H1 And Rx_Data(2) = &H7F Then
                T5_2CH_1()
                Rx_N = 0
                Label47.Text = ""
            ElseIf Rx_Data(0) = &H1 And Rx_Data(1) = &H2 And Rx_Data(2) = &H7F Then
                T5_2CH_2()
                Rx_N = 0
                Label48.Text = ""
                '---------rssi讀值
            ElseIf Rx_Data(0) = &H50 And Rx_Data(1) = &H51 Then
                Timer2.Enabled = False
                RSSIandLight()
            ElseIf Rx_Data(0) = &H42 And Rx_Data(1) = &H54 Then
                Timer2.Enabled = False
                'BTimer.Enabled = True
            Else
                Timer2.Enabled = True
            End If
            Rx_N = 0
            Rx_Case = 0
        End If

        Label47.Text = DateString
        Label48.Text = TimeString
        '**************節能區域
        '電度數
        Label43.Text = Format(energy_conservation_1, "0.0000")
        energy_conservation_1 = Label6.Text - Label26.Text

        'CO2
        Label46.Text = Format(co2, "0.0000")
        co2 = Label7.Text - Label36.Text


        '***************節能百分比
        Label62.Text = Format(energy_percentage_1, "00.000")   '-----format的功能就是指定資料長度
        energy_percentage_1 = ((0.21 - Label23.Text) / 0.21) * 100
        Label69.Text = Format(energy_percentage_2, "00.000")
        energy_percentage_2 = ((0.65 - Label25.Text) / 0.65) * 100
        '*******DC小於3時自動斷電

    End Sub
    '要記得Chr(這裡要放十進制要不然就要打&H)
    '----------------------light intensity----------------------------------------------------------------------
    Private Sub Button28_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button28.Click
        Record.Enabled = True

        Chouse = 1

    End Sub
    '--------------------RSSI-------------------------
    Private Sub Button29_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button29.Click


        Chouse = 2

    End Sub
  
    Private Sub Button30_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button30.Click
        Record.Enabled = False
        Chouse = 0
        Form2.Show()

    End Sub



    Private Sub Button26_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button26.Click
        End
    End Sub


    Private Sub Button27_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button27.Click
        Record.Enabled = False
        Form1.Show()
    End Sub


    'Private Sub Button29_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button29.Click
    '    '打開已經存在的EXCEL工件簿文件

    '    xlBook = xlApp.Workbooks.Open(Directory.GetCurrentDirectory() & "\" & "Sample.xlsx")

    '    '停用警告訊息

    '    xlApp.DisplayAlerts = False

    '    '設置EXCEL對象可見

    '    xlApp.Visible = True

    '    '設定活頁簿為焦點

    '    xlBook.Activate()

    '    '顯示第一個子視窗

    '    xlBook.Parent.Windows(1).Visible = True

    '    '引用第一個工作表

    '    xlSheet = xlBook.Worksheets(1)

    '    '設定工作表為焦點

    '    xlSheet.Activate()



    '    '===================================================

    '    '#用Array寫資料至EXCEL
    '    Voltage_CH.Enabled = True


    'End Sub
    'Private Sub Record_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Record.Tick

    '    If NowNum < TimeString And Label9.Text = "已開通" Then
    '        xlSheet.Cells(DateDiff("S", OutsetTime, TimeString) + 1, SClass + 1).value = Label23.Text
    '        NowNum = TimeString
    '    End If

    '    If DateDiff("S", OutsetTime, TimeString) > 3599 Then
    '        Voltage_CH.Enabled = True
    '        Record.Enabled = False
    '    ElseIf DateDiff("S", OutsetTime, TimeString) > 3599 And SClass = 11 Then
    '        Save()
    '        Record.Enabled = False
    '    End If
    'End Sub
    'Private Sub Voltage_CH_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Voltage_CH.Tick

    '    SerialPort1.Write(T5_Station1 + T5_Channel1_PWM + Chr(&HA) + Chr(Val(SClass * 10)))
    '    If Label17.Text = 0 And SClass = 0 Then
    '        SClass = 1
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 10 And SClass = 1 Then
    '        SClass = 2
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 20 And SClass = 2 Then
    '        SClass = 3
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 30 And SClass = 3 Then

    '        SClass = 4
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 40 And SClass = 4 Then
    '        SClass = 5
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 50 And SClass = 5 Then
    '        SClass = 6
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 60 And SClass = 6 Then
    '        SClass = 7
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 70 And SClass = 7 Then
    '        SClass = 8
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 80 And SClass = 8 Then
    '        SClass = 9
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 90 And SClass = 9 Then
    '        SClass = 10
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False

    '    ElseIf Label17.Text = 100 And SClass = 10 Then
    '        SClass = 11
    '        OutsetTime = TimeString
    '        NowNum = TimeString
    '        Record.Enabled = True
    '        Voltage_CH.Enabled = False
    '    End If

    'End Sub


    'Private Sub Save()
    '    '另存新檔
    '    xlBook.SaveAs(Directory.GetCurrentDirectory() & "\" & "TETS.xlsx")
    '    '關閉當前活頁簿EXCEL
    '    xlBook.Close()
    '    xlApp.Quit()
    '    '回收excel
    '    System.Runtime.InteropServices.Marshal.ReleaseComObject(xlApp)
    '    xlApp = Nothing
    '    xlBook = Nothing
    '    xlSheet = Nothing
    '    xlRange = Nothing
    '    GC.Collect()
    'End Sub

    ''--------------------------------各項數值傳送
    'Private Sub Button28_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
    '    Dim abc(127) As Byte
    '    abc(1) = 255
    '    abc(2) = 0
    '    abc(3) = 86
    '    abc(4) = 111
    '    abc(5) = 108
    '    abc(6) = 116
    '    abc(7) = 97
    '    abc(8) = 103
    '    abc(9) = 101
    '    abc(10) = 32
    '    abc(11) = 58
    '    SerialPort1.Write(abc, 1, 11)
    '    SerialPort1.Write(Label17.Text)
    'End Sub


    'Private Sub Button29_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
    '    Dim isend(20) As Byte

    '    isend(1) = 225   '16近制的"FF"
    '    isend(2) = 0
    '    isend(3) = 69
    '    isend(4) = 108
    '    isend(5) = 101
    '    isend(6) = 99
    '    isend(7) = 116
    '    isend(8) = 114
    '    isend(9) = 105
    '    isend(10) = 99
    '    isend(11) = 32
    '    isend(12) = Rx_Data(10) / 100
    '    isend(13) = 46
    '    isend(14) = Rx_Data(10) / 10 Mod 10
    '    isend(15) = Rx_Data(10) Mod 10
    '    SerialPort1.Write(isend, 1, 11)
    '    SerialPort1.Write(Label23.Text)
    'End Sub

    Private Sub Record_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Record.Tick
        Record_Sw += 1
        Select Case Record_Sw
            Case 1
                If Label17.Text < 3 And V3_Conut1 = 1 And Label15.Text = "ON" Then
                    SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(16) + Chr(1) + Chr(1))
                ElseIf Label17.Text >= 3 And V3_Conut1 = 1 And Label15.Text = "OFF" Then
                    SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(16) + Chr(1) + Chr(0))
                End If
            Case 2
                If Label18.Text < 3 And V3_Conut2 = 1 And Label16.Text = "ON" Then
                    SerialPort1.Write(Chr(1) + Chr(1) + Chr(200) + Chr(8) + Chr(1) + Chr(1))
                ElseIf Label18.Text >= 3 And V3_Conut2 = 1 And Label16.Text = "OFF" Then
                    SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(8) + Chr(1) + Chr(0))
                End If
            Case 3
                If Label22.Text < 3 And V3_Conut3 = 1 And label100.Text = "ON" Then
                    SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(8) + Chr(1) + Chr(1))
                ElseIf Label22.Text >= 3 And V3_Conut3 = 1 And label100.Text = "OFF" Then
                    SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(8) + Chr(1) + Chr(0))
                End If
            Case 4
                If Label21.Text < 3 And V3_Conut4 = 1 And Label19.Text = "ON" Then
                    SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(16) + Chr(1) + Chr(1))
                ElseIf Label21.Text >= 3 And V3_Conut4 = 1 And Label19.Text = "OFF" Then
                    SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(16) + Chr(1) + Chr(0))
                End If
                Record_Sw = 0
        End Select

    End Sub

    Private Sub RSSITimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RSSITimer.Tick
        RSSINum += 1
        If RSSINum = 1 Then
            If Rx_Data(15) < 205 And Rx_Data(28) < 205 Then
                V3_Conut1 = 0
                V3_Conut2 = 0
                SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(&H18) + Chr(&H1) + Chr(1))
            ElseIf (Rx_Data(15) > 206 Or Rx_Data(28) > 206) And (Label15.Text <> "ON" And Label16.Text <> "ON") Then
                V3_Conut1 = 1
                V3_Conut2 = 1
                SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(&H18) + Chr(&H1) + Chr(0))
            ElseIf Rx_Data(15) > Rx_Data(28) Then
                SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(&HC) + Chr(&HA) + Chr(100))
            ElseIf Rx_Data(28) > Rx_Data(15) Then
                SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(&HC) + Chr(&HA) + Chr(31))
            End If
        ElseIf RSSINum = 2 Then
            If Rx_Data(15) < 205 And Rx_Data(28) < 205 Then
                V3_Conut3 = 0
                V3_Conut4 = 0
                SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(&H18) + Chr(&H1) + Chr(1))
            ElseIf (Rx_Data(15) > 206 Or Rx_Data(28) > 206) And (Label15.Text <> "ON" And Label16.Text <> "ON") Then
                V3_Conut3 = 1
                V3_Conut4 = 1
                SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(&H18) + Chr(&H1) + Chr(0))
            ElseIf Rx_Data(15) > Rx_Data(28) Then
                SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(&HC) + Chr(&HA) + Chr(31))
            ElseIf Rx_Data(28) > Rx_Data(15) Then
                SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(&HC) + Chr(&HA) + Chr(100))
            End If
        Else
            RSSINum = 0
            RSSITimer.Enabled = False
            Timer2.Enabled = True
        End If
    End Sub

    Sub UART_Rx()

        While SerialPort1.BytesToRead()
            Rx_Data(Rx_N) = SerialPort1.ReadByte

            Rx_N += 1
            Rx_Case = 1
        End While


    End Sub

    Private Sub LightTimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LightTimer.Tick
        LGNum += 1
        Dim a = (Label60.Text - 100) / 3
        Dim b = (Label73.Text - 100) / 3
        If a > 69 Then
            a = 69
        ElseIf a < 0 Then
            a = 0
        End If
        If b > 69 Then
            b = 69
        ElseIf b < 0 Then
            b = 0
        End If
        Select Case LGNum
            Case 1
                SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(&HC) + Chr(&HA) + Chr(100 - a))
            Case 2
                SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(&HC) + Chr(&HA) + Chr(100 - b))
            Case Else
                LGNum = 0
                LightTimer.Enabled = False
                Timer2.Enabled = True
        End Select
    End Sub

    Private Sub BTimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BTimer.Tick


        'Select Case Rx_Data(2)
        '    Case 1
        '        V3_Conut1 = 1
        '        V3_Conut2 = 1
        '        SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(24) + Chr(1) + Chr(0))

        '    Case 2
        '        V3_Conut1 = 0
        '        V3_Conut2 = 0
        '        SerialPort1.Write(Chr(1) + Chr(3) + Chr(1) + Chr(24) + Chr(1) + Chr(1))
        '    Case 3
        '        V3_Conut1 = 1
        '        V3_Conut2 = 1
        '        SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(24) + Chr(1) + Chr(0))
        '    Case 4
        '        V3_Conut1 = 0
        '        V3_Conut2 = 0
        '        SerialPort1.Write(Chr(1) + Chr(2) + Chr(1) + Chr(24) + Chr(1) + Chr(1))
        '    Case 5
        '        SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(12) + Chr(10) + Chr(Rx_Data(3)))
        '    Case 6
        '        SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(12) + Chr(10) + Chr(Rx_Data(3)))
        '    Case Else
        '        BTimer.Enabled = False
        '        Timer2.Enabled = True
        'End Select

        'Rx_Data(2) = 10

    End Sub

End Class
