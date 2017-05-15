#include <WinSock2.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512		// 상수는 값 변경의 번거로움을 덜어준다.
#define DEFAULT_PORT 20012

//using namespace std;

int main()
{
	char buffer[DEFAULT_BUFLEN];
	struct sockaddr_in server_addr, client_addr;
	char temp[20];
	SOCKET server_fd, client_fd;
	int len, msg_size;
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);//윈속 초기화     
	int conn_count = 0;

	if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		printf("Server : can not open Socket\n");
		exit(0);
	}

	memset(&server_addr, 0x00, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(DEFAULT_PORT);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Server: can not bind local address\n");
		exit(0);
	}

	if (listen(server_fd, 2) < 0)
	{
		printf("Server: can not listen connect.\n");
		exit(0);
	}

	len = sizeof(client_addr);
	printf("=====[PORT] : %d =====\n", 20012);
	printf("Server : waiting connection request\n");

	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);


		if (client_fd < 0)
		{
			printf("Server: accept failed\n");
			exit(0);
		}
		
		send(client_fd, "ACT 접속되었습니다.", sizeof("ACT 접속되었습니다."), 0);

		while (recv(client_fd, buffer, DEFAULT_BUFLEN, 0) > 0)
		{
			char * cPtr;
			char tempBuffer[DEFAULT_BUFLEN];

			cPtr = strtok(buffer, " ");

			do{
				cPtr = strtok(NULL, " ");
			} while (cPtr!=NULL);

			sprintf(tempBuffer, "RES %s", cPtr);

			send(client_fd, tempBuffer, strlen(tempBuffer), 0);
		}

	}
	closesocket(server_fd);
	WSACleanup();
	return 0;
}