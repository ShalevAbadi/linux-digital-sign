#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "rsa.h"
#include "hashFile.h"

#define OPTION_ARGV_POS 1
#define FIRST_FILE_NAME_ARGV_POS 2
#define SECOND_FILE_NAME_ARGV_POS 3
#define THIRD_FILE_NAME_ARGV_POS 4

/*
    keyfiles structure:
    keyLength key
*/

void readKey(int *key, int *keyLength, char *filename)
{
    FILE *keyFile = fopen(filename, "r");
    assert(keyFile);
    fscanf(keyFile, "%d %d", keyLength, key);
    fclose(keyFile);
}

void writeKey(int key, int keyLength, char *filename)
{
    FILE *keyFile = fopen(filename, "w+");
    assert(keyFile);
    fprintf(keyFile, "%d %d", keyLength, key);
    fclose(keyFile);
}

int generateRandomPrime()
{
    int primes_len = 143;
    int primes[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                    179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                    263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
                    353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439,
                    443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
                    547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,
                    641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
                    739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
                    839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
                    947, 953, 967, 971, 977, 983, 991, 997};
    time_t t;
    srand((unsigned)time(&t));
    int n = rand() % primes_len;
    return primes[n];
}

int generateKeyPair(char *privateKeyFileName, char *publicKeyFileName)
{
    int p, q, publicK, privateK, keyLength;
    p = generateRandomPrime();
    do
    {
        q = generateRandomPrime();
    } while (q == p);
    if (!generateKeys(p, q, &keyLength, &publicK, &privateK))
    {
        printf("Failed to generate keys\n");
        return 1;
    }
    printf("Public key: %d\nPrivate key: %d\nKey length: %d\n", publicK, privateK, keyLength);
    writeKey(privateK, keyLength, privateKeyFileName);
    writeKey(publicK, keyLength, publicKeyFileName);
    return 0;
}

void wrieSignatureToFile(int signature, char *fileName)
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

int readSignatureFromFile(char *fileName)
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

int signFile(char *fileToSign, char *sigantureFileName, char *privateKeyFileName)
{
    FILE *input;
    int hash, privateK, keyLength, sinature;
    if ((input = fopen(fileToSign, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    hash = hashFile(input);
    fclose(input);
    readKey(&privateK, &keyLength, privateKeyFileName);
    wrieSignatureToFile(encrypt(hash, privateK, keyLength), sigantureFileName);
    return 1;
}

int validateSignature(char *fileToValidate, char *sigantureFileName, char *publicKeyFileName)
{
    FILE *input;
    int hash, publicK, keyLength, signature;
    if ((input = fopen(fileToValidate, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    hash = hashFile(input);
    readKey(&publicK, &keyLength, publicKeyFileName);
    signature = readSignatureFromFile(sigantureFileName);
    if (isValidSignature(hash, publicK, keyLength, signature))
    {
        printf("Valid signature :)\n");
    }
    else
    {
        printf("Not a valid signature :(\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{

    int option;
    char *fileName1, *fileName2, *fileName3;
    if (argc == 4 || argc == 5)
    {
        option = atoi(argv[OPTION_ARGV_POS]);
        fileName1 = argv[FIRST_FILE_NAME_ARGV_POS];
        fileName2 = argv[SECOND_FILE_NAME_ARGV_POS];
        switch (option)
        {
        case 0:
            fileName3 = argv[THIRD_FILE_NAME_ARGV_POS];
            signFile(fileName1, fileName2, fileName3);
            break;
        case 1:
            fileName3 = argv[THIRD_FILE_NAME_ARGV_POS];
            validateSignature(fileName1, fileName2, fileName3);
            break;
        case 2:
            generateKeyPair(fileName1, fileName2);
            break;
        default:
            printf("No option selected, bye :)");
            return 0;
        }
    }
    else if (argc > 3)
    {
        printf("Too many arguments supplied.\n");
        return 1;
    }
    else
    {
        printf("3 or 4 argument expected.\n");
        return 1;
    }
    return 0;
}