// http://community.topcoder.com/tc?module=ProblemDetail&rd=4482&pm=1592
// Problem Name:	 ChessMetric
// Used In:	 TCCC '03 Round 4
// Used As:	 Division I Level One
// Categories:	 Dynamic Programming, Graph Theory

#include <iostream>
#include <vector>

using namespace std;

class ChessMetric {
	public:
	long howMany(int size, vector<int> start, vector<int> end, int numMoves) {
		
		return 0;
	}
}

void test(int size, vector<int> start, vector<int> end, int numMoves, int expected) {
	ChessMetric c;
	int result = c.howMany(size, start, end, numMoves);
	cout << "expected " << expected << ", got " << result << " => " << ((expected == result) ? "passed" : "failed") << endl;
}

int main(int argc, char** argv) {
}
