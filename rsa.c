#include<stdio.h> 
#include<math.h> 

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

int modInverse(int a, int m) 
{ 
    a = a%m; 
    for (int x=1; x<m; x++) 
       if ((a*x) % m == 1) 
          return x; 
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

int isPrime(int n)  
{  
    // Corner cases  
    if (n <= 1)  return 0;  
    if (n <= 3)  return 1;  
    
    // This is checked so that we can skip   
    // middle five numbers in below loop  
    if (n%2 == 0 || n%3 == 0) return 0;  
    
    for (int i=5; i*i<=n; i=i+6)  
        if (n%i == 0 || n%(i+2) == 0)  
           return 0;  
    
    return 1;  
}  

int generateKeys(int p, int q, int* resN, int* publicK, int* privateK)
{
    int n = p*q; 
    int e = 2; 
    int phi = (p-1)*(q-1); 
    while (e < phi) 
    { 
        if (isPrime(e) && gcd(e, phi)==1) 
            break;
        else
            e++; 
    } 
    if(e >= phi){
        printf("Can't find E\n");
        return 0;
    }
    int k = 2;
    int d = modInverse(e, phi);

    *publicK = d;
    *privateK = e;
    *resN = n;

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

int isValidSignature(int hash, int publicK, int keyLength, int expectedCipher)
{
    return decrypt(expectedCipher, publicK, keyLength) == hash;
}
