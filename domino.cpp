#include <bits/stdc++.h>
using namespace std;
const int ms = 123456;
vector<int> adj[ms];
stack<int> sss;
bool seen[ms];

void dfs(int u){
	seen[u] = true;
	for(int v : adj[u]){
		if(!seen[v]){
			dfs(v);
		}
	}
	sss.push(u);
}

void dfs2(int u){
	seen[u] = true;
	for(int v : adj[u])
		if(!seen[v])
			dfs(v);
}

int main(){
	int tt, cnt = 1;
	cin >> tt;
	while(tt--){
		int n, m, a, b;
		cin >> n >> m;
		for(int i = 0; i < ms; i++)
			adj[i].clear();
			
		for(int i = 0; i < m; i++){
			cin >> a >> b;
			a--, b--;
			adj[a].push_back(b);	
		}
		
		memset(seen, 0, sizeof seen);
		for(int i = 0; i < n; i++){
			if(!seen[i])
				dfs(i);
		}
		
		int ans = 0;
		memset(seen, 0, sizeof seen);
		while(!sss.empty()){
			int node = sss.top();
			sss.pop();
			if(!seen[node]){
				ans++;
				dfs(node);	
			}		
		}
		
		cout << "Case " << cnt++ << ": " << ans << endl;
	}
	return 0;
}