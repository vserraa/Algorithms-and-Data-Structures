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
const int sigma = 26;
 
struct Eertree {
    struct Node {
        int id, len, link;
        vector<int> to;
        Node(): id(0), len(0), link(0) {
            to.assign(sigma, -1);
        };
        Node(int id, int len, int link): id(id), len(len), link(link) {
            to.assign(sigma, -1);
        };
    };

    vector<int> occAsMax, occ;
    string T;
    vector<Node> nodes;
    int lsp, nxt;
 
    Eertree() {
        nodes.push_back(Node(-1, -1, 0));
        nodes.push_back(Node(0, 0, 0));
        occ.assign(2, 0);
        occAsMax.assign(2, 0);
        lsp = 0, nxt = 2;
    }
 
    int add(char c) {
        int size = T.size();
        int cur = lsp;
        occAsMax[lsp]++;

        while(nodes[cur].id != -1) {
            if(size-1-nodes[cur].len >= 0 && T[size -1 -nodes[cur].len] == c)
                break;
            cur = nodes[cur].link;            
        }
 
        if(nodes[cur].to[c-'a'] != -1) {
            lsp = nodes[cur].to[c-'a'];
            T.push_back(c);
            return 0;
        }
 
        Node new_node(size+2, nodes[cur].len+2, -1);
        nodes[cur].to[c-'a'] = nxt;
        occAsMax.push_back(1);
        lsp = nxt++;
 
        if(new_node.len == 1) {
            new_node.link = 1;
            nodes.push_back(new_node);
            T.push_back(c);
            return 1;
        }
        
        cur = nodes[cur].link;
        while(nodes[cur].id != -1) {
            if(size-1-nodes[cur].len >= 0 && T[size -1 -nodes[cur].len] == c)
                break;
            cur = nodes[cur].link;  
        }
 
        if(nodes[cur].to[c-'a'] != -1) 
            new_node.link = nodes[cur].to[c-'a'];
        else 
            new_node.link = 0;
 
        nodes.push_back(new_node);
        T.push_back(c);
 
        return 1;
    }

    void build_occ() {
        occ.assign(nxt, 0);
        for(int i = nxt-1; i > 0; i--)
            occ[i] = occAsMax[i];
        for(int = nxt-1; i > 0; i--) 
            occ[ nodes[i].link ] += occ[i];
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    Eertree palindromic_tree;
    for(auto v : s) {
        cout << palindromic_tree.add(v) << endl;
    }
    return 0;
}