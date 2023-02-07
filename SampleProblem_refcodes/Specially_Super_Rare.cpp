//Challenge: Accepted
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#ifdef zisk
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
}
#else
#define debug(...) 0
#define pary(...) 0
#endif
#define ll long long
#define maxn 10000005
#define pri 257
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
ll h[maxn], rh[maxn], po[maxn];

int n;
ll hval(int l, int r) { //[l, r]
	//debug("val", l, r, (h[r] - (l ? h[l-1] : 0) * po[r-l+1]%mod + mod)%mod);
	return (h[r] - (l ? h[l-1] : 0) * po[r-l+1]%mod + mod)%mod;
}
ll rval(int l, int r) {
	l = n - 1 - l;
	r = n - 1 - r;
	swap(l, r);
	//debug("rev", l, r, (rh[r] - (l ? rh[l-1] : 0) * po[r-l+1]%mod + mod) %mod);
	return (rh[r] - (l ? rh[l-1] : 0) * po[r-l+1]%mod + mod) %mod;
}

const int maxc = 600;

ll f(pii p){
	return ((ll)p.ff<<31) + p.ss;
}

const int inf = 1<<30;
int dp[2][2*maxc];
int main() {
	io
	po[0] = 1;
	for (int i = 1;i < maxn;i++) po[i] = po[i-1] * pri % mod;

	string s;
	cin >> s;
	n = s.size();
	int M;
	cin >> M;
	for (int i = 0;i < n;i++) {
		h[i] = ((s[i] - 'a'+1) + pri*(i ? h[i-1] : 0))%mod;
		rh[i] = ((s[n-1-i] - 'a'+1) + pri*(i ? rh[i-1] : 0))%mod;
	}
	int ans = 0;
	for (int i = 0;i < 2*maxc;i++) dp[0][i] = -inf;
	dp[0][maxc] = 0;
	for (int i = 0;i < maxc;i++) {
		for (int j = 0;j < 2*maxc;j++) dp[1][j] = -inf;
		for (int j = 0;j < 2*maxc;j++) {
			ans = max(ans, dp[0][j]);
			if (dp[0][j] < 0) continue;
			//debug(i, j-maxc, dp[0][j]);
			int dif = j - maxc; //n-1 + dif
			int x = (dif + i + dp[0][j]) / 2;
			int l = x, r = n + dif - 1 - x;	
			if (l > r || l < 0 || r > n - 1) continue;
			if (l == r) {
				ans = max(ans, dp[0][j]+1);
			} else {
				int low = 0, up = n;	
				while (low < up - 1) {
					int mid = (low + up) / 2;
					if (l + mid - 1 >= r - mid + 1) up = mid;
					else {
						if (hval(l, l+mid-1) == rval(r-mid+1, r)) low = mid;
						else up = mid;
					}
				}
				l += low, r -= low;
				dp[0][j] += 2 * low;
				if (l <= r) ans = max(ans, dp[0][j] + 1);
				if (j+1 < 2*maxc) dp[1][j+1] = max(dp[1][j+1], dp[0][j]);	
				if (j-1 >= 0) dp[1][j-1] = max(dp[1][j-1], dp[0][j]);
			}
		}
		for (int j = 0;j < 2*maxc;j++) dp[0][j] = dp[1][j];
	}
	cout << ans << "\n";
}
