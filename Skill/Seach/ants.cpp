#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
long long n, a[400005], b[400005],c[400005];
bool check(long long x)
{
    forinc(i,1,n) c[i]=b[i];
    forinc(i,1,n-1)
    {
        long long d=(c[i]-x)-(a[i+1]-a[i]),e=0;
         if(c[i]>x)
             c[i+1]+=max(e,d);
             else if(c[i]<x) c[i+1]+=d;
    }
    return(c[n]>=x);
}
int main()
{
    ios_base::sync_with_stdio(false);
    //freopen("ants.inp","r",stdin);
    //freopen("ants.out","w",stdout);
    cin>>n;
    forinc(i,1,n) cin>>a[i]>>b[i];
    long long l=*min_element(b+1,b+n+1),r=*max_element(b+1,b+n+1);
    long long res;
    while(l<=r)
    {
        long long mid=l+(r-l)/2;
        if(check(mid))
        {
            res=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<res;
}
