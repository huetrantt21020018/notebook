// https://codeforces.com/group/e2kzH9Ilfm/contest/302365/problem/H
// {[()]}
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define int long long
using namespace std;

const int N = 1e7+5, mod = 1e9+7;
int n;
int gt[N], igt[N], p[N];
// p[i] = số cách điền i ngoặc mở
string s;

int pw(int a,int i)
{
    int b = 1;
    for(; i; i >>= 1, a = a*a %mod) if(i&1) b = b*a %mod;
    return b;
}

int C(int k,int n)
{
    return igt[k]*igt[n-k]%mod*gt[n]%mod;
}

void prepare()
{
    gt[0] = 1;
    forinc(i,1,n) gt[i] = gt[i-1]*i %mod;
    igt[n] = pw(gt[n],mod-2);
    fordec(i,n,1) igt[i-1] = igt[i]*i %mod;
    p[0] = 1;
    forinc(i,1,n) p[i] = p[i-1]*3 %mod;
}

int tt(char x)
{
    if(x=='(') return 0;
    if(x=='[') return 1;
    if(x=='{') return 2;
    return 3;
}

int calc(int l,int r,int n) /// số dãy bắt đầu bậc l, kết thúc bậc r và độ dài n
{
    if(l>r) swap(l,r);
    int k=(n+r-l)/2;
    return C(k,n) %mod;
}

int cnt(int i,int n) /// số dãy đúng có bậc bắt đầu i và độ dài n
{
    if(i>n||(n-i)%2) return 0;
    return p[(n-i)/2]*(calc(i,0,n)-calc(i,-2,n)+mod)%mod;
}

void solve()
{
    string s;
    cin >> s;
    s = ' '+s;
    int dem = 0, res = 0;
    forinc(i,1,n)
    {
        int t = tt(s[i]);
        res += t*cnt(dem+1,n-i);
        res %= mod;
        if(t<3) ++dem;
        else --dem;
    }
    cout << (res+1) %mod;
}

main()
{
//    freopen("brcnt2.inp","r",stdin);

    cin >> n;
    prepare();
    solve();
}


/**
A = C((n-i-j)/2,n-i)
B = C((n-i-j)/2-1,n-i)
A-B
*/
