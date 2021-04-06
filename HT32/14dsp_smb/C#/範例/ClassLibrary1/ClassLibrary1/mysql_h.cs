using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.Entity;
using MySql.Data.MySqlClient;
using System.Data;
using System.Diagnostics;
using System.Reflection;

namespace MySql
{
    struct SQLTypedef //結構
    {
        public string FROM;
        public DateTime DATE_YMD;
        public DateTime TIME;
        public string[] COLUMN; //資料表裡的東西(陣列)
        public MySqlConnection SQLConnection;
    }


    class Class1
    {
        const int iOPEN = 1;
        const int iCLOSE = 2;
        const int iRETURN = 3;
        const int Debug = iOPEN;
        static string errormsg;

        public static void MYSQL_Init(ref SQLTypedef SQL, byte iArrayMax, string iServerID, string iUserID, string iPassword, string iDatebase)
        {
            //資料表裡的東西(定義陣列長度陣列宣告為999)======

            //===================================
            Array.Resize(ref SQL.COLUMN, iArrayMax);
            string connStr = "server=" + iServerID + ";uid=" + iUserID + ";pwd=" + iPassword + ";database=" + iDatebase;
            MySqlConnection conn = new MySqlConnection(connStr);
            SQL.SQLConnection = new MySqlConnection();
            SQL.SQLConnection.ConnectionString = connStr;

        }

        //新增=============================================新增
        public static void MYSQL_ADD(SQLTypedef SQL, int Number)
        {
            string SQLStatement = "";
            SQLStatement = "INSERT INTO `" + SQL.FROM + "` (" + "`date`,`time`,";
            for (int i = 1; i <= Number; i++)
            {
                SQLStatement += "`" + Convert.ToString(i) + "`";
                if (i == Number)
                {
                    SQLStatement += ")";
                }
                else
                {
                    SQLStatement += ",";
                }
            }
            SQLStatement += "VALUES(";
            SQLStatement += "'" + string.Format("{0:yyyy-MM-dd}", SQL.DATE_YMD) + "','" + string.Format("{0:HH:mm:ss}", SQL.TIME) + "',";

            for (int i = 1; i <= Number; i++)
            {
                SQLStatement += "'" + SQL.COLUMN[i] + "'";
                if (i == Number)
                {
                    SQLStatement += ")";
                }
                else
                {
                    SQLStatement += ",";
                }
            }

            try
            {
                MySQL_Disconnection(SQL);
                MySQL_Connection(SQL);
                MySQL_Savedata(SQLStatement, SQL);
                MySQL_Disconnection(SQL);
            }
            catch (Exception ex)
            {
                //錯誤行數
                StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                throw;
            }
        }
        //刪除================================================

        public static void MySQL_Delete(SQLTypedef SQL, string id)
        {
            MySqlDataAdapter mysql_adapter;
            string sqlstring = "DELETE FROM " + SQL.FROM + " WHERE ID='" + id + "'";
            MySqlCommand cmd;
            cmd = new MySqlCommand(sqlstring, SQL.SQLConnection);

            try
            {
                MySQL_Disconnection(SQL);
                MySQL_Connection(SQL);
                mysql_adapter = new MySqlDataAdapter(cmd);
                mysql_adapter.DeleteCommand = SQL.SQLConnection.CreateCommand();
                mysql_adapter.DeleteCommand.CommandText = sqlstring;

                MySQL_Disconnection(SQL);
            }
            catch (Exception ex)
            {
                //錯誤行數
                StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                throw;
            }
        }

        //====================================================

        //更新================================================
        public static void MySQL_Update(SQLTypedef SQL, DataTable dt, string id)
        {
            MySqlDataAdapter adapter;
            MySqlCommand cmd;
            string SQLStatement = null;
            SQLStatement = "UPDATE " + SQL.FROM + " SET ";

            for (int i = 1; i < dt.Columns.Count - 3; i++)
            {
                SQLStatement += "`" + i + "`" + "=" + "'" + dt.Rows[Convert.ToInt16(id)].ItemArray[i] + "'"; //.tostring 有問題
                if (i == dt.Columns.Count - 3)
                {
                    SQLStatement += " WHERE id=" + dt.Rows[Convert.ToInt16(id)].ItemArray[0];
                }
                else
                {
                    SQLStatement += ",";
                }
            }
            cmd = new MySqlCommand(SQLStatement, SQL.SQLConnection);

            try
            {
                MySQL_Disconnection(SQL);
                MySQL_Connection(SQL);

                adapter = new MySqlDataAdapter(cmd);
                adapter.UpdateCommand = SQL.SQLConnection.CreateCommand();

                adapter.UpdateCommand.CommandText = SQLStatement;
            }
            catch (Exception ex)
            {
                //錯誤行數
                StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                throw;
            }
        }
        //======================================================

