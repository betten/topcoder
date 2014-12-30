// http://community.topcoder.com/stat?c=problem_statement&pm=2427&rd=4765
// Problem Name:	 Mortgage
// Used In:	 SRM 189
// Used As:	 Division II Level Three
// Categories:	 Math, Search
#include <iostream>
#include <math.h>

using namespace std;

class Mortage {
	public:
	
	int monthlyPayment(int loan, int interest, int term) {
		long long int lo = 1, hi = loan;
		double n, p;
		
		int mos = term * 12;
		float x = 1 + (double)interest/10/12/100;
		cout << x << endl;
		
		while(lo < hi) {
			p = (lo + hi) / 2;
			n = loan;
			for(int i = 0; i < mos; i++) {
				n = n - p;
				//cout << n << endl;
				//cin.get();
				if(n <= 0) break;
				n = ceil(n * x);
				if(n <= 0) break;
			}
			if(n == 0) return p;
			if(n > 0) {
				lo = p + 1;
			}
			else {
				hi = p;
			}
			//cout << n << " " << p << " // " << hi << " " << lo << endl;
			//cin.get();
		}
		return hi;
	}
};

class Mortage2 {  
	public:  
	int ok(double loan, double inter1, long sl, long long tg) { 
		for(int i=0; i< sl; i++) { 
			if (loan<=0) return 1; 
			loan = loan - tg; 
			if (loan<=0) return 1; 
			loan = ceil(loan* (1 + inter1/12/100)) ; 
		} 
		return 0; 
	} 

	int monthlyPayment(int loan, int inter, int term)  
	{  
		long long l=1, r= loan, tg; 
		double inter1 = (double)inter/10; 
		double p = loan;
		while(l<r) { 
			tg = (l+r)/2; 
			p = loan;
			for(int i=0; i< term*12; i++) { 
				if (p<=0) break; 
				p = p - tg; 
				if (p<=0) break; 
				p = ceil(p* (1 + inter1/12/100)) ;
				
				//cout << p << " " << tg << " // " << r << " " << l << endl;
				//cin.get(); 
			} 
			//if (!ok(loan, inter1, term*12, tg))l =tg+1; else r=tg; 
			if(p <= 0) {
				r = tg;
			} else {
				l = tg +1;
			}
		} 
		return l; 
	}
}; 

void test(int loan, int interest, int term, int result) {
	Mortage m;
	int p = m.monthlyPayment(loan, interest, term);
	cout << (p == result ? "passed" : "failed") << " => expected: " << result << ", got: " << p << endl;
}

int main() {
	//test(1000, 50, 1, 86);
	//test(2000000000, 6000, 1, 671844808);
	test(1000000, 1000000, 1000, 988143);
	test(1000000, 129, 30, 10868);
	test(1999999999, 1000000, 1, 1976284585);

}
