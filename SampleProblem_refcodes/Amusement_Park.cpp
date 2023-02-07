//Challenge: Accepted
#include <bits/stdc++.h>
#define ll long long
#define maxn 18
#define mod 998244353
using namespace std;
bool ed[maxn][maxn];
bool indep[1<<maxn];
ll dp[1<<maxn];
int popc[1<<maxn];
int main() {
	//this is the second solution mentioned in the slides
	int n, m;
	cin >> n >> m;
	for (int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		ed[a][b] = ed[b][a] = 1;
	}
	for (int i = 0;i < (1<<n);i++) {
		indep[i] = 1;
		for (int j = 0;j < n;j++) {
			for (int k = j + 1;k < n;k++) {
				if ((i & (1<<j)) && (i & (1<<k))) {
					if (ed[j][k]) {
						indep[i] = 0;
						break;
					}
				}
			}
		}
		if(i) popc[i] = popc[i - (i& (-i))]+1;
	}
	dp[0] = 1;
	for (int i = 1;i < (1<<n);i++) {
		for (int j = i;j > 0;j = (j - 1) & i) {
			dp[i] += (indep[j] ? ((popc[j]& 1) ? dp[i ^ j] : -dp[i ^ j]) : 0);
		}
		dp[i] = ((dp[i] % mod) + mod) % mod;
	}
	cout << dp[(1<<n) - 1] * m % mod *499122177%mod<< endl;
}
