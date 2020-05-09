#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define BUFFER_SIZE 1024
int main()
{
    WSADATA WSAData;
    char receBuf[BUFFER_SIZE];
    char Response[BUFFER_SIZE];
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        printf("��ʼ��ʧ��");
        exit(1);
    }
    SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockServer == INVALID_SOCKET)
    {
        printf("Failed socket() \n");
        return 0;
    }
    SOCKADDR_IN addr_Server; //�������ĵ�ַ����Ϣ
    addr_Server.sin_family = AF_INET;
    addr_Server.sin_port = htons(4567);
    addr_Server.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(sockServer, (SOCKADDR*)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR)
    {
        //�������뱾�ص�ַ��
        printf("Failed socket() %d \n", WSAGetLastError());
        return 0;
    }
    SOCKADDR_IN addr_Clt;

    int fromlen = sizeof(SOCKADDR);
    while (true)
    {
        int last = recvfrom(sockServer, receBuf, 1024, 0, (SOCKADDR*)&addr_Clt, &fromlen);
        if (last > 0)
        {
            //�жϽ��յ��������Ƿ�Ϊ��
            receBuf[last] = '\0';//���ַ������һ��'\0'����ʾ�����ˡ���Ȼ���������
            if (strcmp(receBuf, "bye") == 0)
            {
                cout << " �ͻ��˲�����������..." << endl;
                closesocket(sockServer);
                return 0;
            }
            else
            {
                printf("���յ����ݣ�%s����%s\n", inet_ntoa(addr_Clt.sin_addr), receBuf);
            }
        }
        cout << "�ظ��ͻ�����Ϣ:"; 
            cin >> Response; //���ͻ��˻ظ���Ϣ
        sendto(sockServer, Response, strlen(Response), 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR));
    }

    closesocket(sockServer);

    WSACleanup();
    return 0;
}