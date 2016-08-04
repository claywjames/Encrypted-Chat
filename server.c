#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "encryption.h"
 
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define MAX_CONNECTIONS 1
#define MAX_MESSAGE_LENGTH 512
 
int main(void) {
    WSADATA wsa;
    SOCKET listener, connection;
    struct sockaddr_in server;
    char message[MAX_MESSAGE_LENGTH - 1], encryptedMessage[MAX_MESSAGE_LENGTH] ,recievedMessage[MAX_MESSAGE_LENGTH], decryptedMessage[MAX_MESSAGE_LENGTH - 1];
    int cipherKey, sendResult, recieveResult, shutdownResult;
 
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    } 
    puts("Initialized.");
     
    if((listener = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 1;
    }
    puts("Socket created.");
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 5050 );
     
    if( bind(listener, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        return 1;
    }  
    puts("Bind done");
     
    listen(listener, MAX_CONNECTIONS);
    puts("Waiting for a connection...");
    
    connection = accept(listener , NULL, NULL);
    if (connection == INVALID_SOCKET) {
        printf("accept failed with error code : %d" , WSAGetLastError());
        return 1;
    }
    else {
        puts("Connection accepted");
        closesocket(listener);
    }

    while (1) {
        recieveResult = recv(connection, recievedMessage, MAX_MESSAGE_LENGTH, 0);
        if (recieveResult > 0) {
            printf("encrypted message: %s\n", recievedMessage);
            cipherKey = getCipherKey();
            decrypt(recievedMessage, cipherKey, decryptedMessage);
            printf("Decrypted: %s\n\n", decryptedMessage);
        } else if (recieveResult == 0) {
            puts("connection closed");
            break;
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            break;
        }

        getMessage(message);

        if (strcmp(message, "quit\n") == 0){
            puts("quitting...");
            shutdownResult = shutdown(connection, SD_BOTH);
            if (shutdownResult == SOCKET_ERROR) printf("Shutdown failed: %d\n", WSAGetLastError());
            break;
        }

        cipherKey = getCipherKey();
        encrypt(cipherKey, message, encryptedMessage);
        printf("Encrypted Message: %s\n", encryptedMessage); 

        sendResult = send(connection, encryptedMessage, MAX_MESSAGE_LENGTH, 0);
        if (sendResult < 0) {
            printf("send failed: %d\n", WSAGetLastError());
            break;
        }
        puts("Message Sent\n");
        puts("Waiting for response; no messages can be sent until response arrives.\n");

    }
 
    closesocket(connection);
    WSACleanup();
 
    return 0;
}
