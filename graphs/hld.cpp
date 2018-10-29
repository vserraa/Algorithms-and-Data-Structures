#include <bits/stdc++.h>
using namespace std;
const int ms = 1e4+10;
const int inf = 0x3f3f3f3f;
vector<pair<int, int>> adj[ms];
map<pair<int, int>, int> mp;
int n, st[2*ms], sz[ms], in[ms];
int tt = 0, up[ms][20], pt[ms];
int nxt[ms], out[ms];
char s[1000];

inline void build(){
	for(int i = n-1; i > 0; i--)
		st[i] = max(st[2*i], st[2*i+1]);
}

inline void updt(int i, int val){
	for(st[i += n] = val, i >>= 1; i > 0; i >>= 1){
		st[i] = max(st[2*i], st[2*i+1]);
	}
}

inline int qry(int l, int r){
	int ans = 0;
	for(l += n, r += n+1; l < r; l >>= 1, r >>= 1){
		if(l&1)
			ans = max(ans, st[l++]);
		if(r&1)
			ans = max(ans, st[--r]);
	}
	return ans;
}

void dfs_sz(int u, int p){
	sz[u] = 1;
	int tam = adj[u].size();
	for(int i = 0; i < tam; i++){
		int v = adj[u][i].first, w = adj[u][i].second;
		if(v == p)
			continue;

		dfs_sz(v, u);
		sz[u] += sz[v];
		if(adj[u][0].first == p || sz[v] > sz[adj[v][0].first])
			swap(adj[u][0], adj[u][i]);
	}
}

void dfs_hld(int u, int p){
	in[u] = tt++;
	up[u][0] = p;
	for(int i = 1; i < 20; i++)
		up[u][i] = up[up[u][i-1]][i-1];

	int tam = adj[u].size();
	for(int i = 0; i < tam; i++){
		int v = adj[u][i].first, w = adj[u][i].second;
		if(v == p){
			st[n+in[u]] = w;
			pt[mp[{u, v}]] = in[u];
			continue;
		}

		if(i == 0) nxt[v] = nxt[u];
		else nxt[v] = v;

		dfs_hld(v, u);
	}
	out[u] = tt;
}

inline bool anc(int u, int v){
	return in[u] <= in[v] && out[u] >= out[v];
}

inline int lca(int u, int v){
	if(anc(u, v))
		return u;
	if(anc(v, u))
		return v;

	for(int i = 19; i >= 0; i--){
		if(!anc(up[u][i], v))
			u = up[u][i];
	}

	return up[u][0];
}

inline int get(int u, int v){
	int ans = 0;
	for(; nxt[u] != nxt[v]; u = up[nxt[u]][0])
		ans = max(ans, qry(in[nxt[u]], in[u]));

	return max(ans, qry(in[v] + 1, in[u]));
}

inline int solve(int u, int v){
	int k = lca(u, v);
	return max(get(u, k), get(v, k));
}

int main(){
	int t, a, b, c;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		tt = 0;
		for(int i = 0; i < n; i++)
			adj[i].clear();

		memset(st, 0, sizeof st);
		mp.clear();

		for(int i = 0; i < n-1; i++){
			scanf("%d%d%d", &a, &b, &c);
			a--, b--;
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
			mp[{a, b}] = mp[{b, a}] = i;
 		}

 		dfs_sz(0, 0);
 		dfs_hld(0, 0);
 		build();

 		while(scanf(" %s", s) != EOF && s[0] != 'D'){
 			scanf("%d%d", &a, &b);
 			if(s[0] == 'Q'){
 				a--, b--;
 				printf("%d\n", solve(a, b));
 			}
 			else{
 				a--;
 				updt(pt[a], b);
 			}
 		}
	}

	return 0;
}