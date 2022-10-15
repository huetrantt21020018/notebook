#define taskname "CARDS"
#include <iostream>
#include <cstdio>
using namespace std;

int n, m;
struct TNode
{
    int Value;
    int Size;
    TNode* P;
    TNode* L;
    TNode* R;
};
using PNode = TNode*;
TNode Sentinel;
PNode nil = &Sentinel, root;

void Link(PNode parent, PNode child, bool InRight)
{
    child->P = parent;
    if (InRight) parent->R = child;
    else parent->L = child;
}

void Update(PNode x)
{
    x->Size = x->L->Size + x->R->Size + 1;
}

void Visit(PNode x)
{
    if (x == nil) return;
    Visit(x->L);
    cout << x->Value << ' ';
    Visit(x->R);
}

void PrintTree(PNode T)
{
    Visit(T);
    cout << endl;
}

void Uptree(PNode x)
{
    PNode y = x->P;
    PNode z = y->P;
    if (x == y->L)
    {
        Link(y, x->R, false);
        Link(x, y, true);
    }
    else
    {
        Link(y, x->L, true);
        Link(x, y, false);
    }
    Update(y);
    Update(x);
    Link(z, x, z->R == y);
}

void MoveToRoot(PNode x)
{
    for(;;)
    {
        PNode y = x->P, z = y->P;
        if(y==nil) return;
        if(z!=nil)
        {
            if((x==y->L)==(y==z->L)) Uptree(y);
            else Uptree(x);
        }
        Uptree(x);
    }
}

PNode Locate(PNode T, int i)
{
    while (true)
    {
        int s = T->L->Size;
        if (s + 1 == i) return T;
        if (s >= i) T = T->L;
        else
        {
            i -= s + 1;
            T = T->R;
        }
    }
    return nil;
}

void Init()
{
    nil->Size = 0;
    root = nil;
    for (int i = 1; i <= n; ++i)
    {
        PNode x = new TNode;
        x->Value = i;
        x->Size = i;
        x->R = nil;
        Link(x, root, false);
        root = x;
    }
    root->P = nil;
}

void Split(PNode T, int i, PNode& A, PNode& B)
{
    if (i == 0)
    {
        A = nil;
        B = T;
        return;
    }
    PNode x = Locate(T, i);
    MoveToRoot(x);
    B = x->R;
    A = x;
    A->R = nil;
    B->P = nil;
    Update(A);
}

PNode Join(PNode A, PNode B)
{
    if (A == nil) return B;
    while (A->R != nil) A = A->R;
    MoveToRoot(A);
    Link(A, B, true);
    Update(A);
    return A;
}

void Solve()
{
    while (m-- > 0)
    {
        int i, k, j;
        cin >> i >> k >> j;
        PNode A, B, C;
        Split(root, i - 1, A, B);
        Split(B, k, B, C);
        root = Join(A, C);
        Split(root, j - 1, A, C);
        root = Join(Join(A, B), C);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen(taskname".INP", "r", stdin);
    //freopen(taskname".OUT", "w", stdout);
    cin >> n >> m;
    Init();
    Solve();
    PrintTree(root);
}
