// C program for RSA asymmetric cryptographic 
// algorithm. For demonstration values are 
// relatively small compared to practical 
// application 
#include<stdio.h> 
#include<math.h> 

// Recursive C program to compute modular power 
#include <stdio.h> 

int exponentMod(int A, int B, int C) 
{ 
	// Base cases 
	if (A == 0) 
		return 0; 
	if (B == 0) 
		return 1; 

	// If B is even 
	long y; 
	if (B % 2 == 0) { 
		y = exponentMod(A, B / 2, C); 
		y = (y * y) % C; 
	} 

	// If B is odd 
	else { 
		y = A % C; 
		y = (y * exponentMod(A, B - 1, C) % C) % C; 
	} 

	return (int)((y + C) % C); 
} 

// Returns gcd of a and b 
int gcd(int a, int h) 
{ 
    int temp; 
    while (1) 
    { 
        temp = a%h; 
        if (temp == 0) 
          return h; 
        a = h; 
        h = temp; 
    } 
} 

int generateKeys(int p, int q, int* resN, int* publicK, int* privateK)
{
    
    // First part of public key: 
    int n = p*q; 
    
    // Finding other part of public key. 
    // e stands for encrypt 
    int e = 2; 
    int phi = (p-1)*(q-1); 
    while (e < phi) 
    { 
        // e must be co-prime to phi and 
        // smaller than phi. 
        if (gcd(e, phi)==1) 
            break;

        else
            e++; 
    } 
    if(e >= phi){
        printf("Can't find E\n");
        return 0;
    }
    // Private key (d stands for decrypt) 
    // choosing d such that it satisfies 
    // d*e = 1 + k * totient 
    int k = 2;  // A constant value 
    int d = (1 + (k*phi))/e;

    *publicK = d;
    *privateK = e;
    * resN = n;

    return 1;
}

int decrypt(int cipher, int privateK, int keyLength)
{
    return exponentMod(cipher, privateK, keyLength);
}

int encrypt(int plain, int publicK, int keyLength)
{
    return exponentMod(plain, publicK, keyLength);
}

int isValidSignature(int hash, int publicK, int keyLength, int expectedChiper)
{
    return encrypt(hash, publicK, keyLength) == expectedChiper;
}

// Code to demonstrate RSA algorithm 
int rsa(int hashKey) 
{ 
    // Two random prime numbers 
    int p = 47; 
    int q = 911; 
    int publicK, privateK, keyLength;

    if (!generateKeys(p, q, &keyLength, &publicK, &privateK))
    {
        printf("Failed to generate keys\n");
        return 0;
    }
    //checkDistinctPrimeFactors(p, q);
    // Message to be encrypted 
    printf("\nMessage data = %d", hashKey);
  
    // Encryption c = (msg ^ e) % n 
    int c = encrypt(hashKey, publicK, keyLength);
    printf("\nEncrypted data = %d", c); 
  
    // Decryption m = (c ^ d) % n 
    int m = decrypt(c, privateK, keyLength);
    printf("\nOriginal Message Sent = %d", m); 
    
    printf("\n N = %d and D=%d and E=%d\n", keyLength, privateK, publicK);
    return 1; 
} 
// This code is contributed by Akash Sharan. 
