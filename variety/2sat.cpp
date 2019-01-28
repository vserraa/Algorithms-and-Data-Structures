#include <bits/stdc++.h>
using namespace std;
const int ms = 1e5+10;
int ini[ms];
vector<int> dd[ms], g[ms], gt[ms], order;
int ans[ms], vis[ms], scc[ms], n, m;

void add(int x, int y){
	g[x].push_back(y);
	gt[y].push_back(x);
}

void addOr(int x, int y){
	add(y^1, x);
	add(x^1, y);
}

void addEq(int x, int y){
	addOr(x, y^1);
	addOr(x^1, y);
}

void addDif(int x, int y){
	addEq(x, y^1);
}

void dfs1(int u){
	vis[u] = true;
	for(int v : g[u]){
		if(!vis[v])
			dfs1(v);
	}
	order.push_back(u);
}

void dfs2(int u, int cl){
	scc[u] = cl;
	for(int v : gt[u]){
		if(scc[v] == -1)
			dfs2(v, cl);
	}
}

bool solve(){
	memset(vis, false, sizeof vis);
	memset(scc, -1, sizeof scc);
	memset(ans, 0, sizeof ans);
	for(int i = 0; i < n; i++){
		if(!vis[2*i])
			dfs1(2*i);
		if(!vis[2*i+1])
			dfs1(2*i+1);
	}

	int at = 0;
	reverse(order.begin(), order.end());
	for(int i : order)
		if(scc[i] == -1)
			dfs2(i, at++);

	for(int i = 0; i < n; i++){
		if(scc[2*i] == scc[2*i+1])
			return false;
		ans[i] = scc[2*i] > scc[2*i+1];
	}
	return true;
}

void init(){
	order.clear();
	for(int i = 0; i < ms; i++){
		g[i].clear(), gt[i].clear();
	}
}

int main(){
	//build graph 0-indexed, 2*i is positive i
	//call solve, if true then solution is in ans
	return 0;
}