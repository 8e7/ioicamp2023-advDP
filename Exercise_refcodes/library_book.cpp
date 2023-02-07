//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iomanip>
#include <assert.h>
#include <stack>
#define ll long long
#define maxn 3005
#define pii pair<ll, ll>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
pii a[maxn], b[maxn], tmp[maxn];
ll dp[maxn][maxn][2];
int main() {
	int n, m;
	cin >>n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i].ff >> a[i].ss;
	for (int i = 1;i <= m;i++) cin >> tmp[i].ff >> tmp[i].ss;
	sort(a + 1, a + n + 1);
	sort(tmp + 1, tmp + m + 1);
	int pnt = 1;
	stack<int> stk;
	for (int i = 1;i <= m;i++) {
		while (stk.size() && tmp[i].ss > tmp[stk.top()].ss) {
			stk.pop();
		}
		stk.push(i);
	}
	pnt = stk.size();
	for (int i = pnt;i > 0;i--) {
		b[i] = tmp[stk.top()];
		stk.pop();
	}
	m = pnt;

	for (int i = 0;i <= n;i++) {
		for (int j = 0;j <= m;j++) {
			if (!i && !j) continue;
			dp[i][j][0] = dp[i][j][1] = 1LL<<60;
			if (i) {
				dp[i][j][0] = min(max(dp[i - 1][j][0], a[i].ff) + a[i].ss, max(dp[i - 1][j][1], a[i].ff) + a[i].ss);
			}
			if (j) {
				dp[i][j][1] = min(max(dp[i][j - 1][0], b[j].ff) + b[j].ss, max(dp[i][j - 1][1], b[j].ff + b[j].ss));
			}
		}
	}
	cout << min(dp[n][m][0], dp[n][m][1]) << endl;
}

