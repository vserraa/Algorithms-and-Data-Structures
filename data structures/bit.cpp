#include <bits/stdc++.h>
using namespace std;
const int ms = 1e5+10; 
int a[ms], bit[ms];

void updt(int i, int val){
	a[i] += val;
	for(; i < ms; i += (i&-i))
		bit[i] += val;
}

long long query(int i){
	long long ans = 0;
	for(; i > 0; i -= (i&-i))
		ans += bit[i];
	return ans;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		updt(i, a[i]);
	}

	int q;
	cin >> q;
	while(q--){
		int tp, l, r;
		cin >> tp >> l >> r;
		if(tp == 1){
			cout << query(r) - query(l-1) << endl;
		}
		else{
			updt(l, r-a[l]);
		}
	}
	return 0;
}