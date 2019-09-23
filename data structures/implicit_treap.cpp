#include <bits/stdc++.h>
using namespace std;

class ImplicitTreap {
private:
	struct item {
		int sum, value, prior, cnt;
		item *l, *r;
		item() {}
		item(int value, int p, item *l = NULL, item *r = NULL): value(value), prior(p), cnt(0), l(l), r(r) {}
	};

	typedef item* pitem;

	pitem root;

	int cnt(pitem t) {
		return t ? t->cnt : 0;
	}

	int sum(pitem t) {
		return t ? t->sum : 0;
	}

	void upd_sum(pitem t) {
		if(t) t->sum = t->value + sum(t->l) + sum(t->r);
	}

	void upd_cnt(pitem t) {
		if(t) t->cnt = 1 + cnt(t->l) + cnt(t->r);
	}

	void split(pitem t, int x, pitem &l, pitem &r, int add = 0) {
		if(!t) {
			l = r = NULL;
			return;
		}

		int key = cnt(t->l) + add;
		if(x <= key) {
			split(t->l, x, l, t->l, add), r = t;
		}
		else {
			split(t->r, x, t->r, r, add + 1 + cnt(t->l)), l = t;
		}

		upd_cnt(t);
		upd_sum(t);
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
		upd_sum(t);
	}

	void erase(pitem &t, int key, int add = 0) {
		int cur_key = cnt(t->l) + add;

		if(cur_key == key) {
			merge(t, t->l, t->r);
		}
		else if(key < cur_key) {
			erase(t->l, key, add);
		}
		else {
			erase(t->r, key, add+1+cnt(t->l));
		}

		upd_cnt(t);
		upd_sum(t);
	}

	void output(pitem t) {
		if(!t) return;
		output(t->l);
		cout << t->value << " ";
		output(t->r);
	}

public:
	ImplicitTreap(pitem root = NULL) : root(root) {}
	
	void insert(int pos, int val) {
		pitem t1, t2;
		split(root, pos, t1, t2);
		int prior = rand();
		pitem x = new item(val, prior);
		merge(t1, t1, x);
		merge(root, t1, t2);
	}

	void erase(int key) {
		erase(root, key);		
	}

	int query(int l, int r) {
		pitem t1, t2, t3;
		split(root, l, t1, t2);
		split(t2, r-l+1, t2, t3);
		int ans = t2->sum;
		merge(root, t1, t2);
		merge(root, root, t3);
		return ans;
	}

	void output() {
		output(root);
	}
};


int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	srand(time(NULL));
	ImplicitTreap t;
	while(1) {
		int op;
		cin >> op;
		if(op == 1) {
			//insert
			int val, pos;
			cin >> pos >> val;
			t.insert(pos, val);
		}
		else if(op == 2) {
			//erase
			int pos;
			cin >> pos;
			t.erase(pos);
		}
		else if(op == 3) {
			//query l, r
			int l, r;
			cin >> l >> r;
			cout << t.query(l, r) << endl;
		}
		else if(op == 4) {
			//print array
			t.output();
			cout << endl;
		}
	}
	return 0;
}