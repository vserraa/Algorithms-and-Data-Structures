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

	return c;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();

	vector<int> cl = build_sa(s), sa(n);
	//aqui cl é o vetor com as classes de equivalencia dos sufixos
	//sa eh o proprio suffix array
	for(int i = 0; i < n; i++){
		sa[cl[i]] = i;
		cout << cl[i] << " \n"[i == n-1];
	}

	for(int i = 0; i < n; i++)
		cout << sa[i] << " \n"[i == n-1];
	return 0;
}