#include <bits/stdc++.h>
using namespace std;

double f(double x){
	return x*x + 10;
}

double simpson_integral(double a, double b, int n){
	double ans = f(a) + f(b), h = (b-a)/n;
	for(int i = 1; i <= n-1; i++)
		ans += f(a+h*i)*((i&1)?4:2);
	return ans*h/3.0;
}

//explicit formula, might help in some problem
//gives a better understanding of the algorithm
double explict_si(double a, double b, int n){
	double ans = 0, h = (b-a)/n;
	for(int i = 0; i <= n-2; i += 2){
		ans += (f(a + h*i) + 4*f(a + h*(i+1)) + f(a + h*(i+2)))*h/3.0;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int a, b;
	while(cin >> a >> b){
		cout << simpson_integral(a, b, 1000) << " " << explict_si(a, b, 1000) << endl;
	}
	return 0;
}