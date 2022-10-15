#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int a[1001][1001],h[1001],le[1001],ri[1001];
signed main()
{
    int m,n,res=0;
    cin>>m>>n;
    forinc(i,1,m)
    forinc(j,1,n) cin>>a[i][j];
    forinc(i,1,m)
    {
        deque<int> l,r;
        forinc(j,1,n)
        {
            if(a[i][j]==1)++h[j];
            else h[j]=0;
        }
        forinc(j,1,n)
        {
            while(!l.empty()&&h[l.back()]>=h[j]) l.pop_back();
            if(l.empty()) le[j]=0;
            else le[j]=l.back();
            l.push_back(j);
        }
        fordec(j,n,1)
        {
            while(!r.empty()&&h[r.back()]>=h[j]) r.pop_back();
            if(r.empty()) ri[j]=n+1;
            else ri[j]=r.back();
            r.push_back(j);
        }
        forinc(j,1,n)
        {
            int tmp=h[j]*(ri[j]-le[j]-1);
            res=max(res,tmp);
        }
    }
    cout<<res;
}
