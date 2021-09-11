#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define endl "\n"

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll find_all_solutions(ll a, ll b, ll c, ll x1, ll x2, ll y1, ll y2) {
	if (!a && !b) {
		if (c) return 0;
		return (x2 - x1 + 1) * (y2 - y1 + 1);
	}
	else if (!a) {
		if (c % b) return 0;
		c = c / b;
		if (y1 <= c && c <= y2) return (x2 - x1 + 1);
		return 0;
	}
	else if (!b) {
		if (c % a) return 0;
		c = c / a;
		if (x1 <= c && c <= x2) return (y2 - y1 + 1);
		return 0;
	}

	ll x, y, d;
	d = gcd(a, b, x, y);

	if (c % d == 0) {

		x *= (c / d); // x0
		y *= (c / d); // y0

		b /= d; // x0 + k*b -> b = b/d
		a /= d; // y0 - k*a -> a = a/d

		// k = (X-x0)/b
		double p = (x1 - x) / (double)b;
		double q = (x2 - x) / (double)b;

		if (p > q) swap(p, q);
		x1 = (ll)ceil(p);
		x2 = (ll)floor(q);

		// k = (y0 - Y)/a
		p = (y - y1) / (double)a; 
		q = (y - y2) / (double)a;

		if (p > q) swap(p, q);
		y1 = (ll)ceil(p);
		y2 = (ll)floor(q);

		x1 = max(x1, y1); 
		x2 = min(x2, y2);
		return max(0LL, x2 - x1 + 1);
	}
	return 0;
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll t, tc = 1;
    cin >> t;

    while(t--) {
        ll a, b, c, x1, x2, y1, y2;
        cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
        cout << "Case " << tc++ << ": " << find_all_solutions(a, b, -c, x1, x2, y1, y2) << endl;
    }

	return 0;
}