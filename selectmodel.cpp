#include<iostream>
#include<WinSock2.h>
#include <windows.h>
#include<thread>
#pragma comment(lib,"ws2_32.lib")

#define _C11_THREAD_
#ifdef _C11_THREAD_
void thread_func(const SOCKET sock){
	const SOCKET *sockServer = &sock;
#else
DWORD WINAPI thread_func(LPVOID lpParam){
	SOCKET *sockServer = (SOCKET*)lpParam;
#endif
	sockaddr_in client;
	int dSize = sizeof(client);

	SOCKET AcceptSocket;
	
	timeval time1;
	time1.tv_sec = 2;
	time1.tv_usec = 0;

	fd_set readSet;

	while (1){

		FD_ZERO(&readSet);
		FD_SET(*sockServer, &readSet);
		int ret;
		if ((ret = select(0, &readSet, NULL, NULL, &time1)) >0){
			std::cout << "ret-->" << ret << std::endl;
			if (FD_ISSET(*sockServer, &readSet)){
				AcceptSocket = accept(*sockServer, (sockaddr*)&client, &dSize);//流式套接字sockServer必须处于监听状态下
				std::cout << "client connected!" << ",addr: " << inet_ntoa(client.sin_addr) << "::" << ntohs(client.sin_port) << std::endl;
			}
		}
	}
}

void main(){
	WSADATA wsaData;
	WORD    wsaVesion;
	wsaVesion = MAKEWORD(2, 2);

	if (WSAStartup(wsaVesion, &wsaData) != 0)
	{
		std::cout << "occur error when WSAStartup" << std::endl;
		WSACleanup();
		return;
	}

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(5505);

	if (bind(sockServer, (sockaddr*)&server, sizeof(server)) != 0)
	{
		std::cout << "occur error when bind add" << std::endl;
		WSACleanup();
		return;
	}

	if (listen(sockServer, 10) != 0){
		std::cout << "occur error when listen add" << std::endl;
		WSACleanup();
		return;
	}

	

#ifdef _C11_THREAD_
	std::thread t(thread_func, sockServer);
#else
	DWORD dwThreadId;
	CreateThread(NULL, 0, thread_func, &sockServer, 0, &dwThreadId);
#endif
	system("pause");

}
