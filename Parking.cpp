// http://community.topcoder.com/stat?c=problem_statement&pm=3530&rd=6535
// Problem Name:	 Parking
// Used In:	 SRM 236
// Used As:	 Division I Level Three
// Categories:	 Graph Theory
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>

using namespace std;

#define fv(i, v) for(int i = 0; i < (int)v.size(); i++)
#define f(i, k, n) for(int i = k; i < n; i++)

struct node {
	int i;
	int j;
	int index;
};

class Parking {
	public:
	
	bool BFS(const node &C, const vector<node> &Ps, const vector<string> &park, int **graph) {
		bool visited[park.size()][park[0].size()];
		fv(i, park) {
			fv(j, park[0]) {
				visited[i][j] = 0;
			}
		}
		
		queue<node> q;
		q.push({ C.i, C.j, 0 }); // using index to count time step
		
		node N;
		
		while(!q.empty()) {
			N = q.front();
			q.pop();
			
			if(N.i < 0 || N.i >= (int)park.size() || N.j < 0 || N.j >= (int)park[0].size()) continue;
			if(visited[N.i][N.j]) continue;
			if(park[N.i][N.j] == 'X') continue;
			if(park[N.i][N.j] == 'P') {
				fv(i, Ps) {
					if(Ps[i].i == N.i && Ps[i].j == N.j) {
						graph[C.index][Ps[i].index] = N.index;
					}
				}
			}
			
			visited[N.i][N.j] = true;
			
			q.push({ N.i - 1, N.j, N.index + 1 });
			q.push({ N.i + 1, N.j, N.index + 1 });
			q.push({ N.i, N.j - 1, N.index + 1 });
			q.push({ N.i, N.j + 1, N.index + 1 });
		}
		
		
		return false;
	}
	
	bool connected(int **graph, const vector<node> &Cs, const vector<node> &Ps) {
		bool found;
		map<int, int> PCs;
		int C;
		fv(i, Cs) {
			// first check if this car can reach any parking spots
			found = false;
			f(j, 0, (int)Ps.size()) {
				if(graph[i][j] > 0) {
					found = true;
					break;
				}
			}
			if(!found) return false;
			// now lets find an empty one
			found = false;
			f(j, 0, (int)Ps.size()) {
				if(graph[i][j] > 0 && PCs.count(j) == 0) {
					PCs[j] = i;
					found = true;
					break;
				}
			}
			if(!found) { // we know this car can reach a spot, they're just all full
				f(j, 0, (int)Ps.size()) {
					// possible spot that's currently occupied
					if(graph[i][j] > 0) {
						// get the car in that spot
						C = PCs[j];
						// see if this car can't switch parking spots
						f(k, 0, (int)Ps.size()) {
							// there's parking spot and it's free
							if(graph[C][k] > 0 && PCs.count(k) == 0) {
								PCs[j] = i;
								PCs[k] = C;
								found = true;
								break;
							}
						}
					}
					if(found) break;
				}
			}
			if(!found) return false;
		}
		
		return true;	
	}
	
