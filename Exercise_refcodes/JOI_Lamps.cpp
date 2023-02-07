//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#define ll long long
#define maxn 1000005
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
string sa, sb;
 
int a[maxn], b[maxn], pref[maxn], diff[maxn], pdif[maxn];
int dp[maxn];
int mi[maxn], m0[maxn], m1[maxn];
 
inline int seg(int l, int r) {
	if (l > r) return 0;
	return pref[r] - (l ? pref[l - 1] : 0);
}
int main() {
	io
	int n;
	cin >> n;
	cin >> sa >> sb;
	sa += '0', sb += '0';
	reverse(sa.begin(), sa.end());
	reverse(sb.begin(), sb.end());
	sa += '0', sb += '0';
	n += 2;
	for (int i = 0;i < n;i++) {
		a[i] = (sa[i] == '1') ^ (i ? (sa[i - 1] == '1') : 0);
		b[i] = (sb[i] == '1') ^ (i ? (sb[i - 1] == '1') : 0);
		diff[i] = a[i] ^ b[i];
		pref[i] = (b[i] == 1 ? 1 : 0) + (i ? pref[i - 1] : 0);
		pdif[i] = diff[i] + (i ? pdif[i - 1] : 0);
		//cout << pref[i] << " " << pdif[i] << endl;
	}
	for (int i = 0;i < n;i++) {
		dp[i] = pdif[i] + (i ? mi[i - 1] : 0);
		if (i > 1) {
			dp[i] = min(dp[i], dp[i - 2] + 4 - diff[i] - diff[i + 1]);
		}
		if (i > 2) {
			if (sa[i - 1] == '0') dp[i] = min(dp[i], 4 - diff[i] + pref[i - 1] + m0[i - 3]);
			else dp[i] = min(dp[i], 4 - diff[i] + pref[i - 1] + m1[i - 3]);
		}
		/*
		for (int j = 0;j < i;j++) {
			if (j < i - 1 && sa[j + 1] == sa[i - 1]) { //l == j + 1, r == i - 1;
				dp[i] = min(dp[i], dp[j] + 4 - (diff[i] + diff[j + 1]) + seg(j + 2, i - 1));
			}
		}
		*/
		//cout << dp[i] << " ";
		mi[i] = min(dp[i] - pdif[i], i ? mi[i - 1] : 1<<30);
		if (i < n) {
			m0[i] = (i ? m0[i - 1] : 1<<30);
			m1[i] = (i ? m1[i - 1] : 1<<30);
			if (sa[i + 1] == '0') m0[i] = min(m0[i], dp[i] - diff[i + 1] - pref[i + 1]);
			else m1[i] = min(m1[i], dp[i] - diff[i + 1] - pref[i + 1]);
		}
 
	}
	//cout << endl;
	cout << (dp[n - 1] + 1) / 2 << "\n";
}
