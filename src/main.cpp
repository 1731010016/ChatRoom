#include <iostream>
#include <thread>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed!" << std::endl;
		return -1;
	}


	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket == INVALID_SOCKET) {
		std::cerr << "Socket creation failed!" << std::endl;
		WSACleanup();
		return -1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8082);  // 目标端口
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 目标 IP 地址

	int code = connect(listen_socket, (sockaddr*)&serverAddr, sizeof(serverAddr));

	if (code == SOCKET_ERROR) {
		std::cout << GetLastError();
		std::cerr << "Connection failed!" << std::endl;
		closesocket(listen_socket);
		WSACleanup();
		return -1;
	}
	//std::this_thread::sleep_for(std::chrono::seconds(10));


	return 0;
}