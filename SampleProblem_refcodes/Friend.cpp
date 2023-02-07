//Challenge: Accepted
#include <bits/stdc++.h>
using namespace std;
#ifdef zisk
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r){
	while (l != r)cout << *l << " ", l++;
	cout << endl;
}
#else
#define debug(...) 0
#define pary(...) 0
#endif
#define ll long long
#define maxn 100005
#define pii pair<int, int>
#define ff first
#define ss second
#include "friend.h"

// Find out best sample

int dp[maxn][2];
int findSample(int n,int C[],int h[],int type[]){
	for (int i = 0;i < n;i++) dp[i][1] = C[i], dp[i][0] = 0;
	for (int i = n-1;i > 0;i--) {
		if (type[i] == 0) {
			dp[h[i]][0] += max(dp[i][0], dp[i][1]);
			dp[h[i]][1] += dp[i][0];
		} else if (type[i] == 1) {
			dp[h[i]][1] = max(dp[h[i]][1] + max(dp[i][0], dp[i][1]), dp[h[i]][0] + dp[i][1]);
			dp[h[i]][0] += dp[i][0];
		} else {
			dp[h[i]][1] = max(dp[h[i]][1] + dp[i][0], dp[i][1] + dp[h[i]][0]);
			dp[h[i]][0] += dp[i][0];
		}
	}
	return max(dp[0][0], dp[0][1]);
}
