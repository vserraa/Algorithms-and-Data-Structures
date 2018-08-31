#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n; 
	cin >> n;
	int dist[n][n];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> dist[i][j];

	int dp[1LL<<n][n];
	memset(dp, inf, sizeof dp);
	dp[1][0] = 0;
	for(int mask = 0; mask < 1LL<<n; mask++)
		for(int i = 1; i < n; i++){
			if(mask&(1LL<<i) && mask&1){
				for(int j = 0; j < n; j++)
					if(mask&(1LL<<j))
						dp[mask][i] = min(dp[mask][i], dp[mask^(1LL<<i)][j]+dist[j][i]); 
			}
		}

	int ans = inf;
	for(int i = 1; i < n; i++)
		ans = min(ans, dp[(1LL<<n)-1][i]+dist[i][0]);

	cout << ans << endl;
	return 0;
}