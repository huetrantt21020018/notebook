/*
https://codeforces.com/contest/319/problem/C
*/
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define int long long
#define pii pair<int,int>
#define st first
#define nd second

using namespace std;
const int N = 1e5+5;

int n, a[N], b[N];
int f[N];

struct convex_hull_min
{
    pii st[N];
    int top;
    int F(int i,int a)
    {
        if(i<1 || i>top) return 2e18;
        return st[i].st * a + st[i].nd;
    }
    bool xoa(pii a, pii b, pii c)
    {
        double A = 1.0*(b.nd-a.nd)/(a.st-b.st);
        double B = 1.0*(c.nd-b.nd)/(b.st-c.st);
        return A>=B;
    }
    void add(int a,int b) // y = ax + b
    {
        pii t = make_pair(a,b);
        while(top>1 && xoa(st[top-1],st[top],t)) --top;
        st[++top] = t;
    }
    bool check(int i,int a) // min
    {
        if(F(i,a)<=F(i+1,a)) return 1;
        return 0;
    }
    int sol(int a)
    {
        int l=1, r=top, id=1;
        while(l<=r)
        {
            int mid = (l+r)/2;
            if(check(mid,a))
            {
                id = mid;
                r = mid-1;
            }
            else l = mid+1;
        }
        return F(id,a);
    }
}T;

main()
{
    //freopen("319C.inp","r",stdin);

    cin >> n;
    forinc(i,1,n) cin >> a[i];
    forinc(i,1,n) cin >> b[i];

    T.add(b[1],0);
    forinc(i,2,n)
    {
        f[i] = T.sol(a[i]);
        T.add(b[i],f[i]);
    }
    cout << f[n];
}