	int minTime(vector<string> park) {
		int ci = 0, pi = 0;
		vector<node> Cs, Ps;
		fv(i, park) {
			fv(j, park[i]) {
				if(park[i][j] == 'C') {
					Cs.push_back({ i, j, ci++ });
				}
				else if(park[i][j] == 'P') {
					Ps.push_back({ i, j, pi++ });
				}
			}
		}
		
		int **graph = new int*[Cs.size()];
		fv(i, Cs) {
			graph[i] = new int[Ps.size()];
		}
		fv(i, Cs) {
			fv(j, Ps) {
				graph[i][j] = 0;
			}
		}
		
		fv(i, Cs) {
			BFS(Cs[i], Ps, park, graph);
		}
		
		//////////////////////////////////////
		if(false) {
			fv(i, Cs) {
				fv(j, Ps) {
					cout << graph[i][j] << " ";
				}
				cout << endl;
			}
			cin.get();
		}
		//////////////////////////////////////
		
		if(!connected(graph, Cs, Ps)) return -1;
		
		int lo = 0, hi = 50*50, m;
		bool c;
		while((hi - lo) > 1) {
			m = (hi + lo) / 2;
			int **clone = new int*[Cs.size()];
			fv(i, Cs) {
				clone[i] = new int[Ps.size()];
			}
			fv(i, Cs) {
				fv(j, Ps) {
					clone[i][j] = graph[i][j];
				}
			}
			fv(i, Cs) {
				fv(j, Ps) {
					if(clone[i][j] > m) clone[i][j] = 0;
					else if(clone[i][j] > 0) clone[i][j] = 1;
				}
			}
			c = connected(clone, Cs, Ps);
			if(c) {
				hi = m;
			}
			else {
				lo = m;
			}
			////////////////////////////////////////
			if(false) {
				cout << hi << " // " << lo << endl;
				
				cout << m << " > " << c << endl;
				fv(i, Cs) {
					fv(j, Ps) {
						cout << clone[i][j] << " ";
					}
					cout << endl;
				}
				cin.get();	
			}
			////////////////////////////////////////
		}
		
		return hi;
	}
};

void test(vector<string> park, int expected) {
	Parking p;
	int result = p.minTime(park);
	cout << (result == expected ? "passed" : "failed") << " => expected: " << expected << ", got: " << result << endl;
}

