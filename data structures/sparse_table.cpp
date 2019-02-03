#include <bits/stdc++.h>
using namespace std;
const int ms = (1<<20);
int n, a[ms], lg[ms], st[20][ms];

void build(){
	for(int i = 0; i < n; i++)
		st[0][i] = a[i];
	for(int i = 1; i < 20; i++)
		for(int j = 0; j+(1<<i) <= n; j++){
			st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]);
		}
}

int rmq(int l, int r){
	int tam = r-l+1;
	return min(st[lg[tam]][l], st[lg[tam]][r-(1<<lg[tam])+1]);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	lg[1] = 0;
	for(int i = 2; i < ms; i++)
		lg[i] = lg[i/2]+1;

	for(int i = 0; i < n; i++)
		cin >> a[i];

	build();
	int q;
	cin >> q;
	while(q--){
		int l, r;
		cin >> l >> r;
		cout << rmq(l, r) << endl;
	}

	return 0;
}