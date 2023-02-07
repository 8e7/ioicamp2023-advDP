//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r) {
	while (l != r) {
		cout << *l << " ", l++;
	}
	cout << endl;
}
#define ll long long
#define maxn 5005
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
ll fac[maxn], inv[maxn];
ll dp[maxn][2], s0[maxn];
int main() {
	io
	fac[0] = 1, inv[1] = 1;
	for (int i = 1;i < maxn;i++) fac[i] = fac[i-1] * i % mod;
	for (int i = 2;i < maxn;i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	int n, x;
	cin >> n >> x;
	int y = n - x;	
	for (int i = 0;i <= x;i++) {
		ll s1 = 0;
		for (int j = 0;j <= y;j++) {
			if (!i && !j) continue;
			dp[j][0] = (s0[j] + s1) * inv[i+j]%mod;
			dp[j][1] = (s0[j] + s1 + i) * inv[i+j]%mod;
			s1 = (s1 + dp[j][1])%mod;
			s0[j] = (s0[j] + dp[j][0])%mod;
			//debug(i, j, dp[i][j][0], dp[i][j][1]);
		}
	}
	cout << (dp[y][0] * fac[n])%mod << endl; 	
}
