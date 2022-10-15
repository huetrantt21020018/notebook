// CTP 18.12.20

#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 5e5+5;

struct RMQ
{
	int n, ln;
	vector<vector<int> > T;
	RMQ(vector<int> a)
	{
		int n = a.size() - 1, ln = log2(n);
		T.resize(ln+1, vector<int>(n+1,0));
        forinc(i, 0, n) T[0][i] = a[i];
        forinc(j, 1, ln)
        forinc(i, 0, n) if(i+(1<<(j-1)) <= n)
			T[j][i] = max(T[j-1][i], T[j-1][i+(1<<(j-1))]);
	}
	int get(int l,int r)
	{
		int _ln = log2(r-l+1);
		return max(T[_ln][l], T[_ln][r-(1<<_ln)+1]);
	}
};

int main()
{
	//freopen("qmax.inp","r",stdin);
	int n, m;
	cin >> n >> m;
	vector<int> a(n+2);
	forinc(i,1,m)
	{
		int l, r, k;
		cin >> l >> r >> k;
		a[l] += k; a[r+1] -= k;
	}
	forinc(i,1,n) a[i] += a[i-1];
	RMQ rmq(a);

	int q; cin >> q;
	while(q--)
	{
		int l, r;
		cin >> l >> r;
		cout << rmq.get(l, r) << '\n';
	}
}