// http://community.topcoder.com/stat?c=problem_statement&pm=4700&rd=7995
// Problem Name:	 EncodingTrees
// Used In:	 SRM 261
// Used As:	 Division I Level Two
// Categories:	 Recursion
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define FOR(i, a, b) for(int i = a, n = b; i <= n; i++)
#define COUT(x) cout << x << endl

int ntrees[20];

struct EncodingTrees {
	string getCode(int N, int nr) {
		--nr;
		ntrees[0] = 1;
		FOR(i, 1, 19) {
			ntrees[i] = 0;
			FOR(j, 0, i - 1) {
				// http://stackoverflow.com/questions/5439340/for-binary-tree-suppose-there-is-n-node-how-many-different-structure-can-i-con
				ntrees[i] = ntrees[i] + ntrees[j] * ntrees[i - 1 - j];
			}
			COUT(ntrees[i]);
		}
		if(nr < 0 || nr >= ntrees[N]) return "";
		return "x";
	}
};

int main() {
	EncodingTrees e;
	e.getCode(2, 1);
}
