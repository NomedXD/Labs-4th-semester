#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")



int main() {
    // �������������� ���������� Windows Sockets
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // ������� ����� ��� �������
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // ������ ��������� ������ �������
    sockaddr_in server_address;
    server_address.sin_family = AF_INET; // ��� ������ IPv4
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // ����� �������
    server_address.sin_port = htons(8888); // ����� �����
    bool flag = false;

    // ������������ � �������
    connect(client_socket, (SOCKADDR*)&server_address, sizeof(server_address));
    std::cout << "Connected to server!" << std::endl;
    char bt[1];
    recv(client_socket, bt, 1, 0);
    if (bt[0] == 1)
        flag = true;
    // ������� ����� ��� ��������� � �������� ���������
    char buffer[1024];
    int bytes_received;
    

    // ����������� ���� ��� �������� � ��������� ��������� �� �������
    while (true) {
        if (!flag) {
            // ���������� ��������� �� ������
            std::cin.getline(buffer, 1024);
            // ���������� �������� = 0;
            // ���������� ������ ����� = ������ ������� ��������;
            send(client_socket, buffer, strlen(buffer), 0); // ��� �������� �� ��������� ������ // �������� ���������� ����� � ���������
            
            // �������� ����� �� �������
            bytes_received = recv(client_socket, buffer, 1024, 0);
            // �������� �����
            if (bytes_received == SOCKET_ERROR) {
                // ���� ��������� ������, �� ������ ��� ��������
                std::cout << "Server disconnected." << std::endl;
                break;
            }
            
            // �������� � ������ �������
            buffer[bytes_received] = '\0';
            std::cout << "Server: " << buffer << std::endl;
        }
    }

    // ��������� ����� � ����������� ������� Windows Sockets
    closesocket(client_socket);
    WSACleanup();
    return 0;
}