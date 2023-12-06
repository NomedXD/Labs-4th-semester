#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
    // Инициализируем библиотеку Windows Sockets
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Создаем сокет для сервера
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Задаем параметры адреса сервера
    sockaddr_in server_address;
    server_address.sin_family = AF_INET; // тип адреса IPv4
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // адрес локального узла
    server_address.sin_port = htons(8888); // номер порта

    // Связываем сокет сервера с адресом и портом
    bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address));

    // Начинаем прослушивание входящих соединений
    listen(server_socket, SOMAXCONN);

    std::cout << "Waiting for clients..." << std::endl;

    // Принимаем первого клиента
    SOCKET client_socket1 = accept(server_socket, NULL, NULL);
    std::cout << "Client 1 connected!" << std::endl;
    char buf[1] = { 0 };
    send(client_socket1, buf, 1, 0);

    // Принимаем второго клиента
    SOCKET client_socket2 = accept(server_socket, NULL, NULL);
    std::cout << "Client 2 connected!" << std::endl;
    buf[0] = 1;
    send(client_socket2, buf, 1, 0);

    // Создаем буфер для получения и отправки сообщений
    char buffer[1024];
    int bytes_received;

    // Бесконечный цикл для получения и отправки сообщений между клиентами
    while (true) {
        // Получаем сообщение от первого клиента
        bytes_received = recv(client_socket1, buffer, 1024, 0);
        if (bytes_received == SOCKET_ERROR) {
            // Если произошла ошибка, то клиент был отключен
            std::cout << "Client 1 disconnected." << std::endl;
            break;
        }
        buffer[bytes_received] = '\0';
        std::cout << "Client 1: " << buffer << std::endl;

        // Отправляем сообщение второму клиенту
        send(client_socket2, buffer, bytes_received, 0);

        // Получаем сообщение от второго клиента
        bytes_received = recv(client_socket2, buffer, 1024, 0);
        if (bytes_received == SOCKET_ERROR) {
            // Если произошла ошибка, то клиент был отключен
            std::cout << "Client 2 disconnected." << std::endl;
            break;
        }
        buffer[bytes_received] = '\0';
        std::cout << "Client 2: " << buffer << std::endl;

        // Отправляем сообщение первому клиенту
        send(client_socket1, buffer, bytes_received, 0);
    }

    // Закрываем сокеты и освобождаем ресурсы Windows Sockets
    closesocket(client_socket1);
    closesocket(client_socket2);
    closesocket(server_socket);

    WSACleanup();

    return 0;
}