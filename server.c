#include<stdio.h>
#include<winsock2.h>
 
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define MAX_CONNECTIONS 1
 
int main(void)
{
    WSADATA wsa;
    SOCKET listener, connection;
    struct sockaddr_in server;
 
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    } 
    puts("Initialized.");
     
    if((listener = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    puts("Socket created.");
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 5050 );
     
    if( bind(listener, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }  
    puts("Bind done");
     
    listen(listener, MAX_CONNECTIONS);
    puts("Waiting for incoming connections...");
    
    connection = accept(listener , NULL, NULL);
    if (connection == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
    }
    else 
    {
        puts("Connection accepted");
    }  
 
    closesocket(listener);
    WSACleanup();
 
    return 0;
}
