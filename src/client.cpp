#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int start_client() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed!");
        return -1;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        printf("create client_socket failed! errcode :%d", GetLastError());
        WSACleanup();
        return -1;
    }

    sockaddr_in targetAddr = { 0 };
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_port = htons(8080);  // Ŀ��˿�
    targetAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Ŀ�� IP ��ַ

    if (-1 == connect(client_socket, (sockaddr*)&targetAddr, sizeof(targetAddr))) {
        printf("connect server failed! errcode :%d", GetLastError());
        closesocket(client_socket);
        return -1;
    }

    while (1) {
        char sendBuffer[1024] = { 0 };
        char recvBuffer[1024] = { 0 };

        printf("%s", "please enter: ");
        // ���뷢������
        scanf("%s", sendBuffer);
        // ��������
        int ret = send(client_socket, sendBuffer, (int)strlen(sendBuffer), 0);
        if (ret <= 0) break;
        // ��������
        recv(client_socket, recvBuffer, 1024, 0);
        // ��ӡ��Ӧ����
        printf("%s\n",  recvBuffer);
    }

    closesocket(client_socket);

    return 0;
}

int main() {
    start_client();
    return 0;
}
