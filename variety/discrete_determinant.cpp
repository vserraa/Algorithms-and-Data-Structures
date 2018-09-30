#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;

ll det(vector<vector<ll>> &z, int n) {
    ll d = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            z[i][j] %= mod;
        }
    }
 
    for (int i = 0; i < n; ++i) {
        if (!z[i][i]) {
            bool f = false;
            for (int j = i + 1; j < n; ++j) {
                if (z[j][i]) {
                    f = true;
                    for (int k = i; k < n; ++j) {
                        swap(z[i][k], z[j][k]);
                    }
                    d = -d;
                    break;
                }
            }
            if (!f) {
                return 0;
            }
        }
        for (int j = i + 1; j < n; ++j) {
            while (z[j][i]) {
                ll h = z[i][i] / z[j][i];
                for (int k = i; k < n; ++k) {
                    z[i][k] = (z[i][k] - h * z[j][k]) % mod;
                    swap(z[i][k], z[j][k]);
                }
                d = -d;
            }
        }
        d = (d * z[i][i]) % mod;
    }
 
    return (d + mod) % mod;
}

int main(){
    int n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];

    cout << det(a, n);
    return 0;
}