int main() {
	test({"C.....P", "C.....P", "C.....P"}, 6);
	test({"C.X.....", "..X..X..", "..X..X..", ".....X.P"}, 16);
	test({"XXXXXXXXXXX", "X......XPPX", "XC...P.XPPX", "X......X..X", "X....C....X", "XXXXXXXXXXX"}, 5);
	test({".C.", "...", "C.C", "X.X", "PPP"}, 4);
	test({"CCCCC", ".....", "PXPXP"}, -1);
	test({"..X..", "C.X.P", "..X.."}, -1);
	test({"P.................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.", "..................................................", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXC"}, 1274);
	test({"PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC"}, 80);
	test({"PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC", "PPPPPPPPPPCCCCCCCCCC"}, 10);
	test({"CPCPCPCPCPCPCPCPCPCP", "PCPCPCPCPCPCPCPCPCPC", "CPCPCPCPCPCPCPCPCPCP", "PCPCPCPCPCPCPCPCPCPC", "CPCPCPCPCPCPCPCPCPCP", "PCPCPCPCPCPCPCPCPCPC", "CPCPCPCPCPCPCPCPCPCP", "PCPCPCPCPCPCPCPCPCPC", "CPCPCPCPCPCPCPCPCPCP", "PCPCPCPCPCPCPCPCPCPC"}, 1);
	test({".PPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "PPPPPPPPPP........................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC", "........................................CCCCCCCCCC"}, -1);
	test({"CX...X...X...X...X...X...X...X...X...X...X...XPPP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CXCX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XPXP", "CCCX...X...X...X...X...X...X...X...X...X...X...XP"}, 1174);
	test({"CCCCCXCCCPPPX", "PPPPPXPPPCCCX", "XXXXXXXXXXXXX", "CCCCCPPPPPCCP"}, -1);
	test({"PPPPP.....CCCCC"}, 10);
	test({"C", "P"}, 1);
	test({"PC"}, 1);
	test({"CX", "XP"}, -1);
	test({"P....CP....C"}, 5);
	test({"PXC..............................................P"}, 47);
	test({"..C....X......X.....X..XXX.....C...XX.............", "XXC.XX..XX.X.....XX.......P.C........XX..XX.X..P..", ".X.X.P...X.P.X.X.X......X........XX......C........", "..XX.X.....P.X..X..................C..X...........", ".X..P......P......PC...P..X.X......XP...X......P..", "P.C.P.......X..XP..XX..X.............X...X.X..X..X", "....PP...X...X..C..C....X..PX....X........P.......", "........X...X...........X..X..X........X.X.....C.X", "...X...........X....X..X...X......P...XX..........", "..X......X..........C.P.....X.XX...X.....XP..P....", "X..XXC....C....X...XX.P....X.C.......C.CX...X..X.C", "..............X..XC.X..X..XX..P.....P..C.....X....", "..X.......X.X.....XP.C...............P.........XX.", "X....P.X.P...X....X........P.C.X..C.C...X..P..PPX.", "...X..X.X............X..X..............XPP....X...", "......X....X......C.X.CX..X...CX...XX....C.X....X.", "..........X....X.........PX......X..C....X...X..P.", "..XX...X.CCP.X...........XC.P.XXP..XP.P....XXX...C", "...CXP...X.....XX..CX.X....C...........X..C.....P.", ".P.X....P....X......X..XP..........X........P.X...", "X.X.X..XX..X..........X..C...C..C.....P.X.........", "..P..X...X....P...X.X......P.....P...C...XX....X..", ".X.XP...X.....X...XXX..X.X...X.XX.......X...X...X.", ".......X.....XXX.CX......P...X.X...X.....PX..C....", "...X.................XC....PX..CX.........X...C..X", "X......XXX..C......X....X....X.CXC.X.CX.......P...", ".X..........X..XCX..X..XXX....P...XX.XCXC.........", "X...........P..P..X.X.......XXXX.........P...X....", ".......XX...P.X.C.....X...X........X.....XX.......", "..X.C..P...C..........XX..X.P............X..X.....", ".....X.....C........X..X..........X....X.X.XX....X", ".XX...XXCX.....X................X...XP.......XX.P.", "...X..................X...X.......XP.....CX.C.C...", ".......C.X......P.X....X..X.XX....XC...XX.........", "..X.....C...P.X.X..X.....C.....C...X..C....XP.X.X.", "....C.....X..........X....X.X..X......XCX........X", "..P..C.X..X.X....X.X....X....X.P..........XX.XX...", ".X....X.......X..P.....XCX....C.X....X.X...X...X.X", ".X....XX...X.XX..X........P...XC.P..X.X.....X...X.", "..X.XX.....X................X.....X..........P....", "......XX.......X...X..P....P...PX..C.X....X.......", ".....X............C.XXXPCP..X...X......X.X......P.", "..............X.P..X....P.C.P.....P.........P.....", "..XX....XPX...X.........PX..CCX.....XX..X.XXX.....", ".....PXC.X.................C....X.X........X.C....", "..........X..............P....X..X..X......XXC....", "........X...X.X.X....X.X...X.P.X........C.....P.C.", ".........XX....P......CCX..C.X....XXX...PX.....C..", "XX.X..C.X...PXX...X...X.XC..X....X.C.C.XC.......X.", "C.C.X...PC....X..X..P......................X..X..."}, 12);
	test({"XX.XX.X.X.XX.XX.XXXXC...X.XX.XXXX...XX.XX.XXP...XX", ".XXXX..X....XP.X.CX.PXX.C....XXXX.XXX.X.XX.XX.XXXC", "PXX..XC.X.XC.X.XX..XX.XX..XX..XCX.......XC...X.X..", "XPXXX.......X..P.X.XX.P.X.X.X.CX.X....XX.....X.X..", "X..X..X..XX..X.XC.CX.X.XXXX..X.CX.XXX.XX.X.PXX.PP.", ".P.C.X..X.P..XX....PX....PXC..XXX......X..X.XX.X..", "....XXXXXCC..XX..X..X.P.X..XX....X...X.X...XXXX.X.", "XXXX.PP.XPX.XCX..XX.X.P.X.XXX.....XXX.X..P.XXXX.XX", "X..X.X.XXXX...PXX.PX.PX..XXX.C.XXX.X..XXXXXX.C..XX", ".CX.X.P.XXXX....X..XP.XX.CXC.X...X.X..X..XX.X....X", "C.PX.X...XX.XCX..X..X.X.XXXX...X..X.XXX.X.XX..XX.X", ".X..X....X...X.XX....XX.P.X.XPX..X.X......XX.....X", "...XXX...X.PXXXXX..XX.PPP.X.XX.X.X...XXX.XXX.X..X.", "C.X..XX....XP.P.XC..X.X....P..X..X...XXXXXX.X.XXXX", "...PX..XXXXX..X..X.X..X.XP.XXX..CXP.XX.X....X.X...", "CX.XX.XP.CX..XXXP.X.XX.XXXPX.X.X..XCX..XX...XX..XX", "XXXX.X...X...X.....XX.X.XX...X.X.C.X..XX..X.XPCXX.", "P..XXXX..XX.C..X.X...XX.X.X.P.P.XC.XXX.XC..PX..X.X", "XXX..X.XXX....XX...CXX....X...X.XXX...XPX...X.C.X.", ".X.XX.X..X.....X..X..XX.X.....X.XX.X.X..X.XXX..X..", "XXX.....X...X..XXPXX..XX.....PXXXXX.........XX.CX.", ".......X......X.CX...XX.XX..XXXX..X..CXXXX.P..X..C", "XX..XX.XX..X..XX.XX..X..XX...PP..X.X.X..XXP..XXCX.", ".XX.XXX..X.XXX..XXX..X.X..X.XX.X..X...XXX.PXXX.X.X", ".XXXC..X......XX.X...XXXX.P.XX...XX..XXX.XX..X.X.X", "..X...C..XXX.....XX....XX....XXXXX.X..PXC.X.X.XX..", "....X..XX.PCX...PXXC.X..X..X.X.X..X.X.XX..X.X.XX..", ".CXX...XX...X..XP.X..XX..XX...XXC...XX.X.X.X...X..", "C..XX....X..X..PX.XXX.X..C.XXC.X.XX.XXX..X..XPX.XX", "XXX...X...X.XXC.X.....X....XX.X..X..XPX.XXX.....X.", "XX..XXX.X..X.CX..X..XXPXXX......XX.XPP...XX..C...X", "..XX.X..X.XXXX.X.....XX.XXX....XXXXXXCX.X.X....X..", "XXX.X.XXXXP.C..PXX..XXXXXPXXXXCXXXCX.X..XXX..P..P.", "X.XXXC..P.XX..XX..XXXX..XXX..C..X..P.XX..XX....PXX", "XP.X.X..XXCX..X.X.X.......XXXX.X...X.X.XXXXX...X.X", "...XX...PX....XX..X.X..XX....CXXX..XXX.X....XXX.X.", ".X....X...X.X.XC.X..XC....XPXX.P.X.XX.XX......XXX.", "XPX..X..XX..C..XXXX...CXP.X..XX.XXX..C..X.X.X.....", "X..XXXXX..X.X..XXCX.XX.XXX.XX..XP.X....XCXX.X.P.X.", "..X...XXXC.X.....PX.X.XXP..XX.X.XP..X.XXX..XXXXX..", "X.C.X.CX....C.X..PX...X..XX.PXP..XXC..X......P.XXP", ".X.XX.XX.X.XPXX......XX.X.C....CXX..X..X...X..XXX.", "XXXXX.XX.X.X...PXXX.....X...XX.X...C...P..XXX.X..X", ".XXX.X.......X..XXX..X.XXXXX.X..XXX.X.CCXXX......X", ".P....X.X..X.XXX.X.X...X.CXX.....X...XPX....X.X..X", ".XXC.X.XXXP.XC.P.X.X....X...CXX.X..XX.........X...", "XXXX.X..X.XXCCX....X.X..XXXX..XX..XXC...XXC..XX...", ".XXX.X.X..XX....XXX.X.X....X...X.XXX..X.XXXXXX..X.", "XXX.PXX..C...X...XX.X...XX.XX..X.X.PX.........C...", "..X...X..X...X..X....XCX.XP..X.X......X.XC.....X.X"}, -1);
	test({"P.....P...X.XX.X.X..X...XXXX.....X..P......X.P....", "...XX..P..X...X.X..X..X..X..XX.X.XX....XXX....X...", "X.X..XX..XX..XP.......X....X.X.....PX...........XX", "..XXX..X...X.......X....X..X.X..X.XX.X.XX..P.XX...", ".XX.X.PXP......XX.XXXX......XX.....XXXXXX..X..X...", ".XX.......X...X..XXXX.X.XX..........X...XX......X.", ".PX......XXX.XX.XPX..X....XX.X.X...XXP..XX...XX...", "..X..........X..X...X.X.X.X....X.XP....X..PX......", ".X...X.X.........X..........X.XXXXXX.X....X...XXXX", ".X.P..........XX......X.P..P.X.....X..XPX.P..P..XX", "....X......X.XX.XXX.X..PX.XX......X......C.X....XX", ".......X...XX.XPX.X.XX.XC.XX..X...X..X....PXXX....", ".XX..X..X.....X....X...........X.X..XX...X...X....", "X......C...X.X..X....XX.X..........P......X...XP..", ".X.XXXP.XX.X.X..XX.PPX....X.....X..XX......XXCXXX.", "X.XX..........XXXX.......X....X.....P.X.X...X.XP.P", ".XX.X.....X.PXX.XC.X.XXP.....PX.P.........X..X...X", "X........PXX......X......XXPX..P...X..X....X..XP..", "...X.PX....XX...XX....X.X.P......XX.X.X...X...X...", "....X.XX......PX.X.PX..X..XXX.C..X.XPX.X.X....P.XX", ".XXP.XXX.XX.XX...XX.XX.X..XX...X.X.....PX...X..X..", ".X.....X.XXP...X.....X...XXXXX.X.X........X..X.X.X", "X..X...X..XX..P.X.XXX..XXXPX.X...XX...X.X.......X.", ".XXXXXXXX..X....X.X.X.X..........XP.....X.......X.", ".....X.XXXXX..........XP...X....PXX.X...........XX", ".XXX....X......X.....X.XX..X......XXX......XXX..XX", "......X....XX...X.XXX...X..X.P...X.XX...XX.X.X..XX", "X..P..XX.XP.....X.XXXX.X......X...P..X.PXX.XX.....", ".XX...X..X...X......P...X...PXPX.XX....X......X...", "X......X.XX..XXX.X.......XX..X....X.X.X.X.P..XXX.X", "....X.X.X.XX...X.X.XXPX.XX.P.X..X.X.XX.XXX...X....", ".XX.X..X....X....X..XX.XX..P.XX.....XX..XP.X.XXXXX", ".....XXXX..P.XP...X...X...X.XPX.XX........X....XXX", "..X.....XX...X.........X.X.X.....X.X.XX.XXX.......", "X...X......P..P.P..X....P...XX..X.......X.....X.X.", "XX.X....X.X.X.PXX.X..X..XX........X.......XXXX...X", ".X.X..X..X.X.....X.........X..P.X.....X..XX.X.....", ".XX.........X.XX....XX.....XX..XX.XXXXXXXX....XP.X", "X.P...X..XX.XP...X..P.X.X....XP....PXX...X.X...X..", "......XX.XXX...X.....XX.X....XX..P...C.XX.X...X.X.", "..X.....X......X.XC..XXXX......X....X.X......X.XCX", "..XXX..X....X....X..XXXX.X.P...XP.X.X.X.X....X....", "X.....X.X....X..........X..X.XPXXXX.X..X..XX.X.X.X", ".....X..XX..X..XX....X...XX.X.....X.X..XXX.......X", "XXX...XXXX.....X.......XX.X.X.X.X......X.XXXXP....", "..XX..XX.XX..........C...XXPP..XX...X..........XXX", "XP........X..X..X......X.P....XXX.X..P............", "XXX..X.XXX.X...X.X..X...X...X.P...PX..XXXX..X.....", "XX.X.....X..X.XX..X.X..XPXXX...X.P.X.X.X..X.....XX", ".P.........PX........P..X..X.X.X..XX..XX...X..X..."}, 7);
	test({"."}, 0);
	test({"P"}, 0);
	test({"C"}, -1);
	test({"X"}, 0);
	test({"..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", "..................................................", ".................................................."}, 0);
	
}
