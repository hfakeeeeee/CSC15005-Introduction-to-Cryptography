#define PRIME true
#define NOT_PRIME false
#include <stdlib.h>     
#include <iostream>
#include <time.h>  


using namespace std;

long long gcd(long long a, long long b) 
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long mod_power(long long a, long long b, long long p)
{
    if (b == 1) return a % p;
    else 
    {
        long long x = mod_power(a, b/2, p);

        if(b % 2 == 0) return (x * x) % p;
        else 
        return ( ( (x * x) % p) * a) % p;
        
    }
}

bool fermat(long long n)
{
    if (n==2 || n==3)
    {
        return PRIME;
    }
    if (n < 2) return NOT_PRIME;

    srand (time(NULL));

    long long a = 2 + rand() % (n - 3);

    if( gcd(a , n) != 1) return NOT_PRIME;
    else 
    {
        if (mod_power(a, n-1 , n) != 1) return NOT_PRIME;
        else 
        return PRIME;
    }
 
}
 
bool fermat_test(long long n)
{
    for (int i = 0; i < 3; i++)
    {
        if (fermat(n) == NOT_PRIME) return false;
    }
    return true;
}

int main()
{
    long long n;
    cout << "Enter a number to check if it is prime: ";
    cin >> n;

    if (fermat_test(n) == 1) 
    {
        cout << n <<" is a prime number" << endl;
    } else cout << n << " is a compositive number" << endl;

    return 0;
}

 
