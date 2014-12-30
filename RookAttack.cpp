// http://community.topcoder.com/stat?c=problem_statement&pm=1931&rd=4709
// Problem Name:	 RookAttack
// Used In:	 TCO '03 Semifinals 4
// Used As:	 Division I Level Three
// Categories:	 Graph Theory
// http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=maxFlow2
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <limits.h>
#include <queue>

using namespace std;

//class RookAttack {
	//public:
	//vector<int> lst[300];
	//int row_match[300], col_match[300];
	//bool visited_DFS[300];
	
	//bool find_match_DFS(int row) {
		//if(row == -1) return true;
		//for(size_t i = 0; i < lst[row].size(); i++) {
			//int col = lst[row][i];
			//if(!visited_DFS[col]) {
				//visited_DFS[col] = true;
				//if(find_match_DFS(col_match[col])) {
					//col_match[col] = row;
					//return true;
				//}
			//}
		//}
		//return false;
	//}
	
	//bool find_match_BFS(int source) {
		//int visited[300], row, col;
		//memset(visited, -1, sizeof(visited));
		//visited[source] = source;
		//deque<int> q;
		//q.push_back(source);
		//bool found_path = false;
		//while(!found_path && !q.empty()) {
			//row = q.front(); q.pop_front();
			//for(size_t i = 0; i < lst[row].size(); i++) {
				//col = lst[row][i];
				//int next = col_match[col];
				//if(row != next) {
					//if(next == -1) {
						//found_path = true;
						//break;
					//}
					//if(visited[next] == -1) {
						//q.push_back(next);
						//visited[next] = row;
					//}
				//}
			//}
		//}
		//if(!found_path) return false;
		//while(visited[row] != row) {
			//int aux = row_match[row];
			//row_match[row] = col;
			//col_match[col] = row;
			//row = visited[row];
			//col = aux;
		//}
		//row_match[row] = col;
		//col_match[col] = row;
		//return true;
	//}
	
	//int howMany(int rows, int cols, vector<string> cutouts) {
		//int r, c;
		//for(vector<string>::iterator it = cutouts.begin(); it != cutouts.end(); it++) {
			//stringstream ss(*it);
			//ss >> r >> c;
			//lst[r].push_back(c);
		//}
		//memset(row_match, -1, sizeof(row_match));
		//memset(col_match, -1, sizeof(col_match));
		
		//int ret = 0;
		//for(int i = 0; i < rows; ++i) {
			//ret += find_match_DFS(i);
		//}
		//return ret;
	//}
//};

class RookAttack {
	public:
	
	bool bfs(int **graph, int s, int t, int parent[]) {
		int V = t + 1;
		bool visited[V];
		memset(visited, 0, sizeof(visited));
		queue<int> q;
		int u, v;
		
		q.push(s);
		visited[s] = true;
		
		while(!q.empty()) {
			u = q.front();
			q.pop();
			
			for(v = 0; v < V; v++) {
				if(!visited[v] && graph[u][v] > 0) {
					q.push(v);
					visited[v] = true;
					parent[v] = u;
				}
			}
		}
		
		return visited[t];
	}
	
	void print(int **graph, int V) {
		for(int u = 0; u < V; u++) {
			for(int v = 0; v < V; v++) {
				cout << graph[u][v] << " ";
			}
			cout << endl;
		}
	}
	
