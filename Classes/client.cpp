#include "client.h"

UDPClient::UDPClient() : sockfd(INVALID_SOCKET)
{
	// ��ʼ��winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed to initialize Winsock\n");
		exit(EXIT_FAILURE);
	}
	// ʹ��ipv4Э�飬���ݱ��׽��֣�ʹ��Ĭ��Э��udp
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == INVALID_SOCKET) {
		printf("Create socket error\n");
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	// ���÷�������ַ
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;// ipv4
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);// ������ip
	servaddr.sin_port = htons(SERVER_PORT);// �˿�
}

UDPClient::~UDPClient()
{
	// �ر��׽���
	if (sockfd != INVALID_SOCKET) {
		closesocket(sockfd);
		printf("Client closed\n");
	}
	// ����winsock
	WSACleanup();
}

bool UDPClient::Connect()
{
	return true;  // UDP�������ӵģ����Connect������UDP�в�����Ҫ��
}

void UDPClient::Send(const char* message)
{
	sendto(sockfd, message, strlen(message), 0, (sockaddr*)&servaddr, sizeof(servaddr));

}

void UDPClient::Receive()
{
	char buff[BUFFSIZE];

	while (true) {
		int bytesRead = recvfrom(sockfd, buff, BUFFSIZE - 1, 0, NULL, NULL);

		if (bytesRead == SOCKET_ERROR) {
			printf("Receive error\n");
			break;
		}

		buff[bytesRead] = '\0';
		printf("Received from server: %s\n", buff);
	}
}
