// http://community.topcoder.com/stat?c=problem_statement&pm=3970&rd=7993
// Problem Name:	 AutoLoan
// Used In:	 SRM 258
// Used As:	 Division I Level One , Division II Level Two
// Categories:	 Advanced Math, Search
#include <iostream>

using namespace std;

class AutoLoan {
	public:
	double interestRate(double price, double monthlyPayment, int loanTerm) {
		double balance;
		
		double lo = 0.0, hi = 1.0, r = 1.0;
		
		while((hi - lo) > 0.00000001) {
			r = (hi + lo) / 2;
			balance = price;
			
			for(int i = 0; i < loanTerm; i++) {
				balance = balance - monthlyPayment + balance * r; 
			}
			
			cout << r << " " << balance << " " << (hi + lo) << endl;
			//cin.get();
			
			if(balance == 0) {
				return r * 100 * 12;
			}
			else if(balance > 0) {
				hi = r;
			}
			else { // balance <= 0
				lo = r;
			}
			
		}
		
		return r * 100 * 12;
	}
};

int main() {
	AutoLoan a;
	//cout << a.interestRate(2000, 510, 4) << endl; // 9.56205462458368
	//cout << a.interestRate(6800, 100, 68) << endl; // 1.3322616182218813E-13
	//cout << a.interestRate(15000, 364, 48) << endl; // 7.687856394581649
	//cout << a.interestRate(5628.0, 2197.0, 3) << endl; // 100.00000000000003
	cout << a.interestRate(1000.0, 40.0, 34) << endl; // 22.418392731637795		
}
