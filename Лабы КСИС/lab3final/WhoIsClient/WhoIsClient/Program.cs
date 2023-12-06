using System.Net.Sockets;
using System.Net;
using System.Text;

TcpClient tcpClient = new TcpClient();

string Getdomain( string output)
{
    int index = output.IndexOf("refer: ");
    index += 7;
    char skip = '\n';
    string domain = "";
    while (output[index] != '\n')
    {
        if (output[index] != ' ')
            domain += output[index];
        index++;

    }
    return domain;
}

try
{
    // Попытка подключения к whoisIana
    await tcpClient.ConnectAsync("whois.iana.org", 43);
    Console.WriteLine("Подключение установлено");
    // Чтение доменного имени, которое нужно найти
    string name = Console.ReadLine();
    name += "\r\n";
    // Присовение потока клиента в переменную stream
    NetworkStream stream = tcpClient.GetStream();
    // Перевод доменного имени в utf8 для посылки данных
    var requestData = Encoding.UTF8.GetBytes(name);
    // Посылка данных
    await stream.WriteAsync(requestData);
    stream.Flush();
    int bytes = 2048;
    byte[] info = new byte[bytes];
    // Чтение данных в массив байтов
    await stream.ReadAsync(info, 0, bytes);
    // Перевод полученных данных в строку с учетом кодировки
    string output = Encoding.UTF8.GetString(info);
    // Парсинг строки для поиска сервера, на который идет перенаправление
    string domain = Getdomain(output);
    //Закрытие этого клиента
    tcpClient.Close();
    // Открытие нового клиента и такие же действия , но уже с сервером в переменной domain
    TcpClient tcpClient1 = new TcpClient();
    await tcpClient1.ConnectAsync(domain, 43);
    stream = tcpClient1.GetStream();
    await stream.WriteAsync(requestData);
    stream.Flush();
    await stream.ReadAsync(info, 0, bytes);
    output = Encoding.UTF8.GetString(info);
    Console.WriteLine(output);
}
catch (SocketException ex)
{
    Console.WriteLine(ex.Message);
}
catch (System.IO.IOException ex)
{
    Console.WriteLine(ex.Message);
}
