#include <iostream>

using namespace std;

#define C(x) cout << x << endl

int gcd(int a, int b);
int gcdr(int a, int b);

int gcd(int a, int b) {
	int c;
	while(a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

class Animal {
	public:
	string says() {
		return "?";
	}
};

class Dog : public Animal {
	public:
	string says() {
		return "woof";
	}
};

int gcdr(int a, int b) {
	if(a == 0) return b;
	return gcdr(b%a, a);
}

namespace waka {
void bar() {
	C("hi");
}
}

void foo(void (*fn)()) {
	fn();
}

class Calc {
	int val;
	public:
	Calc(int v) : val(v) {}
	Calc& add(int v) {
		this->val += v;
		return *this;
	}
	Calc& subtract(int v) {
		this->val -= v;
		return *this;
	}
	int getVal() const {
		return this->val;
	}
	Calc operator+ (const Calc& c) {
		int sum = this->getVal() + c.getVal();
		return Calc(sum);
	}
};

template <class T> 
class Waka {
	T w;
	public:
	static int x;
	Waka(int v) : w(v) { x = 20; }
	void foo(T, T);
	Waka<T> operator + (const T&);
};
template <class T>
int Waka<T>::x;

template <class T>
void Waka<T>::foo(T a, T b) {
}
template <class T>
Waka<T> Waka<T>::operator + (const T& t) {
	return *this;
}

class M {
	int val;
	public:
	M() : val(0) {}
	M(int x) : val(x) {}
	M operator+(const M &);
	const int & getVal() const {
		return val;
	}
	friend std::ostream & operator<<(std::ostream &out, const M &m) {
		out << "m = " << m.getVal();
		return out;
	}
};
M M::operator+(const M &m) {
	return M(getVal() + m.getVal());
}

class C {
	public:
	int a, b; string c;
	friend std::ostream& operator<<(std::ostream &out, const C &obj) {
		out << "a => " << obj.a << " b => " << obj.b << " c => " << obj.c;
		return out;
	}
};

#ifndef H_POLY
#define H_POLY

class Polygon {
	static int ID;
	int id;
	protected:
	int width, height;
	public:
	Polygon() { id = ID++; }
	void set_values(int a, int b) {
		width = a;
		height = b;
	}
	int getId() const {
		return id;
	}
	virtual int area() const {
		return 0;
	}
	friend std::ostream& operator<<(std::ostream&, const Polygon&);
};
int Polygon::ID = 0;
std::ostream& operator<<(std::ostream& o, const Polygon& p) {
	o << p.id << " => " << p.area();
	return o;
}

class Rectangle : public Polygon {
	public:
	int area() const {
		return width*height;
	}
};
class Triangle : public Polygon {
	public:
	int area() const {
		return width*height/2;
	}
};
#endif

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {
	public:
	virtual ~Derived() {}
};

template <class T>
T add(T a, T b) {
	return a + b;
}

template <class T1, class T2, int size>
class SoA {
	public:
	const int m_size;
	T1 m_arr1[size];
	T2 m_arr2[size];
	SoA() : m_size(size) {}
	void print() {
		for(int l_i = 0; l_i < size; l_i++) {
			cout << m_arr1[l_i] << endl;
			cout << m_arr2[l_i] << endl;
		}
	}
};

template <class T>
bool baz(T a, T b) {
	return a > b;
}
bool compare(int a, int b) {
	return a > b;
}
bool greaterThan(int a, int b, bool (*fn)(int, int)) {
	return fn(a, b);
}

template <int n>
class Meta {
	public:
	
	enum {
		sum = n + Meta<n-1>::sum,
		fac = n * Meta<n-1>::fac
	};
};
template<>
class Meta<1> {
	public:
	
	enum {
		sum = 1,
		fac = 1
	};
};

int main(int argc, char **argv) {
	
	//C(gcdr(10, 5));
	
	//foo(&waka::bar);
	
	//unsigned int c ;
	//int a[10];
	//// setup array content
	//for (c=1; c<11; c++) a[c-1] = (int)c;
	//// output reversed array content
	//int *b = &a[9] ; // use pointer on l a st array element
	//for (c = 9; c > 0; c--) {
		//cout << *b << " ";
		//b--;
	//}
	////cout << endl;

	Dog *d = new Dog();
	Animal *a = d;
	
	
	
	cout << d->says() << endl;
	cout << a->says() << endl;
	
	Calc c1(5);
	Calc c2(6);
	cout << (c1 + c2).getVal() << endl;
	
	Waka<int> w(5);
	cout << Waka<int>::x << endl;
	
	M m1(6);
	M m2(7);
	cout << (m1 + m2) << endl;
	
	
	C c3;
	c3.a = 2;
	c3.b = 3;
	c3.c = "hello";
	cout << c3 << endl;
	
	C c4(c3);
	cout << c3 << endl;
	cout << c4 << endl;
	
	Polygon *p0 = new Polygon;
	Polygon *p1 = new Rectangle;
	Polygon *p2 = new Triangle;
	p1->set_values(4,4);
	p2->set_values(4,4);
	
	Rectangle r;
	r.set_values(5,5);
	
	cout << *p0 << endl;
	cout << *p1 << endl;
	cout << *p2 << endl;
	cout << r << endl;
	
	
	cout << "----" << endl;
	
	unsigned int l_uint1 = -1;
  unsigned int l_uint2 = -2;
  unsigned int l_uint3 = -1 + 1;
  int l_int1           = true;
  int l_bool1          = -15;
  double* l_pointer    = NULL;//false;
  bool l_bool2         = l_pointer;
  int l_int2           = 3.9;
  float l_float1       = 5 / 2;
  float l_float2       = l_float1 * 0.5; // where's the implicit typecast?

  std::cout << l_uint1    << std::endl;
  std::cout << l_uint2    << std::endl;
  std::cout << l_uint3    << std::endl;
  std::cout << l_bool1    << std::endl;
  std::cout << l_int1     << std::endl;
  std::cout << l_pointer  << std::endl;
  std::cout << l_bool2    << std::endl;
  std::cout << l_int2     << std::endl;
  std::cout << l_float1   << std::endl;
  std::cout << l_float2   << std::endl;
  
	Base *l_pointer1 = new Base;
	Derived *l_pointer2 = reinterpret_cast<Derived *>(l_pointer1);
	int *l_pointer3 = reinterpret_cast<int*>(l_pointer2);
	
	std::cout << (l_pointer1) << std::endl;
  std::cout << (l_pointer2) << std::endl;
  std::cout << (l_pointer3) << std::endl;
  
	cout << add<int>(5.0, 10.0) << endl;
	
	[](int a) { return a*2; };
	
	cout << baz<int>(51, 10) << endl;
	
	cout << Meta<5>::sum << endl;
	cout << Meta<5>::fac << endl;

	return 0;
}
