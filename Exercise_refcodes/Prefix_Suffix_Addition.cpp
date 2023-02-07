//Challenge: Accepted
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
#define maxn 200005
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int a[maxn];
int main() {
	io
	int n;
	cin >> n;
	int pos = 0, neg = 0;
	for (int i = 0;i < n;i++) {
		cin >> a[i];
		if (i) {
			if (a[i-1] < a[i]) pos++;
			else if (a[i-1] > a[i]) neg++;
		}
	}
	int ans = min(pos, neg) + 1;
	vector<pii> dp;
	dp.push_back({0, 2});	
	dp.push_back({a[0], 1});
	for (int i = 1;i < n;i++) {
		vector<pii> nxt, to;
		for (auto p:dp) {
			int val[3] = {0, p.ff, p.ff + a[i] - a[i-1]};
			sort(val, val + 3);	
			for (int k = 0;k < 3;k++) {
				if (val[k] >= 0 && val[k] <= a[i]) {
					to.push_back({val[k], p.ss + 2 - k});
				}
			}
		}
		sort(to.begin(), to.end());
		for (auto p:to) {
			if (nxt.size() && nxt.back().ss <= p.ss) continue;
			nxt.push_back(p);
		}
		dp = nxt;
		debug(i);
		for (auto p:nxt) debug(p.ff, p.ss);
		debug();
	}
	ans = min(ans, dp.back().ss);
	if (dp[0].ff == 0) ans = min(ans, dp[0].ss - 1);
	cout << ans << endl;
}
