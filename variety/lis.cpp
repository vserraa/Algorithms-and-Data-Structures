#include <bits/stdc++.h>
using namespace std;

int lis(int a[], int n){
	vector<int> s;
	for(int i = 0; i < n; i++){
		auto it = lower_bound(s.begin(), s.end(), a[i]);
		if(it == s.end())
			s.push_back(a[i]);
		else
			*it = a[i];
	}
	return s.size();
}

int main(){
	int n; 
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++)
		cin >> a[i];

	cout << lis(a, n) << endl;
	return 0;
}
