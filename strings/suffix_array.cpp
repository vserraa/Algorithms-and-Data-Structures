#include <bits/stdc++.h>
using namespace std;
const int ms = 2e5+10;
int a[ms], c[ms], a1[ms], c1[ms], head[ms], lcp[ms], ra[ms];

//magic suffix array by Andrew Stankevich O(nlogn)
void build_sa(string s){
	s += "$";
	int n = s.size();

	for(int i = 0; i < n; i++)
		a[i] = i;
	sort(a, a+n, [&](int i, int j){
		return s[i] < s[j];
	});

	int cc = 0;
	for(int i = 0; i < n; i++){
		if(i == 0 || s[a[i]] != s[a[i-1]]){
			head[cc] = i;
			c[a[i]] = cc++;
		}
		else c[a[i]] = c[a[i-1]];
	}

	int lo = 1;
	for(; lo < n; lo <<= 1){
		//sort pelo segundo elemento inplace nas cores
		for(int i = 0; i < n; i++){
			//olho primeiro na ordem do sa pro segundo elemento do par e coloco 
			//o elemento que tem esse menor segundo elemento no inicio da cor dele
			int j = (a[i]-lo+n)%n;
			a1[head[c[j]]++] = j;
		}

		cc = 0;
		//aqui faz sort pelo primeiro e prepara a proxima iteracao
		for(int i = 0; i < n; i++){
			//verficia se precisa mudar a cor ou mantem a cor do ultimo cara
			if(i == 0 || c[a1[i]] != c[a1[i-1]] || c[(a1[i]+lo)%n] != c[(a1[i-1]+lo)%n]){
				head[cc] = i;
				c1[a1[i]] = cc++;
			}
			else{
				c1[a1[i]] = c1[a1[i-1]];
			}
		}

		//so copiando pra n cagar no meio da iteracao
		for(int i = 0; i < n; i++)
			a[i] = a1[i], c[i] = c1[i];
	}
}

void build_lcp(string s){
	int n = s.size();
	for(int i = 0; i < n; i++)
		ra[a[i]] = i;

	int z = 0;
	for(int i = 0; i < n; i++){
		if(ra[i] == n-1){
			z = 0;
			continue;
		}

		int j = a[ra[i]+1];
		while(i+z < n && j+z < n && s[i+z] == s[j+z]) z++;
		lcp[ra[i]] = z;
		z = max(0, z-1);
	}
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	build_sa(s);
	for(int i = 0; i < n; i++)
		a[i] = a[i+1];

	for(int i = 0; i < n; i++)
		cout << a[i] << " \n"[i == n-1];

	build_lcp(s);
	for(int i = 0; i < n-1; i++)
		cout << lcp[i] << " \n"[i == n-2];
	return 0;
}