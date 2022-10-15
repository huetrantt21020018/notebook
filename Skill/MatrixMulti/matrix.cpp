#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define st first
#define nd second
#define all(a) a.begin(),a.end()
#define pb push_back

using namespace std;
const int N = 124, mod = 1e9+7;

struct matrix
{
	int n;
	vector<vector<int> > a;
	matrix(int n) : n(n)
	{
        a.resize(n+1);
        forinc(i,0,n) a[i].resize(n+1);
	}
	matrix operator * (matrix o)
	{
		matrix kq(n);
        forinc(i,0,n)
        forinc(j,0,n)
        {
            kq.a[i][j] = 0;
            forinc(k,0,n)
            {
                kq.a[i][j] += 1ll*a[i][k]*o.a[k][j]%mod;
                if(kq.a[i][j]>=mod) kq.a[i][j]-=mod;
            }
        }
        return kq;
	}
	void prinf()
	{
		cout << "\n===========\n";
		forinc(i,0,n)
		{
			forinc(j,0,n) cout << a[i][j] << ' ';
			cout << endl;
		}
		cout << "\n===========\n";
	}
};

matrix pw(matrix a,int i)
{
    matrix b = a;
    i--;
    for(;i;i>>=1,a=a*a) if(i&1) b = b*a;
    return b;
}

int main()
{
    freopen("taskselect.inp","r",stdin);
    freopen("taskselect.out","w",stdout);

    ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

    int test; cin >> test;
    while(test--)
	{
		int k, n;
		cin >> k >> n;
		int dem = k;
		matrix a(k*k);
		int cur = 0;
		forinc(i,1,k)
		{
			a.a[cur][i] = 1;
			if(i==k) continue;
			cur = i;
			forinc(t,1,i)
			{
				a.a[cur][++dem] = 1;
				cur = dem;
			}
		}
		forinc(i,1,k)
		{
			cur = i;
			forinc(t,1,i-1)
			{
				a.a[cur][++dem] = 1;
				//cerr << dem << ' ';
				cur = dem;
			}
			a.a[cur][i] = 1;
		}
		matrix b = pw(a,n);
		cout << b.a[0][k] << '\n';
	}
}