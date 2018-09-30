#include <bits/stdc++.h>
using namespace std;
#define fr(i, a, b) for(int i = a, _ = b; i < _; i++)
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
#define mp make_pair
#define pb push_back
vector<int> adj[10001];
priority_queue<int, vector<int>, greater<int> > pq;

void updt(int node, int ind[]){
	for(int v : adj[node]){
		ind[v]--;
		if(ind[v] == 0){
			pq.push(v);
		}
	}
}

int main(){
	int n, m, v, w;
	scanf("%d%d" ,&n ,&m);
	int ind[n+1];
	memset(ind, 0, sizeof ind);
	fr(i, 0, m){
		scanf("%d%d" ,&v, &w);
		adj[v].pb(w);
		ind[w]++;
	}

	fr(i, 1, n+1)
		if(ind[i] == 0){
			pq.push(i); 
		}
	
	vector<int> ans;
	while(!pq.empty()){
		int node = pq.top();
		pq.pop();
		ans.pb(node);
		updt(node, ind);
	}

	if(ans.size() != n)
		cout << "Impossible";
	else{
		for(int x : ans)
			cout << x << " ";
	}
	return 0;
}