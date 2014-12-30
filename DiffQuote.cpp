// TUM, Advanced Programming, Worksheet 4 Assignment 2
#include <iostream>
#include <cmath>

#define PI 3.1415926

using namespace std;

double my_func(double param) {
	return (180.0 / PI) * sin(param * PI / 180);
}

double differenceQuotient(double (*f)(double), double x_0, double h = 1e-8) {
	double d_f, x_1;
	
	x_1 = x_0 + h;
	d_f = (f(x_1) - f(x_0)) / h;
	return d_f;
}

int main(int argc, char **argv) {
	double param, d_f;
	cout<<"please input parameter you want to calculate in the function"<<endl;
    cin>> param;
//    foo = my_func;
 
    d_f = differenceQuotient(&my_func, param);
    
    cout<<"Difference Quotient is: "<< d_f <<endl; 
    
    int a;
    auto func = [&]() { cout << "hello world" << endl; a = 5; };
    func();     
    cout << a << endl;
    
    return 0;
}
