// http://community.topcoder.com/stat?c=problem_statement&pm=11894
// Problem Name:	 SwitchesAndLamps
// Used In:	 TCO12 Round 2A
// Used As:	 Division I Level One
// Categories:	 Math, Simple Search, Iteration

#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
#include <map>

using namespace std;

#define VS vector<string>
#define f(i, k, n) for(int i = k; i < n; i++)
#define BR cout << "----" << endl;

//class SwitchesAndLamps {
	//public:
	//void print(int **graph, int N) {
		//f(i, 0, N) {
			//f(j, 0, N) {
				//cout << graph[i][j] << " ";
			//}
			//cout << endl;
		//}
	//}
	
	//int theMin(VS switches, VS lamps) {
		//int min = INT_MAX;
		
		//int N = switches[0].size();
		//int **graph = new int*[N];
		//f(i, 0, N) graph[i] = new int[N];
		//f(i, 0, N) {
			//f(j, 0, N) {
				//graph[i][j] = 1;
			//}
		//}
		
		//f(i, 0, (int)switches.size()) {
			//f(j, 0, N) {
				//f(k, 0, N) {
					//if(graph[j][k] != 0) graph[j][k] = (switches[i][j] == lamps[i][k]);
				//}
			//}
		//}
		
		//print(graph, N);		
		
		//return min;
	//}
//};

#define fitsi(it, m) for(map<string, int>::iterator it = m.begin(); it != m.end(); it++) // for iterator string int = fitsi

template<class T> void chmax(T &t, T f) { if (t < f) t = f; }

struct SwitchesAndLamps { 
   
  int theMin(vector <string> A, vector <string> B) { 
    int M = A.size(), N = A[0].size(); 
    int i, j; 
     
    map<string,int> as, bs; 
    for (j = 0; j < N; ++j) { 
      string s = ""; 
      for (i = 0; i < M; ++i) { 
		  s += A[i][j];
	  }
      ++as[s]; 
    } 
    for (j = 0; j < N; ++j) { 
      string s = ""; 
      for (i = 0; i < M; ++i) s += B[i][j]; 
      ++bs[s]; 
    }
    
    BR
    
    fitsi(it, as) {
		cout << it->first << " => " << it->second << endl;
	}
	
	BR
	
	fitsi(it, bs) {
		cout << it->first << " => " << it->second << endl;
	}
     
    int dai = 0; 
     
    for (map<string,int>::iterator it = as.begin(), en = as.end(); it != en; ++it) { 
      string s = it->first; 
      if (!(bs.count(s) && as[s] == bs[s])) { 
        return -1; 
      }
      cout << dai << " " << it->second << endl;
      chmax(dai, it->second); 
      cout << dai << " " << it->second << endl;
      //cin.get();
    } 
cout<<"dai = "<<dai<<endl; 
     
    int k; 
    for (k = 0; 1 << k < dai; ++k) {
		cout << k << " " << dai << endl;
		cout << (1 << k) << endl;
	}
    return k; 
     
  } 
   
};

void test(VS switches, VS lamps, int expected) {
	SwitchesAndLamps s;
	int result = s.theMin(switches, lamps);
	cout << ((result == expected) ? "passed" : "failed") << " => expected: " << expected << ", got: " << result << endl;
}

int main() {
	//test({"NYNN", "NNYN"}, {"NNNY", "NNYN"}, 1);
	//test({"YYNNN", "NNYYN"}, {"NYNNY", "NNNYY"}, -1);
	test({"YNNYNNNNNNNNNNN", "NYYYYYNYYYYYNNY", "YYYNYNNNNYNNNNN", "NYYNYNNNNYNNNNN", "NYYYYNYNNYNNYYN", "NNNNNNYNNYNNYYN", "NYYNYNNNNNNNNNN", "NNNNNNYNNNNNYYN", "YYYNYYYYYNYYYYY", "NNNNNYNYYYYYNNY", "YNNYNNNNNNNNNNN", "YNNYNYYYYYYYYYY", "NYYNYNNNNNNNNNN", "YYYYYYYYYNYYYYY", "YNNNNYYYYYYYYYY", "NYYNYYYYYNYYYYY", "YYYNYYNYYNYYNNY", "NYYYYNNNNNNNNNN", "YYYNYNYNNYNNYYN"}, {"NNNNYNNNNNNYNNN", "NYYYYYYYNYYNNYY", "NNNYNNYNNYNYNYN", "NNNYNNYNNYNNNYN", "YNNYYNYNYYNNYYN", "YNNNNNYNYNNNYNN", "NNNYNNNNNYNNNYN", "YNNNNNNNYNNNYNN", "YYYYNYNYYYYYYYY", "NYYNNYYYNNYNNNY", "NNNNYNNNNNNYNNN", "YYYNYYYYYNYYYNY", "NNNYNNNNNYNNNYN", "YYYYYYNYYYYYYYY", "YYYNNYYYYNYYYNY", "YYYYNYNYYYYNYYY", "NYYYNYNYNYYYNYY", "NNNYYNNNNYNNNYN", "YNNYNNYNYYNYYYN"}, 3);
}
