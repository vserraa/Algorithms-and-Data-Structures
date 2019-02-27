#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int fexp(ll b, ll e, ll m){
	ll ans = 1;
	for(; e > 0; e >>= 1){
		if(e&1)
			ans = (ans*b)%m;
		b = (b*b)%m;
	}
	return ans;
}

vector<int> get_primitives(int m){
	int phi = m, aux = m;
	for(int i = 2; i*i <= aux; i++){
		if(aux%i == 0){
			phi -= phi/i;
			while(aux%i == 0)
				aux /= i;
		}
	}

	if(aux != 1) phi -= phi/aux;

	vector<int> factors;
	aux = phi;
	for(int i = 2; i*i <= aux; i++){
		if(aux%i == 0){
			factors.push_back(i);
			while(aux%i == 0)
				aux /= i;
		}
	}

	if(aux != 1) factors.push_back(aux);

	vector<int> roots;
	for(int a = 1; a < m; a++){
		if(__gcd(a, m) != 1) continue;
		//check if a is primitive 
		bool can = 1;
		for(auto v : factors){
			int t = phi/v;
			can &= (fexp(a, t, m) != 1);
		}

		if(can) 
			roots.push_back(a);
	}

	return roots;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;
	cout << "Primitive roots modulo " << n << " are :";
	vector<int> roots = get_primitives(n);
	for(auto v : roots)
		cout << " " << v;
	cout << endl;
	return 0;
}