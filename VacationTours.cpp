// http://community.topcoder.com/tc?module=ProblemDetail&rd=14279&pm=10897
// Problem Name:	 VacationTours
// Used In:	 TCO10 Round 1
// Used As:	 Division I Level Three
// Categories:	 Graph Theory

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T> inline void checkmax(T &a, T b) { if(b > a) a = b; }

class VacationTours {	
	public:
	
	int getNum(char c) {
		if((c - 'A') >= 0 && (c - 'A') <= 25) {
			return (c - 'A');
		}
		if((c - 'a') >= 0 && (c - 'a') <= 25) {
			return (c - 'a') + 26;
		}
		if((c - '0') >= 0 && (c - '0') <= 9) {
			return (c - '0') + 52;
		}
		if(c == '+') return 62;
		if(c == '/') return 63;
		return 0;
	}
	
	int getIncome(vector<string> c, vector<string> d, int fee) {
		int is = c.size();
		int js = c[0].size();
		
		int **costGraph = new int*[is];
		for(int i = 0; i < is; i++) {
			costGraph[i] = new int[js];
		}
		
		for(int i = 0; i < is; i++) {
			for(int j = 0; j < js; j++) {
				costGraph[i][j] = getNum(c[i][j])*64 + getNum(d[i][j]);
			}
		}
		
		for(int i = 0; i < is; i++) {
			for(int j = 0; j < js; j++) {
				cout << costGraph[i][j] << " ";
			}
			cout << endl;
		}
		
		for(int i = 0; i < is; i++) {
			delete[] costGraph[i];
		}
		delete[] costGraph;
		
		return 0;
	}
};

int main(int argv, char **argc) {
	VacationTours v;
	v.getIncome({"AAA", "AAA", "AAA"}, {"ABJ", "JAB", "BJA"}, 15);
	v.getIncome({"AAAA", "AAAA", "AAAA", "AAAA"}, {"AAAA", "AAAA", "AAAA", "AAAA"}, 100);
	v.getIncome({"A//", "/A/", "//A"}, {"A//", "/A/", "//A"}, 1000);
	return 0;
}
