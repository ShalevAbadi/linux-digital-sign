#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rsa.h"
#include "hashFile.h"

#define MAX_CHAR_INPUT_SIZE 300
#define PRIVATE_KEY_FILE_NAME "rsa.private"
#define PUBLIC_KEY_FILE_NAME "rsa.public"
 
/*
    rsa.public structure
    keyLength publicK
*/

/*
Hash = 78
Public key: 3
Private key: 27907
Key length: 42817
Encrypted hash: 3565
*/
void readPublicKey(int *key, int *keyLength)
{
    FILE *publicKeyFile = fopen(PUBLIC_KEY_FILE_NAME, "r");
    assert(publicKeyFile);
    fscanf(publicKeyFile, "%d %d", keyLength, key);
    fclose(publicKeyFile);
}

void readPrivateKey(int *key, int *keyLength)
{
    FILE *publicKeyFile = fopen(PUBLIC_KEY_FILE_NAME, "r");
    FILE *privateKeyFile = fopen(PRIVATE_KEY_FILE_NAME, "r");
    assert(publicKeyFile);
    assert(privateKeyFile);
    fscanf(publicKeyFile, "%d", keyLength);
    fclose(publicKeyFile);
    fscanf(privateKeyFile, "%d", keyLength);
    fclose(privateKeyFile);
}

void writePublicKey(int key, int keyLength)
{   
    FILE *publicKeyFile = fopen(PUBLIC_KEY_FILE_NAME, "w+");
    assert(publicKeyFile);
    printf("writing public key to %s\n", PUBLIC_KEY_FILE_NAME);
    fprintf(publicKeyFile, "%d %d", keyLength, key);
    fclose(publicKeyFile);
}

void writePrivateKey(int key)
{
    FILE *privateKeyFile = fopen(PRIVATE_KEY_FILE_NAME, "w+");
    assert(privateKeyFile);
    printf("writing private key to %s\n", PRIVATE_KEY_FILE_NAME);
    fprintf(privateKeyFile, "%d", key);
    fclose(privateKeyFile);
}

int hash()
{   
    FILE *input;
    char filePath[MAX_CHAR_INPUT_SIZE];
    printf("Enter file path\n");
    scanf("%49[^\n]%*c", filePath);
    if ((input = fopen(filePath, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
    }
    printf("The mother fucking hash isssss: %d\n" , hashFile(input));
}

int encryptHash()
{   
    int hash, publicK, keyLength;
    printf("Enter hash\n");
    scanf("%d", &hash);
    readPublicKey(&publicK, &keyLength);
    printf("Encrypted hash is: %d\n", encrypt(hash, publicK, keyLength));
}

int decryptHash()
{
    int hash, privateK, keyLength;
    printf("Enter encrypted hash\n");
    scanf("%d", &hash);
    printf("Enter key\n");
    scanf("%d", &privateK);
    printf("Enter key length\n");
    scanf("%d", &keyLength);
    printf("%d\n", decrypt(hash, privateK, keyLength));
}

int generateKeyPair()
{
    int p = 47; 
    int q = 911; 
    int publicK, privateK, keyLength;

    if (!generateKeys(p, q, &keyLength, &publicK, &privateK))
    {
        printf("Failed to generate keys\n");
        return 1;
    }
    printf("Public key: %d\nPrivate key: %d\nKey length: %d\n", publicK, privateK, keyLength);
    writePrivateKey(privateK);
    writePublicKey(publicK, keyLength);
    return 0;
}

int signFile()
{
    FILE *input;
    char filePath[MAX_CHAR_INPUT_SIZE];
    int hash, publicK, keyLength, sinature;
    printf("Enter file path\n");
    scanf("%49[^\n]%*c", filePath);
    if ((input = fopen(filePath, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    hash=hashFile(input);
    readPublicKey(&publicK, &keyLength);
    printf("Singature: %d", encrypt(hash, publicK, keyLength));
}

int validateSignature(){
    FILE *input;
    char filePath[MAX_CHAR_INPUT_SIZE];
    int hash, publicK, keyLength, sinature;
    printf("Enter file path\n");
    scanf("%49[^\n]%*c", filePath);
    if ((input = fopen(filePath, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    hash=hashFile(input);
    printf("Enter singature\n");
    scanf("%d", &sinature);
    readPublicKey(&publicK, &keyLength);
    if(isValidSignature(hash, publicK, keyLength, sinature)){
        printf("Valid signature :)\n");
    } else {
       printf("Not a valid signature :(\n");
    }
    return 0;
}

int main()
{   
    FILE *input;
    int option;
    printf("Select option:\n0)Sign a file\n1)hash\n2)encrypt\n3)validate signature\n4)decrypt hash\n5)generate keys\n");
    scanf("%d", &option);
    getchar();
    switch(option)
    {   
        case 0:
            signFile();
            break;
        case 1:
            hash();
            break;
        case 2:
            encryptHash();
            break;
        case 3:
            validateSignature();
            break;
        case 4:
            decryptHash();
            break;
        case 5:
            generateKeyPair();
            break;
        default:
            printf("No option selected, bye :)");
            return 0;
    }
    return 0;
}