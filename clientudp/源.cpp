#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
# define BUFFER_SIZE 1024 //��������С
int main()
{
	SOCKET sock_Client; //�ͻ�������ͨ�ŵ�Socket
	WSADATA WSAData;
	char receBuf[BUFFER_SIZE]; //�������ݵĻ�����
	char sendBuf[BUFFER_SIZE]; //�������ݵĻ�����

	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		printf("��ʼ��ʧ��!");
		return -1;
	}

	//��ʼ��
	sock_Client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//�����ͻ�������ͨ�ŵ�Socket
	SOCKADDR_IN addr_server; //�������ĵ�ַ���ݽṹ
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(4567);//�˿ں�Ϊ4567
	addr_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //127.0.0.1Ϊ������IP��ַ
	SOCKADDR_IN sock;
	int len = sizeof(sock);
	while (true)
	{
		cout << "������Ҫ���͵�����:";
		cin >> sendBuf;
		sendto(sock_Client, sendBuf, strlen(sendBuf), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
		//int last=recv(sock_Client, receBuf, strlen(receBuf), 0); // (����recv��recvfrom������)
		int last = recvfrom(sock_Client, receBuf, strlen(receBuf), 0, (SOCKADDR*)&sock, &len);
		if (last > 0)
		{
			receBuf[last] = '\0'; //���ַ������һ��'\0'����ʾ�����ˡ���Ȼ���������
			if (strcmp(receBuf, "bye") == 0)
			{
				cout << "������������������..." << endl;//������������byeʱ���ر�socket
				closesocket(sock_Client);
				break;
			}
			else
			{
				printf("���յ����ݣ�%s\n", receBuf);
			}

		}

	}
	closesocket(sock_Client);
	WSACleanup();


	return 0;
}