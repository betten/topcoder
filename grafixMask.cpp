// http://community.topcoder.com/stat?c=problem_statement&pm=2998&rd=5857
// Problem Name:	 grafixMask
// Used In:	 SRM 211
// Used As:	 Division I Level Two
// Categories:	 Recursion
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int pic[400][600];
int q[400*600], head, tail;

void add(int x, int y) {
	if(x < 0 || y < 0 || x >= 600 || y >= 400) return;
	if(pic[y][x] == 1) return;
	pic[y][x] = 1;
	q[tail++] = y*1000 + x;
}

class grafixMask {
	public:
	
	vector<int> sortedAreas(vector<string> rectangles) {
		for(int y = 0; y < 400; y++) {
			for(int x = 0; x < 600; x++) {
				pic[y][x] = 0;
			}
		}
		
		for(unsigned i = 0; i < rectangles.size(); i++) {
			istringstream ss(rectangles[i]);
			int x1, y1, x2, y2;
			ss >> y1 >> x1 >> y2 >> x2;
			for(int y = y1; y <= y2; y++) {
				for(int x = x1; x <= x2; x++) {
					pic[y][x] = 1;
				}
			}
		}
		
		vector<int> hole;
		
		for(int y = 0; y < 400; y++) {
			for(int x = 0; x < 600; x++) {
				if(pic[y][x] == 0) {
					head = tail = 0;
					add(x, y);
					while(head < tail) {
						int cx = q[head]%1000, cy = q[head]/1000;
						head++;
						add(cx+1, cy);
						add(cx-1, cy);
						add(cx, cy+1);
						add(cx, cy-1);
					}
					hole.push_back(tail);
				}
			}
		}
		
		return hole;
	}
};

int main() {
	grafixMask g;
	vector<int> x = g.sortedAreas({"1 1 398 598", "0 0 0 0", "399 599 399 599"});
	for(unsigned i = 0; i < x.size(); i++) {
		cout << x[i] << endl;
	}
	return 0;
}
