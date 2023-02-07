//Challenge: Accepted
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <unordered_map>
#include <queue>
#include <stack>
#include <set>
#include <assert.h>
#include <iomanip>
using namespace std;
void debug() {cout << endl;}
template <class T, class ...U> void debug(T a, U ... b) { cout << a << " "; debug(b...);}
template <class T> void pary(T l, T r) {
	while (l != r) {cout << *l << " ";l++;}
	cout << endl;
}
#define ll long long
#define maxn 105
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int dp[2][3][maxn][1005];
int a[maxn];
void madd(int &x, int v) {
	x += v - mod, x += mod & (x>>31);
}
int main() {
	int n, l;
	cin >> n >> l;
	for (int i = 0;i < n;i++) cin >> a[i];
	sort(a, a + n, [&](int x, int y){return x > y;});
	dp[0][0][0][0] = 1, dp[0][1][1][0] = 2, dp[0][2][2][0] = 1;
	for (int i = 0;i < n-1;i++) {
		int dif = a[i] - a[i+1];
		for (int c = 0;c < 3;c++) {
			for (int j = 1;j <= n;j++) {
				for (int k = 0;k <= l;k++) {
					int cost = k + (j-c) * 2 * dif + c * dif;
					if (cost > l) continue;
					//takes a gap in middle
					madd(dp[1][c][j-1][cost], (ll)dp[0][c][j][k] * (j - c) % mod);
					madd(dp[1][c][j][cost], (ll)dp[0][c][j][k] * (2 * (j-c) + c)% mod);
					madd(dp[1][c][j+1][cost], (ll)dp[0][c][j][k] * j % mod);
					//removes one of the sides
					if (c) {
						madd(dp[1][c-1][j-1][cost], (ll)dp[0][c][j][k] * c % mod);
						madd(dp[1][c-1][j][cost], (ll)dp[0][c][j][k] * c % mod);
					}
				}
			}
		}	
		for (int c = 0;c < 3;c++) {
			for (int j = 0;j <= n;j++) {
				for (int k = 0;k <= l;k++) dp[0][c][j][k] = dp[1][c][j][k], dp[1][c][j][k] = 0;
			}
		}	
		
	}
	int ans = 0;
	for (int i = 0;i <= l;i++) madd(ans, dp[0][0][0][i]);
	cout << ans << endl;
}
