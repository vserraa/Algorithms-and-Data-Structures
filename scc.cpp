#include <bits/stdc++.h>
using namespace std;
const int size = 1e6;
const int inf = 0x3f3f3f;
vector<int> adj[size];
bool seen[size];
int d[size], low[size], tempo = 0;
stack<int> ms;
int scc = 1;

//tarjan's algorithm
void dfs(int u){
	seen[u] = true;
	d[u] = low[u] = tempo++;
	ms.push(u);
	for(int v : adj[u]){
		if(!seen[v]){
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else
			low[u] = min(low[u], d[v]);
	}

	if(low[u] >= d[u]){
		cout << scc++ << " : " << endl;
		int v = -1;
		while(v != u){
			v = ms.top();
			ms.pop();
			cout << v << " ";
			d[v] = inf;
		}
		cout << endl;
	}
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n, m, u, v;
	cin >> n >> m;
	memset(low, 0, sizeof low);
	memset(seen, 0, sizeof seen);
	memset(d, 0, sizeof d);
	for(int i = 0; i < m; i++){
		cin >> u >> v;
		adj[u].push_back(v);
	}

	dfs(0);
	return 0;
}