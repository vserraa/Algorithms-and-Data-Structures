#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
typedef long long ll;

struct CRT {

    ll GCD(ll a, ll b) { return (b == 0) ? a : GCD(b, a % b); }

    inline ll LCM(ll a, ll b) { return a / GCD(a, b) * b; }

    inline ll normalize(ll x, ll mod) { x %= mod; if (x < 0) x += mod; return x; }

    struct GCD_type { ll x, y, d; };

    GCD_type ex_GCD(ll a, ll b) {
        if (b == 0) return {1, 0, a};
        GCD_type pom = ex_GCD(b, a % b);
        return {pom.y, pom.x - a / b * pom.y, pom.d};
    }

    vector<ll> a, n;

    CRT (vector<ll> a, vector<ll> n): a(a), n(n) {
        assert(a.size() == n.size());
        for(int i = 0; i < a.size(); i++) {
            a[i] = normalize(a[i], n[i]);
        }
    }

    bool solve(ll &ans, ll &lcm) {
        int N = a.size();
        ans = a[0];
        lcm = n[0];
        for(int i = 1; i < N; i++) {
            auto pom = ex_GCD(lcm, n[i]);
            ll x1 = pom.x;
            ll d = pom.d;
            if((a[i] - ans) % d != 0) return false;
            ans = normalize(ans + x1 * (a[i] - ans) / d % (n[i] / d) * lcm, lcm * n[i] / d);
            lcm = LCM(lcm, n[i]); 
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        vector<ll> n(2, 0), a(2, 0);
        cin >> a[0] >> n[0] >> a[1] >> n[1];
        CRT c(a, n);
        ll ans, lcm;
        if(c.solve(ans, lcm)) {
            cout << ans << " " << lcm << endl;
        }
        else {
            cout << "no solution" << endl;
        }
    }
    return 0;
}