#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int ms = 400003;
vector<int> ett, adj[ms];
ll c[ms], st[8*ms], lazy[8*ms], last[ms], first[ms];

void dfs(int u, int p = -1){
	ett.push_back(u);
	for(int v : adj[u])
		if(v != p)
			dfs(v, u);

	ett.push_back(u);
}

int main(){
//	ios::sync_with_stdio(0), cin.tie(0);
	int n, q, a, b;
	cin >> n >> q;
	for(int i = 0; i < n; i++){
		scanf("%lld", c+i);
		c[i] = 1LL<<c[i]; 
	}

	for(int i = 0; i < n-1; i++){
		scanf("%d%d", &a, &b);
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0);
	memset(first, -1, sizeof first);
	memset(last, -1, sizeof last);
	for(int i = 0; i < ett.size(); i++){
		if(first[ett[i]] == -1)
			first[ett[i]] = i;
		else
			last[ett[i]] = i;
	}

	return 0;
}