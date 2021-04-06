Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Function floatCount(ByVal a, ByVal b, ByVal c, ByVal d)
        Dim S = 0
        Dim E = 0
        Dim M As Double = 0

        'a
        If (a And 128) Then
            S = -1
        Else
            S = 1

        End If

        For index As Integer = 1 To 7
            If (a And (128 >> index)) Then
                E += 1 << (8 - index)
            End If
        Next
        'ESSSSSSSS  SMMMMMMM MMMMMMM MMMMMMMM
        ''b
        If (b And 128) Then
            E += ((b And 128) >> 7)
        End If
        For index As Integer = 1 To 7
            If (b And (128 >> index)) Then
                M += 2 ^ (-1 * index)
            End If
        Next

        For index As Integer = 1 To 8
            If (c And (128 >> index)) Then
                M += 2 ^ (-1 * index + (-7))
            End If

        Next

        For index As Integer = 1 To 8
            If (d And (128 >> index)) Then
                M += 2 ^ (-1 * index + (-15))
            End If

        Next
        If E = 0 And M = 0 Then
            M = -1
        End If
        Return S * (2 ^ (E - 127)) * (1 + M)
    End Function

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim a As Integer = "&h" + TextBox1.Text
        Dim b As Integer = "&h" + TextBox2.Text
        Dim c As Integer = "&h" + TextBox3.Text
        Dim d As Integer = "&h" + TextBox4.Text
        Label1.Text = floatCount(a, b, c, d)
    End Sub
End Class
