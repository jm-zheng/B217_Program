Public Class Form6

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Form2.Show()
    End Sub

    Private Sub Form6_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer2.Interval = 5000 '設Timer1的時間間隔為1000毫秒，也就是1秒
        Timer2.Enabled = True '啟動Timer1
        If Form1.Label54.Text = "輪播中" Then
            Timer1.Interval = 10000 '設Timer1的時間間隔為1000毫秒，也就是1秒
            Timer1.Enabled = True '啟動Timer1
            Form3.Close()
            Form2.Close()
        End If




    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick

        Dim ecTEXT As Integer
        Dim evTEXT As Integer
        Dim etTEXT As Integer
        et.Text = Form1.et.Text
        eh.Text = Form1.eh.Text
        ec.Text = Form1.ec.Text
        ef.Text = Form1.ef.Text
        ev.Text = Form1.ev.Text
        el.Text = Form1.el.Text
        Me.DataGridView1.Rows.Add(et.Text, eh.Text, ec.Text, ef.Text, ev.Text, el.Text)
        Try
            ecTEXT = CInt(ec.Text)
            evTEXT = CInt(ev.Text)
            etTEXT = CInt(et.Text)

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

            If etTEXT >= 32.0 Then
                et.BackColor = Color.Red
            ElseIf etTEXT < 28.5 Then
                et.BackColor = Color.LightGreen
            Else
                et.BackColor = Color.Orange
            End If

        Catch

        End Try

    End Sub
End Class