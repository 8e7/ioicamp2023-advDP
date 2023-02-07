//Challenge: Accepted
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
}
#define ll long long
#define pii pair<ll, ll>
#define ff first
#define ss second
#define maxn 6005
#define mod 1000000007
#define io ios_base::sync_with_stdio(0);cin.tie(0);
const ll inf = 1LL<<60;
pii a[maxn], b[maxn];
ll dp[2][maxn], ans[maxn];

pii stk[maxn];
ll ma[maxn];
int main() {
	io
	int m, k;
	cin >> m >> k;
	vector<int> len;
	for (int i = 1;i <= m;i++) {
		cin >> b[i].ff >> b[i].ss;
		len.push_back(b[i].ss - b[i].ff);
	}
	vector<pii> in;
	int n = 0;
	for (int i = 1;i <= m;i++) {
		bool inc = 0;
		for (int j = 1;j <= m;j++) {
			if (i == j) continue;
			if (b[i] == b[j] && i < j) {
				inc = 1;
				break;
			}
			if (b[i] != b[j] && b[i].ff <= b[j].ff && b[i].ss >= b[j].ss) {
				inc = 1;
				break;
			}
		}
		if (inc) in.push_back(b[i]);
		else a[++n] = b[i];	
	}	
	sort(a + 1, a + n + 1);
	sort(len.begin(), len.end(), [&](int x, int y){return x > y;});
	ll out = 0;
	for (int i = 0;i < k - 1;i++) out += len[i];
	for (int j = 1;j <= n;j++) dp[0][j] = -inf, dp[1][j] = -inf;
	dp[1][0] = -inf;


	//note: stack is not needed here
	for (int i = 0;i < min(k, n);i++) {	

		int siz = 0, ms = 0;
		stk[siz++] = {dp[0][0], 1<<30};
		ma[ms++] = dp[0][0] + (1<<30);
		for (int j = 1;j <= n;j++) {
			ll best = -inf;
			while (siz && stk[siz-1].ss >= a[j].ss) {
				best = max(best, stk[siz-1].ff);
				siz--, ms--;
			}	
			
			ma[ms] = max(ms ? ma[ms-1] : -inf, best + a[j].ss);
			ms++;
			stk[siz++] = {best, a[j].ss};	
			dp[1][j] = max(dp[1][j], ma[ms-1] - a[j].ff);	
			
			stk[siz++] = {dp[0][j], 1<<30};	
			ma[ms] = max(ms ? ma[ms-1] : -inf, dp[0][j] + (1<<30));
			ms++;
		}
		for (int j = 0;j <= n;j++) {
			dp[0][j] = dp[1][j];dp[1][j] = -inf;
			stk[j] = {0, 0}, ma[j] = 0;
		}
		ans[i+1] = dp[0][n];
	}
	ans[0] = -inf;
	sort(in.begin(), in.end(), [&] (pii x, pii y){return x.ss - x.ff > y.ss - y.ff;});
	ll sum = 0;
	for (int j = 0;j < max(0, k - n - 1);j++) sum += in[j].ss - in[j].ff;	
	out = max(out, sum + ans[min(k, n)]);
	for (int i = max(0, k - n - 1);i < min((int)in.size(), k);i++) { //k - i - 1 <= n
		sum += in[i].ss - in[i].ff;
		//debug(sum, ans[k - i - 1]);
		out = max(out, sum + ans[k - i - 1]);
	}
	cout << out << "\n";
}
