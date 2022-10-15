#include <bits/stdc++.h>
#define int long long
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=1000001;
struct dinh
{
   int x;
   int y;
   int id;
};
dinh a[N],a0={N,N,0},b[N];
int n;
bool ss(dinh a,dinh b)
{
   dinh c={a0.x,a0.y};
   int sq=(b.x-a.x)*(b.y+a.y) + (c.x-b.x)*(c.y+b.y) + (a.x-c.x)*(a.y+c.y);
   return (sq<0);
}
main()
{
   freopen("apples.inp","r",stdin);
   freopen("apples.out","w",stdout);
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   cin>>n;
   forinc(i,1,n)
   {
      cin>>a[i].x>>a[i].y;
      a[i].id=i;
      if(a[i].y<a0.y) a0={a[i].x,a[i].y,i};
      else if(a[i].x<a0.x&&a[i].y==a0.y) a0={a[i].x,a[i].y,i};
   }
   int spt=0;
   forinc(i,1,n) if(i!=a0.id)
   {
      b[++spt]={a[i].x,a[i].y,a[i].id};
   }
   sort(b+1,b+n,ss);
   cout<<a0.id<<" "<<b[n/2].id;
}
