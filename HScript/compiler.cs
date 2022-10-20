using System;
using System.IO;

namespace HScript
{
    internal class compiler
    {
        int i;
        public void compile(string path, string user_name)
        {
            commands();
            path += "\\Main.cpp";
            using (StreamWriter sw = new StreamWriter(@"C:\Users\" + user_name + @"\AppData\Local\Temp\main.hs.tmp"))
            {
                using (StreamReader sr = new StreamReader("start.cpp")) { sw.WriteLine(sr.ReadToEnd()); sr.Close(); }

                sw.Write("        ");
                sw.WriteLine("sfml_window.setTitle(L\"я русский\");");

                using (StreamReader sr = new StreamReader("end.cpp")) { sw.WriteLine(sr.ReadToEnd()); sr.Close(); }

                sw.Close();

                using (StreamWriter end = new StreamWriter(path)) { using (StreamReader sr = new StreamReader(@"C:\Users\" + user_name + @"\AppData\Local\Temp\main.hs.tmp")) { end.WriteLine(sr.ReadToEnd()); sr.Close(); } }
            }
        }

        private void commands()
        {
            string text;
            using (StreamReader sr = new StreamReader("main.hs")) { text = sr.ReadToEnd(); sr.Close(); }

            for (int a = 0; a < text.Length - 1; a++)
            {
                if ()
            }
        }

        private bool locate_word(string text, string word, int number)
        {
            bool locate = false;
            bool main = true;
            int i = 0;
            int lenght = 0;
            while (main)
            {
                if (lenght == word.Length)
                {
                    locate = true;
                    main = false;
                }
                try
                {
                    if (text[number] == word[i])
                    {
                        lenght++;
                    }
                }
                catch
                {
                    locate = false;
                    main = false;
                }
                number++;
                i++;
            }
            if (locate)
            {
                i = number;
                return true;
            }
            return false;
        }
    }
}