	int howMany(int rows, int cols, vector<string> cutouts) {
		int V = rows + cols + 2;
		// http://www.dreamincode.net/forums/topic/144007-multidimensional-arrays/
		int **graph = new int*[V];
		for(int i = 0; i < V; i++) graph[i] = new int[V];
		int u, v;

		// init everything to 0
		for(v = 0; v < V; v++) {
			for(u = 0; u < V; u++) {
				graph[u][v] = 0;
			}
		}
		// source can reach all row nodes, capacity 1
		for(v = 1; v < rows + 1; v++) {
			graph[0][v] = 1;
		}
		// all row nodes can all column nodes, capacity 1
		for(u = 1; u < rows + 1; u++) {
			for(v = rows + 1; v < V - 1; v++) {
				graph[u][v] = 1;
			}
		}
		// all column nodes can reach sink, capacity 1
		for(u = rows + 1; u < V - 1; u++) {
			graph[u][V-1] = 1;
		}
		
		string coords;
		for(size_t i = 0; i < cutouts.size(); i++) {
			istringstream ss(cutouts[i]);
			// http://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings
			while(getline(ss, coords, ',')) {
				istringstream css(coords);
				css >> u >> v;
				graph[u+1][rows+1+v] = 0;
			}
		}
		
		int parent[V];
		int s = 0, t = V - 1;
		int max_flow = 0;
		while(bfs(graph, s, t, parent)) {
			int path_flow = INT_MAX;
			for(v = t; v != s; v = parent[v]) {
				u = parent[v];
				path_flow = min(path_flow, graph[u][v]);
			}
			max_flow += path_flow;
			for(v = t; v != s; v = parent[v]) {
				u = parent[v];
				graph[u][v] -= path_flow;
				graph[v][u] += path_flow;
			}
		}
		
		return max_flow;
	}
};

