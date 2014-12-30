// http://community.topcoder.com/stat?c=problem_statement&pm=1524&rd=4472
// Problem Name:	 Marketing
// Used In:	 TCCC '03 Round 2
// Used As:	 Division I Level Two
// Categories:	 Graph Theory
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum Consumer { Adult, Teenager };

struct product {
	int index;
	Consumer consumer;
	bool visited = false;
	vector<product*> neighbors;
};

class Marketing {
	public:
	
	long howMany(vector<string> compete) {
		
		int s = compete.size();
		
		vector<product> products;
		for(int i = 0; i < s; i++) {
			product p;
			p.index = i;
			products.push_back(p);
		}
		
		
		//bool competitors[s][s];
		//for(int i = 0; i < s; i++) {
			//for(int j = 0; j < s; j++) {
				//competitors[i][j] = false;
			//}
		//}

		for(int i = 0, j; i < s; i++) {
			istringstream ss(compete[i]);
			while(ss >> j) {
				//competitors[i][j] = true;
				//competitors[j][i] = true;
				
				products[i].neighbors.push_back(&products[j]);
				products[j].neighbors.push_back(&products[i]);
			}
		}
		
		//for(size_t i = 0; i < products.size(); i++) {
			//cout << "product: " << products[i].index << endl;
			//cout << "competitors: ";
			//for(size_t j = 0; j < products[i].neighbors.size(); j++) {
				//if(j != 0) {
					//cout << ", ";
				//}
				//cout << (*products[i].neighbors[j]).index;
			//}
			//cout << endl;
			//cout << "----" << endl;
		//}
		
		///////////////////////////////////////////////////
		
		bool success;
		int ways = 1;
		
		for(size_t i = 0; i < products.size(); i++) {
			if(products[i].visited) continue;
			
			success = DFS(products[i], Adult);
			
			if(success) {
				ways = ways*2;
			} else {
				return -1;
			}
		}
		
		///////////////////////////////////////////////////
		
		// build graph, array, whatever
		// find all ways to traverse all nodes st A.neighbor is not a T node
		
		//for(int i = 0; i < s; i++) {
			//for(int j = 0; j < s; j++) {
				//cout << competitors[i][j];
			//}
			//cout << endl;
		//}
		
		return ways;
	}
	
	bool DFS(product &p, Consumer c) {
		if(p.visited) {
			if(p.consumer != c) {
				return false;
			}
			return true;
		}
		
		p.visited = true;
		p.consumer = c;
		
		Consumer opposite = (c == Adult) ? Teenager : Adult;
		
		for(size_t i = 0; i < p.neighbors.size(); i++) {
			if(!DFS(*p.neighbors[i], opposite)) return false;
		}
		
		return true;
	}
};

int main() {
	Marketing m;
	cout << m.howMany({"1 4","2","3","0",""}) << endl; // 2
	cout << m.howMany({"1","2","0"}) << endl; // -1
	cout << m.howMany({"1","2","3","0","0 5","1"}) << endl; // 2
	cout << m.howMany({"","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""}) << endl; // 1073741824
	cout << m.howMany({"1","2","3","0","5","6","4"}) << endl; // -1
	cout << m.howMany({"1 2 3 4", "", "", "", "", "1 15", "2 15", "3 15", "4 15", "10", "11", "12", "13", "14", "9", ""}) << endl; // 4
	cout << m.howMany({"1 2 4", "5 3", "3 6", "7", "5 6", "7", "7", "", "", "", "11 12 14", "15 13", "13 16", "17", "15 16", "17", "17", "", "", "", "", "", "", "", ""}) << endl; // 2048
}
