#include <stdio.h>
#include <WinSock2.h>
#include <stdlib.h>

#define PORT_NUM      20012
#define MAX_MSG_LEN 512
#define SERVER_IP        "127.0.0.1"
int main()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);//윈속 초기화           

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//소켓 생성
	if (sock == -1) { return -1; }

	SOCKADDR_IN servaddr = { 0 };//소켓 주소
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(PORT_NUM);

	int re = 0;
	re = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));//연결 요청
	if (re == SOCKET_ERROR) { exit(1); }

	char msg[MAX_MSG_LEN] = "";
	char buffer[MAX_MSG_LEN] = "";
	int recvData = 0;

	recvData = recv(sock, msg, sizeof(msg), 0);//수신
	
	if (recvData == 0)
	{
		printf("연결 종료\n");
		closesocket(sock);
	}

	printf("수신:%s\n", msg);

	while (true)
	{
		gets_s(msg, MAX_MSG_LEN);
		sprintf(buffer, "REQ %s", msg);
		send(sock, buffer, strlen(buffer), 0);//송신
		if (strcmp(buffer, "REQ exit") == 0) { break; }
		recv(sock, buffer, strlen(msg), 0);//수신
		printf("수신:%s\n", msg);
	}
	closesocket(sock);//소켓 닫기
	WSACleanup();//윈속 해제화
	return 0;
}