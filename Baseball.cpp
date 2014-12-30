// http://coursera.cs.princeton.edu/algs4/assignments/baseball.html
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class BaseballElimination {
	int numTeams;
	vector<string> schedule;
	vector<string> standings;
	string *t;
	int *w;
	int *l;
	int *r;
	int **graph;
	
	public:
	
	BaseballElimination(vector<string>, vector<string>);// create a baseball division from given filename in format specified below
	~BaseballElimination();
	int numberOfTeams(); 								// number of teams
	vector<string> teams(); 							// all teams
	int wins(string); 									// number of wins for given team
	int losses(string); 								// number of losses for given team
	int remaining(string); 								// number of remaining games for given team
	int against(string, string); 						// number of remaining games between team1 and team2
	bool isEliminated(string); 							// is given team eliminated?
	vector<string> certificateOfElimination(string); 	// subset R of teams that eliminates given team; null if not eliminated
};

BaseballElimination::BaseballElimination(vector<string> standarg, vector<string> schedarg) {
	schedule = schedarg;
	standings = standarg;
	numTeams = standings.size();
	
	t = new string[numTeams];
	w = new int[numTeams];
	l = new int[numTeams];
	r = new int[numTeams];
	
	stringstream ss;
	for(int i = 0; i < numTeams; i++) {
		ss << standings[i];
		ss >> t[i] >> w[i] >> l[i] >> r[i];
	}
	for(int i = 0; i < numTeams; i++) {
		for(int j = i+1; j < numTeams; j++) {
			cout << i << "-" << j << endl;
		}
	}
	graph = new int*[numTeams];
	for(int i = 0; i < numTeams; i++) {
		graph[i] = new int[numTeams];
	}
}
BaseballElimination::~BaseballElimination() {
	delete[] t;
	delete[] w;
	delete[] l;
	delete[] r;
}
int BaseballElimination::numberOfTeams() {
	return 0;
}
vector<string> BaseballElimination::teams() {
	return {};
}
int BaseballElimination::wins(string team) {
	return 0;
}
int BaseballElimination::losses(string team) {
	return 0;
}
int BaseballElimination::remaining(string team) {
	return 0;
}
int BaseballElimination::against(string team1, string team2) {
	return 0;
}
bool BaseballElimination::isEliminated(string team) {
	return false;
}
vector<string> BaseballElimination::certificateOfElimination(string team) {
	return {};
}


int main(int argv, char** argc) {
	BaseballElimination b = { 
		{
			"Atlanta 		83 71 8",
			"Philadelphia 	80 79 3",
			"New_York 		78 78 6",
			"Montreal 		77 82 3"
		},
		{
			"0 1 6 1",
			"1 0 0 2",
			"6 0 0 0",
			"1 2 0 0"
		}
	};
	b.numberOfTeams();
	return 0;
}
