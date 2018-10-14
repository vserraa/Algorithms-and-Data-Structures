#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
const int ms = 2e6+2;
int trie[ms][52], link[ms], sz = 0;
vector<int> terminal[ms];
char txt[ms], pat[ms];
bitset<1000> term[ms];

inline int get(char c){
	if(c >= 'a' && c <= 'z') return c-'a';
	else return 26 + c - 'A';
}

void insert(int i){
	int node = 0, tam = strlen(pat);
	for(int j = 0; j < tam; j++){
		char c = pat[j];
		if(trie[node][get(c)] == -1){
			trie[node][get(c)] = ++sz;
		}
		node = trie[node][get(c)];
	}
	term[node][i] = 1;
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
				term[to] = term[to] | term[f];
			}
		}
	}
}

bitset<1000> search(){
	bitset<1000> ans;
	int node = 0, tam = strlen(txt);
	for(int i = 0; i < tam; i++){
		char c = txt[i];
		node = trie[node][get(c)];
		ans = ans | term[node];
	}
	return ans;
}

int main(){
	memset(trie, -1, sizeof trie);
	scanf(" %s", txt);
	int q;
	scanf("%d", &q);
	int ans[q];
	memset(ans, 0, sizeof ans);
	for(int i = 0; i < q; i++){
		scanf(" %s", pat);
		insert(i);
	}

	build_links();
	bitset<1000> v = search();
	for(int i = 0; i < q; i++)
		ans[i] = v[i];

	for(int i = 0; i < q; i++){
		if(ans[i])
			printf("Y\n");
		else
			printf("N\n");
	}
	return 0;
}