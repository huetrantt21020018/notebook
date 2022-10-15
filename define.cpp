#include <bits/stdc++.h>
using namespace std;
#define forinc(i, a, b) for(int i=a; i<=b; ++i)
#define fordec(i, a, b) for(int i=a; i>=b; --i)
#define forb(i, BS) for(int i=BS._Find_first(); i<BS.size(); i=BS._Find_next(i))
#define forv(a, b) for(auto &a : b)
#define pb push_back
#define all(a) a.begin(),a.end()
#define bit(x,i) ((x>>i)&1)
#define onbit(x,i) (x|(1<<i))
#define offbit(x,i) (x&~(1<<i))
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r){return l+rng()%(r-l+1);}

typedef long long lli;
typedef unsigned long long llu;
typedef pair<int, int> pii;
#define st first
#define nd second

const int N = 5e5 + 5;

void readInput()
{

}

void prepare()
{

}

void solve()
{

}

int main()
{
    if(fopen("input.txt","r"))
    {
        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    }
//    fastio;

    readInput();

    prepare();

	solve();

}
