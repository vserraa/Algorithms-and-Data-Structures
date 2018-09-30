#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int ms = 400003;
ll st[4*ms], lazy[4*ms], a[ms];

void build(int i, int l, int r){
	if(l == r)
		st[i] = a[l];
	else{
		int mid = (l+r)/2;
		build(2*i, l, mid);
		build(2*i+1, mid+1, r);
		st[i] = st[2*i]+st[2*i+1];
	}
}

void updt(int i, int l, int r, int lr, int rr, ll val){
	if(lazy[i] != 0){
		st[i] += (r-l+1)*lazy[i];
		if(l != r){
			lazy[2*i] += lazy[i];
			lazy[2*i+1] += lazy[i];
		}
		lazy[i] = 0;
	}

	if(rr < l || lr > r)
		return;

	if(l >= lr && r <= rr){
		st[i] += val;
		if(l != r){
			lazy[2*i] += val;
			lazy[2*i+1] += val;
		}
		return;
 	}

 	int mid = (l+r)/2;
 	updt(2*i, l, mid, lr, rr, val);
 	updt(2*i+1, mid+1, r, lr, rr, val);
 	st[i] = st[2*i]+st[2*i+1];
}

ll query(int i, int l, int r, int lr, int rr){
	if(lazy[i] != 0){
		st[i] += (r-l+1)*lazy[i];
		if(l != r){
			lazy[2*i] += lazy[i];
			lazy[2*i+1] += lazy[i];
		}
		lazy[i] = 0;
	}

	if(rr < l || lr > r)
		return 0;

	if(l >= lr && r <= rr)
		return st[i];

	int mid = (l+r)/2;
 	return query(2*i, l, mid, lr, rr)+query(2*i+1, mid+1, r, lr, rr);
}

int main(){

}
