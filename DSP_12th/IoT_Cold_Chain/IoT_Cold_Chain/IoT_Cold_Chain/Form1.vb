Public Class Form1
    Dim cc_Pno = 0
    Dim cc_BOX = 0
    Public devno
    Public temp
    Public ls
    Public gx
    Sub show_pic(ByVal selindex)
        Select Case selindex
            Case 0
                PictureBox1.Image = My.Resources.cc1_現流海魚5尾組合包1099

            Case 1
                PictureBox1.Image = My.Resources.cc2_現流海魚5尾組合包1099
            Case 2
                PictureBox1.Image = My.Resources.cc3_現流螃蟹組合包1099
            Case 3
                PictureBox1.Image = My.Resources.cc4_現流黑喉魚3尾入499
            Case 4
                PictureBox1.Image = My.Resources.cc5_現流紅目鰱3尾入699
            Case 5
                PictureBox1.Image = My.Resources.cc6_現撈海魚歡樂組999_
            Case 6
                PictureBox1.Image = My.Resources.cc7_流白帶魚1大尾入_350

        End Select


    End Sub

    Private Sub ComboBox2_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox2.SelectedIndexChanged
        cc_Pno = ComboBox2.SelectedIndex
        show_pic(cc_Pno)
        Label3.Text = ComboBox2.Text

    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
        Next
    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox1.SelectedIndexChanged
        SerialPort1.PortName = ComboBox1.Items(ComboBox1.SelectedIndex)
        SerialPort1.Open()
        Timer1.Enabled = True
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim RXD$ = SerialPort1.ReadExisting()
        If RXD$ <> "" Then
            Label5.Text = RXD$
            Label3.Text = Mid(Label5.Text, 1, 2)
            devno = Mid(Label5.Text, 1, 2)
            temp = Mid(Label5.Text, 5, 5)
            ls = Mid(Label5.Text, 12, 3)
            gx = Mid(Label5.Text, 17, 1)
            Select Case Mid(Label5.Text, 2, 1)
                Case "1"
                    PictureBox1.Image = My.Resources.cc1_現流海魚5尾組合包1099

                Case "2"
                    PictureBox1.Image = My.Resources.cc3_現流螃蟹組合包1099
                Case "3"
                    PictureBox1.Image = My.Resources.cc4_現流黑喉魚3尾入499
                Case "4"
                    PictureBox1.Image = My.Resources.cc5_現流紅目鰱3尾入699
                Case "5"
                    PictureBox1.Image = My.Resources.cc6_現撈海魚歡樂組999_
                Case "6"
                    PictureBox1.Image = My.Resources.cc7_流白帶魚1大尾入_350
            End Select
        End If

    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If ComboBox4.Text = "" Then
            MsgBox(" 請輸入貨物編號")
        Else
            Dim ANS = MsgBox("確定將宅配貨號" & ComboBox4.Text & "存入到" & ComboBox3.Text, MsgBoxStyle.YesNoCancel)
            'Label15.Text = ANS
            '' If
            '    +.ANS = 6 Then
            'erialPort1.Write("D1" & "_P" & Mid(ComboBox4.Text, 3, 1))
            'End If

        End If
    End Sub

    Private Sub ComboBox3_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox3.SelectedIndexChanged
        cc_Pno = ComboBox3.SelectedIndex

    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        SerialPort1.Write("S1")
        Form2.Show()

    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        SerialPort1.Write("S0")
    End Sub

    Private Sub ComboBox4_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ComboBox4.SelectedIndexChanged
        cc_Pno = Val(Mid(ComboBox4.Text, 4, 1))
        show_pic(cc_Pno - 1)
        ComboBox2.SelectedIndex = cc_Pno - 1
        Label3.Text = ComboBox2.Text
    End Sub

    Private Sub GroupBox3_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GroupBox3.Enter

    End Sub

    Private Sub GroupBox1_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles GroupBox1.Enter

    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Form2.Show()
    End Sub
End Class
