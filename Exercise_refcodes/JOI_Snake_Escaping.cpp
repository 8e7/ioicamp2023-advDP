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
#define maxn 1<<20
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int s0[maxn], s1[maxn];
int main() {
	io
		int n, q;
	cin >> n >> q;
	string s;	
	cin >> s;
	for (int i = 0;i < (1<<n);i++) s0[i] = s1[i] = s[i] - '0';	
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < (1<<n);j++) {
			if (j & (1<<i)) {
				s1[j] += s1[j - (1<<i)];
			} else {
				s0[j] += s0[j + (1<<i)];
			}
		}
	}	
	while (q--) {
		string se;
		cin >> se;
		reverse(se.begin(), se.end());
		int c[3] = {0, 0, 0};
		for (int i = 0;i < n;i++) {
			if (se[i] == '?') se[i] = '2';
			c[se[i] - '0']++;
		}
		int mi = min_element(c, c+3) - c;	
		//debug(mi);
		vector<int> pos;
		int p = 0;
		for (int i = 0;i < n;i++) {
			if (se[i] - '0' == mi) pos.push_back(i);
			else {
				if (se[i] - '0' == 2) p += (1<<i) * mi;
				else p += (1<<i) * (se[i] - '0');
			}
		}
		int siz = pos.size();
		int ans = 0;
		for (int i = 0;i < (1<<siz);i++) {
			int add = p;		
			for (int j = 0;j < siz;j++) {
				if (i & (1<<j)) add += 1<<pos[j];
			}
			if (mi == 2) ans += s[add] - '0'; 	
			else {
				int k = __builtin_popcount(i);
				if (mi == 1) {
					k = siz - k;
					ans += (k % 2 ? -1 : 1) * s1[add];
					//debug(add, (k % 2 ? -1 : 1) * s1[add]);
				} else {
					ans += (k % 2 ? -1 : 1) * s0[add];
					//debug(add, (k % 2 ? -1 : 1) * s0[add]);
				}
			}
		}
		cout << ans << "\n";
		//debug();
	}
}
