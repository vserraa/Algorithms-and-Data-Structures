#include <bits/stdc++.h>
using namespace std;
#define fr(i, a, b) for(int i = a, _ = b; i < _; i++)
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<int, int> pii;

int main(){
	int nn; cin >> nn;
	fr(lo, 0, nn){
		int n, j, area = 0, ans = 0;
		stack<int> s;
		cin >> n;
		int a[n];
		fr(i, 0, n)
			cin >> a[i];
		
		for(j = 0; j < n; j++){
			if(s.empty() || a[j] >= a[s.top()])
				s.push(j);
			else{
				while(!s.empty() && a[j] < a[s.top()]){
					int top = s.top();
					s.pop();
					if(!s.empty())
						area = a[top]*(j-s.top()-1);
					else 
						area = a[top]*j;
					ans = max(ans, area);
				}
				s.push(j);
			}
		}

		while(!s.empty()){
			int top = s.top();
			s.pop();
			if(!s.empty())
				area = a[top]*(j-s.top()-1);
			else 
				area = a[top]*j;
			ans = max(ans, area);
		}

		cout << ans << endl;
	}
	return 0;
}