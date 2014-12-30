// http://community.topcoder.com/stat?c=problem_statement&pm=3561&rd=6519
// Problem Name:	 SortEstimate
// Used In:	 SRM 230
// Used As:	 Division I Level One , Division II Level Two
// Categories:	 Math, Search
#include <iostream>
#include <math.h>

using namespace std;

class SortEstimate {
	public:
	// Given time nanoseconds, return the largest double n such that c*n*lg(n) <= time.
	double howMany(int c, int time) {
		
		double lo = 1, hi = 2000000000, n, t;
		while((hi - lo) > 1e-9) {
			n = (lo + hi) / 2;
			
			t = c * n * log(n) / log(2); // lg(n) = ln(n)/ln(2) where ln denotes the natural log.
			
			if(t == time) return n;
			else if(t > time) {
				hi = n;
			}
			else { // t <= time
				lo = n;
			}
		}
		
		return n;
	}
};

int main() {
	SortEstimate s;
	cout << s.howMany(1, 8) << " = " << 4.0 << endl;
	cout << s.howMany(2, 16) << " = " << 4.0 << endl;
	cout << s.howMany(37, 12392342) << " = " << 23104.999312341137 << endl;
	cout << s.howMany(1, 2000000000) << " = " << 7.637495090348122E7 << endl;
}
