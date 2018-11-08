#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int ms = 1e5+10; 
int a[ms], bit[ms], n;

void updt(int i, int val){
	a[i] += val;
	for(; i < ms; i += (i&-i))
		bit[i] += val;
}

ll query(int i){
	ll ans = 0;
	for(; i > 0; i -= (i&-i))
		ans += bit[i];
	return ans;
}

int find_first_ge(ll val){
	int pos = 0;
	ll now = 0;
	for(int i = 1<<19; i > 0; i >>= 1){
		if(pos + i <= n && now + bit[pos+i] < val){
			now += bit[pos+i];
			pos += i;
		}
	}

	return pos; //1-indexed 
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
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