#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4000005;
int lp[N + 1];
int phi[N + 1];
vector<int> pr;
ll cpp[N];

void calc_sieve() {
    phi[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            phi[i] = i - 1;
            pr.push_back(i);
        }
        else {
            if (lp[i] == lp[i / lp[i]])
                phi[i] = phi[i / lp[i]] * lp[i];
            else
                phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}

int main() {
	calc_sieve();
	return 0;
}