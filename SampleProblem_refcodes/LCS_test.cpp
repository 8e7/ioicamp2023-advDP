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
#define maxn 100005
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
#define iter(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define pb emplace_back
ll solve(int n, ll S) {
	vector<int> a(n);
	for (int i = 0;i < n;i++) a[i] = (S>>i)&1;
	unordered_map<ll, ll> dp, nxt;
	dp[0] = 1;

	ll se = (1LL<<(n+1))-1;
	auto to = [&] (ll state, int c) {
		int last = n;
		for (int i = n-1;i >= 0;i--) {
			if ((state>>i)&1) {
				last = i;
			} else if (a[i] == c) {
				state &= se - (1LL<<last);
				state |= (1LL<<i);	
				last = i;
			}
		}
		return state;
	};
	
	for (int i = 0;i < n;i++) {
		for (auto [state, cnt]:dp) {
			nxt[to(state, 0)] += cnt;
			nxt[to(state, 1)] += cnt;
		}
		dp = nxt;
		assert(dp.size() <= nxt.size());
		nxt.clear();
	}
	return dp.size();
}
int main() {
	io;
	ll n;
	cin >> n;
	vector<int> ma(n+1, 0), se(n+1, 0);
	for (ll i = 0;i < (1LL<<n);i++) {
		ll val = solve(n, i);
		int cnt = __builtin_popcountll(i);
		if (val >= ma[cnt]) {
			ma[cnt] = val;
			se[cnt] = i;
		}
	}	
	for (int i = 0;i <= n;i++) {
		debug(ma[i]);
		for (int j = 0;j < n;j++) cout << ((se[i]>>j)&1);
		cout << "\n";
	}
	/*
	for (int i = 0;i <= n;i++) {
		for (int j = 0;j <= n - i;j++) {
			ll num = (1LL<<i)-1;
			cout << solve(i+j, num) << " ";	
		}
		cout << "\n";
	}
	*/
}
