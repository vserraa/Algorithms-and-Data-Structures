#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
const int ms = 2e6+2;
int trie[ms][52], link[ms], sz = 0;
char txt[ms], pat[ms];
int term[ms];

inline int get(char c){
	if(c >= 'a' && c <= 'z') return c-'a';
	else return 26 + c - 'A';
}

void insert(string pat){
	int node = 0;
	for(auto c : pat){
		if(trie[node][get(c)] == -1){
			trie[node][get(c)] = ++sz;
		}
		node = trie[node][get(c)];
	}
	term[node] += 1;
}

void build_links(){
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int node = q.front();
		q.pop();
		for(auto ch = 0; ch < 52; ch++){
			int &to = trie[node][ch];
			int f = node == 0 ? 0 : trie[link[node]][ch];
			if(to == -1){
				to = f;
			}
			else{
				link[to] = f;
				q.push(to);
				term[to] += term[f];
			}
		}
	}
}

int search(string &s){
	int ans = 0;
	int node = 0;
	for(auto c : s){
		node = trie[node][get(c)];
		ans += term[node];
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	memset(trie, -1, sizeof trie);
	string s;
	cin >> s;
	int q;
	cin >> q;
	for(int i = 0; i < q; i++){
		cin >> pat;
		insert(pat);
	}

	build_links();
	cout << search(s) << endl;
	return 0;
}