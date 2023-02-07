//Challenge: Accepted
#pragma GCC optimize("Ofast")
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <bitset>
#include <set>
#include <queue>
#include <stack>
#include <assert.h>
#include <cmath>
#include <iomanip>
#include <random>
#include <unordered_map>
#include <chrono>
using namespace std;
void debug(){cout << endl;};
template<class T, class ...U> void debug(T a, U ... b){cout << a << " ", debug(b ...);};
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
};
#define ll long long
#define ld long double
#define maxn 205
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int dp[2][maxn][maxn];
int C[maxn][maxn];

int mod;
void madd(int &x, int v) {
	x = x + v - mod; x += mod & (x>>31);
}
int n;
int solve(int mi) {
	for (int i = 0;i < maxn;i++) {
		for (int j = 0;j < maxn;j++) dp[0][i][j] = dp[1][i][j] = 0;
	}
	for (int x = 1;x <= mi;x++) dp[0][0][x] = 1;
	for (int i = mi+1;i <= n + 1;i++) {
		for (int j = 0;j <= mi;j++) {
			for (int k = 1;k <= n;k++) {
				if (!dp[0][j][k]) continue;
				for (int c = 0;j + c * (i - mi) <= mi && k + c <= n;c++) {
					if (!c || i >= k + c + 1) {
						madd(dp[1][j + c * (i - mi)][k + c], (ll)dp[0][j][k] * C[k + c][c]%mod);
					}
				}		
			}
		}	
		for (int j = 0;j <= mi;j++) {
			for (int k = 1;k <= n;k++) {
				dp[0][j][k] = dp[1][j][k], dp[1][j][k] = 0;
			}
		}
	}
	int ret = 0;
	for (int j = 0;j <= mi;j++) madd(ret, dp[0][j][n]);
	return ret;
}
int main() {
	io
	cin >> n >> mod;
	C[0][0] = 1;
	for (int i = 1;i < maxn;i++) {
		for (int j = 0;j <= i;j++) C[i][j] = (C[i-1][j] + (j ? C[i-1][j-1] : 0))%mod;
	}
	int sq = sqrt(n);
	int ans = 0;
	for (int i = max(n - 2 * sq - 1, 1);i <= n+1;i++) {
		madd(ans, solve(i));
	}
	cout << ans << endl;
}
