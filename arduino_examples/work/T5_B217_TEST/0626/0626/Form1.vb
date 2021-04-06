Public Class Form1
    Dim abc_data As String = ""
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        SerialPort1.Open()
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        abc_data = SerialPort1.ReadExisting
        If abc_data <> "" Then
            Label1.Text = ""
            For index = 1 To abc_data.Length
                Label1.Text &= Hex(Asc(Mid(abc_data, index, 1))) & " "

            Next
            If Mid(abc_data, 1, 1) = Chr(&H4C) Then
                If Mid(abc_data, 4, 1) = "L" Then
                    Label2.Text = Mid(abc_data, 2, 2)
                ElseIf Mid(abc_data, 3, 1) = "L" Then
                    Label2.Text = Mid(abc_data, 2, 1)
                Else
                    Label2.Text = Mid(abc_data, 2, 3)
                End If

            End If
        End If

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Timer1.Enabled = True

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Write("1")
        Label1.Text = 1
        Label2.Text = "開燈"
        PictureBox1.Image = My.Resources._1
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        SerialPort1.Write("2")
        Label1.Text = 2
        Label2.Text = "關燈"
        PictureBox1.Image = My.Resources._2
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        SerialPort1.Write("3")
        Label1.Text = 3
        Label2.Text = "光照度模式"
        PictureBox1.Image = My.Resources._2
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        SerialPort1.Write("4")
        Label1.Text = 4
        Label2.Text = "開窗"
        PictureBox2.Image = My.Resources._3

    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        SerialPort1.Write("5")
        Label1.Text = 5
        Label2.Text = "關窗"
        PictureBox2.Image = My.Resources._4
    End Sub




End Class

