#include <bits/stdc++.h>
using namespace std;
const int ms = 1e5+10;
vector<int> adj[ms];
int sz[ms], dpar[ms], st[20][ms], d[ms], rem[ms];
int n, in[ms], out[ms], CTpar[ms], tempo = 0;

void dfs_pre(int u, int p){
	d[u] = (p==u)?0:d[p]+1;
	st[0][u] = p;
	in[u] = tempo++;
	for(int v : adj[u]){
		if(v == p) continue;
		dfs_pre(v, u);
	}
	out[u] = tempo++;
}

void build_lca(){
	for(int j = 1; j < 20; j++)
		for(int i = 1; i <= n; i++)
			st[j][i] = st[j-1][st[j-1][i]];
}

bool isAncestor(int u, int v){
	return in[v] >= in[u] && out[v] <= out[u]; 
}

int lca(int u, int v){
	if(isAncestor(u, v))
		return u;
	if(isAncestor(v, u))
		return v;

	for(int i = 19; i >= 0; i--)
		if(!isAncestor(st[i][u], v))
			u = st[i][u];

	return st[0][u];
}

int getDist(int u, int v){
	return d[u] + d[v] - 2*d[lca(u, v)];
}

void dfs_sz(int u, int p){
	sz[u] = 1;
	for(int v : adj[u]){
		if(v == p || rem[v]) continue;
		dfs_sz(v, u);
		sz[u] += sz[v];
	}
}

int getCentroid(int u, int p, int tam){
	for(int v : adj[u]){
		if(rem[v] || v == p) continue;
		if(2*sz[v] > tam)
			return getCentroid(v, u, tam);
	}
	return u;
}

void decompose(int u, int p = -1){
	dfs_sz(u, p);
	int c = getCentroid(u, p, sz[u]);
	CTpar[c] = p;
	rem[c] = 1;
	for(int v : adj[c]){
		if(v != p && !rem[v])
			decompose(v, c);
	}
}

//1-indexed graph
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int q;
	cin >> n;
	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs_pre(1, 1);
	build_lca();
	decompose(1);
	return 0;
}