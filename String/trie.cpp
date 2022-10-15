/*
https://codeforces.com/group/EHjycaJ7hn/contest/291337/problem/PRODUCT
*/
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define st first
#define nd second
#define pb push_back
using namespace std;
const int N = 1e5+1, M = 2e6+1;
string s[N], t[N];
vector<int> st[N], ed[N];
int m, n, res[N];

struct Tnode
{
    int child[4];
    int mi, ma, cnt;
};
int V(char x)
{
    if(x=='H') return 1;
    if(x=='A') return 0;
    if(x=='M') return 3;
    if(x=='I') return 2;
}
struct trie
{
    Tnode Trie[M];
    int nT;
    int root;
    int AddNode()
    {
        nT++;
        for(int i=0; i<4; i++)
            Trie[nT].child[i]=0;
        Trie[nT].mi = n+1;
        Trie[nT].ma = 0;
        Trie[nT].cnt = 0;
        return nT;
    }
    void AddWord(string &s, int id)
    {
        int r=root;
        for(int i=0; i<s.size(); i++)
        {
            int k=V(s[i]);
            int l;
            if (Trie[r].child[k]==0)
            {
                l=AddNode();
                Trie[r].child[k]=l;
            }
            Trie[r].mi = min(Trie[r].mi, id);
            Trie[r].ma = max(Trie[r].ma, id);
            Trie[r].cnt++;
            r=Trie[r].child[k];
        }
        Trie[r].mi = min(Trie[r].mi, id);
        Trie[r].ma = max(Trie[r].ma, id);
        Trie[r].cnt++;
    }
    pii Mima(string &s)
    {
        int r=root;
        for(int i=0; i<s.size(); i++)
        {
            int k=V(s[i]);
            if (Trie[r].child[k]==0)
                return {0,0};
            r=Trie[r].child[k];
        }
        return {Trie[r].mi, Trie[r].ma};
    }
    int Count(string &s)
    {
        int r=root;
        for(int i=0; i<s.size(); i++)
        {
            int k=V(s[i]);
            if (Trie[r].child[k]==0)
                return 0;
            r=Trie[r].child[k];
        }
        return Trie[r].cnt;
    }
}T;

int main()
{
    //freopen("product.inp","r",stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> m >> n;
    forinc(i,1,n) cin >> s[i];
    sort(s+1,s+n+1);

    T.root = T.AddNode();
    forinc(i,1,n) T.AddWord(s[i],i);

    forinc(i,1,m)
    {
        string S;
        cin >> S >> t[i];
        reverse(t[i].begin(),t[i].end());
        pii Q = T.Mima(S);
        st[Q.st].pb(i);
        ed[Q.nd].pb(i);
    }

    T.nT = 0;
    T.root = T.AddNode();

    forinc(i,1,n)
    {
        for(int q: st[i])
        {
            res[q] -= T.Count(t[q]);
        }
        reverse(s[i].begin(),s[i].end());
        T.AddWord(s[i],i);
        for(int q: ed[i])
        {
            res[q] += T.Count(t[q]);
        }
    }
    forinc(i,1,m) cout << res[i] << '\n';
}
