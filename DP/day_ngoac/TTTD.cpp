// QHĐ thứ tự từ điển + QHĐ chữ số < dãy ngoặc >
//https://codeforces.com/group/e2kzH9Ilfm/contest/302365/problem/B
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define int long long

using namespace std;
const int N = 1e3+5, MAX = 2e18;

int n, k, p;
string s;
char kt[6] = {'(','[','{',')',']','}'}, ans[N];

int f[N][N][2][2], dd[N][N][2][2];
int calc(int i,int j,int ok,int bac)
{
    if(j<0 || j>k) return 0;
    if(i==n+1) return (bac && !j);
    if(dd[i][j][ok][bac]) return f[i][j][ok][bac];
    dd[i][j][ok][bac] = 1;
    int ret = 0, ok1 = (bac|(j+1==k));
    if(ok)
    {
        ret += 3*calc(i+1,j+1,1,ok1);
        ret += calc(i+1,j-1,ok,bac);
    }
    else
    {
        if(s[i]=='(') ret += calc(i+1,j+1,0,ok1);
        else if(s[i]=='[') ret += calc(i+1,j+1,1,ok1)+calc(i+1,j+1,0,ok1);
        else if(s[i]=='{') ret += 2*calc(i+1,j+1,1,ok1)+calc(i+1,j+1,0,ok1);
        else ret += 3*calc(i+1,j+1,1,ok1)+calc(i+1,j-1,0,bac);
    }
//cout << i << ' ' << s[i] << ' ' << j << ' ' << bac << ' '<<ok1 << ' '<< ret<< endl;
    return f[i][j][ok][bac] = ret;
}

int fre[N][N][2], F[N][N][2];
int tinh(int i,int c,int ok)
{
    if(c<0 || c>k) return 0;
    if(i==n+1) return (ok && !c);
    if(fre[i][c][ok]) return F[i][c][ok];
    fre[i][c][ok] = 1;
    int ret = 3*tinh(i+1,c+1,ok|(c+1==k)) + tinh(i+1,c-1,ok);
    ret = min(ret,MAX);
    return F[i][c][ok] = ret;
}

void lankq(int i,int c,int ok)
{
    if(i>n) return;
    bool _set = 0;
    forinc(t,0,2)
    {
//cout <<i<< ' '<< p << ' ' << tinh(i+1,c+1,ok|(c+1==k)) << endl;
        if(p <= tinh(i+1,c+1,ok|(c+1==k)))
        {
            ans[i] = kt[t];
//cout << "* "<< i << ' ' << t << ' ' << ans[i] << endl;
            lankq(i+1,c+1,ok|(c+1==k));
            _set = 1;
            break;
        }
        p -= tinh(i+1,c+1,ok|(c+1==k));
    }
    if(!_set)
    {
        ans[i] = kt[3];
        lankq(i+1,c-1,ok);
    }
}


main()
{
    //freopen("brcnt1.inp","r",stdin);

    cin >> n >> k;
    cin >> s;
    s = ' '+s;
    cout << calc(1,0,0,0) << '\n';
    cin >> p;
    tinh(1,0,0);
    lankq(1,0,0);
    stack<int> st;
    forinc(i,1,n)
    {
        if(ans[i]=='('||ans[i]=='['||ans[i]=='{')
        {
            cout << ans[i];
            st.push(i);
        }
        else
        {
            if(ans[st.top()]=='(') cout << ')';
            if(ans[st.top()]=='[') cout << ']';
            if(ans[st.top()]=='{') cout << '}';
            st.pop();
        }
    }
}


/**
Một ngoặc mở chỉ khớp với một ngoặc đóng
-> Coi tất cả ngoặc đóng là ')'
*/
