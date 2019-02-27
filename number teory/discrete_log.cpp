#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fexp(ll b, ll e, ll mod){
	ll ans = 1;
	for(; e > 0; e >>= 1){
		if(e&1)
			ans = (ans*b)%mod;
		b = (b*b)%mod;
	}
	return ans;
}

//O(sqrt(m)*log(m))
ll discrete_log(ll a, ll b, ll m){
	//let x = n*p - q
	//p is in [1, m/n] q is in [0, n]
	//we know that for sure x <= phi(m) since a^phi(m) = 1 mod m
	//then a^np = b*a^q mod m

	unordered_map<ll, ll> f1;
	ll n = 1 + sqrt(m);

	for(ll p = n; p >= 1; p--)
		f1[fexp(a, n*p, m)] = p;

	ll ans = -1;
	for(ll q = 0; q <= n; q++){
		ll aux = (b*fexp(a, q, m))%m;
		if(f1.count(aux))
			ans = (ans==-1) ? n*f1[aux]-q : min(ans, n*f1[aux] - q);
	}

	return ans;
}

//find x such that a^x = b mod m
//gcd(a, m) = 1 --- might be possible to remove this constrait
int main(){
	ll a, b, m;
	while(scanf("%lld%lld%lld", &m, &a, &b) != EOF && (a|b|m)){
		ll x = discrete_log(a, b, m);
		if(x == -1)
			cout << "no solution" << endl;
		else
			cout << x << endl;
	}
	return 0;
}