int main() {
	RookAttack r;
	//cout << r.howMany(8, 8, {}) << endl; // 8
	//cout << r.howMany(3, 3, {"0 0","1 0","1 1","2 0","2 1","2 2"}) << endl; // 2
	//cout << r.howMany(3, 3, {"0 0","1 2","2 2"}) << endl; // 3
	//cout << r.howMany(200, 200, {}) << endl; // 200
	//cout << r.howMany(2, 2, {"0 0","0 1","1 1","1 0"}) << endl; // 0
	//cout << r.howMany(6, 6, {"0 0", "0 2", "0 4", "1 1", "1 3", "1 5", "2 0", "2 2", "2 4", "3 1", "3 3", "3 5", "4 0", "4 2", "4 4", "5 1", "5 3", "5 5", "2 0", "2 2", "2 4"}) << endl; // 6
	cout << r.howMany(15, 25, {"0 14,14 19,11 23,4 22,13 4,9 11,9 14,4 19,12 19", "11 23,11 16,4 21,1 16,0 15,5 2,1 23,8 15,0 17,3 11", "2 24,2 9,9 0,13 13,2 16,1 1,11 12,9 1,3 23,12 0", "3 22,5 2,10 9,3 9,11 1,9 16,14 20,4 15,5 14,3 9", "13 19,2 12,14 21,5 8,10 17,8 20,8 24,8 3,11 24", "0 15,9 12,9 15,7 5,1 7,4 15,13 19,13 14,8 19,2 17", "3 16,12 24,9 9,9 13,12 14,3 4,2 8,2 21,10 16,1 24", "3 11,3 0,11 22,11 3,6 9,10 18,12 4,12 23,11 22", "11 23,4 18,13 21,8 0,14 9,9 23,9 21,1 9,5 3,8 12", "2 5,7 1,12 21,12 0,8 24,9 13,1 1,14 16,6 21,2 11", "14 6,13 14,7 15,14 13,6 12,14 12,4 12,1 4,8 2,3 24", "14 7,5 9,4 12,8 20,2 20,7 19,0 20,13 22,5 6,0 4", "0 0,2 2,8 18,7 10,2 12,9 0,1 10,6 6,13 15,9 24,2 7", "3 21,5 10,3 11,2 13,6 10,6 13,4 10,8 10,10 11", "10 17,10 3,12 18,11 11,4 14,12 16,5 20,1 11,8 16", "7 15,8 13,6 3,13 12,2 11,3 0,7 3,5 17,7 8,3 21", "5 10,14 13,5 12,12 0,7 12,13 16,3 7,7 14,13 21", "7 16,9 10,3 3,8 10,14 1,4 17,4 2,2 22,5 20,10 6", "5 24,9 6,3 4,0 0,0 10,4 5,1 5,13 16,2 21,3 24,1 13", "11 17,1 5,14 5,2 1,12 4,12 14,3 16,12 10,12 21", "3 7,3 1,2 14,12 15,9 0,7 1,6 12,10 1,13 18,7 18", "11 18,9 15,9 16,14 7,6 0,1 1,4 16,12 24,9 9,11 7", "6 23,7 4,5 20,11 8,7 17,4 8,13 21,1 18,13 4,6 7", "3 9,12 14,13 11,12 2,12 6,2 8,10 9,4 24,8 12,3 20", "13 3,5 13,12 1,2 10,11 20,11 2,13 1,12 18,4 18", "8 7,13 22,4 2,10 18,4 10,7 22,3 24,2 19,6 21,9 20", "6 6,6 11,2 21,2 3,10 10,0 21,7 7,12 3,1 16,14 10", "3 9,3 23,6 17,1 22,3 19,10 20,5 10,1 7,13 4,4 19", "6 12,2 9,6 13,10 12,3 12,14 13,3 13,2 15,8 18,5 14", "3 3,10 24,12 8,13 8,4 5,2 4,0 21,10 22,6 7,7 1,5 7", "12 18,5 24,7 14,5 19,12 3,14 2,3 13,9 23,10 9,3 7", "2 15,13 2,5 4,14 16,2 13,4 15,13 2,13 24,4 12", "14 2,0 1,12 3,11 13,2 23,14 8,6 3,5 12,3 0,8 6", "13 0,0 21,6 1,2 18,1 16,6 23,14 6,0 16,11 9,1 10", "0 24,2 13,12 4,3 14,5 17,8 13,4 0,5 18,2 7,2 2", "7 21,3 9,9 2,11 17,2 15,13 10,4 3,13 20,8 1,0 11", "9 4,6 18,0 23,3 12,12 24,2 19,12 13,3 10,12 17,4 2", "4 11,6 22,6 14,9 18,14 18,2 4,2 24,1 21,7 3,5 16", "2 6,6 9,5 11,8 15,12 8,6 22,13 1,5 6,2 4,7 3,6 11", "11 16,7 17,9 8,10 9,12 24,14 16,8 24,8 19,14 14", "11 6,1 6,4 2,11 14,10 19,10 6,9 9,2 19,5 10,14 19", "14 5,13 17,2 6,8 0,9 21,5 4,3 5,5 19,0 15,12 2", "10 22,2 23,5 17,10 13,6 14,1 19,2 0,14 8,13 18", "2 11,7 13,9 10,6 7,10 23,5 12,1 16,5 20,9 7,3 17", "0 2,5 2,5 21,2 9,2 24,10 10,10 7,11 2,1 20,12 17", "11 5,8 14,11 2,13 23,1 1,11 1,12 2,12 11,8 11,2 12", "7 0,7 4,5 9,7 10,4 5,7 17,7 18,12 4,14 8,2 8,9 5", "6 23,3 3,11 22,9 3,2 2,9 19,4 9,7 21,8 16,2 1", "2 14,0 21,11 17,2 15,3 15,3 22,1 12,3 13,3 0,6 0", "2 17,12 10,7 17,7 12,7 3,10 7,14 21,8 18,9 16,2 24"}) << endl; // 14
	cout << r.howMany(15, 17, {"13 7,13 5,14 13,5 0,9 3,4 7,14 9,9 3,14 14,10 16", "0 15,7 1,4 9,7 0,10 15,4 8,7 7,2 0,6 2,5 10,11 12", "5 5,13 1,11 14,13 13,5 4,5 5,0 12,3 4,2 3,2 7,3 12", "6 12,8 7,9 2,9 12,1 3,5 0,8 7,9 16,6 8,4 8,8 13", "4 6,3 7,14 3,1 4,6 10,11 4,14 8,7 1,9 0,13 15,5 1", "2 4,7 0,3 7,9 1,8 13,7 14,3 13,4 7,6 2,8 3,11 7", "2 9,8 5,8 8,1 9,2 7,12 12,12 9,4 13,9 7,1 6,13 4", "0 3,1 4,5 9,13 0,0 5,1 12,12 13,13 8,8 6,4 5,13 13", "11 14,13 1,4 8,3 5,14 8,1 9,0 12,7 0,6 12,2 7,13 0", "9 2,3 8,6 9,14 3,12 8,9 12,6 2,1 11,10 16,10 7,8 9", "8 0,2 16,6 13,9 10,6 5,1 8,1 1,2 1,10 12,13 11", "9 6,1 14,12 13,11 4,8 13,1 12,13 6,2 12,13 7,9 10", "0 2,5 14,9 10,2 14,8 6,11 7,8 5,12 12,8 12,12 8", "12 3,0 5,14 4,12 9,6 13,10 5,3 1,14 1,11 9,12 4", "3 3,5 9,6 13,5 11,5 0,7 1,5 9,5 14,13 4,3 3,4 4", "3 9,8 4,9 8,9 9,8 14,3 15,7 11,12 2,13 2,13 5,4 0", "10 10,0 1,12 11,9 4,3 6,14 5,1 16,5 12,4 12,11 4", "8 4,12 2,11 4,2 10,7 7,13 10,13 8,4 16,11 7,10 5", "12 6,2 10,3 12,8 6,0 4,1 14,12 7,3 16,9 9,2 9,5 4", "1 9,7 16,13 1,12 13,1 8,13 5,8 0,1 7,6 10,5 15", "8 3,10 16,13 6,3 3,2 8,0 6,12 10,9 5,7 4,13 8", "12 0,13 1,2 4,10 1,5 11,10 12,3 5,5 9,14 15,10 5", "2 5,7 16,4 14,7 2,5 1,1 12,12 15,2 1,1 14,12 6", "8 6,6 2,14 3,1 13,1 7,1 15,6 12,11 11,5 6,11 3,6 3", "2 3,5 7,14 10,6 8,3 5,7 6,0 14,5 8,3 16,3 10,4 7", "0 10,7 12,0 4,8 0,5 1,12 8,14 11,2 7,3 1,5 14,8 7", "3 13,10 9,0 8,7 5,5 7,10 2,14 13,1 4,13 3,14 12", "12 8,8 0,9 9,2 7,6 13,13 0,5 10,12 13,8 11,4 2", "9 10,5 2,3 12,12 13,10 15,8 3,8 11,7 8,14 14,12 3", "10 6,7 3,10 4,1 15,12 7,0 7,6 10,8 11,2 9,9 2,4 15", "9 9,4 10,1 0,9 4,9 12,6 5,7 5,1 13,9 3,3 3,9 10", "1 8,3 8,11 5,2 12,3 5,8 10,3 8,5 15,13 16,4 9,4 3", "11 10,6 8,13 9,13 2,13 5,0 1,7 16,6 14,8 5,6 14", "11 8,3 4,10 0,5 13,1 14,12 3,3 9,14 5,6 13,0 3", "8 12,6 10,6 15,4 11,10 13,10 13,10 1,1 7,10 0,7 1", "6 15,1 10,4 16,12 11,14 16,9 6,7 12,4 6,0 13,0 9", "12 0,1 5,7 13,5 15,2 14,5 3,9 15,2 6,10 3,6 2,3 9", "6 11,8 11,14 9,10 10,9 15,1 8,5 15,4 15,3 2,8 16", "6 3,0 12,8 1,12 4,1 8,1 1,10 2,6 14,10 0,4 2,8 15", "11 7,6 6,5 4,0 0,7 11,8 0,1 5,2 1,13 11,4 1,8 9", "3 9,11 4,9 3,6 9,2 11,5 14,1 16,9 10,12 6,7 6,6 6", "12 2,0 16,8 7,9 13,11 3,13 11,12 8,10 8,9 11,1 10", "5 8,13 7,14 6,9 12,2 1,8 14,11 14,13 9,10 0,4 2", "12 5,14 11,5 16,7 12,8 3,8 11,7 2,5 7,3 11,8 10", "7 0,13 13,13 3,14 11,5 12,0 11,12 7,3 5,9 8,9 0", "5 11,11 16,14 15,7 7,11 10,0 5,12 14,0 13,11 16", "13 12,13 1,4 11,12 3,2 9,8 11,2 4,14 4,1 0,7 5", "1 16,11 11,13 15,7 3,11 15,7 8,8 10,2 8,5 2,11 12", "2 6,8 2,7 3,11 15,13 5,3 10,4 7,3 7,13 4,9 16,11 8", "1 16,1 5,7 9,9 13,1 4,14 9,7 11,6 11,8 2,8 8,2 12"}) << endl; // 10
}
