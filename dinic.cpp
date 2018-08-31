#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define F first
#define S second
const ll inf = 0x3f3f3f3f;
const ll ms = 5050;
int gl[ms], pt[ms], sz;

struct edge{
	int to;
	ll cap;
	edge(){}
	edge(int to, int cap): to(to), cap(cap) {}
};

vector<int> adj[ms];
edge ed[101010];

inline void add(int u, int v, ll c){
	ed[sz] = edge(v, c);
	adj[u].push_back(sz);
	sz++;
}

bool bfs(int s, int t){
	memset(gl, -1, sizeof gl);
	queue<int> q;
	q.push(s);
	gl[s] = 0;
	while(!q.empty()){
		ll node = q.front();
		q.pop();
		for(int k : adj[node]){
			edge e = ed[k];
			if(e.cap == 0) 
				continue;

			ll v = e.to;
			if(gl[v] == -1){
				gl[v] = gl[node]+1;
				q.push(v);
			}
		}
	}
	return gl[t] != -1;
}

ll dfs(int i, int t, ll flow = inf){
	if(i == t || flow == 0)
		return flow;

	for(int &j = pt[i]; j < adj[i].size(); j++){
		edge &e = ed[adj[i][j]];
		edge &rev = ed[adj[i][j]^1];
		int v = e.to;
		if(gl[v] == gl[i]+1){
			if(ll add = dfs(v, t, min(flow, e.cap))){
				e.cap -= add;
				rev.cap += add;
				return add;
			}
		}
	}
	return 0;
}

ll dinic(int s, int t){
	ll ans = 0, cnt = 0;
	while(bfs(s, t)){
		memset(pt, 0, sizeof pt);
		while(ll temp = dfs(s, t)){
			ans += temp;
		}
	}
	return ans;
}

int main(){
	sz = 0;
	int n, m, u, v, c;
	scanf("%d%d" ,&n, &m);
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &u, &v, &c);
		add(u, v, c);
		add(v, u, c);
	}

	printf("%lld" ,dinic(1, n));
	return 0;
}