// http://community.topcoder.com/stat?c=problem_statement&pm=3935&rd=6532
// Problem Name:	 SmartWordToy
// Used In:	 SRM 233
// Used As:	 Division I Level Two
// Categories:	 Graph Theory
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

struct node {
	string display;
	int presses;
};

class SmartWordToy {
	public:
	
	int minPresses(string start, string finish, vector<string> forbid) {
		//set<string> forbidden;
		bool forbidden[26][26][26][26];
		string a, b, c, d, s;
		for(int i = 0; i < (int)forbid.size(); i++) {
			stringstream ss(forbid[i]);
			ss >> a >> b >> c >> d;
			for(int w = 0; w < (int)a.size(); w++) {
				for(int x = 0; x < (int)b.size(); x++) {
					for(int y = 0; y < (int)c.size(); y++) {
						for(int z = 0; z < (int)d.size(); z++) {
							//stringstream fs;
							//fs << a[w] << b[x] << c[y] << d[z];
							//fs >> s;
							////cout << s << endl;
							//forbidden.insert(s);
							forbidden[a[w] - 'a'][b[x] - 'a'][c[y] - 'a'][d[z] - 'a'] = true;
						}
					}
				}
			}
		}
		
		queue<node> q;
		q.push({ start, 0 });
		
		set<string> visited;
		
		node n;
		string next, prev;
		
		while(!q.empty()) {
			n = q.front();
			q.pop();
			
			//cout << n.display << ", " << forbidden.count(n.display) << endl;
			//cin.get();
			
			//if(forbidden.count(n.display) != 0) continue;
			if(forbidden[n.display[0] - 'a'][n.display[1] - 'a'][n.display[2] - 'a'][n.display[3] - 'a']) continue;
			if(n.display.compare(finish) == 0) return n.presses;
			if(visited.count(n.display) > 0) continue;
			visited.insert(n.display);
			
			for(int i = 0; i < 4; i++) {
				next = n.display;
				next[i] = (next[i] == 'z') ? 'a' : (char)((int)next[i] + 1);
				prev = n.display;
				prev[i] = (prev[i] == 'a') ? 'z' : (char)((int)prev[i] - 1);
				q.push({ next, n.presses + 1 });
				q.push({ prev, n.presses + 1 });
			}
		}
		return -1;
	}
};

void test(string start, string finish, vector<string> forbid, int expected) {
	SmartWordToy s;
	int result = s.minPresses(start, finish, forbid);
	cout << (expected == result ? "passed" : "failed") << " => expected: " << expected << ", got: " << result << endl;
}

