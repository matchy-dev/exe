using System;

namespace crlf
{
    class Crlf
    {
        static int Main(string[] args)
        {
            if (args.Length < 1) {
                string cmd = System.Reflection.Assembly.GetExecutingAssembly().Location;
                int idx = cmd.LastIndexOf("\\");
                if (idx != -1) {
                    cmd = cmd.Substring(idx + 1);
                }
                Console.WriteLine(cmd + " file");
                return -1;
            }

            string filePath = args[0];
            System.IO.FileStream fs = null;

            try {
                fs = new System.IO.FileStream(
                    filePath,
                    System.IO.FileMode.Open,
                    System.IO.FileAccess.Read,
                    System.IO.FileShare.ReadWrite
                );

                byte[] data = new byte[1024];
                int size;
                bool cr, lf, crlf;
                cr = lf = crlf = false;
                byte save = 0;

                while ((size = fs.Read(data, 0, data.Length)) > 0) {
                    for (int i = 0; i < size; i++) {
                        switch (data[i]) {
                            case 10:
                                if (save == 13) {
                                    crlf = true;
                                }
                                else {
                                    lf = true;
                                }
                                break;
                            case 13:
                                break;
                            default:
                                if (save == 13) {
                                    cr = true;
                                }
                                break;
                        }
                        save = data[i];
                    }
                }
                if (save == 13) {
                    cr = true;
                }

                string retStr = "";
                if (cr) {
                    retStr = "CR";
                }
                if (lf) {
                    if (retStr.Length > 0) {
                        retStr += " ";
                    }
                    retStr += "LF";
                }
                if (crlf) {
                    if (retStr.Length > 0) {
                        retStr += " ";
                    }
                    retStr += "CRLF";
                }
                Console.WriteLine(retStr);
            }
            catch (System.IO.IOException ex) {
                Console.WriteLine(ex.Message);
                return -1;
            }
            finally {
                if (fs != null) {
                    fs.Close();
                }
            }

            return 0;
        }
    }
}
