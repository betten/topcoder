// http://community.topcoder.com/stat?c=problem_statement&pm=1593&rd=4494
// Problem Name:	 Circuits
// Used In:	 TCCC '03 Semifinals 4
// Used As:	 Division I Level One
// Categories:	 Graph Theory
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct circuit {
	int index;
	vector<circuit*> neighbors;
	vector<int> costs; // costs[i] = cost to get to neighbor i
};

class Circuits {
	public:
	
	int howLong(vector<string> connects, vector<string> costs) {
		vector<circuit> circuits;
		
		for(size_t i = 0; i < costs.size(); i++) {
			circuit c;
			c.index = i;
			circuits.push_back(c);
		}
		
		int n;
		for(size_t i = 0; i < costs.size(); i++) {
			istringstream ssc(costs[i]);
			istringstream ssn(connects[i]);
			
			while(ssc >> n) {
				circuits[i].costs.push_back(n);
			}
			while(ssn >> n) {
				circuits[i].neighbors.push_back(&circuits[n]);
			}
		}
		
		for(size_t i = 0; i < circuits.size(); i++) {
			cout << "circuit: " << circuits[i].index << endl;
			cout << "connects: ";
			for(size_t j = 0; j < circuits[i].neighbors.size(); j++) {
				cout << (*circuits[i].neighbors[j]).index << "(" << circuits[i].costs[j] << ") ";
			}
			cout << endl;
		}
		
		int p, max = -1;
		for(size_t i = 0; i < circuits.size(); i++) {
			p = longestPath(circuits[i], 0);
			if(p > max) max = p;
		}
		
		return max;
	}
	
	int longestPath(circuit &c, int cost) {
		if(c.neighbors.size() < 1) return cost;
		
		int p, max = -1;
		for(size_t i = 0; i < c.neighbors.size(); i++) {
			p = longestPath(*c.neighbors[i], cost + c.costs[i]);
			if(p > max) max = p;
		}
		return max;
	}
};

int main() {
	Circuits c;
	cout << "----" << endl;
	//cout << c.howLong({"1 2", "2", ""}, {"5 3", "7", ""}) << endl; // 12
	cout << c.howLong({"1 2 3 4 5", "2 3 4 5", "3 4 5", "4 5", "5", ""}, {"2 2 2 2 2", "2 2 2 2", "2 2 2", "2 2", "2", ""}) << endl; // 10
	cout << c.howLong({"1","2","3","","5","6","7",""}, {"2","2","2","","3","3","3",""}) << endl; // 9
	cout << c.howLong({"","2 3","3 4 5","4 6","5 6","7","5 7",""}, {"","30 50","19 6 40","12 10","35 23","8","11 20",""}) << endl; // 105
}
