Public Class Form5
    Public Property ThenForm1 As Object
    Dim asd(127) As String

    Private Sub Form5_Load(sender As Object, e As EventArgs) Handles MyBase.Load



        If Form1.turn1.Text = "旋轉中" Then
            PictureBox1.Image = My.Resources._04_直進旋轉
            Label1.BackColor = Color.Red
            Label1.Text = "運轉中"
            Label3.BackColor = Color.Red
        Else
            Label1.Text = "停止運轉"
            Label3.Text = "停止運轉"
        End If

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Form1.Show()
    End Sub
End Class