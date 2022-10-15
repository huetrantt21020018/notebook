#include <bits/stdc++.h>
using namespace std;

long long base = 137;
long long mod  = (long long) 1e9+123;
int pow_base[100005];

struct hash{
    int len;
    vector <long long> val;

    void init(string s){
        len = s.length();
        s = '0' + s;
        val.assign(len+1, 0);

        for(int i=1;i<s.length();i++)
            val[i] = (val[i-1] * base + (s[i] - 'a')) % mod;
    }

    long long get(int l,int r){
        return (val[r] - val[l-1] * pow_base[r - l + 1] + mod * mod) % mod;
    }
};

string s;
hash hashS;

void prep(){
    pow_base[0] = 1;
    for(int i=1;i<=100000;i++)
        pow_base[i] = pow_base[i-1] * base % mod;
}

int main(){
    prep();

    cin >> s;
    hashS.init(s);
    cout << hashS.get(1, hashS.len);
}
