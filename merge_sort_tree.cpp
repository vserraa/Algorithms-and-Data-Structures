#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
const ll ms = 320000;
const ll inf = 0x3f3f3f3f;
ll a[ms], n;
vector<ll> mgst[4*ms];

void build(ll node = 1, ll l = 0, ll r = n-1){
	if(l == r){
		mgst[node].push_back(a[l]);
	}
	else{
		ll mid = (l+r)/2;
		build(2*node, l, mid);
		build(2*node+1, mid+1, r);
		merge(all(mgst[2*node]), all(mgst[2*node+1]), back_inserter(mgst[node]));
	}
}

ll query(ll x, ll y, ll k, ll node = 1, ll l = 0, ll r = n-1){
	if(r < x || l > y)
		return 0;

	if(l >= x && r <= y){
		return mgst[node].end()-upper_bound(all(mgst[node]), k);
	}

	ll mid = (l+r)/2;
	return query(x, y, k, 2*node, l, mid)+query(x, y, k, 2*node+1, mid+1, r);
}

int main(){
	ll q, lans = 0, x1, x2, x3;
	cin >> n;
	for(ll i = 0; i < n; i++)
		scanf("%lld" ,a+i);

	build();
	cin >> q;
	for(ll i = 0; i < q; i++){
		scanf("%lld %lld %lld" ,&x1, &x2, &x3);
		lans = query(x1-1, x2-1, x3);
		printf("%lld\n" ,lans);
	}
	return 0;
}