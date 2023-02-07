//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
//using namespace __gnu_pbds;
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ";debug(b ...);}
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
}
#define ll long long
#define maxn 3005
#define mod 1000000007
#define pii pair<ll, ll>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
const ll inf = 1LL<<60;
ll a[maxn], pref[maxn];
ll dp[maxn];

ll cost(int l, int r, ll t) {
	return t * (r - l + 1) - pref[r] + pref[l - 1];
}
int main() {
	io
	ll n, z, d;
	cin >> n >> z >> d;
	for (int i = 1;i <= n;i++) cin >> a[i], pref[i] = a[i] + (i ? pref[i - 1] : 0);	
	for (int i = n;i >= 1;i--) {
		dp[i] = inf;
		ll pos = a[i - 1], val = 0;
		int ind = i;
		while (true) {
			if (ind > n) {
				dp[i] = min(dp[i], val);
				break;
			}
			int nxt = n + 1;
			for (int j = ind;j < min(ind + z, n + 1);j++) {
				if (a[j] > pos + d) {
					nxt = j;
					break;
				}
			}
			for (int j = nxt;j < min(ind + z, n + 1);j++) {
				if (a[j] <= pos + 2 * d || nxt == ind) {
					dp[i] = min(dp[i], val + cost(ind, j, a[j]) + dp[j + 1]);
				}
			}
			if (nxt == ind) {
				break;
			}
			//debug(ind, min((int)(ind + z - 1), nxt - 1), pos + d);
			val += cost(ind, min((int)(ind + z - 1), nxt - 1), pos + d);
			ind = min((int)(ind + z), nxt);
			pos += d;
		}
		//debug(dp[i]);
	}	
	cout << dp[1] << endl;
}
/*

9 2 4
3 7 10 12 12 13 13 24 25
*/
