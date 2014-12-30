// http://community.topcoder.com/stat?c=problem_statement&pm=4721&rd=8000
// Problem Name:	 HairCuts
// Used In:	 SRM 267
// Used As:	 Division I Level Three
// Categories:	 Math, Simulation, String Parsing

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

#define f(i, k, n) for(int i = k; i < n; i++)

class HairCuts {
	public:
	
	int parse(string s) {
		int h, m;
		sscanf(s.c_str(), "%d:%d", &h, &m);
		if(h < 9) h += 12;
		return h*60 + m;
	}
	
	double maxCut(vector<string> enter, string lastExit) {
		//int h, m;
		//f(i, 0, (int)enter.size()) {
			//h = atoi(enter[i].substr(0, 2).c_str());
			//if(h < 9) h += 12;
			//m = atoi(enter[i].substr(3, 2).c_str());
			//cout << h << " " << m << endl;
		//}
		//return 0;
		
		vector<int> e;
		for(int i = 0; i < (int) enter.size(); i++) {
			e.push_back(parse(enter[i]));
		}
		sort(e.begin(), e.end());
		
		int x = parse(lastExit);
		
		double lo = 0, hi = 10000;
		
		for(int i = 0; i < 100; i++) {
			double m = (lo + hi) / 2;
			double free = 0;
			for(int j = 0; j < (int) e.size(); j++) {
				free = max(free, (double)e[j]);
				free += m;
			}
			if(free > x) {
				hi = m;
			}
			else {
				lo = m;
			}
		}
		
		double ret = (lo + hi) / 2;
		if(ret < 5 - 1e-15) return -1;
		return ret;
	}
};

void test(vector<string> enter, string lastExit, double expected) {
	HairCuts h;
	double result = h.maxCut(enter, lastExit);
	cout << (result == expected ? "passed" : "failed") << " => expected: " << expected << ", got: " << result << endl;
}

int main() {
	test({"04:22","09:00"}, "05:52", 90.0);
	test({"09:00", "09:00", "09:00", "09:00", "09:00", "09:00", "09:00", "09:00", "09:37"}, "11:21", 15.666666666666893);
}
