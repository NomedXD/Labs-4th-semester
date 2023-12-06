import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class FTPClient {
    public static final int DEFAULT_BUFFER_SIZE = 8192;
    public static int nthIndexOf(String text, char needle, int n)
    {
        for (int i = 0; i < text.length(); i++)
        {
            if (text.charAt(i) == needle)
            {
                n--;
                if (n == 0)
                {
                    return i;
                }
            }
        }
        return -1;
    }
    public static void main(String[] args) {
        String server = "ftp.otenet.gr"; //test.rebex.net   ftp.dlptest.com  demo.wftpserver.com ftp.otenet.gr
        int port = 21;
        String user = "speedtest"; //demo dlpuser demo anonymous
        String pass = "speedtest"; //password rNrKYTX9g7z3RgJRmxWuGHbeu demo *пустая строка*
        Socket socket = null;
        try {
            socket = new Socket(server, port);
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            String response = reader.readLine();
            while (!response.endsWith("220 ")) {
                System.out.println(response);
                response = reader.readLine();
            }
            System.out.println(response);

            System.out.println("USER " + user);
            writer.write("USER " + user + "\r\n");
            writer.flush();
            response = reader.readLine();
            System.out.println(response);

            System.out.println("PASS " + pass);
            writer.write("PASS " + pass + "\r\n");
            writer.flush();
            response = reader.readLine();
            System.out.println(response);

            System.out.println("PWD");
            writer.write("PWD\r\n");
            writer.flush();
            response = reader.readLine();
            System.out.println(response);


            System.out.println("TYPE A");
            writer.write("TYPE A\r\n"); // Установка транспортного режима на ASCII
            writer.flush();
            response = reader.readLine();
            System.out.println(response);

            System.out.println("PASV");
            writer.write("PASV\r\n"); // Пассивный режим передачи данных
            writer.flush();
            response = reader.readLine();
            System.out.println(response);

            StringBuffer str = new StringBuffer(response);
            str.delete(0, str.indexOf("(") + 1);
            str.delete(str.indexOf(")"), str.length());
            Socket socket2 = null;
            String serverTemp = str.substring(0,nthIndexOf(str.toString(),',',4));
            String server2 = serverTemp.replaceAll(",", ".");

            int port2 = Integer.parseInt(str.substring(nthIndexOf(str.toString(),',',4)+1,
                    nthIndexOf(str.toString(),',',5))) * 256 +
                    Integer.parseInt(str.substring(nthIndexOf(str.toString(),',',5)+1, str.length())); //256*40+1
            socket2 = new Socket(server2, port2);
            BufferedReader reader2 = new BufferedReader(new InputStreamReader(socket2.getInputStream()));
            BufferedWriter writer2 = new BufferedWriter(new OutputStreamWriter(socket2.getOutputStream()));

            writer.write("LIST\r\n");
            writer.flush();
            response = reader2.readLine();
            while (response!=null) {
                System.out.println(response);
                response = reader2.readLine();
            }
            response = reader.readLine();
            while (!response.endsWith("226 Directory send OK.")) {
                System.out.println(response);
                response = reader.readLine();
            }
            System.out.println(response);

            System.out.println("TYPE I");
            writer.write("TYPE I\r\n");
            writer.flush();
            response = reader.readLine();
            System.out.println(response);

            System.out.println("PASV");
            writer.write("PASV\r\n"); // Пассивный режим передачи данных
            writer.flush();
            response = reader.readLine();
            System.out.println(response);

            StringBuffer str2 = new StringBuffer(response);
            str2.delete(0, str2.indexOf("(") + 1);
            str2.delete(str2.indexOf(")"), str2.length());
            Socket socket3 = null;
            String serverTemp1 = str2.substring(0,nthIndexOf(str2.toString(),',',4));
            String server3 = serverTemp1.replaceAll(",", ".");

            String s1 = str2.substring(nthIndexOf(str2.toString(),',',4)+1,
                    nthIndexOf(str2.toString(),',',5));
            String s2 = str2.substring(nthIndexOf(str2.toString(),',',5)+1, str2.length());
            int port3 = Integer.parseInt(s1)*256 + Integer.parseInt(s2);
            socket3 = new Socket(server3, port3);

            byte[] array = new byte[500*1000];
            Arrays.fill(array, (byte) 1);
            InputStream reader3 = socket3.getInputStream();
            writer.write("RETR test100k.db\r\n");
            writer.flush();
            response = reader.readLine();
            System.out.println(response);
            response = reader.readLine();
            System.out.println(response);
            array = reader3.readNBytes(102400);



            System.out.println("HELP");
            writer.write("HELP\r\n");
            writer.flush();
            response = reader.readLine();
            while (!response.endsWith("Help OK.")) {
                System.out.println(response);
                response = reader.readLine();
            }
            System.out.println(response);

            // Конец соединения
            System.out.println("QUIT");
            writer.write("QUIT\r\n");
            writer.flush();
            response = reader.readLine();
            System.out.println(response);
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
