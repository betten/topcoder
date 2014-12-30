// http://community.topcoder.com/tc?module=ProblemDetail&rd=15705&pm=12784
// Problem Name:	 HexagonalBoard
// Used In:	 SRM 593
// Used As:	 Division I Level One
// Categories:	 Graph Theory

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HexagonalBoard {
	public:
	
	int minColors(vector<string> board) {
		int k = 0;
		
		int **colors = new int*[board.size()];
		for(int i = 0, n = (int) board.size(); i < n; i++) {
			colors[i] = new int[board[i].size()];
			for(int j = 0, m = (int) board[i].size(); j < m; j++) {
				colors[i][j] = 0;
			}
		}
		
		int N = (int) board.size();
		int M = (int) board[0].size();
		
		for(int i = 0, n = N; i < n; i++) {
			for(int j = 0, m = M; j < m; j++) {
				cout << board[i][j];
				
				if(board[i][j] == '-') continue;
				
				int c = 1;
				while(
					(i > 0 && colors[i-1][j] == c) || // 0,1
					(j > 0 && colors[i][j-1] == c) || // 1,0
					(i < N-1 && j > 0 && colors[i+1][j-1] == c) || // 2,0
					(i < N-1 && colors[i+1][j] == c) || // 2,1
					(j < M-1 && colors[i][j+1] == c) || // 1,2
					(i > 0 && j < M-1 && colors[i-1][j+1] == c)) // 0,2
					c++;
				colors[i][j] = c;
				
				if(c > k) k = c;
			}
			cout << endl;
		}
		
		cout << "----" << endl;
		
		for(int i = 0, n = (int) board.size(); i < n; i++) {
			for(int j = 0, m = (int) board[i].size(); j < m; j++) {
				cout << colors[i][j];
			}
			delete colors[i];
			cout << endl;
		}
		delete colors;

		return k;
	}
};

void test(vector<string> board, int expected) {
	HexagonalBoard h;
	int result = h.minColors(board);
	cout << "expected " << expected << ", got " << result << " => " << ((expected == result) ? "passed" : "failed") << endl;
}

