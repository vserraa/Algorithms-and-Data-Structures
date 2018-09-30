#include <bits/stdc++.h>
using namespace std;
map<string, int> msi;
int cnt, d[100][100];
const int inf = 0x3f3f3f3f;
int dp[1<<4], steinerTree[32][1<<8], best[1<<8];

void clear(){
	msi.clear();
	cnt = 0;
	memset(d, inf, sizeof d);
	memset(steinerTree, inf, sizeof steinerTree);
	memset(best, inf, sizeof best);
	memset(dp, inf, sizeof dp);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n, m;
	while(cin >> n >> m && (n|m)){
		clear();
		string s, t;
		for(int i = 0; i < n; i++){
			cin >> s;
			if(msi.find(s) == msi.end())
				msi[s] = cnt++;
		}

		for(int i = 0; i < n; i++)
			d[i][i] = 0;

		int cost;
		for(int i = 0; i < m; i++){
			cin >> s >> t >> cost;
			d[msi[s]][msi[t]] = min(d[msi[s]][msi[t]], cost);
			d[msi[t]][msi[s]] = min(d[msi[t]][msi[s]], cost);
		}

		for(int k = 0; k < n; k++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		

		int edges[10][2];
		map<int, int> terminals;
		for(int i = 0; i < 4; i++){
			cin >> s >> t;
			edges[i][0] = msi[s], edges[i][1] = msi[t];
			terminals[msi[s]] = 2*i, terminals[msi[t]] = 2*i+1;
		}

		for(auto p : terminals)
			steinerTree[p.first][1<<p.second] = 0;
		
		for(int mask = 0; mask < (1<<8); mask++)
			for(int i = 0; i < n; i++){
				for(int smask = mask; smask > 0; smask = (smask-1)&mask)
					steinerTree[i][mask] = min(steinerTree[i][mask],
						steinerTree[i][smask] + steinerTree[i][mask^smask]);
				
				for(int j = 0; j < n; j++)
					steinerTree[j][mask] = min(steinerTree[j][mask],
						steinerTree[i][mask] + d[i][j]);
			}
		
		for(int mask = 0; mask < (1<<8); mask++){
			for(int i = 0; i < n; i++)
				best[mask] = min(best[mask], steinerTree[i][mask]);
		}
		
		/*se a questão só quiser a steiner tree, basta
		parar aqui e printar best[1<<nTerminals-1]*/

		//the following code solves SPOJ'S ticket to ride
		dp[0] = 0;
		for(int mask = 0; mask < (1<<4); mask++){
			for(int smask = 0; smask < (1<<4); smask++){
				if(mask&smask) 
					continue;
				
				int join = 0;
				for(int i = 0; i < 4; i++){
					if(smask&(1<<i)){
						int x = edges[i][0], y = edges[i][1];
						join |= (1<<terminals[x]);
						join |= (1<<terminals[y]);
					}
				}

				dp[mask|smask] = min(dp[mask|smask], dp[mask] + best[join]);
			}
		}

		cout << dp[(1<<4)-1] << endl;
	}

	return 0;
}