// CTP 11.12.20
// DPT : O(size()/9)

#include <bits/stdc++.h>
using namespace std;

const int base = 1e9, Ndigit = 9;

struct bignum
{
#define lli long long
	int n, sign; // số có dấu ko
    vector<lli> a;
    bignum() : n(0), a(0,0), sign(0) {}
    bignum(int n) : n(n), a(n,0), sign(0) {}
	bignum(string &s) : sign(s[0]=='-') {
		if(sign) s.erase(s.begin());
		n = (s.size() + Ndigit - 1) / Ndigit;
		a.resize(n);
        while(s.size() < n*Ndigit) s = '0' + s;
        int sz = s.size();
        for(int i=0; i<sz; ++i) {
            int id = (sz - i - 1) / Ndigit;
            a[id] = a[id]*10 + s[i]-'0';
		}
	}
	void print() {
		if(sign) cout << '-';
        for(int i=n-1; i>=0; --i) {
			string s;
            lli x = a[i];
            if(!x) s = "0";
            while(x) {
                s = s + char(x%10 + '0');
                x /= 10;
			}
			if(i != n-1) while(s.size() < Ndigit) s = s + '0';
			reverse(s.begin(), s.end());
            cout << s;
		}
	}
	bool smaller(bignum &o) {// abs(cur) < abs(o)
		if(n != o.n) return n < o.n;
		for(int i=n-1; i>=0; --i) if(a[i] != o.a[i]) return a[i] < o.a[i];
		return 0;
	}
	bool operator < (bignum &o) {// cur < o
		if(sign != o.sign) return sign;
		if(!sign) return smaller(o);
		return 1 - smaller(o);
	}
	void stab(bignum &o) {
		while(n < o.n) a.push_back(0), n++;
		while(n > o.n) o.a.push_back(0), o.n++;
	}
	bignum plus(bignum &o) {// abs(cur) + abs(o)
        stab(o);
		bignum c(n);
		lli mem = 0;
        for(int i=0; i<n; ++i) {
			lli sum = a[i] + o.a[i] + mem;
            c.a[i] = sum % base;
            mem = sum / base;
		}
		if(mem) {
			c.n++;
			c.a.push_back(mem);
		}
		return c;
	}
	bignum minus(bignum &o) { // abs(cur) - abs(o)
		stab(o);
		bignum c(n);
		lli mem = 0;
        for(int i=0; i<n; ++i) {
			lli sum = a[i] - o.a[i] - mem;
            c.a[i] = (sum + base) % base;
            mem = (sum < 0);
		}
        while(c.n>1 && !c.a.back()) {
			c.n--;
			c.a.pop_back();
		}
		return c;
	}
	bignum multi(bignum &o) {
        stab(o);
        bignum c(2*n);
        lli nho = 0;
        for(int i=0; i<n; ++i) {
            nho = 0;
            for(int j=0; j<n; ++j) {
                c.a[i+j] += a[i]*o.a[j] + nho;
                nho = c.a[i+j] / base;
                c.a[i+j] %= base;
			}
			c.a[i+n] += nho;
		}
		while(c.n>1 && !c.a.back()) {
			c.n--;
			c.a.pop_back();
		}
		return c;
	}
};

istream& operator >> (istream &cin, bignum &a) {
	string s; cin >> s;
	bignum b(s);
	a = b;
	return cin;
}
ostream& operator << (ostream& cout, const bignum &a) {
    bignum b = a;
    b.print();
    return cout;
}

bignum operator + (bignum a, bignum b) {
	bignum kq;
	if(a.sign == b.sign) { // cùng dấu
		kq = a.plus(b);
		kq.sign = a.sign;
	}
	else {
		if(a.sign) swap(a, b); // a = +; b = -;
        if(a.smaller(b)) {
			kq = b.minus(a);
			kq.sign = 1;
        }
        else {
			kq = a.minus(b);
			kq.sign = 0;
		}
	}
	return kq;
}
bignum operator - (bignum a, bignum b) {
	b.sign ^= 1;
	return a + b;
}
bignum operator * (bignum a, bignum b) {
	bignum kq = a.multi(b);
	kq.sign = (a.sign != b.sign);
	return kq;
}


int main()
{
//	freopen("bignum.inp","r",stdin);
//	freopen("bignum.out","w",stdout);

	bignum A, B;
	cin >> A >> B;

	cout << A+B << '\n';
	cout << A-B << '\n';
	cout << A*B << '\n';
}