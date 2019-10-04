#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BigInt unsigned long long int

int isPrime(BigInt x){
    BigInt i;
    for (i = 2;i * i <= x;i++){
        if (x % i == 0)
        {
            return 0; // x is not prime
        }
    }
    return 1; // prime
}

BigInt inverse_element(BigInt e, BigInt Euler_n){
    BigInt d;
    for (d = 2;d < Euler_n;d++){
        if ((e * d) % Euler_n == 1){
            return d;
        }
    }
}

int isCoprime(BigInt a, BigInt b){
    BigInt temp;
    while (b > 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    if (a == 1){
        return 1; // is Coprime
    }
    else{
        return 0; // not Coprime
    }
}

BigInt Fast_modular_exponentiation(BigInt M, BigInt ep, BigInt mod){
    BigInt remainder = 1;
    unsigned long long int powNum = M;
    while(ep > 0){
        if (ep & 1){
            remainder = (remainder * powNum) % mod; 
        }
        powNum = (powNum * powNum) % mod;
        ep = ep >> 1;
        
    } 
    return remainder;
}
int main(){
    BigInt p, q, n, Euler_n, e, d, M;
    BigInt encrypted_M, decrypted_M;

    // Enter two prime
    printf("Enter two prime number 'p' and 'q' (Ex: 3 7) : ");
    scanf("%lld%lld", &p, &q);
    // check the input numbers are both prime 
    while(!isPrime(p)){
        printf("%lld is not prime number!, ReEnter a prime number 'p' :", p);
        scanf("%lld", &p);
    }
    while (!isPrime(q)){
        printf("%lld is not prime number!, ReEnter a prime number 'q' :", q);
        scanf("%lld", &q);
    }

    // get 'n' by 'p' and 'q'
    n = p * q;
    Euler_n = (p - 1) * (q - 1);


    // Enter public key 'e'
    printf("Enter the 'e' (relatively prime to n = (p - 1)(q - 1)) : ");
    scanf("%lld", &e);
    // check 1 < e < Euler(n)
    while (!(1 < e && e < Euler_n)){
        printf("Require:1 < 'e' < Euler(n), ReEnter the number 'e' : ");
        scanf("%lld", &e);
    }
    // check n and e is coprime
    while(!isCoprime(e, Euler_n))
    {
        printf("%lld and %lld are not relatively prime to each other, ReEnter the number 'e' : ", e, Euler_n);
        scanf("%lld", &e);
    }

    printf("Enter Message 'M' : ");
    scanf("%lld", &M);

    // get 'e' inverse -> (e * d) mod Euler(n) = 1 
    d = inverse_element(e, Euler_n);

    
    
    printf("\n-------------- 1. Initail input----------------\n");
    printf("Input prime number 'p' : \n %lld \n", p);
    printf("Input prime number 'q' : \n %lld \n", q);
    printf("Input public key 'e' : \n %lld \n", e);
    printf("Input Message 'M' : \n %lld \n", M);

    printf("\n-------------- 2.Encrypt and Decrypt Message by [User input] key pair (e, d)       ----------------\n");
    printf("Key pair (e, d) = (%lld, %lld)\n", e, d);
    printf("Message 'M' : %lld \n", M);
    printf("\n2-1. Eecrypt Message by Public key 'e'\n");
    encrypted_M = Fast_modular_exponentiation(M, e, n);
    printf("   %lld ^ %lld mod %lld = %lld\n", M, e, n, encrypted_M);
    printf("   **Encryted Message = %lld\n", encrypted_M);
    printf("2-2. Decrypt Message by private key 'd'\n");
    decrypted_M = Fast_modular_exponentiation(encrypted_M, d, n);
    printf("   %lld ^ %lld mod %lld = %lld\n", encrypted_M, d, n, decrypted_M);
    printf("   **Decryted Message is %lld\n", decrypted_M);


    // random e
    do
    {
        srand(time(NULL));
        e = rand() % Euler_n;
    } while(e <= 1 || !isCoprime(e, Euler_n));
    d = inverse_element(e, Euler_n);
    printf("\n-------------- 3.Encrypt and Decrypt Message by [Random generation] key pair (e, d) ----------------\n");
    printf("Key pair (e, d) = (%lld, %lld)\n", e, d);
    printf("Message 'M' : %lld \n", M);
    printf("\n3-1. Eecrypt Message by Public key 'e'\n");
    encrypted_M = Fast_modular_exponentiation(M, e, n);
    printf("   %lld ^ %lld mod %lld = %lld\n", M, e, n, encrypted_M);
    printf("   **Encryted Message = %lld\n", encrypted_M);
    printf("3-2. Decrypt Message by private key 'd'\n");
    decrypted_M = Fast_modular_exponentiation(encrypted_M, d, n);
    printf("   %lld ^ %lld mod %lld = %lld\n", encrypted_M, d, n, decrypted_M);
    printf("   **Decryted Message is %lld\n", decrypted_M);
}