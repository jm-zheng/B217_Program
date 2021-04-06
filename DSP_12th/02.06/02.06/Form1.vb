Public Class Form1
    Dim abc_data As String = ""
    Dim qwe As SQL_TypeDef = New SQL_TypeDef

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        SerialPort1.Open()
        MySQL_Init(qwe, 5, "127.0.0.1", "root", " ", "bird_test")
        MySQL_Connection()
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        abc_data = SerialPort1.ReadExisting
        If abc_data <> "" Then
            Label1.Text = ""
            For index = 1 To abc_data.Length
                Label1.Text &= Hex(Asc(Mid(abc_data, index, 1))) & " "

            Next

            If Mid(abc_data, 1, 1) = Chr(&H48) Then
                Label3.Text = Mid(abc_data, 2, 2)
                If Mid(abc_data, 4, 1) = Chr(&H54) Then
                    Label5.Text = Mid(abc_data, 5, 2)
                    If Mid(abc_data, 7, 1) <> Chr(&H57) Then
                        Label6.Text = "安全"
                    Else
                        Label6.Text = "危險"
                    End If
                End If

            End If
            Me.DataGridView1.Rows.Add(Label3.Text, Label5.Text, Label6.Text, DateString, TimeString)
            qwe.Form = "test_1"
            qwe.Column("H") = DataGridView1.Rows(0).Cells(0).Value
            qwe.Column("T") = DataGridView1.Rows(0).Cells(1).Value
            qwe.Column("W") = DataGridView1.Rows(0).Cells(2).Value
            qwe.Column("y") = DataGridView1.Rows(0).Cells(3).Value
            qwe.Column("time") = DataGridView1.Rows(0).Cells(4).Value
            MySQL_Add(qwe, 5)
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Timer1.Enabled = True


    End Sub



    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Me.DataGridView1.Rows.Add(Label3.Text, Label5.Text, Label6.Text, DateString, TimeString)
    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick

    End Sub

    Private Sub DataGridView1_CellContentClick(sender As Object, e As DataGridViewCellEventArgs) Handles DataGridView1.CellContentClick

    End Sub
End Class
