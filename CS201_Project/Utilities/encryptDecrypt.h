#ifndef ENCRYPT_DECRYPT
#define ENCRYPT_DECRYPT

#include <bits/stdc++.h>
using namespace std;

inline int generateRandom() {
    return 65+rand()%62;
}
inline int generateRandom2() {
    return 1+rand()%4;
}
inline bool isNumeric(char c) {
    return ((c>='0'&&c<='9')?true:false);
}

vector<int> prime;


void primeFiller(int M) {
    vector<bool> sieve(M, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i < M; ++i) {
        if (sieve[i]) {
            for (int j = i * i; j < M; j += i) {
                sieve[j] = false;
            }
        }
    }
    for (int i = 2; i < M; ++i) {
        if (i>=11 && sieve[i]) prime.push_back(i);
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int getNextPrime(int x) {
    int s=0, e=prime.size()-1;
    while (e-s>1) {
        int mid=(s+e)/2;
        if (x<=prime[mid]) e=mid;
        else s=mid;
    } 
    return prime[e];
}

pair<int,int> getPrimes(string accountNumber) {
    pair<int,int> ans;
    string a,b;
    if(accountNumber.size()!=0){
        a=accountNumber.substr(0,4);
        b=accountNumber.substr(8,4);

    }
    int x=convertToLongLong(a), y=convertToLongLong(b);
    x=getNextPrime(x);
    y=getNextPrime(y);
    if(x==y){
        y=getNextPrime(y);
    }
    return {x,y};
}

// return the keys for that particular accountNumber
pair<int,pair<int,int>> getKeys(string accountNumber) {
    pair<int,int> pq = getPrimes(accountNumber);
    int p=pq.first, q=pq.second;
    int n=p*q, phi=(p-1)*(q-1);
    int pbk=2, pvk = 2;;
    while (gcd(pbk, phi)!=1) pbk++;
    while ((pvk*pbk)%phi!=1) pvk++;
    return {n,{pbk, pvk}};
}

long long modExp(long long base, long long exp, int mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long encrypt(int message, int public_key, int n) {
    return modExp(message, public_key, n);
}

long long decrypt(int encrypted, int private_key, int n) {
    return modExp(encrypted, private_key, n);
}


string encodeMessage(const string &message, string accountNumber) {
    pair<int,pair<int,int>> keys = getKeys(accountNumber);
    int n=keys.first, pbk=keys.second.first;
    string cipherText="";
    for (char c : message) {
        int asciiVal = int(c),  encryptedChar = encrypt(asciiVal, pbk, n);
        string s = to_string(encryptedChar);
        cipherText += s;
        for (int i=1; i<=generateRandom2(); i++) {
            cipherText += char(generateRandom());
        }
    }
    return cipherText;
}

string decodeMessage(const string &cipherText, string accountNumber) {
    pair<int,pair<int,int>> keys = getKeys(accountNumber);
    int n=keys.first, pvk=keys.second.second;
    string plainText;
    int i=0, m=cipherText.size();
    while (i<m) {
        string temp="";
        while (i<m && isNumeric(cipherText[i])) {
            temp+=cipherText[i];
            i++;
        }
        long long int x = convertToLongLong(temp);
        long long int y = decrypt(x,pvk,n);
        plainText += char(y);
        while (i<m && !isNumeric(cipherText[i])) {
            i++;
        }
    }
    return plainText;
}

#endif
