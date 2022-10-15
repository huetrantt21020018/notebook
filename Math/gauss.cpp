#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define ppi pair<pii,int>
#define st first
#define nd second
#define pb push_back

using namespace std;
const int N = 205, MAX = 1e15, mod = 1e9+7;
int n, X[N];

int pw(int a,int i)
{
    int b = 1;
    for(;i;i>>=1,a=a*a%mod) if(i&1) b = b*a%mod;
    return b;
}
int Div(int a,int b)
{
    return (a*b%3+3)%3; // mod3
    return a*pw(b,a-2)%mod;
}

struct matran
{
    int m, n, a[N][N];
    void prinf()
    {
        cout << "\n==========\n";
        forinc(i,1,m)
        {
            forinc(j,1,n) cout << a[i][j] << ' ';
            cout << '\n';
        }
        cout << "\n==========\n";
    }
    void reset(int x,int y)
    {
        m = x, n = y;
        forinc(i,1,m) forinc(j,1,n) a[i][j] = 0;
    }
    void khuGauss()
    {
        forinc(i,1,m)
        {
    ///        Tìm a[k][j] khác 0, k>=i, j nhỏ nhất có thể
            int K = 0, J = 0;
            forinc(j,1,n)
            {
                forinc(k,i,m) if(a[k][j]!=0)
                {
                    K = k, J = j;
                    break;
                }
                if(J) break;
            }
            if(!J) continue;
    ///        Swap(a[k],a[i]);
            forinc(j,1,n) swap(a[i][j], a[K][j]);
    ///        Khử a[][j] bằng dòng i
            forinc(i1,1,m) if(i1!=i && a[i1][J])
            {
                int rat = Div(a[i][J], a[i1][J]);
                forinc(j,1,n)
                {
                    a[i1][j] = a[i1][j]*rat%3;
                    a[i1][j] = (a[i][j]-a[i1][j]+3)%3;
                }
            }
        }
    }
    bool get()
    {
        forinc(i,1,m)
        {
            int j = 1, zero = 1;
            for(; j<n; ++j) if(a[i][j]!=0) {zero = 0; break;}
            if(zero && a[i][n]) return 0;
            X[j] = Div(a[i][n],a[i][j]);
        }
        return 1;
    }
};

bool dat()
{
    matran A;
    A.reset(số hàng, số cột);
    /// Xây bảng hệ số ban đầu
    A.khuGauss();
    return A.get();
}

main()
{
    dat();
}

