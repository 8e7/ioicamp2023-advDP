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
#define pii pair<ll, ll>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
const ll inf = 1LL<<60;
ll s[maxn];
pii a[maxn];
ll cost[maxn], pref[maxn];

struct line{
	ll m, k;
	line(){m = 0, k = -inf;}
	line(ll a, ll b){m = a, k = b;}
	ll getval(ll x){return m*x + k;}
};
vector<ll> vec[maxn];
ll dp[maxn];
int main() {
	io
		ll x, n, m, w, t;
	cin >> x >> n >> m >> w >> t;
	for (int i = 1;i <= n;i++) cin >> s[i];	
	sort(s + 1, s + 1 + n);
	for (int i = 0;i < m;i++) {
		cin >> a[i].ff >> a[i].ss;
	}
	sort(a, a + m);
	for (int j = 0;j < m;j++) {
		cost[j] = w * ((x - a[j].ff) / t + 1);
		pref[j] = a[j].ss;
		if (j) cost[j] += cost[j-1], pref[j] += pref[j-1];
	}
	s[n+1] = x;
	for (int i = 0;i <= n;i++) {
		ll rig = upper_bound(a, a + m, make_pair(s[i+1]%t-1, 1LL<<60)) - a - 1; //[lef, rig]	
		vec[rig].push_back(s[i+1]/t);
	}
	vector<line> conv;	
	conv.push_back(line(w, 0));
	auto search = [&] (ll p) {
		int low = 0, up = conv.size();
		while (low < up - 1) {
			int mid = (low + up) / 2;
			if (conv[mid].getval(p) < conv[mid-1].getval(p)) low = mid;
			else up = mid;
		}
		return conv[low].getval(p);
	};
	for (int i = 0;i < m;i++) {
		if (i) dp[i] = min(dp[i], dp[i-1]);
		for (auto h:vec[i]) {
			dp[i] = min(dp[i], search(h) + pref[i] - cost[i] + h * w * i);	
		}
		line add(-i*w, dp[i] + cost[i] - pref[i]);
		while (conv.size() > 1) {
			line p1 = conv[conv.size() - 2], p2 = conv.back();	
			ll pnt = (p2.k - p1.k + p1.m - p2.m - 1) / (p1.m - p2.m);		
			if (p2.getval(pnt) >= add.getval(pnt)) {
				conv.pop_back();
			} else {
				break;
			}
		}
		conv.push_back(add);
	}

	cout << dp[m-1] + cost[m-1] + (x / t + 1) * w<< endl;
}
