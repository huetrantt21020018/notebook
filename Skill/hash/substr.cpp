#include <bits/stdc++.h>
#define int unsigned long long
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
string a,b;
int h[1111111],ss,pw[1111111],res=0;
main()
{
    //freopen("substr.inp","r",stdin);
    cin>>a>>b;
    a=' '+a;
    b=' '+b;
    int n=a.size();
    int m=b.size();
    forinc(i,1,m-1) h[i]=h[i-1]*29+(b[i]-'a'+1);
    ss=h[m-1];
    forinc(i,1,n-1) h[i]=h[i-1]*29+(a[i]-'a'+1);
    int pw=1;
    forinc(i,1,m-1) pw*=29;
    forinc(i,1,n-m+1)
    {
        int l=i,r=i+b.size()-2;
        int f=h[r]-h[l-1]*pw;
        if(f==ss) cout<<i<<" ";
    }
}
