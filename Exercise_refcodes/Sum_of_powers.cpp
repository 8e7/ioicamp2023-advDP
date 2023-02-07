//Challenge: Accepted
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <iomanip>
#include <queue>
#include <unordered_set>
#include <assert.h>
using namespace std;
void debug() {cout << endl;}
template <class T, class ...U> void debug(T a, U ... b) { cout << a << " "; debug(b...);}
template <class T> void pary(T l, T r) {
	while (l != r) {cout << *l << " ";l++;}
	cout << endl;
}
#define ll long long
#define ld long double
#define maxn 4100
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int dp[maxn][maxn];
ll po[maxn];
ll modpow(ll a, ll p) {
	ll ret = 1, mult = a;
	while (p) {
		if (p & 1) ret = ret * mult % mod;
		mult = mult * mult % mod, p >>= 1;
	}
	return ret;
}
int main() {
	io
	int n, m, k;
	cin >> n >> k >> m;
	for (int i = 1;i <= n;i++) po[i] = modpow(i, m);
	dp[0][0] = 1;
	for (int i = 0;i <= k;i++) {
		for (int j = 0;j <= n;j++) {
			dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j]) % mod;
			if (i && j + i < maxn) dp[i][j+i] = (dp[i][j+i] + dp[i][j]) % mod;
		}
	}
	ll ans = 0;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= k;j++) {
			//debug(i, j, (ll)j * po[i] % mod * (n >= i * j ? dp[k-j][n - i * j] : 0) % mod);
			ans = (ans + po[i] % mod * (n >= i * j ? dp[k-j][n - i * j] : 0) % mod) % mod;
		}
	}
	cout << ans << endl;
}
