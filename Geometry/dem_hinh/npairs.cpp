#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define pii pair<int,int>
using namespace std;
const int N=100;
int res=0;
int main()
{
    freopen("npairs.inp","r",stdin);
    freopen("npairs.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int A,B,C,D;
    cin>>A>>B>>C>>D;
    vector<pii> mb;
    forinc(x,1,N) forinc(y,x+1,N) if(__gcd(x,y)==1) mb.push_back({x,y});
    int sz=mb.size()-1;
    forinc(i,0,sz-1)
    {
        int xx=mb[i].first, yx=mb[i].second;
        forinc(j,0,sz-1)
        {
            int xy=mb[j].first, yy=mb[j].second;
            long long tu=1ll*A*xx*yy+1ll*B*xy*yx;
            long long mau=1ll*yx*yy;
            if(tu%mau) continue;
            tu=1ll*C*xx*yy+1ll*D*xy*yx;
            if(tu%mau) continue;
            ++res;
        }
    }
    cout<<res;
}
