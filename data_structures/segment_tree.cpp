#include <bits/stdc++.h>
using namespace std;
const int size = 1e6+10;
int st[size];
int n, q;
#define fr(i, a, b) for(int i = a, _ =b ;i < _; i++)

void build(){
	for(int i = n-1; i > 0; i--)
		st[i] = st[2*i]+st[2*i+1];
}

int query(int l, int r){
	int ans = 0;
	for(l+=n, r+=n; l < r; l >>= 1, r >>= 1){
		if(l&1) ans += st[l++];
		if(r&1) ans += st[--r];
	}
	return ans;
}

void modify(int x, int val){
	for(x += n, st[x] = val, x >>= 1; x > 0; x>>=1)
		st[x] = st[2*x]+st[2*x+1];
}

int main(){
	scanf("%d", &n);
	memset(st, 0, sizeof st);
	fr(i, 0, n){
		int x;
		scanf("%d" ,&x);
		st[i+n] = x%2;
	}
	build();
	scanf("%d" ,&q);
	fr(i, 0, q){
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		x--;
		if(op == 0){
			modify(x, y%2);
		}
		if(op == 1){
			int ans = query(x, y);
			ans = y-x-ans;
			printf("%d\n" ,ans);
		}
		if(op == 2){
			int ans = query(x, y);
			printf("%d\n" ,ans);
		}
	}
	return 0;
}
