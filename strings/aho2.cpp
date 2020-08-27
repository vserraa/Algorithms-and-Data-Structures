#include <bits/stdc++.h>
using namespace std;
 
const int ms = int(1e5)+10;
vector<int> occur[ms];
int ans[ms], cnt[ms];
string m[ms];

// This is based on @tfg50 implementation
template<const int ALPHA = 26, class T = std::string, const int off = 'a'>
struct Aho {
	struct Node {
		int to[ALPHA];
		int size;
		int fail, pfail;
		int present;
 
		Node() {
			for(int i = 0; i < ALPHA; i++) {
				to[i] = 0;
			}
			size = 0;
			pfail = fail = 0;
			present = 0;
			// maybe initialize some other stuff here
		}
 
		// maybe add some other stuff here
	};
 
	Aho() {
		nodes.push_back(Node());
	}
 
	int addString(const T &str, int idx) {
		int on = 0;
		for(auto ch : str) {
			if(nodes[on].to[ch-off] == 0) {
				nodes[on].to[ch-off] = (int) nodes.size();
				nodes.push_back(Node());
				nodes.back().size = 1 + nodes[on].size;
			}
			on = nodes[on].to[ch-off];
		}
		// makes this node present
		nodes[on].present = idx;
		return on;
	}
 
	void build() {
		std::queue<int> que;
		que.push(0);
		while(!que.empty()) {
			int on = que.front();
			que.pop();
			nodes[on].pfail = nodes[nodes[on].fail].present ? nodes[on].fail : nodes[nodes[on].fail].pfail;
			// do stuff that carries over with fail here
			for(int i = 0; i < ALPHA; i++) {
				int &to = nodes[on].to[i];
				if(to) {
					nodes[to].fail = on == 0 ? 0 : nodes[nodes[on].fail].to[i];
					que.push(to);
				} else {
					to = nodes[nodes[on].fail].to[i];
				}
			}
		}
	}
 
	void search(string &s) {
		int at = 0, n = s.size();
		for(int i = 0; i < n; i++) {
			at = nodes[at].to[s[i]-off];
			
			int temp = at;
			if(!nodes[temp].present) 
				temp = nodes[temp].pfail;
		
			while(temp != 0) {
				int idx = nodes[temp].present;
				occur[idx].push_back(i-m[idx].size()+1);
				if(occur[idx].size() >= cnt[idx]) {
					ans[idx] = min(ans[idx], i-occur[idx][occur[idx].size()-cnt[idx]]+1);
				}
 
				temp = nodes[temp].pfail;
			}
		}	
	}
 
	std::vector<Node> nodes;
};
 
int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	string s;
	cin >> s;
	int t;
	cin >> t;
	Aho<> aut;
	for(int i = 1; i <= t; i++) {
		cin >> cnt[i] >> m[i];
		aut.addString(m[i], i);
	}
 
	aut.build();
	memset(ans, 0x3f, sizeof ans);
	aut.search(s);
	for(int i = 1; i <= t; i++)
		cout << (ans[i]>1e9?-1:ans[i]) << endl;
	return 0;
}
