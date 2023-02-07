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
ll a[maxn], p[maxn];
int main() {
	int n;
	cin >> n;
	ll ans = 0;
	for (int i = 1;i <= n;i++) {
		cin >> a[i];	
		ans += max(a[i], 0LL);
		p[i] = a[i] + p[i-1];
	}
	priority_queue<ll> pq;
	for (int i = 1;i <= n;i++) {
		if (pq.size() && p[i] + pq.top() - max(a[i],0LL) > 0) {
			ans += p[i] + pq.top() - max(a[i], 0LL);	
			pq.pop();
			pq.push(-p[i]);
		} else {
			pq.push(-p[i-1] - max(a[i], 0LL));
		}
	}
	cout << ans << "\n";
}
