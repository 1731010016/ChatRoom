#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET listen_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (listen_socket == INVALID_SOCKET) {
		printf("¥¥Ω®socket ß∞‹, ¥ÌŒÛ¬Î: %d\n", GetLastError());
		return -1;
	}


	return 0;
}