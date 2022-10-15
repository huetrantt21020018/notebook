#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 2002, M = 52;

string S, X, Y;
int n,m,k;
int kmp[M][2], nxt[M][27][2];
int f[N][M][M], res = INT_MIN;

void KMP(string &s, int t)
{
    int j = kmp[1][t] = 0, n = s.size()-1;
    forinc(i,2,n)
    {
        while(j>0 && s[i]!=s[j+1]) j = kmp[j][t];
        if(s[i]==s[j+1]) j++;
        kmp[i][t] = j;
    }
    forinc(i,0,n)
    forinc(c,0,25)
    {
        int j = i;
        while(j>0 && (s[j+1]-'a')!=c) j = kmp[j][t];
        if((s[j+1]-'a')==c) j++;
        nxt[i][c][t] = j;
    }
}

int main()
{
    //freopen("K.inp","r",stdin);

    cin >> S >> X >> Y;

    n = S.size(); m = X.size(); k = Y.size();
    S = ' '+S;
    X = ' '+X;
    Y = ' '+Y;

    KMP(X,0);
    KMP(Y,1);

    memset(f,128,sizeof f);
    res = f[0][0][0];
    int inf = res;
    f[0][0][0]=0;

    forinc(i,0,n)
    forinc(x,0,min(m,i))
    forinc(y,0,min(k,i)) if(f[i][x][y]>inf)
    {
        //cout << i << ' ' << x << ' ' << y <<' ' << f[i][x][y] << '\n';
        if(i==n)
        {
            res = max(res,f[i][x][y]);
            continue;
        }
        if(S[i+1]!='*')
        {
            int c = S[i+1]-'a';
            int x1 = (S[i+1]==X[x+1]) ? (x+1) : nxt[x][c][0];
            int y1 = (S[i+1]==Y[y+1]) ? (y+1) : nxt[y][c][1];
            int z1 = f[i][x][y];
            if(x1==m) z1++;
            if(y1==k) z1--;
            f[i+1][x1][y1] = max(f[i+1][x1][y1],z1);
        }
        else forinc(j,0,25)
        {
            char c = (char) (j+'a');
            int x1 = (c==X[x+1]) ? (x+1) : nxt[x][j][0];
            int y1 = (c==Y[y+1]) ? (y+1) : nxt[y][j][1];
            int z1 = f[i][x][y];
            //cout <<f[i][x][y] <<' ' << c << ' ' << x1 << ' ' << y1 << ' ' << z1 << endl;
            if(x1==m) z1++;
            if(y1==k) z1--;
            //cout <<f[i][x][y] <<' ' << c << ' ' << x1 << ' ' << y1 << ' ' << z1 << endl;
            f[i+1][x1][y1] = max(f[i+1][x1][y1],z1);
        }
        //cout << "\n==============\n";
    }
    cout << res;
}
