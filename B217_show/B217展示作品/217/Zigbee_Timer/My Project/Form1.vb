Public Class Form1
    Dim Set_Date As Date
    Dim Set_Time As Date
    Dim Text_Time As String
    Dim Switch
    Dim Auto_Time_S
    Dim Auto_Time_M
    Dim Auto_Time_H
    Dim Light_Add = 0
    Dim Light_PWM = 0
    Dim abd()

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Label3.Text = DateString
        Label4.Text = TimeString
        'ComboBox1.Text = DataGridView1.Rows(0).Cells(0).Value
        'ComboBox1.Text = DateTimePicker1.Value.ToString("yyyy-MM-dd")


        '時間判斷
        If DataGridView1.Rows.Count > 1 Then
            If DataGridView1.Rows(0).Cells(1).Value <= TimeString Then
                If DataGridView1.Rows(0).Cells(0).Value <= DateString Then

                    Device_Control()
                End If
            End If
        End If
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If DateTimePicker1.Value.ToString("yyyy-MM-dd") < DateString Then
            MessageBox.Show("Date Error")
            DateTimePicker1.Value = DateString
            DateTimePicker1.Value.ToString("yyyy-MM-dd")
        ElseIf TextBox1.Text = "" Or TextBox2.Text = "" Or TextBox3.Text = "" Then
            MessageBox.Show("Time Error")
        ElseIf TextBox1.Text > 24 Or TextBox2.Text > 60 Or TextBox3.Text > 60 Then
            MessageBox.Show("Time Error")
        ElseIf ComboBox1.Text = "" Then
            MessageBox.Show("Station Error")
        ElseIf ComboBox2.Text = "" Then
            MessageBox.Show("Channel Error")
        ElseIf (CheckBox1.Checked = False And CheckBox2.Checked = False) Or (CheckBox1.Checked = True And CheckBox2.Checked = True) Then
            MessageBox.Show("On/Off Error")




        Else
            TextBox3.Text += 3
            Text_Time = (Format(Val(TextBox1.Text), "00") + ":" + Format(Val(TextBox2.Text), "00") + ":" + Format(Val(TextBox3.Text), "00"))
            ' Set_Time = "#" & (Format(Val(TextBox1.Text), "00") + ":" + Format(Val(TextBox2.Text), "00") + ":" + Format(Val(TextBox3.Text), "00")) & "#"

            If CheckBox1.Checked = True Then
                Switch = CheckBox1.Text
            ElseIf CheckBox2.Checked = True Then
                Switch = CheckBox2.Text
            End If
            DataGridView1.Rows.Add(DateTimePicker1.Value.ToString("yyyy-MM-dd"),
                                   Text_Time,
                                   ComboBox1.Text,
                                   ComboBox2.Text,
                                   NumericUpDown1.Value,
                                   Switch)
        End If
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Auto_Time_H = Mid(TimeString, 1, 2)
        Auto_Time_M = Mid(TimeString, 4, 2)
        Auto_Time_S = Mid(TimeString, 7, 2) + 10
        If Auto_Time_S > 59 Then
            Auto_Time_M += 1
            Auto_Time_S -= 60
        End If
        If Auto_Time_M > 59 Then
            Auto_Time_H += 1
            Auto_Time_M -= 60
        End If
        Label1.Text = (Format(Val(Auto_Time_H), "00") + ":" + Format(Val(Auto_Time_M), "00") + ":" + Format(Val(Auto_Time_S), "00"))


        For index = 1 To 4
            Auto_Time_S = Auto_Time_S + 3
            If Auto_Time_S > 59 Then
                Auto_Time_M += 1
                Auto_Time_S -= 60
            End If
            If Auto_Time_M > 59 Then
                Auto_Time_H += 1
                Auto_Time_M -= 60
            End If
            DataGridView1.Rows.Add(DateString,
                                  (Format(Val(Auto_Time_H), "00") + ":" + Format(Val(Auto_Time_M), "00") + ":" + Format(Val(Auto_Time_S), "00")),
                                   ComboBox1.Text,
                                   ComboBox2.Text,
                                   25 * index,
                                   "On")
        Next


        For index = 1 To 4
            Auto_Time_S = Auto_Time_S + 3
            If Auto_Time_S > 59 Then
                Auto_Time_M += 1
                Auto_Time_S -= 60
            End If
            If Auto_Time_M > 59 Then
                Auto_Time_H += 1
                Auto_Time_M -= 60
            End If

            If index = 1 Or index = 3 Then
                DataGridView1.Rows.Add(DateString,
                                      (Format(Val(Auto_Time_H), "00") + ":" + Format(Val(Auto_Time_M), "00") + ":" + Format(Val(Auto_Time_S), "00")),
                                       ComboBox1.Text,
                                       ComboBox2.Text,
                                       125 - 25 * index,
                                       "Off")
            Else
                DataGridView1.Rows.Add(DateString,
                                      (Format(Val(Auto_Time_H), "00") + ":" + Format(Val(Auto_Time_M), "00") + ":" + Format(Val(Auto_Time_S), "00")),
                                       ComboBox1.Text,
                                       ComboBox2.Text,
                                       125 - 25 * index,
                                       "On")
            End If



        Next



    End Sub

    Private Sub CheckBox1_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox1.CheckedChanged
        '  CheckBox1.Checked = True
        'CheckBox2.Checked = False

    End Sub

    Private Sub CheckBox2_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox2.CheckedChanged
        ' CheckBox1.Checked = False
        'CheckBox2.Checked = True
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' DataGridView1.Rows.Add(DateString)
    End Sub

    Private Sub Device_Control()
        Select Case ComboBox1.SelectedIndex + 1
            Case 1
                'Frist.TXD = Frist.T5_Station1
            Case 2
                ' Frist.TXD = Frist.T5_Station2
            Case Else
        End Select

        Select Case ComboBox2.SelectedIndex + 1
            Case 1
                Frist.TXD = Frist.T5_Channel1_Relay
            Case 2
                Frist.TXD = Frist.T5_Channel2_Relay
            Case Else
        End Select

        If DataGridView1.Rows(0).Cells(5).Value = "On" Then
            ' Frist.TXD = Frist.T5_Channel1_Relay_V + Chr(&HA) + Chr(NumericUpDown1.Text)
            Frist.TXD += Chr(&H1) + Chr(&H0)
            Frist.SerialPort1.Write(Frist.TXD)

            Label1.Text = 1
        ElseIf DataGridView1.Rows(0).Cells(5).Value = "Off" Then
            Frist.TXD += Chr(&H1) + Chr(&H1)
            Frist.SerialPort1.Write(Frist.TXD)
        End If
        Light_PWM = DataGridView1.Rows(0).Cells(4).Value
        DataGridView1.Rows.RemoveAt(0)
        Light_Add = 1
        Timer2.Enabled = True

    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        If Light_Add > 0 Then
            Light_Add += 1
            If Light_Add > 5 Then
                Frist.TXD = Frist.T5_Channel1_PWM + Chr(&HA) + Chr(Light_PWM)
                Frist.SerialPort1.Write(Frist.TXD)
                Light_Add = 0
                Timer2.Enabled = False
            End If
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        'Auto_Time_H = Mid(TimeString, 1, 2)
        'Auto_Time_M = Mid(TimeString, 4, 2)
        'Auto_Time_S = Mid(TimeString, 7, 2)
        'DataGridView1.Rows.Add(Format(Val(Auto_Time_H), "00") + ":" + Format(Val(Auto_Time_M), "00") + ":" + Format(Val(Auto_Time_S), "00"))
        'Auto_Time_S = Auto_Time_S + 10
        'DataGridView1.Rows.Add(Format(Val(Auto_Time_H), "00") + ":" + Format(Val(Auto_Time_M), "00") + ":" + Format(Val(Auto_Time_S), "00"))
        DataGridView1.Rows.Add("1", "1", "1", "1", "1")
        DataGridView1.Rows.Add("2")
        DataGridView1.Rows.Add("3")
        DataGridView1.Rows.Add("4")

        '  Label1.Text = Mid(DataGridView1.Rows(1).Cells.Item(0).Value, 7, 2)
        'If Mid(DataGridView1.Rows(1).Cells.Item(0).Value, 7, 2) < Mid(DataGridView1.Rows(0).Cells.Item(0).Value, 7, 2) Then
        '    Button3.Text = False
        'ElseIf DataGridView1.Rows(1).Cells.Item(0).Value > DataGridView1.Rows(0).Cells.Item(0).Value Then
        '    Button3.Text = True
        'End If
    End Sub

    Private Sub CheckBox1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox1.Click

        CheckBox2.Checked = False
    End Sub

    Private Sub CheckBox2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox2.Click
        CheckBox1.Checked = False

    End Sub
End Class