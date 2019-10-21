#include <bits/stdc++.h>
using namespace std;
const int max_val = 1e9;
mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> gen(0, max_val);

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	for(int i = 0; i < 100; i++)
		cout << gen(rng) << endl;
	return 0;
}