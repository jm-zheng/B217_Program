Public Class Form1
    Dim ard_rx_data(127) As Byte
    Dim ard_rx_number As Integer
    Dim ard_tx_data(127) As Byte
    Dim RGB_tx_data(127) As Byte
    Dim drive As SQL_TypeDef = New SQL_TypeDef
    Dim count(6)() As String
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Label6.Text = DateString
        Label7.Text = TimeString
        MySQL_Init(drive, 5, "127.0.0.1", "root", "123456", "drive_bird")
        MySQL_Connection()
        Try
            For Each sp As String In My.Computer.Ports.SerialPortNames
                ComboBox1.Items.Add(sp)
            Next

        Catch ex As Exception

        End Try

    End Sub
    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        If SerialPort1.BytesToRead > 0 Then
            ard_rx_number += 1
            ard_rx_data(ard_rx_number) = SerialPort1.ReadByte
        ElseIf ard_rx_number > 0 Then
            Label1.Text = ""
            For index = 1 To ard_rx_number
                Label1.Text &= Hex(ard_rx_data(index)) & " "
            Next
            '------------------------------------------------------

            If ard_rx_data(1) = &H48 Then
                Label2.Text = Chr(ard_rx_data(6)) & Chr(ard_rx_data(7)) & "%"
            End If
            If ard_rx_data(8) = &H54 Then
                Label3.Text = Chr(ard_rx_data(13)) & Chr(ard_rx_data(14)) & "℃"
            End If
            If ard_rx_data(15) = &H53 And ard_rx_data(16) = &H54 Then
                Label8.Text = Chr(ard_rx_data(20)) & Chr(ard_rx_data(21)) & "℃"
            End If
            If ard_rx_data(22) = &H53 And ard_rx_data(23) = &H48 Then
                Label9.Text = Chr(ard_rx_data(27)) & Chr(ard_rx_data(28)) & "%"
            End If
            If ard_rx_data(5) = &H4E Then
                Label10.Text = "save"
                Label10.BackColor = Color.Green
                PictureBox1.Image = My.Resources.dangerous
            ElseIf ard_rx_data(5) = &H59 Then
                Label10.Text = "warning"
                Label10.BackColor = Color.Red
                PictureBox1.Image = My.Resources.警告燈
            End If

            '-----------------------------------------------------------

            Me.DataGridView1.Rows.Add(DateString, TimeString, Label2.Text, Label3.Text, Label9.Text, Label8.Text, Label10.Text)

            '------------------------------------------------------

            drive.Form = "record"
            drive.Column(1) = DataGridView1.Rows(0).Cells(2).Value
            drive.Column(2) = DataGridView1.Rows(0).Cells(3).Value
            drive.Column(3) = DataGridView1.Rows(0).Cells(4).Value
            drive.Column(4) = DataGridView1.Rows(0).Cells(5).Value
            drive.Column(5) = DataGridView1.Rows(0).Cells(6).Value
            MySQL_Add(drive, 5)

            '------------------------------------------------------
            ard_rx_number = 0
            End If

    End Sub
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            SerialPort1.PortName = ComboBox1.SelectedItem
            SerialPort1.Open()
            Timer1.Enabled = True
            MsgBox("Connect")
        Catch ex As Exception
            MsgBox("Error")
        End Try
    End Sub


End Class
