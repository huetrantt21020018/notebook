// CSP 26.11.20
#include<bits/stdc++.h>
using namespace std;
#define forinc(i,a,b) for(int i=a;i<=b;++i)

const int N = 5e5+10;

struct Hash
{
	#define lli long long
	int n;
	lli base, mod;
    vector<lli> a, pw;
    Hash(int n, lli b, lli m) : n(n), base(b), mod(m), a(n+1), pw(n+1){
    	pw[0] = 1;
    	forinc(i,1,n) pw[i] = pw[i-1] * base % mod;
    }
    void upd(int i,lli x)
    {
        a[i] = a[i-1]*base + x;
        a[i] %= mod;
    }
    lli get(int l,int r)
    {
        lli res = a[r] - a[l-1] * pw[r-l+1] % mod;
		return (res + mod) % mod;
    }
};
int n, val[N], l, r;
int main()
{
	Hash a(n, 19937, 1e9+7);
	forinc(i,1,n) a.upd(i, val[i]);
    cout << a.get(l, r);
}
