#include <bits/stdc++.h>
using namespace std;

int ext_gcd(int a, int b, int &s, int &t, int x = 0, int y = 1, int old_x = 1, int old_y = 0){
	int r = a%b, q = a/b;
	if(r == 0){ 
		s = x, t = y;
		return b;
	}

	return ext_gcd(b, r, s, t, old_x - q*x, old_y - q*y, x, y);
}

int main(){
	int a, b;
	cin >> a >> b;
	if(a < b) swap(a, b);
	//let d = gcd(a, b)
	//s*a + t*b = d
	int s, t;
	int d = ext_gcd(a, b, s, t);
	printf("%d = %d*%d + %d*%d", d, s, a, t, b);

	//if s and t are well defined, then infinite as many solution can be found
	//s(k) = s + k*b/d, t(k) = t - k*a/d 	
	return 0;
}
