// http://community.topcoder.com/stat?c=problem_statement&pm=4823&rd=8074
// Problem Name:	 UnionOfIntervals
// Used In:	 SRM 277
// Used As:	 Division II Level Three
// Categories:	 Search, Sorting
#include <iostream>
#include <vector>

using namespace std;

class UnionOfIntervals {
	public:
	int nthElement(vector<int> lowerBound, vector<int> upperBound, int n) {
		int k = lowerBound.size();
		int i;
		
		long long min = 2000000000, max = -2000000000, mid;
		for(i = 0; i < k; i++) {
			if(lowerBound[i] < min) min = lowerBound[i];
			if(upperBound[i] > max) max = upperBound[i];
		}
		while(min <= max) {
			mid = (min + max) / 2;
			long long t = 0;
			for(i = 0; i < k; i++) {
				if(mid >= lowerBound[i]) {
					if(mid <= upperBound[i]) {
						t = t + mid - lowerBound[i] + 1;
					}
					else {
						t = t + upperBound[i] - lowerBound[i] + 1;
					}
				}
			}
			if(t > n) {
				max = mid - 1;
			}
			else {
				min = mid + 1;
			}
		}
		return min;
	}
};

int main() {
	UnionOfIntervals u;
	cout << u.nthElement({859558895, 85614046, 725716557, 92793907}, {860173933, 85704336, 725836418, 93382737}, 1271767) << endl; // 860031678
}
