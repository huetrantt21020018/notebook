// hw5 trie: 多模式串字符串匹配模板题

#include <iostream>
#include <stdio.h>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

typedef pair<int, int> II;
typedef pair<long long, int> LLI;
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<II> VII;

#define For(i,a,b) for(int i = a;i <= b; i++)
#define Rep(i,a,b) for(int i = a;i >= b; i--)
#define REP(i, n) for(int i = 0; i < n; i++)
#define FOR(i, f) for(auto i : f)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define BUG(x) (cerr << #x << " = " << x << "\n")
#define sz(s) int(s.size())
#define reset(f, x) memset(f, x, sizeof(f))
#define all(x) x.begin(), x.end()
#define two(x) (1LL << x)
#define bit(x, i) ((x >> (i)) & 1LL)
#define onbit(x, i) (x | (1LL << (i)))
#define offbit(x, i) (x & ~(1 << (i)))

const int N = 1000 + 1;
const int L = 120;
const int K = 26;

int n, m;
int g[N*L][K], f[N*L], state;
bool word[N*L];
vector<string> pattern;
queue<int> q;

void buildAC()
{
    reset(f, -1);
    reset(g, -1);
    REP(i, n)
    {
        string s = pattern[i];
        int cur = 0;
        REP(j, sz(s))
        {
            int ch = s[j]-'a';
            if (g[cur][ch] == -1) g[cur][ch] = ++state;
            cur = g[cur][ch];
        }
        word[cur] = true;
    }
    REP(ch, K)
    {
        if (g[0][ch] == -1) g[0][ch] = 0;
        if (g[0][ch])
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        REP(ch, 26)
        {
            if (g[u][ch] != -1)
            {
                int v = g[u][ch];
                int fail = f[u];
                while (g[fail][ch] == -1) fail = f[fail];
                fail = g[fail][ch];
                f[v] = fail;
                q.push(v);
                word[v] |= word[u];
            }
        }
    }
}

int findNext(int u, int ch)
{
    while (g[u][ch] == -1) u = f[u];
    return g[u][ch];
}

bool searchWord(string s)
{
    int cur = 0;
    REP(i, sz(s))
    {
        int ch = s[i]-'a';
        cur = findNext(cur, ch);
        if (word[cur]) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    srand(time(NULL));
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        //freopen("out.txt","w",stdout);
    #endif
    cin >> n;
    For(i, 1, n)
    {
        string s;
        cin >> s;
        pattern.push_back(s);
    }
    buildAC();
    cin >> m;
    while (m--)
    {
        string s;
        cin >> s;
        cout << (searchWord(s) ? "YES\n" : "NO\n");
    }
}
