// http://community.topcoder.com/stat?c=problem_statement&pm=1259&rd=4493
// Problem Name:	 ZigZag
// Used In:	 TCCC '03 Semifinals 3
// Used As:	 Division I Level One
// Categories:	 Dynamic Programming

#include <iostream>
#include <vector>

using namespace std;

class ZigZag {
	public:
	
	int longestZigZag(vector<int> sequence) {
		vector<int> longest;
		
		for(int i = 0, n = (int) sequence.size(); i < n; i++) {
			cout << sequence[i] << endl;
		}
		return 0;
	}
};

void test(vector<int> sequence, int expected) {
	ZigZag z;
	int result = z.longestZigZag(sequence);
	cout << "expected " << expected << ", got " << result << " => " << ((expected == result) ? "passed" : "failed") << endl;
}

int main(int argc, char **argv) {
	test({1, 7, 4, 9, 2, 5}, 6);
	//test({1, 17, 5, 10, 13, 15, 10, 5, 16, 8}, 7);
	//test({10, 20}, 2);
	//test({20, 10}, 2);
	//test({20, 20}, 1);
	//test({44}, 1);
	//test({1, 2, 3, 4, 5, 6, 7, 8, 9}, 2);
	//test({10, 9, 8, 7, 6, 7, 8, 9, 10}, 3);
	//test({12, 333, 700, 436, 1, 919, 959, 456, 456, 456, 1000, 193, 192, 13, 75, 818, 197, 197, 2, 777, 99, 81, 222, 109, 1000, 19, 27, 270, 62, 189, 987, 234, 55, 2, 718, 238, 901, 901, 900, 432, 55, 606, 89, 7, 7, 23, 789, 790, 800, 1000}, 26);
	return 0;
}
