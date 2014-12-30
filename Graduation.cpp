// http://community.topcoder.com/stat?c=problem_statement&pm=2852&rd=5075
// Problem Name:	 Graduation
// Used In:	 SRM 200
// Used As:	 Division I Level Three
// Categories:	 Graph Theory
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <queue>
#include <set>

using namespace std;

class Graduation {
	public:
	
	bool bfs(int **graph, int s, int t, int parent[]) {
		int V = t + 1;
		
		bool visited[V];
		memset(visited, 0, sizeof(visited));
		
		queue<int> q;
		q.push(s);
		
		int u;
		
		while(!q.empty()) {
			u = q.front();
			q.pop();
			
			for(int v = 0; v < V; v++) {
				if(graph[u][v] > 0 && !visited[v]) {
					visited[v] = true;
					parent[v] = u;
					q.push(v);
				}
			}
		}
		
		return visited[t];
	}
	
	string moreClasses(string classesTaken, vector<string> requirements) {
		int V = 2; // source and sink nodes
		V = V + requirements.size();
		
		map<char, int> class_capacity;
		// http://stackoverflow.com/questions/1041620/most-efficient-way-to-erase-duplicates-and-sort-a-c-vector
		set<char> reqs;
		vector<string> R = requirements;
		for(size_t i = 0; i < R.size(); i++) {
			for(int j = R[i].size() - 1; j >= 0; j--	) {
				if(!isdigit(R[i][j])) {
					class_capacity[R[i][j]] = (class_capacity.count(R[i][j]) == 0) ? 1 : class_capacity[R[i][j]] + 1;
					reqs.insert(R[i][j]);
					//cout << requirements[i][j] << " " << reqs.size() << endl;
				}
			}
		}
		V = V + reqs.size();
		
		int **graph = new int*[V];
		for(int i = 0; i < V; i++) graph[i] = new int[V];
		
		int u, v;
		// init everything to 0
		for(u = 0; u < V; u++) {
			for(v = 0; v < V; v++) {
				graph[u][v] = 0;
			}
		}
		// source can reach all requirements
		for(size_t i = 0; i < R.size(); i++) {
			graph[0][i+1] = atoi(R[i].c_str());
		}
		// requirements can reach all classes
		int i = 0;
		map<char, int> req_index, index_req;
		for(set<char>::iterator it = reqs.begin(); it != reqs.end(); it++) {
			req_index[*it] = i;
			index_req[i] = *it;
			i++;
		}
		for(size_t i = 0; i < R.size(); i++) {
			for(int j = R[i].size() - 1; j >= 0; j--	) {
				if(!isdigit(R[i][j])) {// && classesTaken.find(R[i][j]) == string::npos) {
					graph[i+1][1+R.size()+req_index[R[i][j]]] = 1;
				}
			}
		}
		// all classes can reach sink
		for(map<char, int>::iterator it = class_capacity.begin(); it != class_capacity.end(); ++it) {
			//cout << it->first << " " << it->second << endl;
			graph[1+requirements.size()+req_index[it->first]][V-1] = it->second;
		}
		
		//cout << V << endl;
		print(graph, V);
		
		//return "";
		int parent[V], s = 0, t = V - 1;
		int path_flow, max_flow = 0;
		set<char> to_take;
		while(bfs(graph, s, t, parent)) {
			path_flow = INT_MAX;
			for(v = t; v != s; v = parent[v]) {
				u = parent[v];
				path_flow = min(path_flow, graph[u][v]);
			}
			max_flow += path_flow;
			for(v = t; v !=s; v = parent[v]) {
				u = parent[v];
				graph[u][v] -= 1;
				graph[v][u] += 1;
			}
			to_take.insert(index_req[parent[t] - 1 - R.size()]);
		}
		
		for(size_t i = 0; i < classesTaken.size(); i++) {
			to_take.erase(classesTaken[i]);
		}
		string classes = "";
		for(set<char>::iterator it = to_take.begin(); it != to_take.end(); it++) {
			classes += *it;
		}
		cout << "MAX: " << max_flow << endl;
		
		return classes;
	}
	
	void print(int **graph, int V) {
		for(int u = 0; u < V; u++) {
			for(int v = 0; v < V; v++) {
				cout << graph[u][v] << " ";
			}
			cout << endl;
		}
	}
};

void test(string c, vector<string> r, string e) {
	Graduation g;
	string m = g.moreClasses(c, r);
	cout << (e.compare(m) == 0 ? "passed" : "failed") << " => expected: " << e << ", got: " << m << endl;
}

int main() {
	test("A", {"2ABC","2CDE"}, "BCD");
	test("+/NAMT", {"3NAMT","2+/","1M"}, "");
	//test("A", {"100%*Klju"}, "0");
	test("", {"5ABCDE","1BCDE,"}, ",ABCDE");
	test("CDH", {"2AP", "3CDEF", "1CDEFH"}, "AEP");
	//test("", {"4ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvw", "8xyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrst", "11uvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnop", "10qrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkl"}, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefg");
}
