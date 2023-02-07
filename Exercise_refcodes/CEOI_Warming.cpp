//Challenge: Accepted
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int a[maxn], num[maxn];
int main() {
	io
	int n, X;
	cin >> n >> X;
	for (int i = 0;i < n;i++) cin >> a[i];
	vector<int> v;
	for (int i = 0;i < n;i++) {
		int ind = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		num[i] = ind + 1;
		if (ind == v.size()) v.push_back(a[i]);
		else v[ind] = a[i];
	}
	int ans = v.size();
	v.clear();	
	for (int i = n - 1;i > 0;i--) {
		int ind = lower_bound(v.begin(), v.end(), -a[i]) - v.begin();	
		if (ind == v.size()) v.push_back(-a[i]);	
		else v[ind] = -a[i];
		int p = (lower_bound(v.begin(), v.end(), -(a[i-1] - X)) - v.begin());
		ans = max(ans, num[i-1] + p);
	}
	cout << ans << "\n";
}
