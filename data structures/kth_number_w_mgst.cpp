#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int ms = 101210;
int a[ms], n;
typedef pair<int, int> pii;
vector<pii> nums;
vector<int> tree[4*ms];
#define all(v) v.begin(), v.end()

void build(int node = 1, int l = 0, int r = n-1){
	if(l == r){
		tree[node].push_back(nums[l].second);
	}
	else{
		int mid = (l+r)/2;
		build(2*node, l, mid);
		build(2*node+1, mid+1, r);
		merge(all(tree[2*node]), all(tree[2*node+1]), back_inserter(tree[node]));
	}
}

int query(int node, int x, int y, int k, int l = 0, int r = n-1){
 	if(l == r){
 		return tree[node][0];
 	}

 	int mid = (l+r)/2;
 	int m = upper_bound(all(tree[2*node]), y)-lower_bound(all(tree[2*node]), x);
 	if(m >= k)
 		return query(2*node, x, y, k, l, mid);
 	else
 		return query(2*node+1, x, y, k-m, mid+1, r);
}

int main(){
	int m, ll, rr, k;
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		scanf("%d" ,a+i);
		nums.push_back({a[i], i});
	}
		
	sort(all(nums));	
	build();
	for(int i = 0; i < m; i++){
		scanf("%d %d %d" ,&ll, &rr, &k);
		ll--, rr--;
		int pos = query(1, ll, rr, k);
		cout << a[pos] << endl;
	//	printf("%d\n" ,a[query(1, ll, rr, k)]);
	}

	return 0;
}
