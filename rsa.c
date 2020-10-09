// C program for RSA asymmetric cryptographic
// algorithm. For demonstration values are
// relatively small compared to practical
// application
#include <stdio.h>
#include <math.h>
#include <float.h>

// Returns gcd of a and b
int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
}

int isEFactorN(int e, int n)
{
    return n % e == 0;
}

int isEInThetaRange(int e, int glambda)
{
    return e < glambda && e > 1;
}

int generateE(int p, int q, int n, int glambda)
{
    int e = 2;
    while (!(isEInThetaRange(e, glambda) && gcd(glambda, e) == 1))
    {
        e += 1;
    }
    return e;
}

int rsa(int hashKey)
{
    int p = 3;
    int q = 17;
    int n = p * q;
    int glambda = (p - 1) * (q - 1);
    int e = generateE(p, q, n, glambda);
    int k = 13;
    int d = ((k * glambda) + 1) / e;
    double c = powf(hashKey, e);
    c = fmod(c, n);

    //DECRYPTING
    double m = powf(c, d);
    m = fmod(m, n);

    printf("The hashkey is %d\n", hashKey);
    printf("Public Key E = %d\n", e);
    printf("Private Key D = %d\n", d);
    printf("Encrypted Message = %f\n", c);
    printf("Decrypted message = %f\n", m);

    return 1;
}

// Code to demonstrate RSA algorithm
int rsav2(int hashKey)
{
    hashKey = 3;
    // Two random prime numbers
    double p = 3;
    double q = 17;
    // hashKey = 25;
    // First part of public key:
    double n = p * q;

    // Finding other part of public key.
    // e stands for encrypt
    double e = 7;
    double phi = (p - 1) * (q - 1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient
    int k = 2; // A constant value
    double d = (1 + (k * phi)) / e;

    // Message to be encrypted
    printf("Message data = %d", hashKey);

    // Encryption c = (msg ^ e) % n
    float c = powf(hashKey, e);
    c = fmod(c, n);
    printf("\nEncrypted data = %lf", c);

    // Decryption m = (c ^ d) % n
    float m = powf(c, d);
    m = fmod(m, n);
    printf("\nOriginal Message Sent = %lf", m);

    printf("\n n = %lf\n", n);
    printf("d = %f\n", d);
    printf("e = %f\n", e);
    return 0;
}
// This code is contributed by Akash Sharan.
