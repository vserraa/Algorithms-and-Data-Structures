#include <bits/stdc++.h>
using namespace std;
const int size = 1e6;
int tempo = 0, d[size], low[size], f[size];
bool seen[size];
vector<int> adj[size];
vector<int> cut_vertex;
vector<pair<int, int>> bridges;

void dfs(int u, int p = -1){
	bool any = false;
	int nf = 0;
	seen[u] = true;
	d[u] = low[u] = tempo++;	
	for(int v : adj[u]){
		if(!seen[v]){
			dfs(v, u);
			nf++;
			if(low[v] >= d[u]) any = true;
			if(low[v] > d[u]) bridges.push_back({u, v});
			low[u] = min(low[u], low[v]);
		}
		else if(v != p){
			low[u] = min(low[u], d[v]);
		}
	}

	f[u] = tempo++;
	if(p == -1 && nf >= 2)
		cut_vertex.push_back(u);
	else if(p != -1 && any)
		cut_vertex.push_back(u);

}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n, m, u, v;
	cin >> n >> m;
	memset(seen, 0, sizeof seen);
	memset(d, 0, sizeof d);
	memset(low, 0, sizeof low);
	memset(f, 0, sizeof f);
	for(int i = 0; i < m; i++){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1);
	cout << "cut vertexes: " << endl;
	for(int v : cut_vertex)
		cout << v << endl;

	cout << endl << "bridges: " << endl;
	for(auto v : bridges)
		cout << v.first << " " << v.second << endl; 
	return 0;
}