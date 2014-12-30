// http://algs4.cs.princeton.edu/15uf/WeightedQuickUnionUF.java.html
// port of weighted quick union find covered in coursera Algorithms I
#include <iostream>
#include <string>

class WeightedQuickUnionUF {
	
	int *id;
	int *sz;
	int _count;
	
	public:
	
	WeightedQuickUnionUF(int N) {
		_count = N;
		id = new int[N];
		sz = new int[N];
		for(int i = 0; i < N; i++) {
			id[i] = i;
			sz[i] = 1;
		}
	}
	
	int root(int p) {
		while(p != id[p]) {
			p = id[p];
		}
		return p;
	}
	
	bool connected(int p, int q) {
		return root(p) == root(q);
		return false;
	}
	
	void createUnion(int p, int q) {
		int rootP = root(p);
		int rootQ = root(q);
		if(rootP == rootQ) return;
		
		if(sz[rootP] > sz[rootQ]) {
			id[rootQ] = rootP;
			sz[rootP] += sz[rootQ];
		}
		else {
			id[rootP] = rootQ;
			sz[rootQ] += sz[rootP];
		}
		
		_count--;
	}
	
	int count() {
		return _count;
	}
};

int main(int argc, char **argv) {
	int N;
	std::cout << "enter number of objects: ";
	std::cin >> N;
	WeightedQuickUnionUF u(N);
	char c;
	int p, q;
	do {
		std::cout << "enter p: ";
		std::cin >> p;
		std::cout << "enter q: ";
		std::cin >> q;
		
		if(!u.connected(p, q)) {
			u.createUnion(p, q);
			std::cout << p << " " << q << std::endl;
		}
	
		std::cout << "continue? Y/N ";
		std::cin >> c;
	} while(c != 'n' && c != 'N');
	std::cout << u.count() << " components" << std::endl;
}

