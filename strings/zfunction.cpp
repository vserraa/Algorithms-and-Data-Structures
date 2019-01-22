#include <bits/stdc++.h>
using namespace std;
const int ms = 2e5+10;
int z[ms];

void build(string s){
	z[0] = 0;
	int l = 0, r = 0;
	for(int i = 1; i < s.size(); i++){
		if(i <= r)
			z[i] = min(z[i-l], r-i+1);
		while(i+z[i] < s.size() && s[z[i]] == s[i+z[i]]) 
			z[i]++;
		if(i+z[i]-1 > r) 
			l = i, r = i+z[i]-1;
	}
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	string p, t;
	cin >> p >> t;
	string s = p + "#" + t;
	build(s);
	for(int i = p.size()+1; i < s.size(); i++)
		if(z[i] == p.size())
			cout << "Match at position " << i-p.size()-1 << endl;
	return 0;
}