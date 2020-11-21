#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll; 
typedef tuple<int, int, int> t3;

const int N = 150;
const int INF = INT_MAX;
const double EPS = 1e-9;

// guass mod2 --> XoR equations
int gaussMod2 (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }

    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j) {
            sum += ans[j] * a[i][j];
            sum %= 2;
        }
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    
    return 1;
}

// gauss double
int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

// gaus for prime mod *** make sure matrix a is already in mod!!!! ***
int gaussMod (vector < vector<int> > a, vector<int> & ans, int mod) {
    auto fexp = [&](ll b, ll e) {
        ll ans = 1;
        for(; e > 0; e >>= 1) {
            if(e&1) ans = (ans * b) % mod;
            b = (b * b) % mod;
        }
        return ans;
    };

    auto inv = [&](ll v) {
        return fexp(v, mod-2);
    };

    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
 
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
 
        for (int i=0; i<n; ++i)
            if (i != row) {
                int c = a[i][col] * inv(a[row][col]) % mod;
                for (int j=col; j<=m; ++j) {
                    a[i][j] -= (a[row][j] * c) % mod;
                    a[i][j] %= mod;
                    a[i][j] = (a[i][j] + mod) % mod;
                }
            }
        ++row;
    }
 
    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] * inv(a[where[i]][i]) % mod;

    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j) {
            sum += ans[j] * a[i][j] % mod;
            sum %= mod;
        }
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;

    return 1;
}
 
int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    return 0;
}