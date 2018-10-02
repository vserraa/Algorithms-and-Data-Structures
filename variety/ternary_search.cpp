#include <bits/stdc++.h>
using namespace std;

//perceba que a função tem um máximo
double f(double x){
	return 7 - x*x;
}

//funciona tanto pra monotona como pra unimodal
double solve(double l, double r){
	for(int i = 0; i < 300; i++){
		double m1 = l + (r-l)/3;
		double m2 = r - (r-l)/3;
		//se a função tem minimo, inverte o sinal aqui em baixo
		if(f(m1) < f(m2))
			l = m1;
		else
			r = m2;
	}
	return l;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cout << fixed << setprecision(3);
	double l, r;
	cin >> l >> r;
	double ma = solve(l, r);
	cout << "max is at x = " << ma << " ans has value " << f(ma) << endl;
	return 0;
}