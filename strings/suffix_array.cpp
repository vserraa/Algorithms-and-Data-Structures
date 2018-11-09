#include <bits/stdc++.h>
using namespace std;

vector<int> build_sa(string s){
	int n = s.size();
	vector<int> p(n), c(n);
	vector<pair<int, int>> order(n);
	for(int i = 0; i < n; i++)
		p[i] = i;

	sort(p.begin(), p.end(), [&](int i, int j) -> bool {
		return s[i] < s[j];
	});

	int classes = 0;
	for(int i = 0; i < n; i++){
		if(i && s[p[i]] != s[p[i-1]]) classes++;
		c[p[i]] = classes;
	}


	for(int stp = 1; stp <= n; stp <<= 1){
		for(int i = 0; i < n; i++){
			order[i].first = c[i];
			order[i].second = (i+stp<n)?c[i+stp]:-1; //se quiser cyclic shifts pega (i+stp)%n
		}

		sort(p.begin(), p.end(), [&](int i, int j) -> bool {
			return order[i] < order[j];
		});	

		classes = 0;
		for(int i = 0; i < n; i++){
			if(i && order[p[i]] != order[p[i-1]]) classes++;
			c[p[i]] = classes;
		}
	}

	return p;
}

vector<int> build_lcp(string s, vector<int> &sa){
	int n = s.size(), k = 0;
	vector<int> rank(n), lcp(n-1);
	for(int i = 0; i < n; i++)
		rank[sa[i]] = i;

	for(int i = 0; i < n; i++){
		if(rank[i] == n-1){
			k = 0; 
			continue;
		}

		int j = sa[rank[i]+1];
		while(i+k < n && j+k < n && s[i+k] == s[j+k]) k++;

		lcp[rank[i]] = k;
		if(k) k--;
	}

	return lcp;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();

	vector<int> sa = build_sa(s);

	for(int i = 0; i < n; i++)
		cout << sa[i] << " \n"[i == n-1];

	vector<int> lcp = build_lcp(s, sa);
	for(int i = 0; i < n-1; i++)
		cout << lcp[i] << " \n"[i == n-2];

	/*sejam i e j duas posições nao necessariamente 
	adjacentes no suffix array já ordenado, então 
	LCP(i, j) = min(lcp[i], lcp[i+1], ..., lcp[j-1])*/
	return 0;
}