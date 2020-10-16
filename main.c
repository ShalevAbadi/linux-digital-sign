#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include<time.h> 
#include "rsa.h"
#include "hashFile.h"

#define MAX_CHAR_INPUT_SIZE 300
#define PRIVATE_KEY_FILE_NAME "rsa.private"
#define PUBLIC_KEY_FILE_NAME "rsa.public"
#define SIGNATURE_FILE_NAME "signature.enc"

/*
    keyfiles structure:
    keyLength key
*/

void readKey(int *key, int *keyLength, char* filename)
{
    FILE *keyFile = fopen(filename, "r");
    assert(keyFile);
    fscanf(keyFile, "%d %d", keyLength, key);
    fclose(keyFile);
}

void writeKey(int key, int keyLength, char* filename)
{   
    FILE *keyFile = fopen(filename, "w+");
    assert(keyFile);
    printf("writing key to %s\n", keyFile);
    fprintf(keyFile, "%d %d", keyLength, key);
    fclose(keyFile);
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
    int hash, privateK, keyLength;
    printf("Enter hash\n");
    scanf("%d", &hash);
    readKey(&privateK, &keyLength, PRIVATE_KEY_FILE_NAME);
    printf("Encrypted hash is: %d\n", encrypt(hash, privateK, keyLength));
}

int decryptHash()
{
    int hash, publicK, keyLength;
    printf("Enter encrypted hash\n");
    scanf("%d", &hash);
    readKey(&publicK, &keyLength, PUBLIC_KEY_FILE_NAME);
    printf("%d\n", decrypt(hash, publicK, keyLength));
}

int generateRandomPrime()
{      
    int primes_len = 143;
    int primes[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, \
                179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, \
                263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, \
                353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, \
                443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, \
                547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, \
                641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, \
                739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, \
                839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, \
                947, 953, 967, 971, 977, 983, 991, 997};
    time_t t;
    srand((unsigned) time(&t));
    int n = rand() % primes_len;
    return primes[n];
}

int generateKeyPair()
{   
    int p, q, publicK, privateK, keyLength;
    p = generateRandomPrime(); 
    do
    {
        q = generateRandomPrime();
    }
    while(q == p);
    if (!generateKeys(p, q, &keyLength, &publicK, &privateK))
    {
        printf("Failed to generate keys\n");
        return 1;
    }
    printf("Public key: %d\nPrivate key: %d\nKey length: %d\n", publicK, privateK, keyLength);
    writeKey(privateK, keyLength, PRIVATE_KEY_FILE_NAME);
    writeKey(publicK, keyLength, PUBLIC_KEY_FILE_NAME);
    return 0;
}

void wrieSignatureToFile(int signature, char* fileName)
{
    FILE *input;
    if ((input = fopen(fileName, "w+")) == NULL)
        {
            printf("Error - Couldn't open the file");
            return;
        }
    fprintf(input, "%d\n", signature);
    fclose(input);
}

int readSignatureFromFile(char* fileName)
{
    FILE *input;
    int res;
    if ((input = fopen(fileName, "r")) == NULL)
        {
            printf("Error - Couldn't open the file");
            return 1;
        }
    fscanf(input, "%d", &res);
    fclose(input);
    return res;
}

int signFile()
{
    FILE *input;
    char filePath[MAX_CHAR_INPUT_SIZE];
    int hash, privateK, keyLength, sinature;
    printf("Enter file path\n");
    scanf("%49[^\n]%*c", filePath);
    if ((input = fopen(filePath, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    hash=hashFile(input);
    fclose(input);
    readKey(&privateK, &keyLength, PRIVATE_KEY_FILE_NAME);
    wrieSignatureToFile(encrypt(hash, privateK, keyLength), SIGNATURE_FILE_NAME);
}

int validateSignature(){
    FILE *input;
    char filePath[MAX_CHAR_INPUT_SIZE];
    int hash, publicK, keyLength, signature;
    printf("Enter file path\n");
    scanf("%49[^\n]%*c", filePath);
    if ((input = fopen(filePath, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    hash=hashFile(input);
    readKey(&publicK, &keyLength, PUBLIC_KEY_FILE_NAME);
    signature = readSignatureFromFile(SIGNATURE_FILE_NAME);
    if(isValidSignature(hash, publicK, keyLength, signature)){
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