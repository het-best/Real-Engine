using System;
using System.IO;
using System.Text;

namespace HScript
{
    internal class compiler
    {
        int i;
        public void compile(string user_name, string[] settings)
        {
            Console.WriteLine();
            settings[2] += "\\Main.cpp";
            using (StreamWriter sw = new StreamWriter(@"C:\Users\" + user_name + @"\AppData\Local\Temp\main.hs.tmp"))
            {
                using (StreamReader sr = new StreamReader("start.cpp")) { sw.WriteLine(sr.ReadToEnd()); sr.Close(); }

                commands(sw, settings);

                using (StreamReader sr = new StreamReader("end.cpp")) { sw.WriteLine(sr.ReadToEnd()); sr.Close(); }

                sw.Close();

                using (StreamWriter end = new StreamWriter(settings[2])) { using (StreamReader sr = new StreamReader(@"C:\Users\" + user_name + @"\AppData\Local\Temp\main.hs.tmp")) { end.WriteLine(sr.ReadToEnd()); sr.Close(); } }
            }
        }

        private void commands(StreamWriter sw, string[] settings)
        {
            string text;
            using (StreamReader sr = new StreamReader("main.hs")) { text = sr.ReadToEnd(); sr.Close(); }
            try
            {
                if (settings[0] == "rus")
                {
                    Console.WriteLine("ЛОГИ:");
                }
                else if (settings[0] == "eng")
                {
                    Console.WriteLine("LOGS:");
                }
                for (i = 0; i < text.Length - 1; i++)
                {
                    if (locate_word(text, "window.", i))
                    {
                        Console.ForegroundColor = ConsoleColor.Green;
                        if (settings[0] == "rus")
                        {
                            Console.WriteLine("Найдено \"window.\"");
                        }
                        else if (settings[0] == "eng")
                        {
                            Console.WriteLine("Found the \"window.\"");
                        }

                        if (locate_word(text, "set_title = \"", i))
                        {
                            var final_name = "";
                            while (!locate_word(text, "\"", i))
                            {
                                final_name += text[i];
                                i++;
                            }
                            Console.ForegroundColor = ConsoleColor.Cyan;

                            if (settings[0] == "rus")
                            {
                                Console.WriteLine("Найдено \"set_title\" со значением \"" + final_name + "\"");
                            }
                            else if (settings[0] == "eng")
                            {
                                Console.WriteLine("Found the \"set_title\" with meaning \"" + final_name + "\"");
                            }

                            sw.Write("        ");
                            sw.WriteLine("set_title(L\"" + final_name + "\");");
                        }
                    }
                }
                Console.ForegroundColor = ConsoleColor.White;
                if (settings[0] == "rus")
                {
                    Console.WriteLine("Чтобы закрыть логи и сохранить код нажмите enter.");
                }
                else if (settings[0] == "eng")
                {
                    Console.WriteLine("To close logs and save the code press enter.");
                }
                Console.ReadLine();
                Console.Clear();
            }
            catch
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("ERROR");
            }
        }

        private bool locate_word(string text, string word, int number)
        {
            bool locate = false;
            bool main = true;
            int a = 0;
            string locate_word = "";
            while (main)
            {
                if (text[number] == word[a])
                {
                    locate_word += word[a];
                }
                else
                {
                    locate = false;
                    main = false;
                }
                if (locate_word == word)
                {
                    locate = true;
                    main = false;
                }
                number++;
                a++;
            }
            if (locate)
            {
                i = number;
                return true;
            }
            //Console.WriteLine(number);
            return false;
        }
    }
}
