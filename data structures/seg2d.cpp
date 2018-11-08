#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int ms = 1e3;
int a[ms][ms], n, m;
ll st[4*ms][4*ms];

void build_y(int vx, int lx, int rx, int vy, int ly, int ry){
	if(ly == ry){
		if(lx == rx)
			st[vx][vy] = a[lx][ly];
		else
			st[vx][vy] = st[2*vx][vy] + st[2*vx+1][vy];
	}
	else{
		int mid = (ly+ry)/2;
		build_y(vx, lx, rx, 2*vy, ly, mid);
		build_y(vx, lx, rx, 2*vy+1, mid+1, ry);
		st[vx][vy] = st[vx][2*vy] + st[vx][2*vy+1];
	}
}

void build_x(int v, int l, int r){
	if(l != r){
		int mid = (l+r)/2;
		build_x(2*v, l, mid);
		build_x(2*v+1, mid+1, r);
	}

	build_y(v, l, r, 1, 0, m-1);
}

ll qry_y(int vx, int vy, int ly, int ry, int qly, int qry){
	if(ly > ry || ly > qry || ry < qly)
		return 0;
	if(ly >= qly && ry <= qry)
		return st[vx][vy];
	int mid = (ly+ry)/2;
	return qry_y(vx, 2*vy, ly, mid, qly, qry) +
		qry_y(vx, 2*vy+1, mid+1, ry, qly, qry);
}

ll qry_x(int vx, int lx, int rx, int qlx, int qrx, int qly, int qry){
	if(lx > rx || lx > qrx || rx < qlx)
		return 0;

	if(lx >= qlx && rx <= qrx)
		return qry_y(vx, 1, 0, m-1, qly, qry);

	int mid = (lx + rx)/2;
	return qry_x(2*vx, lx, mid, qlx, qrx, qly, qry) +
		qry_x(2*vx+1, mid+1, rx, qlx, qrx, qly, qry);
}

void updt_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int val){
	if(ly == ry){
		if(lx == rx)
			st[vx][vy] = a[x][y] = val;
		else
			st[vx][vy] = st[2*vx][vy] + st[2*vx+1][vy]; 
	}
	else{
		int mid = (ly + ry)/2;
		if(y <= mid)
			updt_y(vx, lx, rx, 2*vy, ly, mid, x, y, val);
		else
			updt_y(vx, lx, rx, 2*vy+1, mid+1, ry, x, y, val);

		st[vx][vy] = st[vx][2*vy] + st[vx][2*vy+1];
	}
}

void updt_x(int vx, int lx, int rx, int x, int y, int val){
	if(lx != rx){
		int mid = (lx+rx)/2;
		if(x <= mid)
			updt_x(2*vx, lx, mid, x, y, val);
		else
			updt_x(2*vx+1, mid+1, rx, x, y, val);
	}

	updt_y(vx, lx, rx, 1, 0, m-1, x, y, val);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];

	build_x(1, 0, n-1);
	int q;
	cin >> q;
	while(q--){
		int op;
		cin >> op;
		if(op == 1){
			int x1, x2, y1, y2;
			cin >> x1 >> x2 >> y1 >> y2;
			cout << qry_x(1, 0, n-1, x1, x2, y1, y2) << endl;
		}
		else{
			int x, y, val;
			cin >> x >> y >> val;
			updt_x(1, 0, n-1, x, y, val);
		}
	}
	return 0;
}
