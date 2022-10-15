#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=2002;
int m,n,G[N][N];
long long res=0;
int gcd(int a,int b)
{
    if(a>b) swap(a,b);
    if(a==0) return b;
    if(G[a][b]) return G[a][b];
    return G[a][b]=gcd(a,b%a);
}
int main()
{
    freopen("chbh.inp","r",stdin);
    freopen("chbh.out","w",stdout);
    cin>>m>>n;
    forinc(i,1,m)
    forinc(j,1,n)
    {
        int trong=(i+1)*(j+1)-gcd(i,j)-2;
        int ngoai=(i-1)*(j-1);
        int sl=(m-i+1)*(n-j+1);
        res+=1ll*(trong+ngoai)*sl;
    }
    cout<<res;
}
