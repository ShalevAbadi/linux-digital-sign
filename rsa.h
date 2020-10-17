#ifndef _myfile_h
#define _myfile_h

int gcd(int a, int h);
int rsa(int hashKey);
int generateKeys(int p, int q, int *resN, int *publicK, int *privateK);
int encrypt(int plain, int privateK, int keyLength);
int isValidSignature(int hash, int publicK, int keyLength, int expectedCipher);

#endif