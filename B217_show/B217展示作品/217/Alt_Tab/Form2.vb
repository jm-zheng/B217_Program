Public Class Form2

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.Hide()
    End Sub
    Dim light As Integer = 100

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Frist.V3_Conut1 = 0
        Frist.V3_Conut2 = 0
        'For i = 1 To 10
        '    light_change = 10 - i
        'Next

        'Frist.SerialPort1.Write((Chr(1) + Chr(1) + Chr(200) + Chr(12) + Chr(10) + Chr(light_change)))
        'If light_change < 3 Then
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(24) + Chr(1) + Chr(1))
        'End If
    End Sub

    '-----------A區 ALL ON OFF

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Frist.V3_Conut1 = 1
        Frist.V3_Conut2 = 1
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(24) + Chr(1) + Chr(0))

    End Sub
    '-----------A-1區 ON OFF
    Private Sub Button13_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button13.Click
        Frist.V3_Conut1 = 1
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(16) + Chr(1) + Chr(0))
    End Sub

    Private Sub Button12_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button12.Click
        Frist.V3_Conut1 = 0
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(16) + Chr(1) + Chr(1))
    End Sub
    '----------A-2區 ON OFF
    Private Sub Button15_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button15.Click
        Frist.V3_Conut2 = 1
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(8) + Chr(1) + Chr(0))
    End Sub

    Private Sub Button14_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button14.Click
        Frist.V3_Conut2 = 0
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(8) + Chr(1) + Chr(1))
    End Sub

    '------------A區ALL調光

    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        light = light + 10
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(12) + Chr(10) + Chr(light))

    End Sub

    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click
        light = light - 10
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(12) + Chr(10) + Chr(light))


    End Sub
    'A-1調光
    Private Sub Button16_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button16.Click
        light = light + 10
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(4) + Chr(10) + Chr(light))

    End Sub

    Private Sub Button17_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button17.Click
        light = light - 10
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(4) + Chr(10) + Chr(light))

    End Sub
    'A-2調光
    Private Sub Button18_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button18.Click
        light = light + 10
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(8) + Chr(10) + Chr(light))

    End Sub

    Private Sub Button19_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button19.Click
        light = light - 10
        Frist.SerialPort1.Write(Chr(1) + Chr(3) + Chr(200) + Chr(8) + Chr(10) + Chr(light))

    End Sub



    '------------B區 ALL　ON OFF

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Frist.V3_Conut3 = 1
        Frist.V3_Conut4 = 1
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(24) + Chr(1) + Chr(0)) ' on
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Frist.V3_Conut3 = 0
        Frist.V3_Conut4 = 0
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(24) + Chr(1) + Chr(1)) 'off
    End Sub
    '------------B-1   ON OFF
    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Frist.V3_Conut3 = 1
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(8) + Chr(1) + Chr(0))
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        Frist.V3_Conut3 = 0
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(8) + Chr(1) + Chr(1))
    End Sub
    '----------B-2  ON OFF
    Private Sub Button10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button10.Click
        Frist.V3_Conut4 = 1
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(16) + Chr(1) + Chr(0))
    End Sub

    Private Sub Button11_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button11.Click
        Frist.V3_Conut4 = 0
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(16) + Chr(1) + Chr(1))
    End Sub






    '---------B區 ALL 調光

    Private Sub Button20_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button20.Click
        light = light + 10
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(12) + Chr(10) + Chr(light))

    End Sub

    Private Sub Button21_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button21.Click
        light = light - 10
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(12) + Chr(10) + Chr(light))


    End Sub


    '-------B-1區 調光
    Private Sub Button22_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button22.Click
        light = light + 10
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(8) + Chr(10) + Chr(light))

    End Sub

    Private Sub Button23_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button23.Click
        light = light - 10
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(8) + Chr(10) + Chr(light))

    End Sub
    '---------B-2區 調光
    Private Sub Button24_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button24.Click
        light = light + 10
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(4) + Chr(10) + Chr(light))

    End Sub

    Private Sub Button25_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button25.Click
        light = light - 10
        Frist.SerialPort1.Write(Chr(1) + Chr(2) + Chr(200) + Chr(4) + Chr(10) + Chr(light))

    End Sub



End Class