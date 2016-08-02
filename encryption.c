#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASCII_LOWERCASE_A 97
#define ASCII_LOWERCASE_Z 122


int getCipherKey(void)
{
	char inputCipherKey[4];
	int cipherKey;
	printf("Enter the cipher key you wish to use: \n");
	fgets(inputCipherKey, 4, stdin);
	cipherKey = atoi(inputCipherKey);
	if (cipherKey < 1 || cipherKey > 25) {
		printf("Cipher key not valid.\n");
		return getCipherKey();
	}
	return cipherKey;
}

int validateMessage(char message[200])
{
	int i;
	for (i = 0; i < strlen(message) - 1; i++) {
		if (!(isalpha(message[i]) || message[i] == 32)) {
			return 0;
		}
	}
	return 1;
}

void getMessage(char message[200])
{
	printf("Enter message: \n");
	fgets(message, 200, stdin);
	if (validateMessage(message) == 0) {
		printf("Invalid Message\n");
		getMessage(message);
	}
}

void encrypt(int cipherKey, char message[200], char encryptedMessage[201])
{
	int i, newLetter;

	encryptedMessage[0] = 96 + cipherKey;
	for (i = 0; i < strlen(message) - 1; i++) {
		if (message[i] == 32) {
			encryptedMessage[i + 1] = message[i];
			continue;
		}
		message[i] = tolower(message[i]);
		newLetter = message[i] + cipherKey;
		if (!islower(newLetter)) newLetter = (ASCII_LOWERCASE_A - 1)+ (newLetter - ASCII_LOWERCASE_Z);
		encryptedMessage[i + 1] = newLetter;

	}

	encryptedMessage[i + 1] = '\0';
}

void decrypt(char encrypted[201], int cipherKey, char decrypted[200]) 
{
	int i, newLetter;

	for (i = 0; i < strlen(encrypted) - 1; i++) {
		if (encrypted[i + 1] == 32) {
			decrypted[i] = encrypted[i + 1];
			continue;
		}else {
			newLetter = encrypted[i + 1] - cipherKey;
			if (!islower(newLetter)) newLetter = (ASCII_LOWERCASE_Z + 1) - (ASCII_LOWERCASE_A - newLetter);
			decrypted[i] = newLetter;
		}
	}
	decrypted[i] = '\0';
}

int main(void) 
{
	char message[200], encryptedMessage[201], decryptedMessage[200];
	int encryptCipherKey, decryptCipherKey;

	encryptCipherKey = getCipherKey();
	getMessage(message);
	
	encrypt(encryptCipherKey, message, encryptedMessage);
	printf("encrypted: %s\n", encryptedMessage);

	printf("To decrypt, continue\n");
	decryptCipherKey = getCipherKey();
	decrypt(encryptedMessage, decryptCipherKey, decryptedMessage);
	printf("Decrypted Message: %s\n", decryptedMessage);

	fgetc(stdin);
	return 0;
}