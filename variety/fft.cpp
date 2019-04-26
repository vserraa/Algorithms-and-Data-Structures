#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
typedef long long ll;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert = false) {
	int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
    	double alfa = (invert?-1:1)*2*PI/len;
    	cd wlen(cos(alfa), sin(alfa));
    	for(int i = 0; i < n; i += len) {
    		cd w(1);
    		for(int j = 0; j < len/2; j++) {
    			cd u = a[i+j], v = w*a[i+j+len/2];
    			a[i+j] = u+v;
    			a[i+j+len/2] = u-v;
    			w *= wlen;
    		}
    	}
    }

    if(invert) {
    	for(auto &x : a)
    		x /= n;
    }
}
 
//a[0]*x^grau + ... + a[grau] --> invert = true
//caso seja a[0] + .. + a[grau]*x^grau --> invert = false
vector<ll> multiply(vector<ll> p1, vector<ll> p2, bool invert = false) {
	if(invert) {
		reverse(p1.begin(), p1.end());
		reverse(p2.begin(), p2.end());
	}

	vector<cd> fa(p1.begin(), p1.end()), fb(p2.begin(), p2.end());
	int n = 1;
	while(n < fa.size() + fb.size()) 
		n <<= 1;

	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for(int i = 0; i < n; i++)
		fa[i] *= fb[i];

	fft(fa, true);
	vector<ll> ans(n);
	for(int i = 0; i < n; i++)
		ans[i] = round(fa[i].real()); 

	ans.resize(p1.size()+p2.size()-1);
	if(invert) 
		reverse(ans.begin(), ans.end());

	return ans;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n;
		m = n;
		vector<ll> p1(n+1), p2(m+1);
		for(int i = 0; i < n+1; i++)
			cin >> p1[i];
		for(int i = 0; i < m+1; i++)
			cin >> p2[i];

		vector<ll> ans = multiply(p1, p2, true);

		for(int i = 0; i <= n+m; i++)
			cout << ans[i] << " \n"[i==n+m];
	}

	return 0;
}