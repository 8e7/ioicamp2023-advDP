//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
void debug() {cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
}
#define ll long long
#define maxn 1000005
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
ll modpow(ll a, ll p) {
	ll ret = 1;
	while (p) {
		if (p & 1) ret = ret * a % mod;
		a = a * a % mod, p >>= 1;
	}
	return ret;
}
int p[maxn];
bool vis[maxn];
ll fac[maxn], finv[maxn];
ll c(int n, int m) {
	if (m > n) return 0;
	return fac[n] * finv[m] % mod * finv[n-m]%mod;
}
int main() {
	io
	fac[0] = 1;
	for (int i = 1;i < maxn;i++) fac[i] = fac[i-1] * i % mod;
	finv[maxn-1] = modpow(fac[maxn-1], mod - 2);
	for (int i = maxn - 2;i >= 0;i--) finv[i] = finv[i+1] * (i+1)%mod;
	int n;
	cin >> n;
	int cnt = 0;
	for (int i = 1;i <= n;i++) cin >> p[i], cnt += i != p[i] ? 1 : 0;	
	ll ans = fac[n] * n % mod * n % mod;
	ans = (ans - (fac[n+1] * 2%mod * finv[3] % mod * cnt % mod) + mod) % mod;
	for (int i = 1;i <= n;i++) {
		if (!vis[i]) {
			int cur = i, siz = 0;
			do {
				siz++;
				vis[cur] = 1;
				cur = p[cur];
			} while (!vis[cur]);
			if (siz % 2 == 0) {
				ans = (ans + (c(n, siz+1) + c(n, siz)) % mod * fac[siz/2] %mod * fac[siz/2] * 2 % mod * fac[n-siz]%mod)%mod; 
			}
		}
	}
	cout << ans << endl;
}