        public static DataTable MySQL_Retrieve(SQLTypedef SQL)
        {
            MySqlDataAdapter mysql_adapter;
            MySqlCommand cmd;
            DataTable dt = new DataTable();
            string sqlstring = "SELECT * FROM " + SQL.FROM; //SHOW FULL FIELDS FROM 資料庫.資料表   看註解用
            cmd = new MySqlCommand(sqlstring, SQL.SQLConnection);

            try
            {
                MySQL_Disconnection(SQL);
                MySQL_Connection(SQL);

                mysql_adapter = new MySqlDataAdapter(cmd);
                mysql_adapter.Fill(dt);

                MySQL_Disconnection(SQL);

                //CLEAR DT
                return dt;
            }
            catch (Exception ex)
            {
                if (Debug == iOPEN)
                {
                    //錯誤行數
                    StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                    int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                    //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                    string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                    errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                }
                return dt;
            }
        }

        //========================================================

        public static DataTable MySQL_Select(SQLTypedef SQL, string col, string val)
        {
            MySqlDataAdapter mysql_adapter;
            MySqlCommand cmd;
            DataTable dt = new DataTable();
            string sqlstring = "";
            if (val != "")
            {
                sqlstring = "SELECT * FROM " + SQL.FROM + " WHERE `" + col + "`='" + val + "'";
            }
            else
            {
                sqlstring = "SELECT * FROM " + SQL.FROM + " WHERE `" + col + "`";
            }

            cmd = new MySqlCommand(sqlstring, SQL.SQLConnection);
            MySQL_Connection(SQL);

            try
            {
                mysql_adapter = new MySqlDataAdapter(cmd);
                mysql_adapter.Fill(dt);

                //CLEAR DT
                return dt;
            }
            catch (Exception ex)
            {
                if (Debug == iOPEN)
                {
                    //錯誤行數
                    StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                    int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                    //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                    string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                    errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                }
                return dt;
            }
        }

        //============================================================

        string connStr = "server=127.0.0.1;userid=root;password=;Database=shong;charset=utf8;Allow Zero Datetime=True;"; //Database

        public static Boolean MySQL_Connection(SQLTypedef SQL)
        {
            try
            {
                if (SQL.SQLConnection.State == ConnectionState.Open)
                {
                    SQL.SQLConnection.Close();
                }
                if (SQL.SQLConnection.State == ConnectionState.Closed)
                {
                    SQL.SQLConnection.Open();
                    //MsgBox.show("Successfully Connected to MySQL Database.")
                }
                return true;
            }
            catch (Exception ex)
            {
                if (Debug == iOPEN)
                {
                    //錯誤行數
                    StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                    int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                    //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                    string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                    errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                    return false;
                }
            }
        }

        //=====================================================================

        public static Boolean MySQL_Disconnection(SQLTypedef SQL)
        {
            try
            {
                if (SQL.SQLConnection.State == ConnectionState.Open)
                {
                    SQL.SQLConnection.Close();
                }
                return true;
            }
            catch (Exception ex)
            {
                if (Debug == iOPEN)
                {

                    //錯誤行數
                    StackTrace trace = new System.Diagnostics.StackTrace(ex, true);
                    int line = trace.GetFrame(trace.FrameCount - 1).GetFileLineNumber();
                    //string filename = My.computer.FileSystem.GetName(trace.GetFrame(trace.FrameCount - 1).GetFileName);
                    string functionName = trace.GetFrame(trace.FrameCount - 1).GetMethod().Name;
                    errormsg = "錯誤發生於 " + functionName + " 函式中的第 " + Convert.ToString(line) + " 行\n" + "錯誤信息: " + ex.Message + "發生錯誤";
                    return false;
                }
            }
        }

        //=====================================================================

        public static void MySQL_Savedata(string aa, SQLTypedef SQL)
        {
            MySqlCommand cmd = new MySqlCommand();
            cmd.CommandText = aa;
            cmd.CommandType = System.Data.CommandType.Text;
            cmd.Connection = SQL.SQLConnection;
            cmd.ExecuteNonQuery();
        }
    }
}
