#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int ms = 1e5+10;
int a[ms], spt[ms][20], n;

void pre(){
	for(int i = 0; i < n; i++)
		spt[i][0] = i;

	for(int j = 1; (1<<j) <= n; j++)
		for(int i = 0; i+(1<<j)-1 < n; i++){
			if(a[spt[i][j-1]] < a[spt[i+(1<<(j-1))][j-1]])
				spt[i][j] = spt[i][j-1];
			else
				spt[i][j] = spt[i+(1<<(j-1))][j-1];
		}
}

int rmq(int l, int r){
	int ans = inf;
	for(int j = 19; j >= 0; j--){
		if(l + (1<<j) - 1 <= r){
			ans = min(ans, a[spt[l][j]]);
			l += 1<<j;
		}
	}
	return ans;
}

//the fointowing code solves SPOJ'S RMQSQ
int main(){
	cin >> n;
	for(int i = 0; i < n; i++)
		scanf("%d", a+i);
	
	pre();
	int q;
	cin >> q;
	while(q--){
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", rmq(l, r));
	}

	return 0;
}