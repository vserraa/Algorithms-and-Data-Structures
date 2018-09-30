#include <bits/stdc++.h>
using namespace std;
#define fr(i, a, b) for(int i = a, _ = b; i < _; i++)
typedef pair<int, int> pii;

int find(vector<int> &parent, int i, int &rank){
	if(parent[i] == -1)
		return i;
	else 
		return parent[i] = find(parent, parent[i], ++rank);
}

int Union(vector<int> &parent, int x, int y){
	int rx = 0, ry = 0, px = find(parent, x, rx), py = find(parent, y, ry);
	if(px == py)
		return -1;

	if(rx > ry)
		return parent[y] = px;
	else
		return parent[x] = py;
}

int main(){
	int n, m, v, w;
	cin >> n >> m;
	vector<int> val(n);
	vector<int> parent(n, -1);
	fr(i, 0, n){
		cin >> val[i];
	}	

	fr(i, 0, m){
		cin >> v >> w;
		if(Union(parent, v, w) == -1)
			cout << "Edge " << v << "-" << w << " will creat a cycle in the graph" << endl;
	}

	return 0;
}
