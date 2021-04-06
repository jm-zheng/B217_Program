Public Class Form1
    Dim RXD$
    Dim temp As String
    Dim tvoc As String
    Dim humiduty As String
    Dim pm25 As String
    Dim co2 As String
    Dim stuts As String
    Dim position As String

    Dim t2_flag As Integer = 0

    '資料庫'
    Dim aqi_data As SQL_TypeDef = New SQL_TypeDef

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)

        Next
        MySQL_Init(aqi_data, 9, "120.109.168.233", "HIT", "", "air_device")
    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        SerialPort1.PortName = ComboBox1.Items(ComboBox1.SelectedIndex)


    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        RXD$ = SerialPort1.ReadExisting

        If RXD$ <> "" Then
            Label1.Text = ""
            For index = 1 To RXD$.Length
                Label1.Text &= Mid(RXD$, index, 1) & ""
            Next

            If Mid(RXD$, 1, 1) = "D" Then
                stuts = ""
                stuts = Mid(RXD$, 1, 5)
            End If
            If Mid(RXD$, 1, 1) = "p" Then
                pm25 = ""
                pm25 = Mid(RXD$, 3, 3)
            End If
            If Mid(RXD$, 1, 1) = "c" Then
                co2 = ""
                co2 = Mid(RXD$, 3, 4)
            End If
            If Mid(RXD$, 1, 1) = "T" Then
                tvoc = ""
                tvoc = Mid(RXD$, 3, 3)
            End If
            If Mid(RXD$, 1, 1) = "h" Then
                humiduty = ""
                humiduty = Mid(RXD$, 3, 5)
            End If
            If Mid(RXD$, 1, 1) = "t" Then
                temp = ""
                temp = Mid(RXD$, 3, 5)
            End If
            If Mid(RXD$, 1, 1) = "P" Then
                position = ""
                position = Mid(RXD$, 1, 5)
            End If

        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        SerialPort1.Open()
        Timer1.Enabled = True
        Timer2.Enabled = True
    End Sub

    Private Sub DataGridView1_CellContentClick(sender As Object, e As DataGridViewCellEventArgs)

    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick

        If t2_flag > 1 Then

            Me.DataGridView1.Rows.Add(DateString, TimeString, stuts, position, temp, humiduty, co2, tvoc, pm25)
            aqi_data.Form = "air_sensor"
            If DataGridView1.Rows.Count > 1 Then
                'DataGridView1.Rows.Count - 2  資料行數減-2
                aqi_data.Column(1) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(2).Value
                aqi_data.Column(2) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(3).Value
                aqi_data.Column(3) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(4).Value
                aqi_data.Column(4) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(5).Value
                aqi_data.Column(5) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(6).Value
                aqi_data.Column(6) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(7).Value
                aqi_data.Column(7) = DataGridView1.Rows(DataGridView1.Rows.Count - 2).Cells(8).Value
                MySQL_Add(aqi_data, 7)

            End If
        Else
            t2_flag += 1
        End If



    End Sub

    Private Sub DataGridView1_CellContentClick_1(sender As Object, e As DataGridViewCellEventArgs) Handles DataGridView1.CellContentClick

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Close()
        Timer1.Enabled = False
        Timer2.Enabled = False
    End Sub
End Class
