using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using MySql.Data.MySqlClient;

namespace CS_MySQL_01
{
    class Program
    {
        public static string dbHost = "127.0.0.1";//資料庫位址
        public static string dbUser = "root";//資料庫使用者帳號
        public static string dbPass = "usbw";//資料庫使用者密碼
        public static string dbName = "test";//資料庫名稱
        public static string connStr = "server=" + dbHost + ";Port=3307;uid=" + dbUser + ";pwd=" + dbPass + ";database=" + dbName;
        static void pause()
        {
            Console.Write("Press any key to continue . . . ");
            Console.ReadKey(true);
        }
        static void CS_MySQL_Insert()
        {         
            MySqlConnection conn = new MySqlConnection(connStr);
            MySqlCommand command = conn.CreateCommand();

            conn.Open();
            String cmdText = "SELECT * FROM test1 WHERE date < 8";
            MySqlCommand cmd = new MySqlCommand(cmdText, conn);
            MySqlDataReader reader = cmd.ExecuteReader(); //execure the reader
            while (reader.Read())
            {
                for (int i = 0; i < 3; i++)
                {
                    String s = reader.GetString(i);
                    Console.Write(s + "\t");
                }
                Console.Write("\n");
            }


            Console.ReadLine();
            conn.Close();
        }
        static void Main(string[] args)
        {
            CS_MySQL_Insert();
            pause();
        }
    }
}
