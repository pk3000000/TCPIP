#include <stdio.h>
#include <WinSock2.h>
#include <stdlib.h>

#define PORT_NUM      20012
#define MAX_MSG_LEN 512
#define SERVER_IP        "127.0.0.1"
int main()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);//���� �ʱ�ȭ           

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//���� ����
	if (sock == -1) { return -1; }

	SOCKADDR_IN servaddr = { 0 };//���� �ּ�
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(PORT_NUM);

	int re = 0;
	re = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));//���� ��û
	if (re == SOCKET_ERROR) { exit(1); }

	char msg[MAX_MSG_LEN] = "";
	char buffer[MAX_MSG_LEN] = "";
	int recvData = 0;

	recvData = recv(sock, msg, sizeof(msg), 0);//����
	
	if (recvData == 0)
	{
		printf("���� ����\n");
		closesocket(sock);
	}

	printf("����:%s\n", msg);

	while (true)
	{
		gets_s(msg, MAX_MSG_LEN);
		sprintf(buffer, "REQ %s", msg);
		send(sock, buffer, strlen(buffer), 0);//�۽�
		if (strcmp(buffer, "REQ exit") == 0) { break; }
		recv(sock, buffer, strlen(msg), 0);//����
		printf("����:%s\n", msg);
	}
	closesocket(sock);//���� �ݱ�
	WSACleanup();//���� ����ȭ
	return 0;
}