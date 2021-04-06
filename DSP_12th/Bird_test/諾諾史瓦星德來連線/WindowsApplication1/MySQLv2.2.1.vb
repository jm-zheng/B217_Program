Imports MySql.Data.MySqlClient
Module MySQL



    Public Sub MySQL_Init(ByRef iSQL As SQL_TypeDef, ByVal iArrayMax As Integer, ByRef iServerID As String,
                          ByRef iUserID As String, ByRef iPassword As String, ByRef iDatabase As String)
        ReDim iSQL.Column(iArrayMax)
        serverstring = "server=" & iServerID & ";userid= " & iUserID & ";password=" & iPassword & ";Database=" & iDatabase & ";charset=utf8;Allow Zero Datetime=True;"
        SQLConnection.ConnectionString = serverstring
    End Sub

    Public Function MySQL_Connection()

        Try
            If SQLConnection.State = ConnectionState.Closed Then
                SQLConnection.Open()
                'MsgBox("Successfully Connected to MySQL Database.")
            End If
            Return True
        Catch ex As Exception
            If Debug = iOPEN Then
                MsgBox(ex.ToString)
                Return False
            ElseIf Debug = iRETURN Then
                Return ex.ToString
            Else
                Return False
            End If
        End Try
    End Function

    Public Sub MySQL_Add(ByVal SQL As SQL_TypeDef, ByVal Number As Integer)
        'Dim SQLStatement1 As String = "INSERT INTO `" & KSI.Form & "` (`A`,`B`,`C`,`D`,`E`,`F`,`Station`,`Date`,`Time`) VALUES('" & KSI.A & " ','" & KSI.B & " ','" & KSI.C & " ','" & KSI.D & " ','" & KSI.E & " ','" & KSI.F & " ','" & KSI.Station & " ','" & KSI.Date_YMD & " ','" & KSI.Time & " ')"

        Dim SQLStatement As String = Nothing
        SQLStatement = "INSERT INTO `" & SQL.Form & "` ("
        SQLStatement &= "`DATE`,`TIME`,"

        For index = 1 To Number
            SQLStatement &= "`" & index & "`"

            If index = Number Then
                SQLStatement &= ")"
            Else
                SQLStatement &= ","
            End If
        Next

        SQLStatement &= "VALUES("
        SQLStatement &= "'" & Format(DateValue(Now), "yyyy-MM-dd") & "','" & Format(TimeValue(Now), "HH:mm:ss") & "',"

        For index = 1 To Number
            SQLStatement &= "'" & SQL.Column(index) & "'"
            If index = Number Then
                SQLStatement &= ")"
            Else
                SQLStatement &= ","
            End If
        Next

        MySQL_Savedata(SQLStatement)
    End Sub


    'RETERIEVE DATA
    Public Function MySQL_Retrieve(ByVal SQLform As String)

        Dim cmd As MySqlCommand
        Dim dt As New DataTable()
        'SQL STMT
        Dim sqlstring As String = "SELECT * FROM " & SQLform ' SHOW FULL FIELDS FROM 資料庫.資料表   看註解用

        cmd = New MySqlCommand(sqlstring, SQLConnection)

        'OPEN CON,RETRIEVE,FILL DGVIEW
        Try
            'SQLConnection.Open()
            mysql_adapter = New MySqlDataAdapter(cmd)

            mysql_adapter.Fill(dt)

            'SQLConnection.Close()

            'CLEAR DT
            Return dt

        Catch ex As Exception
            MsgBox(ex.Message)
            Return 0
            'SQLConnection.Close()
        End Try

    End Function

    Public Sub MySQL_Update(ByVal SQL As SQL_TypeDef, ByVal dt As DataTable, ByVal id As String)

        Dim con As New MySqlConnection(serverstring)
        Dim adapter As MySqlDataAdapter
        Dim cmd As MySqlCommand
        Dim SQLStatement As String = Nothing
        SQLStatement = "UPDATE " & SQL.Form & " SET "



        For index = 1 To dt.Columns.Count - 1
            SQLStatement &= "`" & index & "`" & "=" & "'" & dt.Rows(0).Item(index) & "'"

            If index = dt.Columns.Count - 1 Then
                SQLStatement &= " WHERE id=" & id
            Else
                SQLStatement &= ","
            End If
        Next
        cmd = New MySqlCommand(SQLStatement, con)
        'OPEN CON,EXECUT UPDATE,CLOSE'
        Try
            con.Open()
            adapter = New MySqlDataAdapter(cmd)
            adapter.UpdateCommand = con.CreateCommand()

            adapter.UpdateCommand.CommandText = SQLStatement

            If adapter.UpdateCommand.ExecuteNonQuery() > 0 Then
                'MsgBox("Successfully Updated")
            End If
            'con.Close()

        Catch ex As Exception
            MsgBox(ex.Message)
            'con.Close()
        End Try
    End Sub

    Public Sub MySQL_Delete(ByVal SQL As SQL_TypeDef, id As String)
        Dim con As New MySqlConnection(serverstring)
        Dim sqlstring As String = "DELETE FROM " & SQL.Form & " WHERE ID='" & id & "'"
        Dim cmd As MySqlCommand
        cmd = New MySqlCommand(sqlstring, SQLConnection)

        'OPEN CON,EXECUTE UPDATE,CLOSE CON
        Try
            'con.Open()
            mysql_adapter.DeleteCommand = con.CreateCommand()
            mysql_adapter.DeleteCommand.CommandText = sqlstring

            'PROMPT FOR CONFIRMATION
            'If MessageBox.Show("Sure ??", "DELETE", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) = System.Windows.Forms.DialogResult.OK Then
            If cmd.ExecuteNonQuery() > 0 Then
                'MsgBox("Successfully Deleted")

            End If
            ' End If
            con.Close()

        Catch ex As Exception
            MsgBox(ex.Message)
            con.Close()

        End Try
    End Sub

    Public Sub DataGridView_SET(ByVal dgv As DataGridView, ByVal dt As DataTable)
        'DataGridView_INIT(dgv, dt)

        dgv.DataSource = dt
        'For Each row In dt.Rows
        '    Populate(row(0), row(1), row(2), row(3))
        'Next
    End Sub

    '====================================   OH!!  NO!!   ====================================
    '=============================   Back to the top ,please   ==============================

    Const Debug As Integer = iOPEN

    Structure SQL_TypeDef
        Dim Form As String
        Dim Date_YMD As String
        Dim Time As String
        Dim Column() As String

    End Structure

    Const iOPEN As Integer = 1
    Const iCLOSE As Integer = 2
    Const iRETURN As Integer = 3

    Dim KSI_SENSOR As SQL_TypeDef = New SQL_TypeDef
    Dim serverstring As String = "server=127.0.0.1;userid=root;password=;Database=shong;charset=utf8;Allow Zero Datetime=True;" 'My Database
    Public SQLConnection As MySqlConnection = New MySqlConnection
    Dim mysql_adapter As MySqlDataAdapter

    Public Sub MySQL_Savedata(ByRef aa As String)
        Dim cmd As MySqlCommand = New MySqlCommand
        With cmd
            .CommandText = aa
            .CommandType = CommandType.Text
            .Connection = SQLConnection
            .ExecuteNonQuery()
        End With
    End Sub

    'DataGridView INIT
    Public Sub DataGridView_INIT(ByVal dgv As DataGridView, ByVal dt As DataTable)
        dgv.ColumnCount = dt.Columns.Count

        For index = 1 To dgv.ColumnCount
            dgv.Columns(index - 1).Name = index
        Next

    End Sub



    'Public Sub UpdateDG(ByVal SQL As SQL_TypeDef, ByVal dtv As DataGridView)  'datagrideview 表格更新用

    '    Dim con As New MySqlConnection(serverstring)
    '    Dim adapter As MySqlDataAdapter
    '    Dim cmd As MySqlCommand
    '    Dim SQLStatement As String = Nothing
    '    SQLStatement = "UPDATE " & SQL.Form & " SET "



    '    For index = 1 To dtv.ColumnCount - 1
    '        SQLStatement &= "`" & index & "`" & "=" & "'" & dtv.SelectedRows(0).Cells(index).Value & "'"

    '        If index = dtv.ColumnCount - 1 Then
    '            SQLStatement &= " WHERE id=" & dtv.SelectedRows(0).Cells(0).Value
    '        Else
    '            SQLStatement &= ","
    '        End If
    '    Next
    '    cmd = New MySqlCommand(SQLStatement, con)
    '    'OPEN CON,EXECUT UPDATE,CLOSE'
    '    Try
    '        con.Open()
    '        adapter = New MySqlDataAdapter(cmd)
    '        adapter.UpdateCommand = con.CreateCommand()

    '        adapter.UpdateCommand.CommandText = SQLStatement

    '        If adapter.UpdateCommand.ExecuteNonQuery() > 0 Then
    '            MsgBox("Successfully Updated")
    '        End If
    '        'con.Close()

    '    Catch ex As Exception
    '        MsgBox(ex.Message)
    '        'con.Close()
    '    End Try
    'End Sub
End Module
