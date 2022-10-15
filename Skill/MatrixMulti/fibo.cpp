#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)

using namespace std;

long long BASE=1000000007;
struct Matrix
{
   long long m[2][2];
};

Matrix operator * (Matrix x,Matrix y)
{
      Matrix M;
      forinc(i,0,1)
      forinc(j,0,1)
      {
          M.m[i][j]=0;
          forinc(t,0,1)
          M.m[i][j]+=x.m[i][t]*y.m[t][j]%BASE;
          M.m[i][j]=M.m[i][j]%BASE;
      }
      return M;
}

Matrix m,a={0,1,1,1},b={0,0,1,0};

Matrix pw(int n)
{
    if(n==1) return a;
    Matrix tmp=pw(n/2);
    if(n%2) return tmp*tmp*a;
    else return tmp*tmp;
}

main()
{
    freopen("fibo.in","r",stdin);
    freopen("fibo.out","w",stdout);
    ios_base::sync_with_stdio(false);
    int n; cin>>n;
    if(n==0) {cout<<0;return 0;}
    if(n==1) {cout<<1;return 0;}
    Matrix kq=pw(n-1)*b;
    cout<<kq.m[1][0];
}
