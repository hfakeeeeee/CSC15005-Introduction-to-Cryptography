#define PRIME true
#define NOT_PRIME false
#include <bits/stdc++.h>


using namespace std;

// Kiem tra so nguyen to khong hieu qua voi so qua lon
uint64_t gcd(uint64_t a, uint64_t b) 
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

uint64_t mod_power(uint64_t a, uint64_t b, uint64_t p)
{
    if (b == 1) return a % p;
    else 
    {
        uint64_t x = mod_power(a, b/2, p);

        if(b % 2 == 0) return (x * x) % p;
        else 
        return ( ( (x * x) % p) * a) % p;
        
    }
}

bool fermat(uint64_t n)
{
    if (n==2 || n==3)
    {
        return PRIME;
    }
    if (n < 2) return NOT_PRIME;

    srand (time(NULL));
    uint64_t a = 2 + rand() % (n - 3);

    if( gcd(a , n) != 1) return NOT_PRIME;
    else 
    {
        if (mod_power(a, n-1 , n) != 1) return NOT_PRIME;
        else 
        return PRIME;
    }
 
}
 
bool fermat_test(uint64_t n)
{
    for (uint64_t i=0; i < 3; i++)
    {
        if (fermat(n) == false) return false;
    }
    return true;
}
// Kiem tra snt 2 lau hon nhung hieu qua hon
bool isPrime(uint64_t num) {
    vector<uint64_t> num_factors;
    for (uint64_t i=2; i<=static_cast<uint64_t>(sqrt(num)); i++){
        if (num % i == 0) {
            num_factors.push_back(i);
            num_factors.push_back(num/i);
        }
    }
    if (num_factors.size() != 0) return false;
    else return true;
}


void menu() {
    cout << "------  KeySize  ------\n";
    cout << "|    [1]: 512 bits    |\n";
    cout << "|    [2]: 1024 bits   |\n";
    cout << "|    [3]: 2048 bits   |\n";
    cout << "-----------------------\n";
}

// Nhan 2 so lon
string multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
 
    vector<int> result(len1 + len2, 0);
 
    int i_n1 = 0;
    int i_n2 = 0;
     
    for (int i=len1-1; i>=0; i--) {
        int carry = 0;
        int n1 = num1[i] - '0';
        i_n2 = 0;           
        for (int j=len2-1; j>=0; j--) {
            int n2 = num2[j] - '0';
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            carry = sum/10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
 
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
 
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
 
    if (i == -1)
    return "0";
 
    string s = "";
     
    while (i >= 0)
        s += std::to_string(result[i--]);
    return s;
}

// Cong so lon
string sum(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2);
    string str = "";

    uint64_t n1 = str1.length(), n2 = str2.length();
 
    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    uint64_t carry = 0;
    for (uint64_t i=0; i<n1; i++)
    {
        uint64_t sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
 
        carry = sum/10;
    }
    for (uint64_t i=n1; i<n2; i++)
    {
        uint64_t sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());
 
    return str;
}

