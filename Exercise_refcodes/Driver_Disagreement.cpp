//Challenge: Accepted
#include <bits/stdc++.h>
using namespace std;
#ifdef zisk
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r){
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
int l[maxn], r[maxn], t[maxn];

unordered_map<ll, int> dis;
ll f(pii p){
	return (ll)p.ff * maxn + p.ss;
}

struct DSU{
	int par[maxn];
	void init(int n){
		for (int i = 0;i < n;i++) par[i] = i;
	}
	int find(int a){
		return a == par[a] ? a : (par[a] = find(par[a]));
	}
	bool Union(int a, int b){
		a = find(a), b = find(b);
		if (a == b) return 0;
		par[a] = b;
		return 1;
	}
} dsu;
int main() {
	io
	int n, A, B;
	cin >> n >> A >> B;
	for (int i = 0;i < n;i++) {
		cin >> l[i] >> r[i] >> t[i];
	}	
	dsu.init(n);
	queue<pii> que;
	que.push({A, B});
	dis[f({A, B})] = 1;
	while (que.size()) {
		pii cur = que.front();que.pop();
		if (t[cur.ff] != t[cur.ss]) {
			cout << dis[f(cur)] - 1 << "\n";
			return 0;
		}
		if (!dsu.Union(cur.ff, cur.ss))	continue;
		int d = dis[f(cur)];
		pii to = {l[cur.ff], l[cur.ss]};
		if (!dis[f(to)]) {
			dis[f(to)] = d + 1;
			que.push(to);
		}
		to = {r[cur.ff], r[cur.ss]};
		if (!dis[f(to)]) {
			dis[f(to)] = d + 1;
			que.push(to);
		}
	}	
	cout << "indistinguishable\n";
}
