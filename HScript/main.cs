using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;
using System.Linq;
using System.Management;
using System.Threading;

namespace HScript
{
    internal class main
    {
        static void Main(string[] args)
        {
            ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT UserName FROM Win32_ComputerSystem");
            ManagementObjectCollection collection = searcher.Get();
            string user_name = (string)collection.Cast<ManagementBaseObject>().First()["UserName"];

            var usr_temp = user_name.Split(Convert.ToChar(@"\"));
            user_name = usr_temp[1];            

            //загружаем настройки
            if (!Directory.Exists(@"C:\Users\" + user_name + @"\AppData\Roaming\Real engine"))
            {
                Directory.CreateDirectory(@"C:\Users\" + user_name + @"\AppData\Roaming\Real engine");
                using (StreamWriter sw = new StreamWriter(@"C:\Users\" + user_name + @"\AppData\Roaming\Real engine\settings.json"))
                {
                    sw.Write("{\n  'lang': 'rus',\n  'version': 'alpha 0.0.1',\n  'path_to_engine': ''\n}");
                }
            }

            string[] settings = new string[3];

            StreamReader reader = File.OpenText(@"C:\Users\" + user_name + @"\AppData\Roaming\Real engine\settings.json");
            JsonTextReader jsonTextReader = new JsonTextReader(reader);
            JObject jsonObject = (JObject)JToken.ReadFrom(jsonTextReader);
            settings[0] = jsonObject["lang"].ToString();
            settings[1] = jsonObject["version"].ToString();
            settings[2] = jsonObject["path_to_engine"].ToString();
            reader.Close();

            //вывод названия
            using (StreamReader sr = new StreamReader("icon.txt"))
            {
                Console.ForegroundColor = ConsoleColor.Magenta;
                for (int i = 0; i < 7; i++)
                {
                    Console.WriteLine(sr.ReadLine());
                }
                sr.Close();
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine();
            }

            //начало
            if (settings[0] == "rus")
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine("Спасибо за использование HScript!!!");
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine("Версия: " + settings[1]);
                Console.WriteLine();
                Console.WriteLine("Введите “help„ для помощи.");
            }
            else if (settings[0] == "eng")
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine("Thank for using HScript!!!");
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine("Version: " + settings[1]);
                Console.WriteLine();
                Console.WriteLine("Enter “help„ for help.");
            }

            //главный поток
            bool main_thread = true;
            while (main_thread)
            {
                Console.WriteLine();
                switch (Console.ReadLine())
                {
                    case "help":
                        if (settings[0] == "rus")
                        {
                            Console.WriteLine("“exit„ - выходит из программы.");
                            Console.WriteLine("“set path„ - ввод пути к проекту.");
                            Console.WriteLine("“compile„ - компилирует проект.");
                        }
                        else if (settings[0] == "eng")
                        {
                            Console.WriteLine("“exit„ - exit from programm.");
                            Console.WriteLine("“set path„ - enter path to the project.");
                            Console.WriteLine("“compile„ - compiles the project.");
                        }
                        break;
                    case "set path":
                        if (settings[0] == "rus")
                        {
                            Console.WriteLine(@"Введите путь в формате: “C:\Folder\Project folder„.");
                        }
                        else if (settings[0] == "eng")
                        {
                            Console.WriteLine(@"Enter path in the format: “C:\Folder\Project folder„.");
                        }
                        string json = File.ReadAllText(@"C:\Users\" + user_name + @"\AppData\Roaming\Real engine\settings.json");
                        dynamic jsonObj = JsonConvert.DeserializeObject(json);
                        jsonObj["path_to_engine"] = Console.ReadLine();
                        File.WriteAllText(@"C:\Users\" + user_name + @"\AppData\Roaming\Real engine\settings.json", JsonConvert.SerializeObject(jsonObj, Formatting.Indented));
                        settings[2] = jsonObj["path_to_engine"];
                        break;
                    case "compile":
                        if (settings[2] == "")
                        {
                            if (settings[0] == "rus")
                            {
                                Console.WriteLine("Пожалуйста введите путь к проекту командой “set path„.");
                            }
                            else if (settings[0] == "eng")
                            {
                                Console.WriteLine("Please enter the path to project with command “set path„.");
                            }
                        }
                        else
                        {
                            compiler compiler = new compiler();
                            compiler.compile(user_name, settings);
                            //вывод названия
                            using (StreamReader sr = new StreamReader("icon.txt"))
                            {
                                Console.ForegroundColor = ConsoleColor.Magenta;
                                for (int i = 0; i < 7; i++)
                                {
                                    Console.WriteLine(sr.ReadLine());
                                }
                                sr.Close();
                                Console.ForegroundColor = ConsoleColor.White;
                                Console.WriteLine();
                            }

                            //начало
                            if (settings[0] == "rus")
                            {
                                Console.ForegroundColor = ConsoleColor.Yellow;
                                Console.WriteLine("Спасибо за использование HScript!!!");
                                Console.ForegroundColor = ConsoleColor.White;
                                Console.WriteLine("Версия: " + settings[1]);
                                Console.WriteLine();
                                Console.WriteLine("Введите “help„ для помощи.");
                            }
                            else if (settings[0] == "eng")
                            {
                                Console.ForegroundColor = ConsoleColor.Yellow;
                                Console.WriteLine("Thank for using HScript!!!");
                                Console.ForegroundColor = ConsoleColor.White;
                                Console.WriteLine("Version: " + settings[1]);
                                Console.WriteLine();
                                Console.WriteLine("Enter “help„ for help.");
                            }
                        }
                        break;
                    case "exit":
                        main_thread = false;
                        if (settings[0] == "rus")
                        {
                            Console.WriteLine("Пока(");
                        }
                        else if (settings[0] == "eng")
                        {
                            Console.WriteLine("Goodbye(");
                        }
                        break;
                    case "impossible":
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(932, 150);
                        Thread.Sleep(150);
                        Console.Beep(1047, 150);
                        Thread.Sleep(150);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(699, 150);
                        Thread.Sleep(150);
                        Console.Beep(740, 150);
                        Thread.Sleep(150);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(932, 150);
                        Thread.Sleep(150);
                        Console.Beep(1047, 150);
                        Thread.Sleep(150);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(784, 150);
                        Thread.Sleep(300);
                        Console.Beep(699, 150);
                        Thread.Sleep(150);
                        Console.Beep(740, 150);
                        Thread.Sleep(150);
                        Console.Beep(932, 150);
                        Console.Beep(784, 150);
                        Console.Beep(587, 1200);
                        Thread.Sleep(75);
                        Console.Beep(932, 150);
                        Console.Beep(784, 150);
                        Console.Beep(554, 1200);
                        Thread.Sleep(75);
                        Console.Beep(932, 150);
                        Console.Beep(784, 150);
                        Console.Beep(523, 1200);
                        Thread.Sleep(150);
                        Console.Beep(466, 150);
                        Console.Beep(523, 150);
                        break;
                }
            }
        }
    }
}