// Tru so lon
bool isSmaller(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
 
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
 
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
 
    return false;
}
string subtract(string str1, string str2)
{
    if (isSmaller(str1, str2))
        swap(str1, str2);
 
    string str = "";
 
    int n1 = str1.length(), n2 = str2.length();
 
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
 
    int carry = 0;
 
    for (int i = 0; i < n2; i++) {
 
        int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }

    for (int i = n2; i < n1; i++) {
        int sub = ((str1[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }
    reverse(str.begin(), str.end());
 
    return str;
}

// Calc RSA keyGen String execution
string calc_n(string p, string q) {
    return multiply(p, q);
}

string calc_Phin(string p, string q) {
    string def = "1";
    string p_1 = subtract(p, def);
    string q_1 = subtract(q, def);
    return multiply(p_1, q_1);
}

// Random Prime Number
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    int64_t res = 0;
    while (a != 0) {
        if (a & 1) {
 
            res = (res + b) % m;
        }
        a >>= 1;
        b = (b << 1) % m;
    }
    return res;
}
 
uint64_t powMod(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t x = 1; 
    a %= n;
    while (b > 0) {
        if (b % 2 == 1) {
            x = mulmod(x, a, n); // multiplying with base
        }
        a = mulmod(a, a, n); // squaring the base
        b >>= 1;
    }
    return x % n;
}
 
std::vector<int> first_primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                    31, 37, 41, 43, 47, 53, 59, 61, 67,
                                    71, 73, 79, 83, 89, 97, 101, 103,
                                    107, 109, 113, 127, 131, 137, 139,
                                    149, 151, 157, 163, 167, 173, 179,
                                    181, 191, 193, 197, 199, 211, 223,
                                    227, 229, 233, 239, 241, 251, 257,
                                    263, 269, 271, 277, 281, 283, 293,
                                    307, 311, 313, 317, 331, 337, 347, 
                                    349, 353, 359, 367, 373, 379, 383, 
                                    389, 397, 401, 409, 419, 421, 431, 
                                    433, 439, 443, 449, 457, 461, 463, 
                                    467, 479, 487, 491, 499, 503, 509};
 
uint64_t getRandom64() {
    
    constexpr int bits = 31;
    std::bitset<bits> a;
    a.reset();
    
    srand(time(NULL));
    static std::mt19937 gen(rand());
    std::uniform_int_distribution<short> distr(0, 1);
 
    for (int i = 0; i < bits; i++) {
        a[i] = distr(gen);
    }
 
    a[0] = 1;
    a[bits - 1] = 1;
    return a.to_ullong();
}
uint64_t getLowLevelPrime() {
    
    while (true) {
        uint64_t candidate = getRandom64();
        bool is_prime = true;
        /*for (int i = 0; i < first_primes.size(); i++) {
            if (candidate == first_primes[i])
                return candidate;
 
            if (candidate % first_primes[i] == 0) {
                is_prime = false;
                break;
            }
        }*/
        if (fermat_test(candidate) != 1) {
            is_prime = false;
        }
        if (is_prime)
            return candidate;
    }
}
bool trialComposite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2) {
    if (powMod(a, evenC, to_test) == 1)
        return false;
 
    for (int i = 0; i < max_div_2; i++) {
        uint64_t temp = static_cast<uint64_t>(1) << i;
        if (powMod(a, temp * evenC, to_test) == to_test - 1)
            return false;
    }
 
    return true;
}
bool MillerRabinTest(uint64_t to_test) {
    constexpr int accuracy = 20;
 
    int max_div_2 = 0;
    uint64_t evenC = to_test - 1;
    while (evenC % 2 == 0) {
        evenC >>= 1;
        max_div_2++;
    }

    srand(time(NULL));
    static std::mt19937 gen(rand());
    std::uniform_int_distribution<uint64_t> distr(2, to_test);

    for (int i = 0; i < accuracy; i++) {
        uint64_t a = distr(gen);
 
        if (trialComposite(a, evenC, to_test, max_div_2)) {
            return false;
        }
    }
    return true;
}
 
uint64_t getBigPrime() {
    while (true) {
        uint64_t candidate = getLowLevelPrime();
        if (MillerRabinTest(candidate))
            return candidate;
    }
}
// Calc RSA keyGen Number execution
uint64_t calc_n_num(uint64_t p, uint64_t q) {
    return p * q;
}
uint64_t calc_Phin_num(uint64_t p, uint64_t q) {
    return (p-1) * (q-1);
}
uint64_t calc_e(uint64_t phi){
    uint64_t e;
    do {
        e = 2 + rand() % (phi - 2);
    }
    while (fermat_test(e) != 1 && gcd(e, phi) != 1);
    return e;
}
uint64_t calc_d(uint64_t phi, uint64_t e){
    uint64_t k = 1;
    while (((k*phi)+1)%e != 0) {
        k++;
    }
    uint64_t d = ((k*phi)+1)/e;
    return d;
}


int main() {
    int key_size, option;
    menu();
    cout << "Select your choice: ";
    cin >> option;

    switch (option) {
        case 1:
            key_size = 512;
            break;
        case 2:
            key_size = 1024;
            break;
        case 3:
            key_size = 2048;
            break;
        default:
            cout << "Error!!!\n";
            break;
    }
    cout << "Key Gen Size: " << key_size << endl;
    uint64_t p;
    p = getBigPrime();
    uint64_t q;
    q = getBigPrime();

    cout << "p: " << p << endl;
    cout << "q: " << q << endl;

    // string str_p = to_string(p);
    // string str_q = to_string(q);
    // cout << calc_n(str_p, str_q) << endl;
    // cout << calc_Phin(str_p, str_q) << endl;
    uint64_t phin = calc_Phin_num(p, q);
    uint64_t e = calc_e(phin);
    cout << "n = p*q = " << calc_n_num(p, q) << endl;
    cout << "Phi(n) = (p - 1) * (q - 1) = " << phin << endl;
    cout << "e: " << e << endl;
    cout << "d: " << calc_d(phin, e) << endl;
    return 0;
}