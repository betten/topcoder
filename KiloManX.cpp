// http://community.topcoder.com/stat?c=problem_statement&pm=2288&rd=4725
// Problem Name:	 KiloManX
// Used In:	 SRM 181
// Used As:	 Division I Level Three
// Categories:	 Dynamic Programming
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>
#include <queue>

using namespace std;

//struct Boss {
	//int index;
	//int shots;
	//int health;
	//bool visited;
//};

//class KiloManX {
	//public:
	
	//int leastShots(vector<string> damageChart, vector<int> bossHealth) {
		//int n = damageChart.size();
		//int shotsNeeded[n][n];
		//for(int i = 0; i < n; i++) {
			//for(int j = 0; j < n; j++) {
				//shotsNeeded[i][j] = (i == j || damageChart[i][j] == '0') ? bossHealth[j] : ceil((float)bossHealth[j] / (float)(damageChart[i].at(j) - '0'));
				//cout << shotsNeeded[i][j] << " ";
			//}
			//cout << endl;
		//}
		//vector<bool> visited(n, false);
		//vector<Boss> bosses;
		//for(int i = 0; i < n; i++) {
			//bosses.push_back({ i, 0, bossHealth[i], false });
		//}
		
		//return 0;
	//}
//};

struct node {
	int weapons;
	int shots;
};
class CompareNode {
	public:
	bool operator()(node &n1, node &n2) {
		return (n1.shots > n2.shots);
	}
};

class KiloManX {
	public:
	
	bool visited[32768];
	
	int leastShots(vector<string> damageChart, vector<int> bossHealth) {
		priority_queue<node, vector<node>, CompareNode> q;
		q.push({ 0, 0 });
		
		int numWeapons = damageChart.size();
		
		while(!q.empty()) {
			node top = q.top();
			q.pop();
			
			if(visited[top.weapons]) continue;
			visited[top.weapons] = true;
			cout << top.weapons << " / " << numWeapons << endl;
			cin.get();
			
			
			if(top.weapons == (1 << numWeapons) - 1) return top.shots;
			
			for(int i = 0; i < numWeapons; i++) {
				if((top.weapons >> i) & 1) continue;
				
				int best = bossHealth[i];
				for(int j = 0; j < numWeapons; j++) {
					if(i == j) continue;
					
					if (((top.weapons >> j) & 1) && damageChart[j][i] != '0') {
						int shotsNeeded = bossHealth[i] / (damageChart[j][i] - '0');
						if (bossHealth[i] % (damageChart[j][i] - '0') != 0) shotsNeeded++;
						best = min(best, shotsNeeded);
					}
				}

				// Add the new node to be searched, showing that we defeated boss i, and we used 'best' shots to defeat him.
				q.push({ top.weapons | (1 << i), top.shots + best });
			}
		}
		
		return 0;
	}
};

int main() {
	KiloManX k;
	//cout << "least shots: " << k.leastShots({"070","500","140"}, {150,150,150}) << endl; // 218
	//cout << "least shots: " << k.leastShots({"1542", "7935", "1139", "8882"}, {150,150,150,150}) << endl; // 205
	cout << "least shots: " << k.leastShots({"07", "40"}, {150,10}) << endl; // 48
}
