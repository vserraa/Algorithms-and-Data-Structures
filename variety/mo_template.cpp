#include <bits/stdc++.h>
using namespace std;
const int ms = 1e4+10;
typedef long long ll;
int block_size;
unordered_map<int, int> t;
int cnt[ms];
set<int> can;

struct qry{
	int l, r, idx;
	qry() {}
	qry(int l, int r, int idx): l(l), r(r), idx(idx) {}
	bool operator <(const qry &h){
		if(l/block_size < h.l/block_size) return true;
		if(l/block_size == h.l/block_size && r > h.r) return true;
		return false;
	}	
};

int main(){
	int n, q, l, r;
	scanf("%d %d", &n, &q);
	block_size = sqrt(n);
	vector<qry> v;
	int a[n];
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}

	for(int i = 0; i < q; i++){
		scanf("%d %d", &l, &r);
		l--, r--;
		v.push_back(qry(l, r, i));
	}

	sort(v.begin(), v.end());
	int ans[q];
	int mo_l = 0, mo_r = -1;
	for(auto now : v){
		l = now.l, r = now.r;
		while(mo_r < r){
			mo_r++, cnt[a[mo_r]]++;
		}
		while(mo_r > r){
			cnt[a[mo_r]]--, mo_r--;
		}
		while(mo_l > l){
			mo_l--, cnt[a[mo_l]]++;
		}
		while(mo_l < l){
			cnt[a[mo_l]]--, mo_l++;
		}

		ans[now.idx] = *can.rbegin();
	}

	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
