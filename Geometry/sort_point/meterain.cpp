#include <bits/stdc++.h>
#define int long long
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=5005;
int x[N],y[N],sq=0;
main()
{
   freopen("meterain.inp","r",stdin);
   freopen("meterain.out","w",stdout);
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   int n,m; cin>>n;
   forinc(i,1,n) cin>>x[i]>>y[i];
   x[n+1]=x[1]; y[n+1]=y[1];
   forinc(i,1,n) sq+=(x[i+1]-x[i])*(y[i+1]+y[i]);
   sq=abs(sq);
   cin>>m;
   forinc(test,1,m)
   {
      int u,v,s=0,ok=1;
      cin>>u>>v;
      forinc(i,1,n)
      {
         int tp=abs((u-x[i])*(v+y[i])+(x[i]-x[i+1])*(y[i]+y[i+1])+(x[i+1]-u)*(y[i+1]+v));
         if(tp==0)
         {
            ok=0;
            cout<<"NO"<<'\n';
            break;
         }
         s+=tp;
         if(s>sq)
         {
            ok=0;
            cout<<"NO"<<'\n';
            break;
         }
      }
      if(ok)
      {
         if(s==sq)cout<<"YES"<<'\n';
         else cout<<"NO"<<'\n';
      }
   }
}
