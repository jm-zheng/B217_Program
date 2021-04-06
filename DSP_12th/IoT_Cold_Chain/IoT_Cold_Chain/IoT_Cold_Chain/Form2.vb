Public Class Form2

    Private Sub GroupBox3_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GroupBox3.Enter

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        PictureBox1.Image = Form1.PictureBox1.Image
        Label5.Text = Form1.devno
        lb_Temp.Text = Form1.temp

        Dim temp_val = Val(Mid(lb_Temp.Text, 1, 1)) * 100 + Val(Mid(lb_Temp.Text, 2, 1)) * 10 + Val(Mid(lb_Temp.Text, 4, 1))
        If temp_val > TextBox1.Text * 10 Then
            Label3.Text = "溫度過高....."
            Label3.BackColor = Color.Red

        Else
            Label3.Text = "生鮮保持正常溫度....."
            Label3.BackColor = Color.LightBlue
        End If
        ' Dim lb_ls = Val(Mid(lb_ls.Text, 1, 1)) * 100 + Val(Mid(lb_ls.Text, 2, 1)) * 10 + Val(Mid(lb_ls.Text, 4, 1))
        If temp_val > TextBox1.Text * 10 Then
            Label3.Text = "溫度過高....."
            Label3.BackColor = Color.Red

        Else
            Label3.Text = "生鮮保持正常溫度....."
            Label3.BackColor = Color.LightBlue
        End If
        lb_LS.Text = Form1.ls
        Select Case Form1.gx
            Case "X"
                lb_3G_X.Text = "無法辨識狀態"
            Case "U"
                lb_3G_X.Text = "正常放置狀態"

            Case "D"
                lb_3G_X.Text = "反向態"
            Case "X"
                lb_3G_X.Text = "無法辨識狀態"
            Case "X"
                lb_3G_X.Text = "無法辨識狀態"
        End Select
    End Sub
End Class