#include <bits/stdc++.h>
using namespace std;
const double EPS = 1E-9;

double det(vector<vector<double>> &a){
	double det = 1;
	for (int i = 0; i < n; i++) {
	    int k = i;
	    for (int j = i+1; j < n; j++)
	        if (abs(a[j][i]) > abs(a[k][i]))
	            k = j;
	    if (abs(a[k][i]) < EPS) {
	        det = 0;
	        break;
	    }
	    swap (a[i], a[k]);
	    if (i != k)
	        det = -det;

		double now = a[i][i];
	    det *= now;
	    for (int j = i; j < n; j++)
	        a[i][j] /= now;
	    
	    for (int j = i+1; j < n; j++)
	        if (j != i && abs(a[j][i]) > EPS){
	        	double factor = a[j][i];
	            for (int k = i; k < n; k++)
	                a[j][k] -= a[i][k]*factor;
	        }
	}

	return det;
}

int main(){
	int n;
	cin >> n;
	vector<vector<double>> a(n, vector<double>(n));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> a[i][j];


	return 0;
}