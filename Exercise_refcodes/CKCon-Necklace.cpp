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
#define maxn 23
#define mod 1000000007
#define pii pair<ll, ll>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
#define iter(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
vector<pii> adj[maxn];
int f[1<<maxn], g[1<<maxn];
int main() {
	io
	int n, m;
	cin >> n >> m;
	for (int i = 0;i < m;i++) {
		int u, v, w;
		cin >> u >> v >> w;	
		u--, v--;
		if (v < u) swap(u, v);
		adj[u].push_back({v, w});
	}	
	f[0] = g[0] = 1;	
	for (int a = 0;a < n;a++) {
		for (auto [b, w]:adj[a]){
			int u = n - 1 - a, v = n - 1 - b;
			for (int i = 0;i < (1<<(n-a));i++) {
				g[i] = ((ll)g[i] + (ll)f[i ^ (1<<u) ^ (1<<v)] * w) % mod;
			}
			for (int i = 0;i < (1<<(n-a));i++) f[i] = g[i];
		}	
	}
	cout << (f[0] + mod - 1)%mod << "\n";
}
