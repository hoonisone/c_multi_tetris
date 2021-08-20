#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "error.h"
#include "client.h"
#pragma warning(disable : 4996)
ClientSocket* clientSocketCreate(char* ip, int port) {

    ClientSocket* cs = (ClientSocket*)malloc(sizeof(ClientSocket));
    if (WSAStartup(MAKEWORD(2, 2), &cs->wsaData) != 0) //소켓 라이브러리를 초기화하고 있다.
        errorPrint("WSAStartup() error!");

    cs->hSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성하고
    if (cs->hSocket == INVALID_SOCKET)
        errorPrint((char*)"socket() error");

    memset(&cs->servAddr, 0, sizeof(cs->servAddr));
    cs->servAddr.sin_family = AF_INET;
    cs->servAddr.sin_addr.s_addr = inet_addr(ip);
    cs->servAddr.sin_port = htons(port);

    if (connect(cs->hSocket, (SOCKADDR*)&cs->servAddr, sizeof(cs->servAddr)) == SOCKET_ERROR) //생성된 소켓을 바탕으로 서버에 연결요청을 하고 있다
        errorPrint((char*)"connect() error!");

    return cs;
}

int clientSocketRequest(ClientSocket* cs, char* request, char* response) {
    send(cs->hSocket, request, BUFFER_SIZE-1, 0);
    int result = recv(cs->hSocket, response, BUFFER_SIZE - 1, 0); //recv 함수 호출을 통해서 서버로부터 전송되는 데이터를 수신하고 있다.
    return result;
}

void clientSocketTerminate(ClientSocket* cs) {
    closesocket(cs->hSocket); //소켓 라이브러리 해제

    WSACleanup();
    free(cs);
}