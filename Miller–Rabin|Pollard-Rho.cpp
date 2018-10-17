#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int sp[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

ll mulmod(ll a, ll b, ll p) { //returns (a*b)%p;
	ll y = (ld)a * b / p + 0.5;
	ll r = a * b - y * p;
	if (r < 0) r = r + p;
	return r;
}

ll powmod(ll a, ll n, ll mod) { //returns (a^n)%mod, where n >= 0
	ll res = 1, pow = a % mod;
	while(n) {
        if(n & 1) res = mulmod(res, pow, mod);
        pow = mulmod(pow, pow, mod);
        n >>= 1;
	}
	return res;
}

/*Miller–Rabin Strong Pseudoprime Test*/
bool strong_pseudo_primetest(ll n, int a) { // O(log n)
    //returns 1 if n is a strong pseudo prime for base a, returns 0 otherwise
	ll e = n-1, res; int s = 0;
    //n-1 = (2^s)*d where d is odd
    //strong pseudo prime iff [ ( (a^d)%n == 1 ) || ( a^(d*(2^r)) %n == n-1 where r in {0,..,s-1} ) ]
	while(~e & 1)  e >>= 1, ++s;
	res = powmod(a, e, n);
	if(res == 1 || res == n-1) return 1;
	while(--s >= 0) {
		res = mulmod(res, res, n);
		if(res == n-1) return 1;
	}
	return 0;
}

/*Miller–Rabin primality test deterministic variant*/
bool isprime(ll n) {
	if(n < 2) return 0;
	if(n < 4) return 1;

	if(!strong_pseudo_primetest(n,2)) return 0;
	if(!strong_pseudo_primetest(n,3)) return 0;
	if(n < 1373653LL) return 1;

	if(!strong_pseudo_primetest(n,5)) return 0;
	if(n < 25326001LL) return 1;

	if(!strong_pseudo_primetest(n,7)) return 0;
    if(n == 3215031751LL) return 0;
	if(n < 118670087467LL) return 1;

	if(!strong_pseudo_primetest(n,11)) return 0;
	if(n < 2152302898747LL) return 1;

	if(!strong_pseudo_primetest(n,13)) return 0;
	if(n < 3474749660383LL) return 1;

	if(!strong_pseudo_primetest(n,17)) return 0;
	if(n < 341550071728321LL) return 1;

	if(!strong_pseudo_primetest(n,19)) return 0;
	if(!strong_pseudo_primetest(n,23)) return 0;
	if(n < 3825123056546413051LL) return 1;

	if(!strong_pseudo_primetest(n,29)) return 0;
	if(!strong_pseudo_primetest(n,31)) return 0;
	if(!strong_pseudo_primetest(n,37)) return 0;
	return 1;
}


ll pollard_rho(ll n) { // O(n^(1/4)).
    // returns a non-trivial factor of n unless n itself is prime.
    if(n <= 3 || isprime(n)) return n;
    while(1) {
        int cnt = 1, cycleSz = 2;
        ll x = rand() % n, y = x, c = rand() % n;
        if (!c || c == n - 2) ++c;
        do {
            ll u = __gcd(n - x + y, n);
            if (u > 1 && u < n) return u;
            if (++cnt == cycleSz) y = x, cycleSz <<= 1;
            x = (c + mulmod(x, x, n)) % n;
        } while (x != y);
    }
    return n;
}

vector<pair<ll, int> > factorize(ll n){
    vector<pair<ll, int> > factors;
    for (int i = 0; i < 25 && n > 1; ++i) {
        if (n % sp[i]) continue;
        int c = 0;
        while (n % sp[i] == 0) n /= sp[i], ++c;
        factors.emplace_back(sp[i], c);
    }
    vector<ll> divs;
    if (n > 1) divs.push_back(n);
    for (int i = 0; i < (int)divs.size(); ++i){
        ll x = pollard_rho(divs[i]);
        if(x == divs[i]) continue; // divs[i] is prime.
        divs[i--] /= x; // divs[i] is composite may have x to any power.
        divs.push_back(x);
    }
    sort(divs.begin(), divs.end());
    int l = 0, r = -1;
    while(++r < (int)divs.size()) {
        if(r == n-1 || divs[r+1] != divs[l]) {
            factors.emplace_back(divs[l], r-l+1), l = r+1;
        }
    }
    return factors;

}
