#include <bits/stdc++.h>
using namespace std;
const int size = 1e6+10;
string p, t;
int b[size];

void kmp_pre(){
	int sz = p.size();
	int i = 0, j = -1;
	b[i] = j;
	while(i < sz){
		while(j >= 0 && p[j] != p[i]) j = b[j];
		j++, i++;
		b[i] = j;
	}
}

bool kmp_search(){
	int sz = t.size(), m = p.size();
	int i = 0, j = 0;
	while(i < sz){
		while(j >= 0 && t[i] != p[j]) j = b[j];
		i++, j++;
		if(j == m){
			//found match starting at i-j
			//return true;
			j = b[j];
		}
	}
	return false;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int tc; cin >> tc;
	while(tc--){
		cin >> t;
		int q; cin >> q;
		while(q--){
			cin >> p;
			memset(b, 0, sizeof b);
			kmp_pre();
			if(kmp_search())
				cout << "y" << endl;
			else
				cout << "n" << endl;
		}
	}
	return 0;
}