#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "encryption.h"

#pragma comment(lib,"WS2_32.lib") //Winsock Library

#define MAX_MESSAGE_LENGTH 512

int main(void) {
    WSADATA wsa;
    SOCKET connection;
    char IP[16], message[MAX_MESSAGE_LENGTH - 1], encryptedMessage[MAX_MESSAGE_LENGTH], recievedMessage[MAX_MESSAGE_LENGTH], decryptedMessage[MAX_MESSAGE_LENGTH - 1];
    struct sockaddr_in server;
    int cipherKey, sendResult, recieveResult, shutdownResult;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    puts("Initialized.");

    if((connection = socket(AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    puts("Socket created.");
 
    puts("Please enter your chat partner's IP address");
    fgets(IP, 16, stdin);

    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons( 5050 );    

    if (connect(connection, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    puts("Connected.");

    while (1) {
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

    }

    closesocket(connection);
    WSACleanup();
    return 0;
}