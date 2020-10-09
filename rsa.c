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

// Code to demonstrate RSA algorithm 
int rsa(int hashKey) 
{ 
    // Two random prime numbers 
    int p = 43; 
    int q = 47; 
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
  
    // Private key (d stands for decrypt) 
    // choosing d such that it satisfies 
    // d*e = 1 + k * totient 
    int k = 2;  // A constant value 
    int d = (1 + (k*phi))/e; 
    
    //checkDistinctPrimeFactors(p, q);
    // Message to be encrypted 
    printf("\nMessage data = %d", hashKey); 
  
    // Encryption c = (msg ^ e) % n 
    int c = exponentMod(hashKey, e, n); 
    printf("\nEncrypted data = %d", c); 
  
    // Decryption m = (c ^ d) % n 
    int m = exponentMod(c, d, n); 
    printf("\nOriginal Message Sent = %d", m); 
    
    printf("\n n = %d", n);
    return 0; 
} 
// This code is contributed by Akash Sharan. 
