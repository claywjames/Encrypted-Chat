#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib,"WS2_32.lib") //Winsock Library

int main(void)
{
    WSADATA wsa;
    SOCKET connection;
    char IP[16];
    struct sockaddr_in server;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    puts("Initialized.");

    if((connection = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    puts("Socket created.");
 
    puts("Please enter your chat partner's IP address");
    fgets(IP, 16, stdin);

    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );    

    if (connect(connection, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    puts("Connected");

    return 0;
}