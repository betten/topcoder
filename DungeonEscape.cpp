// http://community.topcoder.com/stat?c=problem_statement&pm=2449&rd=5073
// Problem Name:	 DungeonEscape
// Used In:	 SRM 198
// Used As:	 Division I Level Two
// Categories:	 Graph Theory
#include <vector>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct node {
	int i;
	int j;
	int time;
};
class CompareNode {
	public:
	bool operator()(node &n1, node &n2) {
		return (n1.time > n2.time);
	}
};

class DungeonEscape {
	public:
	
	int exitTime(vector<string> up, vector<string> down, vector<string> east, vector<string> west, int startLevel, int startEasting) {
		int L = up.size();
		int n = up[0].size();
		
		bool visited[L][n];
		for(int i = 0; i < L; i++) {
			for(int j = 0; j < n; j++) {
				visited[i][j] = false;
			}
		}
		
		priority_queue<node, vector<node>, CompareNode> q;
		
		q.push({ startLevel, startEasting, 0 });
		
		while(!q.empty()) {
			node top = q.top();
			q.pop();
			
			// i = 0 --> 4n
			// i = 1 --> 3n
			// i = 2 --> 2n
			// i = 3 --> n
			
			if(top.i >= L || top.j < 0 || top.j >= n) continue; // out of bounds
			if(top.time >= (L - top.i)*n) continue; // flooded
			if(top.i < 0) return top.time;
			if(visited[top.i][top.j]) continue;
			visited[top.i][top.j] = true;
			
			if(up[top.i][top.j] != 'x') { 
				q.push({ top.i - 1, top.j, top.time + (up[top.i][top.j] - '0') });
			}
			if(down[top.i][top.j] != 'x') {
				q.push({ top.i + 1, top.j, top.time + (down[top.i][top.j] - '0') });
			}
			if(east[top.i][top.j] != 'x') { 
				q.push({ top.i, top.j + 1, top.time + (east[top.i][top.j] - '0') });
			}
			if(west[top.i][top.j] != 'x') {
				q.push({ top.i, top.j - 1, top.time + (west[top.i][top.j] - '0') });
			}
		}
		
		return -1;
	}
};

int main() {
	DungeonEscape d;
	cout << "exit time: " << d.exitTime({"0x4",
 "0x3",
 "0x3"},
{"0x9",
 "009",
 "0x9"},
{"0x9",
 "1x9",
 "009"},
{"0x9",
 "0x0",
 "009"},
2,
2) << endl; // 10

	cout << "exit time: " << d.exitTime({"xxxxxxxxx1",
 "1xxxxxxxxx",
 "xxxxxxxxx1"},
{"xxxxxxxxxx",
 "xxxxxxxxxx",
 "xxxxxxxxxx"},
{"1111111111",
 "xxxxxxxxxx",
 "1111111111"},
{"xxxxxxxxxx",
 "1111111111",
 "xxxxxxxxxx"},
2,
0) << endl; // 30

	cout << "exit time: " <<  d.exitTime({"xxxxxxxxx1",
 "xxxx999991",
 "x999999991"},
{"1111111111",
 "1111111111",
 "1111111111"},
{"1111122242",
 "2222222241",
 "2111111111"},
{"xxxxxxxxx1",
 "1111111111",
 "xxxxxxxxx1"},
2,
0) << endl; // -1

	cout << "exit time: " << d.exitTime({"1x2x3x4x5x6x7x8x9",
 "00000000000000000",
 "98765432223456789",
 "12345678987654321"},
{"00000000000000000",
 "00000000000000000",
 "00000000000000000",
 "00000000000000000"},
{"xxxxxxxxxxxxxxxxx",
 "xxxxxxxxxxxxxxxxx",
 "22222222222222222",
 "33333333333333333"},
{"xxxxxxxxxxxxxxxxx",
 "xxxxxxxxxxxxxxxxx",
 "22222222222222222",
 "33333333333333333"},
3,
12) << endl; // 17
}