int main(int argc, char **argv) {
	//test({"---", "---", "---"}, 0);
	//test({"-X--", "---X", "----", "-X--"}, 1);
	//test({"XXXX", "---X", "---X", "---X"}, 2);
	//test({"-XX", "X-X", "XX-"}, 2);
	//test({"-X--", "XXXX", "---X", "-XX-"}, 3);
	//test({"X"}, 1);
	//test({"-"}, 0);
	//test({"XXXXXXXX--XX--XXXXXXX-XXXXXXXXX-XXXXXXXX-X-XXX-XXX", "XXXXXXX--XXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXX", "XX-XXX---XXXXXXXXXXXXXXX-XXX--X-XXXX--XXXXXXXXXXX-", "--X-XXXXXXXXXXXXXX--XXXXX-XXXXXXXXXXX--XX-XXXXX-X-", "-XXXXXX-XXXXX-X-XX--XX---X-XXXXXXXXX-XXXXX-XXX-X-X", "-XXXXXXXX---XXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXX-X", "-XXXXXXXX-XXXXXXXXX-XXXX-X-XXXXXXXXXXXXXXXX-XXXXXX", "XXXXXXXX-XXXXXX-XXXXXXX-XXXXX-XXXXXXX--XXXXX-XXX--", "XXX--XX-XXXX-X-XX-X-XX-XXXXX--XX-XX--XXXXXX--XXXXX", "XXXXXXXXX-XXXXXXX-XX-X-XXXXXX-XX-XXXXXXX-XX-XXXX-X", "XXXXXXX-X-XXXXX--XXXXXXXXXXXXX-XXXXX-X-XXXXXXX--XX", "XX-XXXXXXX-XX--XXX-XXXXXXXXXXX----XXXX-XXXXXXXX-XX", "XXXX---XXXXXXXX-XXX--XXXX-XXXXXXXXXXXXXXXXXXXXX-X-", "XXXXXX-XXX-XXXXXXXXX-XXXXXXX-XXXXXX-X-XXXXXXXXXXXX", "-XXXXX-XXXXXXXXXXXXXXX-XX-XXXXXXXXXXXXXXXXXXXX-XX-", "XXX-XXX-XXXXXX-XXXXXXXXXXX-XX--XXXXXXXX-XXXXX--XX-", "XX-XXX-XXX-XXXXXXXXX-XX-XXXX-X-X-XX-XXX-X-XXX-XX-X", "XXXXXXXX-XXXXXX-XX-XX-XXX-XX-XXX-XXXXXXXX-X-XXXXXX", "XXXXX-XXXXXX-XXXXX--XXXXXXX-X-XXXX-XXXXXXXXXXXXXX-", "X-XXX--XXXXXX-X-XXXXX--XX-XXX-XXXXXX-X-XXXXXX-XXXX", "XXXXXXXXXX-XX-XXXXXXXX-XXXXXXXXXXXX-X-XXXXXXXXXXXX", "-X-XXXXXXXX--XXXXXXXXXXXXXXXXXXXXXXXX-XXXX--XXXXXX", "XX-XXXX-XXXXXXXXXXXXXXXX-X-XXXXXX-X-X-X-XXX-XXXXXX", "-XXX---XXXXX-X-XXXXXXXXX-XXXXXXXXXXXXX-XXX--XX-X-X", "-X-XXXXXXXXXXXXXXXXX-XXX-XXXX-XXXX--XXXXXX-X-XXXXX", "XXXXXXXX-X-XXXX---XXXXXXXXX--XX-X-XXXXXXXX-XXXXXXX", "-XXX-XXXXXXXXX-XXXXXXXXX-X-XXXXXXXXX-XXXX-XXXXXX-X", "XXXXXXXXXXXXXXXXXX-XX-XXX-XXXXXXXX---XXXXX-XXX--XX", "XXXX-XXXX-XXXX-X-XXX-XXXXXXXXXX-XX-XXXXXXXXXXXX--X", "--XX-XX-XXXX-XX-XXXXXXXXXXXXXX-XXXXXXXX-X-XXXXXXXX", "X-XXXXX-XXX-XXXXXXXXXXXX-XXX-XXXXXX-XX-XXXXXXX-XXX", "-XXXXXXXX-XXXXX-XXX--XXXXXXXXXX-XXXX-XXXXXXXXXXXXX", "X--XXX-XXXXX-XXXXXXXXXX-XXXXX-X-XXXXXXX--XXXXXXXXX", "XX--XXXX-X-XXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XX", "X-X--XXXXXX--XXXX--XX-XXXXXXXXXXXX-XXXXXXXXXXX-XXX", "XXXXX-XXXXXXX-X--XXXXXXXXXXXX-XXXXXX--X-XXXXXXXXXX", "-X-XXXXXXXXXXXXXXX-XX-XXXXXXX-X-XXX--X-XX-XX-XXXXX", "XXXXXXXXXX-XXXX-XX-XXX-XXXX-XXXXXXX-XX--XXXXX-X---", "XXXXXXXXXXXXXXXX-XXXXXXX-XXXXXX-XXXXXXXXXXXXXXXXX-", "-X--X-XXXXXXX-X--XXX-XX-XXXXX-XXXXXXXXXXXXXXXXXXX-", "X-XXX-XXXXXX-XXXX-XX-XX-XXXXXX-X-XXXXXX-XXXXXXXXXX", "XXXXX--XXXXXXXXXXXXXXXX--XX-X--XXXXXXX-X-XXXXX-X-X", "XXXXXXXXXXXX--XXXX-XX--XXXXX-XXXXXXXXX--XX-XXX-XXX", "-XXXXXXX-XXXXX--X-XXXXX--XXX-XXXXXXXXXX-XX-XXXXXXX", "XXXX-XXXXXXXXXXX--XXXXXXXXXX-XXX-XXX-XXXXX-X-X-XX-", "XXX-XX--XXXXXXXXX--XX--XXXXXXX-XXXXX-XXXXXX-XXXXXX", "-XXXXXXXXXX-XXXXX--XXXXXXXXXXXXXXXXXXX-X-XXXX-XXXX", "XXXXXX-X--XXXXX-X-XXXXXXXXXXXXXX-XXXXXXX-XX-X-X--X", "XX-XXXX-XXXXX-XXXXXXXXXX-XXX-XXXXXX-XXXX-XXXXXXXXX", "XXXXXXX-XXXXX-XXXXXXX-XXX-XX--X-X-XXXXXXXX-XXX-XXX"}, 3);
	//test({"XXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXX--XXXXXXXXXXX", "XXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXX-XXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXX-XXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXX--XXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XX-XXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXX", "XXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXX-X-XXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "X-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXX", "XX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXX", "XXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXX-XXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "-X-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXX-XX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"}, 3);
	//test({"XX-XX--","-XX-XXX","X-XX--X","X--X-X-","XX-X-XX","-X-XX-X","-XX-XX-"}, 3);
	//test({"X-X-X---X-X-X---X-X--X--X--X---X-X-X-X--X--X----X-", "-----X-------X-----------X---X---------------X---X", "-X------X--X---X---X--X--------X--X--X-X-X-X--X---", "--X---X--X--X----X--X---X-X--X--X--X--------X--X-X", "X--X------X--X----X---X----X--X--------X-X---X----", "-X---X-X---X---X----X--X-X--X---X--X-X-----X--X-X-", "--------X----X----X--X----X--X---X-------X--X----X", "X-X-X-----X----X---X--X-X----------X--X---X----X--", "-----X--X--X-X---X--X-----X--X-X----X--X---X-X--X-", "X--X--X--X-----X--X---X-X--X-----X---X--X--------X", "-X--X--X---X-X--X---X----X--X--X------X---X---X---", "--X-----X-----X--X-----X--X--X---X-X---X---X----X-", "X---X-X--X-X---X--X--X-----X--X------X--X---X----X", "--X----X-----X--X--X--X-X---X--X--X-------X---X---", "X---X---X--X--X--X-------------------X------X--X-X", "------X-----X-----X-X-X--X-X-X--X--X---X--X--X----", "-X-X---X-X---X-X--------------X------X--X--X---X-X", "-----------X------X-X-X---X-X---X--X--X--X---X----", "-X-X-X--X-----X-X------X-----X-------------X---X--", "---------X-X------X-X------X--X-X-X-X--X----X---X-", "-X---X-X------X------X-X-X--X--------X--X--------X", "---X----X--X----X-X----------X--X-X-------X-X-X---", "---------X----X------X-X-X-X---------X-X--------X-", "X-X-X-X----X----X-X---------X-X-X--X----X-X-X-----", "--------X-----------X------------X------------X-X-", "X-X--X------X-X--X---X-X-X--X-X----X-X---X--X-----", "-------X-X-----X--X-------X-----------X---X--X--X-", "X-X-X--------X-------X-X----X-X-X-X-X--X---------X", "-----X---X-X---X-X-X------X----------X---X-X--X---", "--X----X----X--------X--X-----X--X-X--X-----X--X-X", "X--X-----------X--X---X---X-X--X----X--X-----X----", "-X---X--X-X--X--X--X------------X----X---X-X---X--", "---X--X----------X---X-X-X---X---X-X--X-----X---X-", "X--------X-X--X----X-------X--X-----X---X-----X---", "-X-X--X--------X----X---X---X--X--X--X---X-X-----X", "----X--X-X--X---X----X-------X--X--X--X-----X-X---", "X-X-----------X---X----X-X----------X---X------X--", "---X-X---X--X--X---X-------X-X-X-X---X---X--X----X", "-X----X---X--X--X----X-X-X--------X-------X---X---", "----X------X--X----X-------X--X-X---X-X-X--X-----X", "X-X----X-X------X---X---X--------X-----------X-X--", "-----X----X-X-X---X--X---X--X-X---X--X---X------X-", "--X-----X-------X--X--X---X----X-------X---X-X---X", "X--X--X--X--X-X--X--X--X---X-X----X--X--X------X--", "----X-----X----X--X--X--X-----X-X--X--X--X---X----", "X------X---X-X--X--X------X------X--X--X--X----X-X", "--X-X-----------------X-X--X---X------------X-----", "X----X--X--X-X-X-X-X--------X----X--X--X--X----X-X", "-X--------------------X-X-X--X-------X-------X----", "--X--X-X-X-X-X--X-X-X------X---X-X-X--X-X-X---X-X-"}, 1);
	//test({"X-X-XX-X-X-X--X-XXXX-XX-XXX--XX-XX-XXX-X-XX-X-X-XX", "X-X---X-X---XX-X---X--X---X-X--X-XX----XX-XX-X-X-X", "X--XX-XX-X-X-X--XX-X-X-XX-X-X--XX--XXXX--X---X-XX-", "-XX-X--X-X-X-XX--X----X--X--XX---X-----XX-XX--X--X", "X-X--X-X-X--X--X-XX-XX--X-----XX-X-X-X--X--XX--X--", "XX-X-X-X-X-X-X-X--X--XXX-XXXX--XX-X--XX-XX---X-X-X", "---XX-X---X-X-X-X-XXX-------X---X-X-X--X-X--X--X-X", "X---X-X-X--X-X--X---XX-XX-XX-XX--X-X-X-X-XXX-X-XX-", "X-X-XX-X-X--X-X--X----X-----X-XX-X---X------X-X--X", "X--X-X-X-XX-X-XX--XXX-X-XXX-X--X-XXXX-X-XXX-X-X-X-", "-X---X-X---X----XX----X-----X-X-X----X------XX-X--", "X-XX-X-XX-X-XX-X-XXXX-XXXXX-X-X---X---XXXXXX-X--XX", "X-----X-X-X--XX-X----X----X-X--XX--XXX-------XX--X", "XXXXX-X--X-XX-XX--XX-X-XX-X-XX--XXX----X-XXX---X-X", "-----X-X-X--XX--X--X-XX-X--X--X----XXX-X---XX-X-X-", "XXXX--X-X--X--X-XX--X-X-XX-X-X-XXX----X--X--X-X-XX", "---XXX-X--X-XX---X-X--XX-X-XX-----X-XX-X-XX-X----X", "X-X--XX-XX---X-X-XX-X--X-X--XX-XXX-X-X-X---X-XXX-X", "XX--X-X--XXX--X-X--X-XX-X-XX-X----X-X---X--X----X-", "-X-X-------XXX--XXX----X-X-X-X---X---X-X-X---XXX-X", "-X--XXXX-X---X-X---XX-X--XX---XXX-XX-XX--X-XX--X-X", "X-X-------X--X--X-X--X-X--XXXX--X--X--XX--X--X-X-X", "-X-XXXX-X-X-X-XX-X-XX-X-X----XX-X-X-XX-XX--X-X-XX-", "X-X---X-X-XX-X-X--X-X-X-X-XX-----X---X---XX--X--X-", "X-X-X--X-X--X--X--XX---X-X--XXX-X-XX--X-X--X-X-X-X", "X-X-X-X-X--X-XX-XX--X-X-X-X----X-X---X--XX-X--X-X-", "---X--X--X-X---X-XX-X-X-XX-XX-X---XXX-XX-X--X-X--X", "XXX-X--XX-X--XX----X-X-X-XX-XX-XX----X-XX-XX---XX-", "--XX-XX--X-X---XX--X--X-X-X--X--XXX--XX--X--X-X-XX", "XX--X-XX-X-X-XX--XX-X-XX-X-X-XX---XXX--XX-XX-X-X-X", "-X-X-X---X-X--XX---X-X-XX--X--X-XX--X---X--X-X-X-X", "-XX--XXXX--XX--XX-X--XX--X---X-X--X--XX-X------X--", "X-X-X---XX---XX-X-----X-X-XXX--X-X-XX---X-XXX---X-", "X---XX----XXX--X-XXXX-X-X---X-X-X-X-XXX-X---X-XX-X", "XXX--XX-X----X--X---X---X-X----X-X-X---X-XXX-X---X", "--X-X-XX-X-X--XX-XX--XX-XX-XXX-X--X-X-X-X--X-XXXX-", "X--X-X--X-X-XX-XX--X--X---X----XXX-X-X-X-X------XX", "XXX-X-X-XX-X--X--XX--X-XX-X-X----X---X-XX-XXXXX--X", "--XX-X-----XXX----X-X-X-X-X-X-XX--X--X---X-----X-X", "X------XXX---XXXX-X--X--XX--X--XX--XX-X-X-X-XX-X--", "XXXXXX-----X-----X-XX--X-X---XX--XX--X-X---X---X-X", "-------X-X-X-XX-X-X-XX-X-X-XX-XXX--X----XX--XX-XX-", "XX-XXX-X-X-X--X---XX-X-X-X---X---XX-XXXX--XX----X-", "-XX---X-X-X--X-XXX---X--X-XX---XX-X----X-X-X-XX--X", "X-XXX--X--XX--X---X-X-XX-X--XX--XX--XXX-X-X-X-XXX-", "X---X-X-X--XXX--X-X-X--X-X-X--XX--XX--X----X-----X", "X-XX-X--XXX--XXX-X-X-X-X-X-X---X-X--X--XXX--X-XXX-", "X--X--XX---XX--X--X---X-X-X-XXX-X-X-X-----XX----X-", "X--XX----XX--X--X--XX-XX-------X-X---X--X----X-X-X", "X-X-XXXXX--XX-XX-XX-X---XXXXXX-X-XXX-XXX-XXXX-X-X-"}, 2);
	test({"X-X-", "X-X-", "X-X-", "XX--"}, 2);
	return 0;
}
