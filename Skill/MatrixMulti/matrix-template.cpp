struct TMatrix {
    int n, data[MAXN][MAXN];
    TMatrix(int _n = 0, int _v = 0): n(_n) {
        FOR(i, 0, n) {
            FOR(j, 0, n) data[i][j] = 0;
            data[i][i] = _v;
        }
    }
    void setval(int i, int j, int v) {
        data[i][j] = v;
    }
    int* operator[] (int r) {
        return data[r];
    }
    const int* operator[] (int r) const {
        return data[r];
    }
    void print() {
        FOR(i, 0, n) FOR(j, 0, n) printf("%d%c", data[i][j], j + 1 == n ? '\n' : ' ');
    }
};

TMatrix operator*(const TMatrix& a, const TMatrix b) {
    TMatrix ret(a.n);
    FOR(i, 0, a.n) FOR(j, 0, a.n) FOR(k, 0, a.n)
    ret[i][j] = (ret[i][j] + (long long)(a[i][k]) * b[k][j]) % MOD;
    return ret;
}

TMatrix operator^(const TMatrix& a, int p) {
    TMatrix ret(a.n, 1), t = a;
    while(p) {
        if(p & 1)
            ret = ret * t;
        t = t * t;
        p >>= 1;
    }
    return ret;
}
