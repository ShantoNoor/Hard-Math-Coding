#include<bits/stdc++.h>
using namespace std;

#define endl "\n"

using i64 = int64_t;
using i128 = __int128_t;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

inline i64 add(i64 a, i64 b, i64 M) {a += b ; return a >= M ? a - M : a ;}
inline i64 sub(i64 a, i64 b, i64 M) {a -= b ; return a < 0 ? a + M : a ;}

i64 mult(i64 a, i64 b, i64 M) {
    return (i128)a * b % M;
}

i64 binpower(i64 base, i64 e, i64 M) {
    i64 result = 1;
    base %= M;
    while (e) {
        if (e & 1)
            result = (i128)result * base % M;
        base = (i128)base * base % M;
        e >>= 1;
    }
    return result;
}

i64 binpower(i64 base, i64 e) {
    i64 result = 1;
    while (e) {
        if (e & 1)
            result = (i128)result * base;
        base = (i128)base * base;
        e >>= 1;
    }
    return result;
}

bool check_composite(i64 n, i64 a, i64 d, i64 s) {
    i64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (i64 r = 1; r < s; r++) {
        x = (i128)x * x % n;
        if (x == n - 1)
            return false;
        if (x == 1)
            return true;
    }
    return true;
};

bool MillerRabin(i64 n) {
    if (n < 2)
        return false;

    for (i64 a : {2, 3, 5, 13, 19, 73, 193, 407521, 299210837}) {
        if(a > n)
            break;
        if(a == n)
            return true;
        if(n%a == 0)
            return false;
    }

    i64 r = 0;
    i64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (i64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

i64 f(i64 x, i64 c, i64 M) {
    return (mult(x, x, M) + c) % M;
}

i64 brent(i64 n, i64 x0=2, i64 c=1) {
    if(n%2 == 0) return 2;
    i64 x = x0;
    i64 g = 1;
    i64 q = 1;
    i64 xs, y;

    c = rnd()%(n-1)+1;

    i64 m = 128;
    i64 l = 1;
    while (g == 1) {
        y = x;
        for (i64 i = 1; i < l; i++)
            x = f(x, c, n);
        i64 k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (i64 i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = __gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = __gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}

vector <i64> factor (i64 n) {
    if (n == 1) return {};
    if (MillerRabin(n)) return {n};
    i64 x = brent(n);
    while(x == n) x = brent(n);;
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

pair<i64, i64> fib (i64 n, i64 m) {
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1, m);

    i64 c = mult(p.first, sub(mult(2, p.second, m), p.first, m), m);

    i64 d = add(mult(p.first, p.first, m), mult(p.second, p.second, m), m);

    if (n & 1)
        return {d, (c + d) % m};
    else
        return {c, d};
}

i64 pisano_period_prime(i64 p) {
  if (p == 2) return 3;
  if (p == 5) return 20;
  i64 x = p % 5 == 1 or p % 5 == 4 ? p - 1 : 2 * p + 2;
  auto v = factor(x);
  map<i64, int> mp;
  for (auto x: v) {
    mp[x]++;
  }
  vector<i64> d;
  d.push_back(1);
  for (auto [p, e]: mp) {
    i64 cur = 1;
    int sz = d.size();
    for (int i = 0; i < e; i++) {
      cur *= p;
      for (int j = 0; j < sz; j++) {
        d.push_back(d[j] * cur);
      }
    }
  }
  sort(d.begin(), d.end());
  for (auto x: d) {
    if (fib(x, p).first == 0 && fib(x + 1, p).first == 1) {
      return x;
    }
  }
  return -1;
}

i64 pisano_period(i64 n) {
  auto v = factor(n);
  map<i64, i64> mp;
  for (auto x: v) {
    mp[x]++;
  }
  i64 ans = 1;
  for (auto [p, e]: mp) {
    i64 cur = pisano_period_prime(p);
    cur *= binpower(p, e-1);
    ans = ans / __gcd(ans, cur) * cur;
  }
  return ans;
}

i64 findD(i64 m){
    /*
      takes m: a number as input
      and returns the smallest d where: Fib(d) % m = 0
    */
    i64 pp = pisano_period(m);
    if(pp % 4 == 0 && fib(pp/4, m).first == 0) return pp/4;
    if(pp % 2 == 0 && fib(pp/2, m).first == 0) return pp/2;
    return pp;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

    int t; cin >> t;
    while(t--) {
        i64 a, b, k; cin >> a >> b >> k;

        i64 ans, d, mod = 1e9+7;
        d = findD(k);

        ans = sub(binpower(a, b, mod), binpower(a, b, d) % mod, mod);
        ans = mult(ans, binpower(d, mod-2, mod), mod);
        ans = (ans + 1) % mod;

        cout << ans << endl;
    }

	return 0;
}
