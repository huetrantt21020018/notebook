// mảng cộng dồn 2D
// voi 20 bài 4
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
#define st first
#define nd second
const int N = 1e5+5, inf = 1e9;

typedef pair<int,int> pii;

struct cumulative{
	int row, col;
	vector<vector<int> > AddRow, AddCol;
	cumulative(int m, int n) : row(m), col(n){
		AddRow.assign(m+3,vector<int>(n+3));
		AddCol.assign(m+3,vector<int>(n+3));
	}
	void upd(int x,int y,int u,int v,int val){
		AddCol[x][y] += val;
		AddCol[x][v+1] -= val;
		AddCol[u+1][y] -= val;
		AddCol[u+1][v+1] += val;
	}
	int get(int u,int v){
		AddCol[u][v] += AddCol[u][v-1];
		return AddCol[u][v] + AddRow[u][v];
	}
	void trans(int u){
		forinc(i,1,col) AddRow[u+1][i] += AddCol[u][i] + AddRow[u][i];
	}
};

int m, n, k;
vector<int> a[N];
vector<pii> change[N];

int sol(int t){
	cumulative b(m,n);
	int cnt = 0;
	forinc(i,1,m) {
		forinc(j,1,n) {
			int A = (a[i][j] + b.get(i,j)) % 3;
			if(A != t){
				int i1 = change[i][j].st, j1 = change[i][j].nd, ne = (t-A+3) % 3;
				if(!i1) return inf;
				b.upd(i,j, i1,j1, ne);
				cnt += ne;
			}
		}
		b.trans(i);
	}
	return cnt;
}

int main(){
	freopen("light.inp","r",stdin);
	freopen("light.out","w",stdout);

	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> m >> n >> k;
	forinc(i,1,m) {
		a[i].resize(n+3);
		change[i].resize(n+3);
	}
	forinc(i,1,m) forinc(j,1,n) cin >> a[i][j];
	forinc(i,1,k){
		int r, c, x, y;
		cin >> r >> c >> x >> y;
		change[r][c] = {x, y};
	}
	int res = min(sol(1), sol(2));
	if(res == inf) cout << -1;
	else cout << res;
}