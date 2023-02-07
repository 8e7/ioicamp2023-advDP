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
#define maxn 1<<18
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
#define iter(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define pb emplace_back
ll inc[18][maxn];
int main() {
	io;
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	for (int c = 0;c < k;c++) {
		vector<ll> a, pref, se;
		int cur = 0;

		ll sum = 0;
		for (int i = 0;i < n;i++) {
			if (s[i] - 'a' == c) {
				se.push_back(cur);
				cur = 0;
				int j = i;
				while (j < n && s[j] - 'a' == c) j++;
				a.push_back(j - i);
				sum += (ll)(j-i) * (j-i);
				pref.push_back(j-i);
				if (pref.size() > 1) pref[pref.size()-1] += pref[pref.size()-2];
				i = j - 1;	
			} else {
				cur |= 1<<(s[i]-'a');
			}
		}
		vector<int> pos;
		int siz = a.size();
		for (int i = 0;i < siz;i++) {
			int val = 0;
			for (int j = 1;j < pos.size();j++) {
				val |= se[pos[j-1]];	
				inc[c][val] += 2 * a[i] * (pref[pos[j-1]-1] - (pos[j] >= 1 ? pref[pos[j]-1] : 0));
			}
			if (i == siz - 1) break;
			int tmp = se[i+1];
			vector<int> to;
			to.push_back(i+1);
			for (int j:pos) {
				if ((tmp | se[j]) != tmp) {
					to.push_back(j);
				}
				tmp |= se[j];
			}
			if (to.back() != 0) to.push_back(0);
			pos = to;
		}
		for (int j = 0;j < k;j++) {
			for (int i = 0;i < (1<<k);i++) {
				if ((i>>j) & 1) inc[c][i] += inc[c][i ^ (1<<j)];
			}
		}
		for (int i = 0;i < (1<<k);i++) inc[c][i] += sum;
	}
	int q;
	cin >> q;
	while (q--) {
		string t; cin >> t;
		int se = 0;
		for (char c:t) se |= 1<<(c-'a');
		ll ans = 0;
		for (int i = 0;i < k;i++) {
			if (!((se>>i)&1)) ans += inc[i][se];
		}
		cout << ans << "\n";
	}	
}
