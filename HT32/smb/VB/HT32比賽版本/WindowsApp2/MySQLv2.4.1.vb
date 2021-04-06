Imports MySql.Data.MySqlClient
Module MySQL

    Public Sub MySQL_Init(ByRef iSQL As SQL_TypeDef, ByVal iArrayMax As Integer, ByRef iServerID As String,
                          ByRef iUserID As String, ByRef iPassword As String, ByRef iDatabase As String)
        ReDim iSQL.Column(iArrayMax)
        serverstring = "server=" & iServerID & ";userid= " & iUserID & ";password=" & iPassword & ";Database=" & iDatabase & ";charset=utf8;Allow Zero Datetime=True;"
        SQLConnection.ConnectionString = serverstring
    End Sub

    Public Sub MySQL_Add(ByVal SQL As SQL_TypeDef, ByVal Number As Integer)
        MySQL_Connection()

        Dim SQLStatement As String = Nothing
        SQLStatement = "INSERT INTO `" & SQL.Form & "` ("
        SQLStatement &= "`date`,`time`,"

        For index = 1 To Number
            SQLStatement &= "`" & index & "`"

            If index = Number Then
                SQLStatement &= ")"
            Else
                SQLStatement &= ","
            End If
        Next

        SQLStatement &= "VALUES("
        SQLStatement &= "'" & Format(DateValue(Now), "yyyy-MM-dd") & "','" & TimeString & "',"

        For index = 1 To Number
            SQLStatement &= "'" & SQL.Column(index) & "'"
            If index = Number Then
                SQLStatement &= ")"
            Else
                SQLStatement &= ","
            End If
        Next

        MySQL_Savedata(SQLStatement)

        MySQL_Connection()
    End Sub


    'RETERIEVE DATA 
    Public Function MySQL_Retrieve(ByVal SQL As SQL_TypeDef)
        Dim mysql_adapter As MySqlDataAdapter
        Dim cmd As MySqlCommand
        Dim dt As New DataTable()
        'SQL STMT
        Dim sqlstring As String = "SELECT * FROM " & SQL.Form ' SHOW FULL FIELDS FROM 資料庫.資料表   看註解用

        cmd = New MySqlCommand(sqlstring, SQLConnection)

        'OPEN CON,RETRIEVE,FILL DGVIEW
        Try
            MySQL_Connection()
            mysql_adapter = New MySqlDataAdapter(cmd)

            mysql_adapter.Fill(dt)

            MySQL_Disconnection()

            'CLEAR DT
            Return dt

        Catch ex As Exception
            If Debug = iOPEN Then
                MsgBox(ex.ToString)
                'Return False
            ElseIf Debug = iRETURN Then
                'Return ex.ToString
            Else
                'Return False
            End If
            Return dt
            'SQLConnection.Close()
        End Try

    End Function

    Public Sub MySQL_Update(ByVal SQL As SQL_TypeDef, ByVal dt As DataTable, ByVal id As String)

        ' Dim con As New MySqlConnection(serverstring)
        Dim adapter As MySqlDataAdapter
        Dim cmd As MySqlCommand
        Dim SQLStatement As String = Nothing
        SQLStatement = "UPDATE " & SQL.Form & " SET "

        For index = 1 To dt.Columns.Count - 3
            'SQLStatement &= "`" & index & "`" & "=" & "'" & dt.Rows(0).Item(index) & "'"
            SQLStatement &= "`" & index & "`" & "=" & "'" & dt.Rows(id - 1).Item(index.ToString) & "'"
            If index = dt.Columns.Count - 3 Then
                SQLStatement &= " WHERE id=" & id
            Else
                SQLStatement &= ","
            End If
        Next
        cmd = New MySqlCommand(SQLStatement, SQLConnection)
        'OPEN CON,EXECUT UPDATE,CLOSE'
        Try
            MySQL_Connection()
            adapter = New MySqlDataAdapter(cmd)
            adapter.UpdateCommand = SQLConnection.CreateCommand()

            adapter.UpdateCommand.CommandText = SQLStatement

            If adapter.UpdateCommand.ExecuteNonQuery() > 0 Then
                'MsgBox("Successfully Updated")
            End If
            'con.Close()

        Catch ex As Exception
            If Debug = iOPEN Then
                MsgBox(ex.ToString)
                'Return False
            ElseIf Debug = iRETURN Then
                'Return ex.ToString
            Else
                'Return False
            End If
        End Try

        MySQL_Disconnection()
    End Sub

    Public Sub MySQL_Delete(ByVal SQL As SQL_TypeDef, id As String)
        'Dim con As New MySqlConnection(serverstring)
        Dim mysql_adapter As MySqlDataAdapter
        Dim sqlstring As String = "DELETE FROM " & SQL.Form & " WHERE ID='" & id & "'"
        Dim cmd As MySqlCommand
        cmd = New MySqlCommand(sqlstring, SQLConnection)

        'OPEN CON,EXECUTE UPDATE,CLOSE CON
        Try
            MySQL_Connection()
            mysql_adapter = New MySqlDataAdapter(cmd)
            mysql_adapter.DeleteCommand = SQLConnection.CreateCommand()
            mysql_adapter.DeleteCommand.CommandText = sqlstring

            'PROMPT FOR CONFIRMATION
            'If MessageBox.Show("Sure ??", "DELETE", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) = System.Windows.Forms.DialogResult.OK Then
            If cmd.ExecuteNonQuery() > 0 Then
                'MsgBox("Successfully Deleted")

            End If
            ' End If


        Catch ex As Exception
            If Debug = iOPEN Then
                MsgBox(ex.ToString)
                'Return False
            ElseIf Debug = iRETURN Then
                'Return ex.ToString
            Else
                'Return False
            End If
        End Try
        MySQL_Disconnection()
    End Sub

    'Select DATA 
    Public Function MySQL_Select(ByVal SQL As SQL_TypeDef, ByVal col As String, ByVal val As String)
        Dim mysql_adapter As MySqlDataAdapter
        Dim cmd As MySqlCommand
        Dim dt As New DataTable()
        'SQL STMT
        Dim sqlstring As String = ""
        If val <> "" Then
            sqlstring = "SELECT * FROM " & SQL.Form & " WHERE `" & col & "`='" & val & "'"
        Else
            sqlstring = "SELECT * FROM " & SQL.Form & " WHERE `" & col & "`"
        End If


        cmd = New MySqlCommand(sqlstring, SQLConnection)

        'OPEN CON,RETRIEVE,FILL DGVIEW
        Try
            MySQL_Connection()
            mysql_adapter = New MySqlDataAdapter(cmd)

            mysql_adapter.Fill(dt)

            MySQL_Disconnection()

            'CLEAR DT
            Return dt

        Catch ex As Exception
            If Debug = iOPEN Then
                MsgBox(ex.ToString)
                'Return False
            ElseIf Debug = iRETURN Then
                'Return ex.ToString
            Else
                'Return False
            End If
            Return dt
            'SQLConnection.Close()
        End Try

    End Function

    Public Sub DataGridView_SET(ByVal dgv As DataGridView, ByVal dt As DataTable)

        dgv.DataSource = dt

    End Sub

    '====================================   OH!!  NO!!   ====================================
    '=============================   Back to the top ,please   ==============================

    Const Debug As Integer = iCLOSE

    Structure SQL_TypeDef
        Dim Form As String
        Dim Date_YMD As String
        Dim Time As String
        Dim Column() As String

    End Structure

    Const iOPEN As Integer = 1
    Const iCLOSE As Integer = 2
    Const iRETURN As Integer = 3

    Dim serverstring As String = "server=127.0.0.1;userid=root;password=123456;Database=factory;charset=utf8;Allow Zero Datetime=True;" 'My Database
    Public SQLConnection As MySqlConnection = New MySqlConnection

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

    Public Function MySQL_Disconnection()

        Try
            If SQLConnection.State = ConnectionState.Open Then
                SQLConnection.Close()
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

End Module
