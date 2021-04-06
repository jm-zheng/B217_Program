Imports MySql.Data.MySqlClient
Imports System.Net
Imports System.Net.Sockets
Imports System.Text
Public Class Form1
    Dim Checkbox(8) As CheckBox
    Dim Label(15) As Label
    Dim Tx_Buf(127) As Byte
    Dim Rx_Buf(127) As Byte
    Dim Device As Integer = 1
    Dim Device1 As Integer = 1
    Dim d1 = &H32
    Dim MeterRt(8) As Integer
    Public Rx_Number As Integer
    Public Link_switch As Integer = 0
    Dim Tx_Flag As Integer = 1
    Dim serverstring As String = "server=192.168.0.195;userid=vbuser;password=vbuser;Database=holtek;CharSet=utf8;"
    Dim SQLConnection As MySqlConnection = New MySqlConnection
    Dim Table_Count As Integer = 0       '資料總數
    Dim Flag_SQL_Number As Integer = 0
    Private myTcpClient As TcpClient
    Public Declare Function GetTickCount Lib "kernel32" () As Long
    '閘道器收
    Private Sub SerialPort1_DataReceived(ByVal sender As System.Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Me.Invoke(New EventHandler(AddressOf Recive))
    End Sub
    '啟動讀COM 資料庫連接
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        For j As Integer = 0 To My.Computer.Ports.SerialPortNames.Count - 1
            ComboBox1.Items.Add(My.Computer.Ports.SerialPortNames(j))
        Next

        SQL_Connection()
        Checkbox(6) = CheckBox6 : Checkbox(7) = CheckBox7 : Checkbox(8) = CheckBox8
        Label(1) = Label1 : Label(4) = Label4 : Label(5) = Label5
        Label(6) = Label6 : Label(9) = Label9 : Label(10) = Label10
        Label(11) = Label11 : Label(14) = Label14 : Label(15) = Label15
        'Timer9.Enabled = True
        For Each tabpg As TabPage In TabControl1.TabPages
            'MsgBox(tabpg.Name)
            If tabpg.Name.StartsWith("TabPage2") Then TabControl1.TabPages.Remove(tabpg)
        Next
    End Sub
    '資料庫連接副函式
    Private Sub SQL_Connection()
        SQLConnection.ConnectionString = serverstring
        Try
            If SQLConnection.State = ConnectionState.Closed Then
                SQLConnection.Open()
                MsgBox("Successfully Connected to MySQL Database.")
            End If
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try
    End Sub
    '資料庫連接副函式
    Public Sub SaveNames(ByRef aa As String)
        Dim cmd As MySqlCommand = New MySqlCommand
        With cmd
            .CommandText = aa
            .CommandType = CommandType.Text
            .Connection = SQLConnection
            .ExecuteNonQuery()
        End With
    End Sub
    '寫進資料表接副函式
    Public Sub save_P()
        If Label56.Text <> Nothing And Label57.Text <> Nothing And Label42.Text <> Nothing And Label4.Text <> Nothing And Label9.Text <> Nothing And Label14.Text <> Nothing Then
            Dim SQLStatement As String = "INSERT INTO holtek_power (DateTime,meter1,meter2,meter3,mA,mB) VALUES('" & Label98.Text & "','" & Label4.Text & " ','" & Label9.Text & " ','" & Label14.Text & " ','" & Label79.Text & " ','" & Label81.Text & " ')"
            SaveNames(SQLStatement)
        End If
        'Label5.Text = Nothing
        'Label7.Text = Nothing
        'Label8.Text = Nothing
    End Sub
    '收資料
    Private Sub Recive()
        Threading.Thread.Sleep(17)
        Rx_Number = 0
        While SerialPort1.BytesToRead
            Rx_Number += 1
            Rx_Buf(Rx_Number) = SerialPort1.ReadByte
        End While

        For A = 1 To 3
            If Rx_Buf(1) = &H1F And Rx_Buf(2) = &H0 + A Then
                EA100()
            End If
        Next

        If Rx_Buf(5) = &HC Then
            Rx_Status()
        End If
        If Rx_Buf(1) = &H1 And Rx_Buf(2) = &H7 Then
            Rx_Status1()
        End If
        If Rx_Buf(1) = &H1 And Rx_Buf(2) = &H8 Then
            Rx_Status2()
        End If
    End Sub

    'EA100副函式
    Private Sub EA100()
        Try


            For A = 5 To 7
                If Rx_Buf(1) = &H1F And Rx_Buf(2) = &H1 + A - 1 - 4 Then
                    MeterRt(A + 1) = 0

                    If Chr(Rx_Buf(3)) & Chr(Rx_Buf(4)) = "PO" Then

                        If A = 5 Then
                            Label1.Text = Chr(Rx_Buf(9)) & Chr(Rx_Buf(10))
                        ElseIf A = 6 Then
                            Label6.Text = Chr(Rx_Buf(9)) & Chr(Rx_Buf(10))
                        Else
                            Label11.Text = Chr(Rx_Buf(9)) & Chr(Rx_Buf(10))
                        End If


                        Checkbox(A + 1).ForeColor = Color.Green
                    End If
                    If Chr(Rx_Buf(4)) & Chr(Rx_Buf(5)) = "P:" And Checkbox(A + 1).ForeColor = Color.Green Then
                        Label(A + 4).Text = Chr(Rx_Buf(6)) & Chr(Rx_Buf(7)) & Chr(Rx_Buf(8)) & Chr(Rx_Buf(9)) & Chr(Rx_Buf(10)) & Chr(Rx_Buf(11)) & Chr(Rx_Buf(12))

                    End If

                End If
            Next
        Catch ex As Exception

        End Try


    End Sub
    'EA100狀態輪詢 問完即關閉並啟動Timer2
    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick

        Device += 1


        If Checkbox(Device + 5).Checked = True Then
            d1 = &H31
        ElseIf Checkbox(Device + 5).Checked = False Then
            d1 = &H32
        End If
        For B = 1 To 2
            If Device = B Then
                Tx_Buf(1) = &H1F
                Tx_Buf(2) = B
                Tx_Buf(3) = 0
                Tx_Buf(4) = 0
                Tx_Buf(5) = d1

                SerialPort1.Write(Tx_Buf, 1, 5)
            End If
        Next
        If Device = 3 Then
            Device = 1
            Timer1.Enabled = False
            Timer12.Enabled = True
        End If

    End Sub

    '時間
    Private Sub Timer3_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer3.Tick
        Label56.Text = DateString
        Label57.Text = TimeString
        Label98.Text = DateString & " " & TimeString
        Label62.Text = Label1.Text & Label44.Text & Label6.Text & Label43.Text & Label11.Text & Label40.Text & Label48.Text
    End Sub
    '上傳至資料庫
    Private Sub Timer4_Tick_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer4.Tick
        If Label4.Text <> Nothing And Label9.Text <> Nothing And Label14.Text <> Nothing And Label42.Text <> Nothing Then
            save_P()
        End If
    End Sub
    '電表總耗電量
    Private Sub Timer5_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer5.Tick
        ' If Label4.Text <> Nothing And Label9.Text <> Nothing And Label14.Text <> Nothing Then
        Try


            Label42.Text = (Mid(Label4.Text, 1, 6) * 1 + Mid(Label9.Text, 1, 6) * 1 + Mid(Label14.Text, 1, 6) * 1)
            Label18.Text = (Mid(Label4.Text, 1, 6) * 1 + Mid(Label9.Text, 1, 6) * 1 + Mid(Label14.Text, 1, 6) * 1)
            'End If
        Catch ex As Exception

        End Try
    End Sub
    '開啟閘道器

    '更新資料
    Public Sub Data1()
        Dim cmd = New MySqlCommand("Select * from holtek_switch ", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With

        If TABLE.Rows(0)(4).ToString() = "1" Then
            If TABLE.Rows(0)(1).ToString() = "1" Then
                CheckBox6.Checked = True
            ElseIf TABLE.Rows(0)(1).ToString() = "2" Then
                CheckBox6.Checked = False
            End If
            If TABLE.Rows(0)(2).ToString() = "1" Then
                CheckBox7.Checked = True
            ElseIf TABLE.Rows(0)(2).ToString() = "2" Then
                CheckBox7.Checked = False
            End If
            If TABLE.Rows(0)(3).ToString() = "1" Then
                CheckBox8.Checked = True
            ElseIf TABLE.Rows(0)(3).ToString() = "2" Then
                CheckBox8.Checked = False
            End If
            Data()
        End If
    End Sub
    Public Sub Light()
        Dim cmd = New MySqlCommand("Select * from b217_0724_switch ", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With

        If TABLE.Rows(0)(5).ToString() = "1" Then
            If TABLE.Rows(0)(1).ToString() = "1" Then
                AO()
            ElseIf TABLE.Rows(0)(1).ToString() = "2" Then
                AC()
            End If
            If TABLE.Rows(0)(2).ToString() = "1" Then
                BO()
            ElseIf TABLE.Rows(0)(2).ToString() = "2" Then
                BC()
            End If
            If TABLE.Rows(0)(3).ToString() = "1" Then
                AH()
            ElseIf TABLE.Rows(0)(3).ToString() = "2" Then
                AL()
            End If
            If TABLE.Rows(0)(4).ToString() = "1" Then
                BH()
            ElseIf TABLE.Rows(0)(4).ToString() = "2" Then
                BL()
            End If
            Light2()
        End If
    End Sub
    Private Sub Timer6_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer6.Tick
        Data1()
        Light()
        scheduling()
        'all()
    End Sub
    Private Sub Data()
        Dim SQLStatement As String = "UPDATE holtek_switch SET meter1='',meter2='',meter3='',ch='0'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Light2()
        Dim SQLStatement As String = "UPDATE b217_0724_switch SET Switch='',Switch2='',Aduty='',Bduty='',ch='0'"
        SaveNames(SQLStatement)
    End Sub

    Public Sub DG()
        Tx_Buf(1) = &H1F
        Tx_Buf(2) = &H6
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H0
        Tx_Buf(5) = &H31

        SerialPort1.Write(Tx_Buf, 1, 5)
    End Sub
    Public Sub DH()
        Tx_Buf(1) = &H1F
        Tx_Buf(2) = &H6
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H0
        Tx_Buf(5) = &H32

        SerialPort1.Write(Tx_Buf, 1, 5)
    End Sub
    Public Sub DI()
        Tx_Buf(1) = &H1F
        Tx_Buf(2) = &H7
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H0
        Tx_Buf(5) = &H31

        SerialPort1.Write(Tx_Buf, 1, 5)
    End Sub
    Public Sub DJ()
        Tx_Buf(1) = &H1F
        Tx_Buf(2) = &H7
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H0
        Tx_Buf(5) = &H32

        SerialPort1.Write(Tx_Buf, 1, 5)
    End Sub
    Public Sub DK()
        Tx_Buf(1) = &H1F
        Tx_Buf(2) = &H8
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H0
        Tx_Buf(5) = &H31

        SerialPort1.Write(Tx_Buf, 1, 5)
    End Sub
    Public Sub DL()
        Tx_Buf(1) = &H1F
        Tx_Buf(2) = &H8
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H0
        Tx_Buf(5) = &H32

        SerialPort1.Write(Tx_Buf, 1, 5)
    End Sub

    Private Sub PA33V()
        Tx_Buf(1) = &HBA
        Tx_Buf(2) = &H3
        Tx_Buf(3) = &H1
        Tx_Buf(4) = &H4
        Tx_Buf(5) = &H11
        Tx_Buf(6) = &H0
        Tx_Buf(7) = &H0
        Tx_Buf(8) = &H6
        Tx_Buf(9) = &H75
        Tx_Buf(10) = &H34

        SerialPort1.Write(Tx_Buf, 1, 10)
    End Sub

    Public Function IEEE754Trn(ByVal Data1 As Integer, ByVal Data2 As Integer, ByVal Data3 As Integer, ByVal Data4 As Integer)
        Dim S = 1
        Dim E = 0
        Dim M As Double = 0
        Dim Val As Double = 0

        If (Data1 And 256) Then
            S = -1
        End If

        E = (Data1 << 1)
        E += (Data2 >> 7)
        M = ((Data2 And 127) << 16) + ((Data3 And 255) << 8) + (Data4)

        Val = S * (2 ^ (E - 127)) * (1 + (M / 2 ^ 23))

        Return Val
    End Function

    Public Sub Rx_Status()
        'Label43.Text = IEEE754Trn(Rx_Buf(8), Rx_Buf(9), Rx_Buf(6), Rx_Buf(7))
        'Label44.Text = IEEE754Trn(Rx_Buf(12), Rx_Buf(13), Rx_Buf(10), Rx_Buf(11))
        'Label45.Text = IEEE754Trn(Rx_Buf(16), Rx_Buf(17), Rx_Buf(14), Rx_Buf(15))
    End Sub

    Public Sub scheduling()
        Dim cmd = New MySqlCommand("SELECT * FROM scheduling ORDER BY Date,Time ", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With


        Try
            If TABLE.Rows(0)(0).ToString() = Label56.Text And TABLE.Rows(0)(1).ToString() = Label57.Text Then

                If TABLE.Rows(0)(2).ToString() = "1號電表" And TABLE.Rows(0)(3).ToString() = "開" Then
                    'DG()
                    Link4()
                End If
                If TABLE.Rows(0)(2).ToString() = "1號電表" And TABLE.Rows(0)(3).ToString() = "關" Then
                    'DH()
                    Link1()
                End If
                If TABLE.Rows(0)(2).ToString() = "2號電表" And TABLE.Rows(0)(3).ToString() = "開" Then
                    'DI()
                    Link5()
                End If
                If TABLE.Rows(0)(2).ToString() = "2號電表" And TABLE.Rows(0)(3).ToString() = "關" Then
                    'DJ()
                    Link2()
                End If
                If TABLE.Rows(0)(2).ToString() = "3號電表" And TABLE.Rows(0)(3).ToString() = "開" Then
                    'DK()
                    Link6()
                End If
                If TABLE.Rows(0)(2).ToString() = "3號電表" And TABLE.Rows(0)(3).ToString() = "關" Then
                    'DL()
                    Link3()
                End If
                '//////燈光
                If TABLE.Rows(0)(2).ToString() = "A區燈光" And TABLE.Rows(0)(3).ToString() = "開" Then
                    AO()
                End If
                If TABLE.Rows(0)(2).ToString() = "A區燈光" And TABLE.Rows(0)(3).ToString() = "關" Then
                    AC()
                End If
                If TABLE.Rows(0)(2).ToString() = "A區燈光" And TABLE.Rows(0)(3).ToString() = "高照度" Then
                    AH()
                End If
                If TABLE.Rows(0)(2).ToString() = "A區燈光" And TABLE.Rows(0)(3).ToString() = "低照度" Then
                    AL()
                End If
                If TABLE.Rows(0)(2).ToString() = "B區燈光" And TABLE.Rows(0)(3).ToString() = "開" Then
                    BO()
                End If
                If TABLE.Rows(0)(2).ToString() = "B區燈光" And TABLE.Rows(0)(3).ToString() = "關" Then
                    BC()
                End If
                If TABLE.Rows(0)(2).ToString() = "B區燈光" And TABLE.Rows(0)(3).ToString() = "高照度" Then
                    BH()
                End If
                If TABLE.Rows(0)(2).ToString() = "B區燈光" And TABLE.Rows(0)(3).ToString() = "低照度" Then
                    BL()
                End If


                scheduling2()
            End If
        Catch ex As Exception

        End Try

    End Sub
    Public Sub AO()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H2
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H18
        Tx_Buf(5) = &H1
        Tx_Buf(6) = &H0
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub
    Public Sub AC()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H2
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H18
        Tx_Buf(5) = &H1
        Tx_Buf(6) = &H1
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub
    Public Sub AH()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H2
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &HC
        Tx_Buf(5) = &HA
        Tx_Buf(6) = &H64
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub
    Public Sub AL()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H2
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &HC
        Tx_Buf(5) = &HA
        Tx_Buf(6) = &H1E
        SerialPort1.Write(Tx_Buf, 1, 6)

    End Sub
    Public Sub BO()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H3
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H18
        Tx_Buf(5) = &H1
        Tx_Buf(6) = &H0
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub
    Public Sub BC()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H3
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &H18
        Tx_Buf(5) = &H1
        Tx_Buf(6) = &H1
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub
    Public Sub BH()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H3
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &HC
        Tx_Buf(5) = &HA
        Tx_Buf(6) = &H64
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub
    Public Sub BL()
        Tx_Buf(1) = &H1
        Tx_Buf(2) = &H3
        Tx_Buf(3) = &H0
        Tx_Buf(4) = &HC
        Tx_Buf(5) = &HA
        Tx_Buf(6) = &H1E
        SerialPort1.Write(Tx_Buf, 1, 6)
    End Sub

    Private Sub scheduling2()
        Dim SQLStatement As String = "DELETE FROM scheduling WHERE Time='" & Label57.Text & "'"
        SaveNames(SQLStatement)
    End Sub

    Private Sub Uninstall()
        Dim cmd = New MySqlCommand("SELECT * FROM uninstall", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With

        Label12.Text = TABLE.Rows(0)(1).ToString()
        Label13.Text = TABLE.Rows(0)(2).ToString()
        Label16.Text = TABLE.Rows(0)(3).ToString()

    End Sub

    Private Sub Timer2_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer2.Tick
        Uninstall()
    End Sub

    Private Sub Timer7_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer7.Tick
        Try
            If Label42.Text > Val(Label17.Text) And Mid(Label12.Text, 1, 1) = 1 Then
                Label19.Text = Label18.Text - (Mid(Label4.Text, 1, 6))
                Link1()
                If Label19.Text > Val(Label17.Text) And Mid(Label13.Text, 1, 1) = 2 Then
                    Label19.Text = Label18.Text - (Mid(Label9.Text, 1, 6))
                    Link2()
                    If Label19.Text > Val(Label17.Text) And Mid(Label16.Text, 1, 1) = 3 Then
                        Label19.Text = Label18.Text - (Mid(Label14.Text, 1, 6))
                        Link3()
                    End If

                ElseIf Label19.Text > Val(Label17.Text) And Mid(Label13.Text, 1, 1) = 3 Then
                    Link3()
                    Label19.Text = Label18.Text - (Mid(Label14.Text, 1, 6))
                    If Label19.Text > Val(Label17.Text) And Mid(Label16.Text, 1, 1) = 2 Then
                        Link2()
                        Label19.Text = Label18.Text - (Mid(Label9.Text, 1, 6))
                    End If
                End If

            ElseIf Label42.Text > Val(Label17.Text) And Mid(Label12.Text, 1, 1) = 2 Then
                Label19.Text = Label18.Text - (Mid(Label9.Text, 1, 6))
                Link2()
                If Label19.Text > Val(Label17.Text) And Mid(Label13.Text, 1, 1) = 1 Then
                    Label19.Text = Label18.Text - (Mid(Label4.Text, 1, 6))
                    Link1()
                    If Label19.Text > Val(Label17.Text) And Mid(Label16.Text, 1, 1) = 3 Then
                        Label19.Text = Label18.Text - (Mid(Label14.Text, 1, 6))
                        Link3()
                    End If
                ElseIf Label19.Text > Val(Label17.Text) And Mid(Label13.Text, 1, 1) = 3 Then
                    Label19.Text = Label18.Text - (Mid(Label14.Text, 1, 6))
                    Link3()
                    If Label42.Text > Val(Label17.Text) And Mid(Label16.Text, 1, 1) = 1 Then
                        Label19.Text = Label18.Text - (Mid(Label4.Text, 1, 6))
                        Link1()
                    End If
                End If
            ElseIf Label42.Text > Val(Label17.Text) And Mid(Label12.Text, 1, 1) = 3 Then
                Label19.Text = Label18.Text - (Mid(Label14.Text, 1, 6))
                Link3()
                If Label19.Text > Val(Label17.Text) And Mid(Label13.Text, 1, 1) = 1 Then
                    Label19.Text = Label18.Text - (Mid(Label4.Text, 1, 6))
                    Link1()
                    If Label19.Text > Val(Label17.Text) And Mid(Label16.Text, 1, 1) = 2 Then
                        Label19.Text = Label18.Text - (Mid(Label9.Text, 1, 6))
                        Link2()
                    End If
                ElseIf Label19.Text > Val(Label17.Text) And Mid(Label13.Text, 1, 1) = 2 Then
                    Label19.Text = Label18.Text - (Mid(Label9.Text, 1, 6))
                    Link2()
                    If Label19.Text > Val(Label17.Text) And Mid(Label16.Text, 1, 1) = 1 Then
                        Label19.Text = Label18.Text - (Mid(Label4.Text, 1, 6))
                        Link1()
                    End If
                End If

            End If
        Catch ex As Exception

        End Try

       

    End Sub
    Private Sub switch1()
        Dim cmd = New MySqlCommand("SELECT * FROM holtek_switch1", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With
        Label39.Text = TABLE.Rows(0)(1).ToString()
        If TABLE.Rows(0)(2).ToString() = "1" Then
            CheckBox6.Checked = True

            Label24.Text = Val(Label24.Text) + Val(Mid(Label4.Text, 1, 6))
            If CheckBox6.Checked = False Then
                Link1()
            End If
        End If
        If TABLE.Rows(0)(2).ToString() = "2" Then
            CheckBox6.Checked = False

            Label22.Text = Val(Label24.Text / 3600)

            If Label22.Text <> "0" Then
                holtek_switchW1()
            End If

            holtek_switch1()
            Label22.Text = "0"
            Label47.Text = "0"
            Label24.Text = "0"
            Label29.Text = "0"
        End If
    End Sub

    Private Sub switch2()
        Dim cmd = New MySqlCommand("SELECT * FROM holtek_switch2", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With
        Label37.Text = TABLE.Rows(0)(1).ToString()
        If TABLE.Rows(0)(2).ToString() = "1" Then
            CheckBox7.Checked = True

            Label27.Text = Val(Label27.Text) + Val(Mid(Label9.Text, 1, 6))
            If CheckBox7.Checked = False Then
                Link2()
            End If
        End If
        If TABLE.Rows(0)(2).ToString() = "2" Then
            CheckBox7.Checked = False


            Label25.Text = Val(Label27.Text / 3600)

            If Label25.Text <> "0" Then
                holtek_switchW2()
            End If

            holtek_switch2()
            Label25.Text = "0"
            Label46.Text = "0"
            Label27.Text = "0"
            Label32.Text = "0"
        End If
    End Sub

    Private Sub switch3()
        Dim cmd = New MySqlCommand("SELECT * FROM holtek_switch3", SQLConnection)
        Dim SQLAdapter As New MySqlDataAdapter
        Dim TABLE As New DataTable
        With SQLAdapter
            .SelectCommand = cmd
            .Fill(TABLE)
        End With
        Label38.Text = TABLE.Rows(0)(1).ToString()
        If TABLE.Rows(0)(2).ToString() = "1" Then
            CheckBox8.Checked = True

            Label30.Text = Val(Label30.Text) + Val(Mid(Label14.Text, 1, 6))
            If CheckBox8.Checked = False Then
                Link3()
            End If
        End If
        If TABLE.Rows(0)(2).ToString() = "2" Then
            CheckBox8.Checked = False



            Label31.Text = Val(Label30.Text / 3600)

            If Label31.Text <> "0" Then
                holtek_switchW3()
            End If

            holtek_switch3()
            Label47.Text = "0"
            Label30.Text = "0"
            Label31.Text = "0"
            Label33.Text = "0"
        End If
    End Sub

    Private Sub holtek_switch1()
        Dim SQLStatement As String = "UPDATE holtek_switch1 SET homeappliance1='3'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub holtek_switch2()
        Dim SQLStatement As String = "UPDATE holtek_switch2 SET homeappliance2='3'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub holtek_switch3()
        Dim SQLStatement As String = "UPDATE holtek_switch3 SET homeappliance3='3'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub holtek_switchW1()
        Dim time, h, m, s As Integer
        time = Int(DateDiff(DateInterval.Second, CDate(Label39.Text), CDate(Label57.Text)))
        h = Int(time / 3600)
        m = Int((time - h * 3600) / 60)
        s = time - h * 3600 - m * 60

        If h < 10 And m < 10 And s < 10 Then
            Label23.Text = ("0" & h & ":" & "0" & m & ":" & "0" & s)
        ElseIf h < 10 And m < 10 And s >= 10 Then
            Label23.Text = ("0" & h & ":" & "0" & m & ":" & s)
        ElseIf h < 10 And m >= 10 And s < 10 Then
            Label23.Text = ("0" & h & ":" & m & ":" & "0" & s)
        ElseIf h < 10 And m >= 10 And s >= 10 Then
            Label23.Text = ("0" & h & ":" & m & ":" & s)
        ElseIf h >= 10 And m < 10 And s < 10 Then
            Label23.Text = (h & ":" & "0" & m & ":" & "0" & s)
        ElseIf h >= 10 And m < 10 And s >= 10 Then
            Label23.Text = (h & ":" & "0" & m & ":" & s)
        ElseIf h >= 10 And m >= 10 And s < 10 Then
            Label23.Text = (h & ":" & m & ":" & "0" & s)
        ElseIf h >= 10 And m >= 10 And s >= 10 Then
            Label23.Text = (h & ":" & m & ":" & s)
        End If
        Dim SQLStatement As String = "INSERT INTO holtek_power1 (Date,Time,Time1,Time2,homeappliance1,P) VALUES('" & Label56.Text & "','" & Label39.Text & "','" & Label57.Text & "','" & Label23.Text & "','" & Mid(Label44.Text, 1, 6) & "度" & "','" & Mid(Label5.Text, 1, 3) & "元" & "')"
        SaveNames(SQLStatement)
    End Sub
    Private Sub holtek_switchW2()
        Dim time, h, m, s As Integer
        time = Int(DateDiff(DateInterval.Second, CDate(Label37.Text), CDate(Label57.Text)))
        h = Int(time / 3600)
        m = Int((time - h * 3600) / 60)
        s = time - h * 3600 - m * 60

        If h < 10 And m < 10 And s < 10 Then
            Label26.Text = ("0" & h & ":" & "0" & m & ":" & "0" & s)
        ElseIf h < 10 And m < 10 And s >= 10 Then
            Label26.Text = ("0" & h & ":" & "0" & m & ":" & s)
        ElseIf h < 10 And m >= 10 And s < 10 Then
            Label26.Text = ("0" & h & ":" & m & ":" & "0" & s)
        ElseIf h < 10 And m >= 10 And s >= 10 Then
            Label26.Text = ("0" & h & ":" & m & ":" & s)
        ElseIf h >= 10 And m < 10 And s < 10 Then
            Label26.Text = (h & ":" & "0" & m & ":" & "0" & s)
        ElseIf h >= 10 And m < 10 And s >= 10 Then
            Label26.Text = (h & ":" & "0" & m & ":" & s)
        ElseIf h >= 10 And m >= 10 And s < 10 Then
            Label26.Text = (h & ":" & m & ":" & "0" & s)
        ElseIf h >= 10 And m >= 10 And s >= 10 Then
            Label26.Text = (h & ":" & m & ":" & s)
        End If
        Dim SQLStatement As String = "INSERT INTO holtek_power2 (Date,Time,Time1,Time2,homeappliance2,P) VALUES('" & Label56.Text & "','" & Label37.Text & "','" & Label57.Text & "','" & Label26.Text & "' ,'" & Mid(Label43.Text, 1, 6) & "度" & "','" & Mid(Label10.Text, 1, 3) & "元" & "')"
        SaveNames(SQLStatement)
    End Sub
    Private Sub holtek_switchW3()
        Dim time, h, m, s As Integer
        time = Int(DateDiff(DateInterval.Second, CDate(Label38.Text), CDate(Label57.Text)))
        h = Int(time / 3600)
        m = Int((time - h * 3600) / 60)
        s = time - h * 3600 - m * 60

        If h < 10 And m < 10 And s < 10 Then
            Label28.Text = ("0" & h & ":" & "0" & m & ":" & "0" & s)
        ElseIf h < 10 And m < 10 And s >= 10 Then
            Label28.Text = ("0" & h & ":" & "0" & m & ":" & s)
        ElseIf h < 10 And m >= 10 And s < 10 Then
            Label28.Text = ("0" & h & ":" & m & ":" & "0" & s)
        ElseIf h < 10 And m >= 10 And s >= 10 Then
            Label28.Text = ("0" & h & ":" & m & ":" & s)
        ElseIf h >= 10 And m < 10 And s < 10 Then
            Label28.Text = (h & ":" & "0" & m & ":" & "0" & s)
        ElseIf h >= 10 And m < 10 And s >= 10 Then
            Label28.Text = (h & ":" & "0" & m & ":" & s)
        ElseIf h >= 10 And m >= 10 And s < 10 Then
            Label28.Text = (h & ":" & m & ":" & "0" & s)
        ElseIf h >= 10 And m >= 10 And s >= 10 Then
            Label28.Text = (h & ":" & m & ":" & s)
        End If
        Dim SQLStatement As String = "INSERT INTO holtek_power3 (Date,Time,Time1,Time2,homeappliance3,P) VALUES('" & Label56.Text & "','" & Label38.Text & "','" & Label57.Text & "','" & Label28.Text & "', '" & Mid(Label40.Text, 1, 6) & "度" & "','" & Mid(Label15.Text, 1, 3) & "元" & "')"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Timer8_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer8.Tick
        switch1()
        switch2()
        switch3()
        all()
    End Sub

    Private Sub Link1()
        Dim SQLStatement As String = "UPDATE holtek_switch1 SET homeappliance1='2'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Link2()
        Dim SQLStatement As String = "UPDATE holtek_switch2 SET homeappliance2='2'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Link3()
        Dim SQLStatement As String = "UPDATE holtek_switch3 SET homeappliance3='2'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Link4()
        Dim SQLStatement As String = "UPDATE holtek_switch1 SET homeappliance1='1'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Link5()
        Dim SQLStatement As String = "UPDATE holtek_switch2 SET homeappliance2='1'"
        SaveNames(SQLStatement)
    End Sub
    Private Sub Link6()
        Dim SQLStatement As String = "UPDATE holtek_switch3 SET homeappliance3='1'"
        SaveNames(SQLStatement)
    End Sub

    Private Sub Timer9_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer9.Tick

        Label47.Text = Val(Label47.Text) + Val(Label4.Text)

        Label46.Text = Val(Label46.Text) + Val(Label9.Text)

        Label45.Text = Val(Label45.Text) + Val(Label14.Text)

        Label86.Text = Val(Label86.Text) + Val(Label79.Text)

        Label85.Text = Val(Label85.Text) + Val(Label81.Text)

    End Sub



    Private Sub Timer10_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer10.Tick
        Dim d, f, g, h, i As Decimal
        d = (Val(Label47.Text) / 3600000)
        f = (Val(Label46.Text) / 3600000)
        g = (Val(Label45.Text) / 3600000)
        h = (Val(Label86.Text) / 3600000)
        i = (Val(Label85.Text) / 3600000)
        Dim Y As Double = Math.Round(d, 4)
        Dim J As Double = Math.Round(f, 4)
        Dim K As Double = Math.Round(g, 4)
        Dim L As Double = Math.Round(h, 4)
        Dim M As Double = Math.Round(i, 4)


        Label44.Text = Y
        Label43.Text = J
        Label40.Text = K
        Label67.Text = L
        Label72.Text = M

        If Y * 2.1 >= 0.1 Then
            Label5.Text = Mid(Y * 2.1, 1, 3)
        End If
        If J * 2.1 >= 0.1 Then
            Label10.Text = Mid(J * 2.1, 1, 3)
        End If
        If K * 2.1 >= 0.1 Then
            Label15.Text = Mid(K * 2.1, 1, 3)
        End If
        Label48.Text = Y + J + K

        If L * 2.1 >= 0.1 Then
            Label68.Text = Mid(L * 2.1, 1, 3)
        End If
        If M * 2.1 >= 0.1 Then
            Label71.Text = Mid(M * 2.1, 1, 3)
        End If
        Label88.Text = L + M


        Label61.Text = Val(Mid(Label48.Text, 1, 5))
        If Val(Label61.Text) < 120 Then
            Label60.Text = Val(Mid(Y * 2.1, 1, 3)) + Val(Mid(J * 2.1, 1, 3)) + Val(Mid(K * 2.1, 1, 3))
            Label87.Text = Val(Mid(L * 2.1, 1, 3)) + Val(Mid(M * 2.1, 1, 3))
        ElseIf Val(Label61.Text) > 120 And Val(Label61.Text) < 330 Then
            Label60.Text = Val(Mid(Y * 2.68, 1, 3)) + Val(Mid(J * 2.68, 1, 3)) + Val(Mid(K * 2.68, 1, 3))
            Label87.Text = Val(Mid(L * 2.68, 1, 3)) + Val(Mid(M * 2.68, 1, 3))
        ElseIf Val(Label61.Text) > 330 And Val(Label61.Text) < 500 Then
            Label60.Text = Val(Mid(Y * 3.61, 1, 3)) + Val(Mid(J * 3.61, 1, 3)) + Val(Mid(K * 3.61, 1, 3))
            Label87.Text = Val(Mid(L * 3.61, 1, 3)) + Val(Mid(M * 3.61, 1, 3))
        ElseIf Val(Label61.Text) > 501 And Val(Label61.Text) < 700 Then
            Label60.Text = Val(Mid(Y * 4.48, 1, 3)) + Val(Mid(J * 4.48, 1, 3)) + Val(Mid(K * 4.48, 1, 3))
            Label87.Text = Val(Mid(L * 4.48, 1, 3)) + Val(Mid(M * 4.48, 1, 3))
        ElseIf Val(Label61.Text) > 701 And Val(Label61.Text) < 1000 Then
            Label60.Text = Val(Mid(Y * 5.03, 1, 3)) + Val(Mid(J * 5.03, 1, 3)) + Val(Mid(K * 5.03, 1, 3))
            Label87.Text = Val(Mid(L * 5.03, 1, 3)) + Val(Mid(M * 5.03, 1, 3))
        ElseIf Val(Label61.Text) > 1000 Then
            Label60.Text = Val(Mid(Y * 5.28, 1, 3)) + Val(Mid(J * 5.28, 1, 3)) + Val(Mid(K * 5.28, 1, 3))
            Label87.Text = Val(Mid(L * 5.28, 1, 3)) + Val(Mid(M * 5.28, 1, 3))
        End If
    End Sub



    Private Sub Timer11_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer11.Tick
        If CheckBox6.Checked = False And Val(Mid(Label4.Text, 1.7)) = 0 Then
            Label47.Text = "0"
        End If
        If CheckBox7.Checked = False And Val(Mid(Label9.Text, 1.7)) = 0 Then
            Label46.Text = "0"
        End If
        If CheckBox8.Checked = False And Val(Mid(Label14.Text, 1.7)) = 0 Then
            Label45.Text = "0"
        End If

    End Sub

    Private Sub Timer12_Tick(sender As Object, e As EventArgs) Handles Timer12.Tick
        Device1 += 1
        For C = 2 To 3
            If Device1 = C Then
                Tx_Buf(1) = &H1
                Tx_Buf(2) = C
                Tx_Buf(3) = &H1
                Tx_Buf(4) = &H1
                Tx_Buf(5) = &H7F

                SerialPort1.Write(Tx_Buf, 1, 5)
            End If
        Next
        If Device1 = 4 Then
            Device1 = 1
            Timer12.Enabled = False
            Timer1.Enabled = True
        End If
    End Sub
    Public Sub Rx_Status1()

        If Rx_Buf(19) <> 0 Then
            Label66.Text = "ON"
            Label79.Text = Rx_Buf(19)
            Label80.Text = Rx_Buf(17) & Chr(37)
        Else
            Label66.Text = "OFF"
            Label79.Text = Rx_Buf(19)
            Label80.Text = "0" & Chr(37)
        End If
    End Sub
    Public Sub Rx_Status2()

        If Rx_Buf(19) <> 0 Then
            Label73.Text = "ON"
            Label81.Text = Rx_Buf(19)
            Label82.Text = Rx_Buf(17) & Chr(37)
        Else
            Label73.Text = "OFF"
            Label81.Text = Rx_Buf(19)
            Label82.Text = "0" & Chr(37)
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If (ComboBox1.Text <> "") Then
            If (Link_switch = 0) Then
                Link_switch = 1
                Button1.BackColor = Color.White
                Button1.ForeColor = Color.Black
                Button1.Text = "啟動"
                SerialPort1.PortName = ComboBox1.Text
                SerialPort1.Open()
                Timer1.Enabled = True

                Timer4.Enabled = True
                Timer5.Enabled = True
                Timer6.Enabled = True
                Timer7.Enabled = True
                Timer8.Enabled = True
                Timer9.Enabled = True
                Timer10.Enabled = True

            ElseIf (Link_switch = 1) Then
                Link_switch = 0
                Button1.BackColor = Color.LightSalmon   '淺橙紅
                Button1.ForeColor = Color.White   '白色
                Button1.Text = "關閉"
                SerialPort1.Close()
                Reset()
                Timer1.Enabled = False

                Timer4.Enabled = False
                Timer5.Enabled = False
                Timer6.Enabled = False
                Timer7.Enabled = False
                Timer9.Enabled = False
                Timer10.Enabled = False
                Timer12.Enabled = False
            End If
        End If
    End Sub
    Private Sub all()
        Dim SQLStatement As String = "UPDATE power SET m1='" & Label4.Text & "W" & "' ,m2='" & Label9.Text & "W" & "',m3='" & Label14.Text & "W" & "',mA='" & Label79.Text & "W" & "',mB='" & Label81.Text & "W" & "'"
        SaveNames(SQLStatement)
    End Sub

    Private Sub Label56_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Label56.Click

    End Sub

    Private Sub TabPage1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TabPage1.Click

    End Sub
End Class
