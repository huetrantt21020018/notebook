/*
https://codeforces.com/group/EHjycaJ7hn/contest/291337/problem/H
*/
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define int long long
using namespace std;

const int N = 2002, MAX = 2e9;
int n,g,k,a[N];
int s[N], s1[N], c[N][N], f[N][N];

void sol(int l,int r,int u,int v,int g1)
{
    if(u>v) return;
    int m = (u+v)/2, k = l;
    forinc(i,l,min(m-1,r))
    {
        if(f[i][g1-1]+c[i+1][m]<f[m][g1])
        {
            f[m][g1] = f[i][g1-1]+c[i+1][m];
            k = i;
        }
    }
    if(u==v) return;
    sol(l,k,u,m-1,g1);
    sol(k,r,m+1,v,g1);
}

main()
{
    //freopen("H.inp","r",stdin);

    cin >> n >> g >> k;
    forinc(i,1,n)
    {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
        s1[i] = s1[i-1] + a[i]*a[i];
    }
    forinc(i,1,n)
    forinc(j,i,n)
    {
        int v;
        if(k==1)
        {
            int tv = (i+j)/2;
            c[i][j] = a[tv]*(tv-i+1)-(s[tv]-s[i-1]) + (s[j]-s[tv])-a[tv]*(j-tv);
        }
        else
        {
            v = (s[j]-s[i-1])/(j-i+1);
            c[i][j] = (s1[j]-s1[i-1]) - 2*v*(s[j]-s[i-1]) + v*v*(j-i+1);
            v = (s[j]-s[i-1])/(j-i+1)+1;
            c[i][j] = min(c[i][j], (s1[j]-s1[i-1]) - 2*v*(s[j]-s[i-1]) + v*v*(j-i+1));
        }
    }
    memset(f,127,sizeof f);
    f[0][0] = 0;
    forinc(i,1,g) sol(0,n,1,n,i);
    cout << f[n][g];
}
