#include <bits/stdc++.h>
using namespace std;
#define fr(i, a, b) for(long long i = a, _ = b; i < _; i++)

class BinaryIndexedTree{
private:
	long long *bit;
	long long size;
public:
	BinaryIndexedTree(long long size){
		bit = new long long[size+1];
		this->size = size+1;
		fr(i, 0, size+1)
			bit[i] = 0;
	}
	long long getNext(long long i){
		long long complement = (i & (~i+1));
		return i + complement;
	}
	long long getParent(long long i){
		long long complement = (i & (~i+1));
		return i - complement;
	}
	void build_tree(long long *original){
		long long next;
		fr(i, 0, size-1){
			next = i+1;
			do{
				bit[next] += original[i];
				next = getNext(next);
			}while(next < size);
		}		
	}
	long long prefixSum(long long index){
		long long sum = 0, parent = index+1;
		do{
			sum += bit[parent];
			parent = getParent(parent);
		}while(parent > 0);
		return sum;
	}
	void updtVal(long long *original, long long index, long long newVal){
		long long dif = newVal-original[index], next = index+1;
		original[index] = newVal;
		do{
			bit[next] += dif;
			next = getNext(next);
		}while(next < size);
	}
};

int main(){
	ios::sync_with_stdio(0);
	long long n, m, size = int(1e5)+1;
	cin >> n >> m;
	long long original[n];
	fr(i, 0, n)
		cin >> original[i];

	long long second[size] = {0};
	fr(i, 0, n)
		second[original[i]]++;

	BinaryIndexedTree tree(n);
	BinaryIndexedTree nelem(size);

	tree.build_tree(original);
	nelem.build_tree(second);
	fr(i, 0, m){
		char op;
		long long x, y;
		cin >> op >> x;
		if(op == 'C'){
			cin >> y;
			nelem.updtVal(second, original[x-1], second[original[x-1]]-1);
			tree.updtVal(original, x-1, y);
			nelem.updtVal(second, y, second[y]+1);
		}
		else if(op == 'S'){
			cin >> y;
			cout << tree.prefixSum(y-1) - tree.prefixSum(x-2) << endl;
		}
		else if(op == 'Q'){
			cout << nelem.prefixSum(x) << endl;
		}
	}
	return 0;
}