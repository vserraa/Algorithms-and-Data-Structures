#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define F first
#define S second
const int size = 1e4+100;
const int M = 20;
ll dp[size][M], d[size], l[size];
vector<pii> adj[size];

void dfs(int i, int p, int dist, int lvl){
	dp[i][0] = p;
	l[i] = lvl, d[i] = dist; 
	for(int j = 1; j < M; j++){
		if(dp[i][j-1] != -1)
			dp[i][j] = dp[dp[i][j-1]][j-1];
	}

	for(auto v : adj[i]){
		if(v.F == p) continue;
		
		dfs(v.F, i, dist+v.S, lvl+1);
	}
}

int walk(int i, int k){
	int up = l[i]-k;
	for(int j = M-1; j >= 0; j--)
		if(dp[i][j] != -1 && l[dp[i][j]] >= up)
			i = dp[i][j];

	return i;
}

int lca(int u, int v){
	if(l[u] < l[v]) swap(u, v);
	if(u == v) return u;

	for(int i = M-1; i >= 0; i--){
		if(dp[u][i] != -1 && l[dp[u][i]] >= l[v])
			u = dp[u][i];
	}

	if(u == v) return u;

	for(int i = M-1; i>= 0; i--)
		if(dp[u][i] != -1 && dp[v][i] != -1 && dp[u][i] != dp[v][i]){
			u = dp[u][i], v = dp[v][i];
		}

	return dp[u][0];
}


//the following code solves SPOJ'S QTREE2
int main(){
	int t; cin >> t;
	while(t--){
		memset(dp, -1, sizeof dp);
		memset(d, 0, sizeof d);
		memset(l, 0, sizeof l);
		for(int i = 0; i < size; i++) 
			adj[i].clear();

		int n, a, b, c; cin >> n;
		for(int i = 0; i < n-1; i++){
			cin >> a >> b >> c;
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
		}

		dfs(1, -1, 0, 0);
		string s;
		while(cin >> s && s != "DONE"){
			cin >> a >> b;
			int mid = lca(a, b);
			ll dab = d[a]+d[b]-2*d[mid];
			if(s == "DIST"){
				cout << dab << endl;
			}
			else{
				cin >> c;
				ll d1 = 1+l[a]-l[mid], d2 = 1+l[a]+l[b]-2*l[mid];
				if(c <= d1)
					cout << walk(a, c-1) << endl;
				else
					cout << walk(b, d2-c) << endl;
			}
		}

	}
	return 0;
} 
