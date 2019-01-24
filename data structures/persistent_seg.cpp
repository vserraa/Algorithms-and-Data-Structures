#include <bits/stdc++.h>
using namespace std;
const int ms = 1e5+10;
int a[ms];

struct Vertex {
    Vertex *l, *r;
    int sum;
    Vertex(): l(nullptr), r(nullptr), sum(0) {}
    Vertex(int x): l(nullptr), r(nullptr), sum(x) {}
    Vertex(Vertex *l, Vertex *r): l(l), r(r), sum(0) {
        if(l) sum += l->sum;
        if(r) sum += r->sum;
    }
};

int cc = 0;
Vertex buffer[ms * 20];

Vertex* createNode() {
	return &buffer[cc++];
}
 
vector<Vertex*> roots;
 
Vertex* build(int l, int r) {
    if(l == r) {
    	Vertex* ans = createNode();
    	*ans = Vertex(a[l]);
        return ans;
    }
 
    int mid = (l+r)/2;
    Vertex* ans = createNode();
    *ans = Vertex(build(l, mid), build(mid+1, r));
    return ans;
}
 
int query(Vertex *node, int ql, int qr, int l, int r){
    if(ql > r || qr < l)
        return 0;
 
    if(l >= ql && r <= qr)
        return node->sum;
 
    int mid = (l+r)/2;
    return query(node->l, ql, qr, l, mid) + 
        query(node->r, ql, qr, mid+1, r);
}
 
Vertex* update(Vertex *node, int tgt, int newVal, int l, int r){
    if(l == r){
    	Vertex *ans = createNode();
    	*ans = Vertex(node->sum + newVal);
    	return ans;
    }
 
    int mid = (l+r)/2;
    if(tgt <= mid){
    	Vertex *ans = createNode();
    	*ans = Vertex(update(node->l, tgt, newVal, l, mid), node->r);
    	return ans;
    }
    else{
    	Vertex *ans = createNode();
    	*ans = Vertex(node->l, update(node->r, tgt, newVal, mid+1, r));
    	return ans;
    }
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	vector<Vertex*> roots;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];

	roots.push_back(build(0, n-1));
	int q;
	cin >> q;
	while(q--){
		int op;
		cin >> op;
		if(op == 2){
			int l, r, v;
			cin >> v >> l >> r;
			l--, r--;
			cout << query(roots[v], l, r, 0, n-1) << endl;
		}
		else{
			int idx, pos, toAdd;
			cin >> idx >> pos >> toAdd;
			pos--;
			roots.push_back(update(roots[idx], pos, toAdd, 0, n-1));
		}
	}

	return 0;
}