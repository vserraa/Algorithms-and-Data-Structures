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

struct SuffixAutomaton {
    struct state {
        int len, link;
        map<char, int> next;
    };

    SuffixAutomaton(int MAXLEN): MAXLEN(MAXLEN) {
        sz = 0;
        st.resize(2*MAXLEN);
        sa_init();
    }

    int MAXLEN;
    vector<state> st;
    int sz, last;

    void sa_init() {
        st[0].len = 0;
        st[0].link = -1;
        sz++;
        last = 0;
    }

    void sa_extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};


int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    SuffixAutomaton sa(s.size());
    for(auto c : s) {
        sa.sa_extend(c);
    }
    return 0;
}