#include <iostream>
#include <thread>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

void handle_client(SOCKET client_socket) {
    printf("%llu: ��������\n", client_socket);
    while (1) {
        char buffer[1024] = { 0 };
        int ret = recv(client_socket, buffer, 1024, 0);
        if (ret <= 0) {
            break;
        }
        printf("%llu: %s\n", client_socket, buffer);
        // ԭ�ⲻ������ȥ
        send(client_socket, buffer, (int)strlen(buffer), 0);
    }
    closesocket(client_socket);
    printf("%llu: �뿪����\n", client_socket);
}


int start_server() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed!");
        return -1;
    }

    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == INVALID_SOCKET) {
        printf("Socket creation failed!");
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr = { 0 };
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);  // Ŀ��˿�
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Ŀ�� IP ��ַ

    if (-1 == bind(listen_socket, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
        printf("bind socket failed! errcode :%d", GetLastError());
        return -1;
    }

    if (-1 == listen(listen_socket, 10)) {
        printf("listen socket failed! errcode :%d", GetLastError());
        return -1;
    }

    // �ȴ��ͻ�������
    while (1) {
        SOCKET client_socket = accept(listen_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            printf("accept socket failed! errcode :%d", GetLastError());
            continue;
        }
        // ʹ���̴߳����ͻ�������
        std::thread(handle_client, client_socket).detach();  // detach ���߳̽��Զ����������̲߳���Ҫ�ȴ���
    }
    // �رշ���socket
    closesocket(listen_socket);
    WSACleanup();
    return 0;
}

int main() {
    start_server();
    return 0;
}