#include <bits/stdc++.h>
using namespace std;
const int ms = 1e6+20, sigma = 26;
int a[ms][sigma];

void build(string p){
	int brd = 0;
	for(int i = 0; i < sigma; i++)
		a[0][i] = 0;
	
	a[0][p[0]-'a'] = 1;
	for(int i = 1; i <= p.size(); i++){
		for(int ch = 0; ch < sigma; ch++)
			a[i][ch] = a[brd][ch];
		
		if(i < p.size()){
			a[i][p[i]-'a'] = i+1;
			brd = a[brd][p[i]-'a'];
 		}
	}
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		string s, p;
		cin >> s >> p;
		build(p);
		int now = 0;
		vector<int> ans;
		for(int i = 0; i < s.size(); i++){
			now = a[now][s[i]-'a'];
			if(now == p.size())
				ans.push_back(i-p.size()+2);
		}

		if(ans.size() == 0)
			cout << "Not Found" << endl;
		else{
			cout << ans.size() << endl;
			for(int i = 0; i < ans.size(); i++)
				cout << ans[i] << " \n"[i == ans.size()-1];
		}
		cout << endl;
	}
	return 0;
}
