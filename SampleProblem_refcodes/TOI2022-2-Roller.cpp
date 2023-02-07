//Challenge: Accepted
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 505
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
vector<int> adj[maxn];
int p[maxn];
ll c[maxn][maxn], fac[maxn], finv[maxn];
vector<ll> f[maxn], g[maxn];
ll modpow(ll a, ll x) {
	ll ret = 1;
	while (x) {
		if (x & 1) ret = ret * a % mod;
		x >>= 1, a = a * a % mod;
	}
	return ret;
}
void dfs(int n, int par) {
	f[n].resize(1, 1);
	for (int v:adj[n]) {
		if (v != par) {
			dfs(v, n);	
			int rs = f[n].size(), vs = f[v].size(); 
			vector<ll> tmp(rs + vs - 1);
			for (int i = 0;i < rs;i++) {
				for (int j = 0;j < vs;j++) {
					tmp[i + j] = (tmp[i+j] + f[n][i] * f[v][j] % mod * c[i+j][i])%mod;
				}
			}	
			f[n] = tmp;
		}
	}
	
	if (p[n]) {
		g[n].clear();	
		g[n].resize(maxn, 0);
		ll sum = 0;
		for (int i = 0;i < f[n].size();i++) {
			sum = (sum + f[n][i] * finv[i]) % mod;	
			for (int j = 1;j < maxn - 1 - i;j++) {
				g[n][j-1] = (g[n][j-1] + f[n][i] * c[i+j][j] %mod * finv[i+j]%mod)%mod;
			}
		}
		f[n].resize(1);
		f[n][0] = sum;
	} else {
		f[n].insert(f[n].begin(), 0);
		for (int v:adj[n]) {
			if (v != par) {
				vector<ll> val = g[v];
				int vs = val.size();
				for (int u:adj[n]) {
					if (u != par && u != v) {
						vs = val.size();
						vector<ll> to(vs, 0);
						for (int i = 0;i < vs;i++) {
							for (int k = 0;k < f[u].size();k++) {
								if (k > i) break;
								to[i-k] = (to[i-k] + f[u][k] * val[i] % mod * c[i][k] % mod)%mod;	
							}
						}	
						val = to;
						while (val.size() && val.back() == 0) val.pop_back();
					}
				}	
				if (val.size()) {
					f[n][0] = (f[n][0] + val[0]);
					if (g[n].size() < val.size()) g[n].resize(val.size());
					for (int i = 1;i < val.size();i++) g[n][i-1] = (g[n][i-1] + val[i])%mod;
				}
			}
		}
	}
}
int main() {
	c[0][0] = 1;
	fac[0] = finv[0] = 1;
	for (int i = 1;i < maxn;i++) {
		fac[i] = fac[i-1] * i % mod;
		finv[i] = modpow(fac[i], mod - 2);
		for (int j = 0;j <= i;j++) {
			c[i][j] = (c[i-1][j] + (j ? c[i-1][j-1] : 0))%mod;
		}
	}
	int n, m;
	cin >> n >> m;
	for (int i = 0;i < m;i++) {
		int x;
		cin >> x;
		p[x] = 1;
	}	
	for (int i = 0;i < n - 1;i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}	
	dfs(1, 0);
	cout << f[1][0] * fac[n - m] % mod<< "\n";
}
