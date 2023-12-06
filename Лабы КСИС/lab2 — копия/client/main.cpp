#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")



int main() {
    // Инициализируем библиотеку Windows Sockets
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Создаем сокет для клиента
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Задаем параметры адреса сервера
    sockaddr_in server_address;
    server_address.sin_family = AF_INET; // тип адреса IPv4
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // адрес сервера
    server_address.sin_port = htons(8888); // номер порта
    bool flag = false;

    // Подключаемся к серверу
    connect(client_socket, (SOCKADDR*)&server_address, sizeof(server_address));
    std::cout << "Connected to server!" << std::endl;
    char bt[1];
    recv(client_socket, bt, 1, 0);
    if (bt[0] == 1)
        flag = true;
    // Создаем буфер для получения и отправки сообщений
    char buffer[1024];
    int bytes_received;
    

    // Бесконечный цикл для отправки и получения сообщений от сервера
    while (true) {
        if (!flag) {
            // Отправляем сообщение на сервер
            std::cin.getline(buffer, 1024);
            // переменная врекмени = 0;
            // переменная массив копия = массив который посылаем;
            send(client_socket, buffer, strlen(buffer), 0); // ТУТ ПОМЕНЯТЬ НА РАНДОМНЫЕ ДАННЫЕ // ЗАВОДИШЬ ПЕРЕМЕННУЮ ВРЕМЯ И ЗАНУЛЯЕШЬ
            
            // Получаем ответ от сервера
            bytes_received = recv(client_socket, buffer, 1024, 0);
            // Измерить время
            if (bytes_received == SOCKET_ERROR) {
                // Если произошла ошибка, то сервер был отключен
                std::cout << "Server disconnected." << std::endl;
                break;
            }
            
            // Сравнить с копией массива
            buffer[bytes_received] = '\0';
            std::cout << "Server: " << buffer << std::endl;
        }
    }

    // Закрываем сокет и освобождаем ресурсы Windows Sockets
    closesocket(client_socket);
    WSACleanup();
    return 0;
}