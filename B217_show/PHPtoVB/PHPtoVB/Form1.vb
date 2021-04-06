Public Class Form1
    Dim SQL As SQL_TypeDef = New SQL_TypeDef
    Dim Tx_Data(127) As Byte
    Dim Rx_Data(99999) As Byte
    Dim UartTimes = 0

    Dim Rx_Number As Integer = 1
    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
        Next
        If ComboBox1.Items.Count Then
            ComboBox1.Text = ComboBox1.Items.Item(0)
        End If

        ComboBox2.Text = ComboBox2.Items.Item(3)
        ComboBox3.Text = ComboBox3.Items.Item(0)
        ComboBox4.Text = ComboBox4.Items.Item(0)
        ComboBox5.Text = ComboBox5.Items.Item(0)
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Try
            MySQL_Init(SQL, 10, TextBox1.Text, TextBox2.Text, TextBox3.Text, TextBox4.Text)
            SQL.Form = TextBox5.Text
            MySQL_Connection()
            Timer1.Start()
        Catch ex As Exception
            ex.ToString()
        End Try
    End Sub

    Private Sub Timer1_Tick(sender As System.Object, e As System.EventArgs) Handles Timer1.Tick
        Try
            Dim dt As DataTable = New DataTable
            dt = MySQL_Retrieve(TextBox5.Text)
            If dt.Rows.Count > 0 Then
                Button1.Text = dt.Rows(0)(1)
                Dim str As String = dt.Rows(0)(1)
                ASCtoVal(str, Tx_Data)
                SQL.Form = TextBox5.Text
                MySQL_Delete(SQL, 1)
            End If

            If Tx_Data(0) > 0 Then
                UartPort.Write(Tx_Data, 1, Tx_Data(0)) '轉成16進制 A1 = 41 31  '
                'Button2.Text = ""
                'For index = 1 To Tx_Data(0)
                '    Button2.Text &= Hex(Tx_Data(index)) & " "
                'Next
                Tx_Data(0) = 0
            End If

        Catch ex As Exception

        End Try
        
    End Sub

    Private Sub ASCtoVal(ByVal str As String, ByVal val() As Byte)
        For index = 1 To str.Length Step 2
            val(index - (index - 1) / 2) = Int("&h" & Mid(str, index, 2))
            Tx_Data(0) = (index - (index - 1) / 2)
        Next
    End Sub

    Private Sub UARTButton_Click(sender As System.Object, e As System.EventArgs) Handles UARTButton.Click
        Try
            If UartTimes = 0 Then
                UartPort.PortName = ComboBox1.SelectedItem
                UartPort.BaudRate = ComboBox2.Text
                UartPort.DataBits = ComboBox3.Text
                UartPort.Parity = ComboBox4.SelectedIndex
                UartPort.StopBits = ComboBox5.Text
                UartPort.Open()
                UARTButton.Text = "Close"
                UartTimer.Enabled = True
                UartTimes = 1
            Else
                UartPort.Close()
                UartTimes = 0
                UARTButton.Text = "Open"
                UartTimer.Enabled = False
            End If
        Catch ex As Exception
            MsgBox(ex.ToString & Chr(10) & Chr(10) & "沒有此ComPort，或者啟動中")
        End Try
        
    End Sub

    Private Sub UartTimer_Tick(sender As System.Object, e As System.EventArgs) Handles UartTimer.Tick
        If UartPort.BytesToRead Then
            Rx_Data(Rx_Number) = UartPort.ReadByte
            Rx_Number += 1
        ElseIf Rx_Number > 1 Then
            'ODlabel.Text = ""
            For index As Integer = 1 To Rx_Number - 1
                'ODlabel.Text &= Hex(RxBuf(index)).PadLeft(2, "0") & " "
            Next

            Rx_Number = 1
        End If
    End Sub

    Private Sub TextBox1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox1.TextChanged

    End Sub
End Class