int main() {
	//test("aaaa", "zzzz", {"a a a z", "a a z a", "a z a a", "z a a a", "a z z z", "z a z z", "z z a z", "z z z a"}, 8);
	//test("aaaa", "bbbb", {}, 4);
	//test("aaaa", "mmnn", {}, 50);
	//test("aaaa", "zzzz", {"bz a a a", "a bz a a", "a a bz a", "a a a bz"}, -1);
	//test("aaaa", "zzzz", {"cdefghijklmnopqrstuvwxyz a a a",  "a cdefghijklmnopqrstuvwxyz a a", "a a cdefghijklmnopqrstuvwxyz a", "a a a cdefghijklmnopqrstuvwxyz"}, 6);
	//test("aaaa", "bbbb", {"b b b b"}, -1);
	//test("zzzz", "aaaa",
//{"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk",
 //"abcdefghijkl abcdefghijkl abcdefghijkl abcdefghijk"}, -1);
	//test("mmma", "yyyy", {"qwertyuiopasdfg qwertyuiopasdfg qwertyuiopasdfg z", "qwertyuiopasdfg qwertyuiopasdfg hjklzxvcbnm z", "qwertyuiopasdfg hjklzxvcbnm qwertyuiopasdfg z", "qwertyuiopasdfg hjklzxvcbnm hjklzxvcbnm z", "hjklzxvcbnm qwertyuiopasdfg qwertyuiopasdfg z", "hjklzxvcbnm qwertyuiopasdfg hjklzxvcbnm z", "hjklzxvcbnm hjklzxvcbnm qwertyuiopasdfg z", "hjklzxvcbnm hjklzxvcbnm hjklzxvcbnm z", "qwertyuiopasdfg qwertyuiopasdfg z qwertyuiopasdfg", "qwertyuiopasdfg qwertyuiopasdfg z hjklzxvcbnm", "qwertyuiopasdfg hjklzxvcbnm z qwertyuiopasdfg", "qwertyuiopasdfg hjklzxvcbnm z hjklzxvcbnm", "hjklzxvcbnm qwertyuiopasdfg z qwertyuiopasdfg", "hjklzxvcbnm qwertyuiopasdfg z hjklzxvcbnm", "hjklzxvcbnm hjklzxvcbnm z qwertyuiopasdfg", "hjklzxvcbnm hjklzxvcbnm z hjklzxvcbnm", "qwertyuiopasdfg z qwertyuiopasdfg qwertyuiopasdfg", "qwertyuiopasdfg z qwertyuiopasdfg hjklzxvcbnm", "qwertyuiopasdfg z hjklzxvcbnm qwertyuiopasdfg", "qwertyuiopasdfg z hjklzxvcbnm hjklzxvcbnm", "hjklzxvcbnm z qwertyuiopasdfg qwertyuiopasdfg", "hjklzxvcbnm z qwertyuiopasdfg hjklzxvcbnm", "hjklzxvcbnm z hjklzxvcbnm qwertyuiopasdfg", "hjklzxvcbnm z hjklzxvcbnm hjklzxvcbnm", "z qwertyuiopasdfg qwertyuiopasdfg qwertyuiopasdfg", "z qwertyuiopasdfg qwertyuiopasdfg hjklzxvcbnm", "z qwertyuiopasdfg hjklzxvcbnm qwertyuiopasdfg", "z qwertyuiopasdfg hjklzxvcbnm hjklzxvcbnm", "z hjklzxvcbnm qwertyuiopasdfg qwertyuiopasdfg", "z hjklzxvcbnm qwertyuiopasdfg hjklzxvcbnm", "z hjklzxvcbnm hjklzxvcbnm qwertyuiopasdfg", "z hjklzxvcbnm hjklzxvcbnm hjklzxvcbnm", "n ablm ablm abcdefghijkl", "n ablm abcdefghijkl ablm", "n abcdefghijkl ablm ablm", "abcdefghijklm n abcdefghijklm abcdefghijklm", "abcdefghijklm abcdefghijklm n abcdefghijklm", "abcdefghijklm abcdefghijklm abcdefghijklm n", "bcdefghijklm bcdefghijkl ablm ablm", "abcdefghijkl ablm bcdefghijkl ablm", "ablm bcdefghijklm bcdefghijkl ablm", "abcdefghijkl ablm ablm bcdefghijkl", "ablm abcdefghijkl ablm bcdefghijkl", "ablm ablm bcdefghijklm bcdefghijkl"}, 228);
	//test("qjbk", "snlc", {"r wk uqgd sqchfteg", "tupexrioblc wycbvn jwtq jk", "qwamsfkouj jidr lyptnore qurtw", "vxqaigb rjxo cvmjr ixoldjfw", "cybsrfigxl im qg elwda", "xsapvqybt fqkd tpafyqhw utgq", "cjfe den s wbm", "pgxij pgreu o a", "wskpftb sbmpl hajmgrnvsbq gpqemcklih", "wvnky turvbiso wtfnm idablx", "ifnvjmg a cb narquidvs"}, 24);
	test("aaaa", "dddd", {"jbd ja j jd", "jd jbc jcd jabd", "jabd jad j jb", "jabd jb jabcd jad", "jab jd jbc jabcd", "jbcd jacd ja jbc", "jc jacd jbcd jbd", "jab ja jbd jb", "jabd jad j j", "jad ja jbc jcd", "jabc j ja jbc", "jc jbd jc ja", "jcd jbc jabd jd", "jad jbd jbcd jab", "j jad jbcd jbd", "jc jad jcd jacd", "ja jb jc jbcd", "jb j jd jc", "jbc jc jb jabcd", "jd jabc jabcd ja", "jbc jabd jcd ja", "jad ja jcd jbcd", "jbd jac jabd jbd", "jabcd jbc jcd jabcd", "jcd jc jbd jab", "jac jabd jabd j", "jabcd jbd jacd jbc", "jb jd ja jbcd", "jabcd jabc jd jbd", "jd jad j jabcd", "jabd jabcd jacd j", "jbc jc jd jd", "jab jcd jbcd jcd", "jc ja jb jad", "jbcd jab jbcd jabcd", "jac jcd ja jacd", "jabc ja jabcd j", "jabcd jcd jac jac", "jbcd jabd jad jc", "j jacd jb j", "jbd jad jac jabd", "jacd jac jbcd jbcd", "jbd jad ja jd", "jabcd jbcd jbcd jb", "jabcd jac jacd jcd", "jabc ja jacd jb", "jb jc j jd", "j ja jacd jacd", "jbd ja jd jabc", "jabd jc jd jab"}, 14);
}
