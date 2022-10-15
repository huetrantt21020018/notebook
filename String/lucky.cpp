#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int N=102,INF=-1;
string A,B,C;
int nA,nB,nC;
int kmp[N],nxt[N][26],f[N][N][N];
int nxA[N][26],nxB[N][26],cur[26];
string ans[N][N][N];
int main()
{
    freopen("lucky.inp","r",stdin);
    freopen("lucky.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>A>>B>>C;
    nA=A.size(),nB=B.size(),nC=C.size();
    A=' '+A; B=' '+B; C=' '+C;
    // tinh mang kmp
    int j=0;
    forinc(i,2,nC)
    {
        while((j>0)&&C[i]!=C[j+1]) j=kmp[j];
        if(C[i]==C[j+1]) ++j;
        kmp[i]=j;
    }
    // tinh nxt cua C
    forinc(i,0,nC)
    forinc(c,0,25)
    {
        int j=i;
        while((j>0)&&C[j+1]-'A'!=c) j=kmp[j];
        if(C[j+1]-'A'==c) ++j;
        nxt[i][c]=j;
    }
    // tinh nxt cua A
    forinc(i,0,25) cur[i]=nA+1;
    fordec(i,nA,0)
    {
        forinc(c,0,25) nxA[i][c]=cur[c];
        cur[A[i]-'A']=i;
    }
    // tinh nxt cua B
    forinc(i,0,25) cur[i]=nB+1;
    fordec(i,nB,0)
    {
        forinc(c,0,25) nxB[i][c]=cur[c];
        cur[B[i]-'A']=i;
    }
    forinc(pa,0,nA+1) forinc(pb,0,nB+1) forinc(pc,0,nC+1) f[pa][pb][pc]=INF;
    f[0][0][0]=0;
    int res=0,a=0,b=0,c=0;
    forinc(pa,0,nA) forinc(pb,0,nB) forinc(pc,0,nC) if(f[pa][pb][pc]!=INF)
    {
        if(res<f[pa][pb][pc])
        {
            res=f[pa][pb][pc];
            a=pa; b=pb; c=pc;
        }
        int len=f[pa][pb][pc]+1;
        forinc(x,0,25)
        {
            int pa1=nxA[pa][x];
            int pb1=nxB[pb][x];
            int pc1=nxt[pc][x];
            if(pc1==nC) continue;
            if(f[pa1][pb1][pc1]<len)
            {
                f[pa1][pb1][pc1]=len;
                ans[pa1][pb1][pc1]=ans[pa][pb][pc]+(char)(x+'A');
            }
        }
    }
    if(res==0) return cout<<0,0;
    cout<<ans[a][b][c];
}
