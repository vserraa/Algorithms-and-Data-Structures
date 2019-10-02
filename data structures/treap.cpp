#include <bits/stdc++.h>
using namespace std;

struct Treap {
	struct item {
		int key, prior, cnt;
		item *l, *r;
		item() {}
		item(int k, int p, item *l = NULL, item *r = NULL): key(k), prior(p), cnt(0), l(l), r(r) {}
	};

	typedef item* pitem;

	int get_cnt(pitem t) {
		return t ? t->cnt : 0;
	}

	void upd_cnt(pitem t) {
		if(t) t->cnt = 1 + get_cnt(t->l) + get_cnt(t->r);
	}

	void split(pitem t, int x, pitem &l, pitem &r) {
		if(!t) {
			l = r = NULL;
		}
		else if(x <= t->key) {
			//quando coloca <= tudo que for MENOR vai pra t1
			//e tudo que for MAIOR OU IGUAL vai pra t2
			//se trocar pra < tudo que for MENOR OU IGUAL vai pra t1
			//e tudo que for MAIOR vai pra t2
			split(t->l, x, l, t->l), r = t;
		}
		else {
			split(t->r, x, t->r, r), l = t;
		}

		upd_cnt(t);
	}

	//merge t1 e t2 e guarda em t
	//todas as keys em t1 são menores que as keys em t2
	void merge(pitem &t, pitem t1, pitem t2) {
		if(!t1 || !t2) {
			t = t1 ? t1 : t2;
		}
		else if(t1->prior > t2->prior) {
			merge(t1->r, t1->r, t2), t = t1;
		}
		else {
			merge(t2->l, t1, t2->l), t = t2;
		}

		upd_cnt(t);
	}

	void insert(pitem &t, pitem it) {
		if(!t) {
			t = it;
		}
		else if(it->prior > t->prior) {
			split(t, it->key, it->l, it->r), t = it;
		}
		else {
			insert((it->key < t->key) ? t->l : t->r, it);
		}

		upd_cnt(t);
	}

	void erase(pitem &t, int key) {
		if(t->key == key) {
			merge(t, t->l, t->r);
		}
		else {
			erase((key < t->key) ? t->l : t->r, key);
		}

		upd_cnt(t);
	}

	//unite eh um merge genarilizado
	pitem unite(pitem l, pitem r) {
		if(!l || !r) return l ? l : r;
		if(l->prior < r->prior) swap(l, r);
		pitem lt, rt;
		split(r, l->key, lt, rt);
		l->l = unite(l->l, lt);
		l->r = unite(l->r, rt);
		return l;
	}
};


int main() {
	ios::sync_with_stdio(0), cin.tie(0);


	return 0;
}