#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#define MAX_MESSAGE_LENGTH 512

int getCipherKey(void);
int validateMessage(char message[MAX_MESSAGE_LENGTH - 1]);
void getMessage(char message[MAX_MESSAGE_LENGTH - 1]);
void encrypt(int cipherKey, char message[MAX_MESSAGE_LENGTH - 1], char encryptedMessage[MAX_MESSAGE_LENGTH]);
void decrypt(char encrypted[MAX_MESSAGE_LENGTH], int cipherKey, char decrypted[MAX_MESSAGE_LENGTH - 1]);

#endif