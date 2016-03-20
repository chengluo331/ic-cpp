#include <iostream>
#include <cmath>
using namespace std;

#define PRIME 2017

template <unsigned int p>
class primefield{
	unsigned int a;
public:
	primefield<p>(int n) { 
		a = n < 0 ? (n+p)%p : n%p; 
	};
	primefield<p>& operator+= (const primefield<p>& q);
	primefield<p> operator* (const primefield<p>& q) const;
	primefield<p>& operator*= (const primefield<p>& q);
	primefield<p> operator^ (unsigned int n) const; // power
	primefield<p> operator/ (const primefield<p>& q) const;
	primefield<p> operator+ (const primefield<p>& q) const;
	primefield<p> operator- (const primefield<p>& q) const;
	operator unsigned int() const;
	void print(ostream& os) const;
};

template <unsigned int p>
primefield<p>& primefield<p>::operator+= (const primefield<p>& q){
	a += q.a;
	a %= p;
	return (*this);
}

template <unsigned int p>
primefield<p> primefield<p>::operator+ (const primefield<p>& q) const{
	primefield<p> r(*this);
	r += q;
	return r;
}

template <unsigned int p>
primefield<p> primefield<p>::operator- (const primefield<p>& q) const{
	primefield<p> r(a - q.a);
	return r;
}

template <unsigned int p>
primefield<p> primefield<p>::operator* (const primefield<p>& q) const {
	primefield<p> r(*this);
	r *= q;
	return r;
}

template <unsigned int p>
primefield<p>& primefield<p>::operator*= (const primefield<p>& q) {
	a *= q.a;
	a %= p;
	return (*this);
}

template <unsigned int p>
primefield<p> primefield<p>::operator^ (unsigned int n) const {
	primefield<p> r(1);
	for (size_t i = 0; i < n; i++)
	{
		r *= (*this);
	}
	return r;
}

template <unsigned int p>
primefield<p> primefield<p>::operator/ (const primefield<p>& q) const{
	return (*this)*(q ^ (p - 2));
}

template <unsigned int p>
primefield<p>::operator unsigned int() const{
	return static_cast<unsigned int>(a);
}

template <unsigned int p>
void primefield<p>::print(ostream& os) const{
	os << a;
}

template <unsigned int p>
ostream& operator<<(ostream& os, const primefield<p> q){
	q.print(os);
	return os;
}

template <unsigned int p>
primefield<p> power(const primefield<p>& q, unsigned int n){
	return q^n;
}

template <unsigned int p>
primefield<p> factorial(const primefield<p>& q){
	if (q == 1) return primefield<p>(1);
	return q*factorial(q - primefield<p>(1));
}

int main() {
	//primefield<PRIME> partial_sum(0);
	//for (unsigned int i = 1; i <= 50; ++i) {
	//	partial_sum += primefield<PRIME>(1) / primefield<PRIME>(i);
	//}
	//cout << "sum_i=1^50 1/i = " << partial_sum << endl;
	//unsigned int aa, bb;
	//cout << "a, b = "; cin >> aa >> bb;
	//primefield<PRIME> a(aa), b(bb);
	//cout << "a + b = " << a + b << endl;
	//cout << "a - b = " << a - b << endl;
	//cout << "a * b = " << a * b << endl;
	//cout << "a / b = " << a / b << endl;
	//cout << "a^10 = " << power(a, 10) << endl;
	//cout << "a! = " << factorial(a) << endl;
	cout << power(primefield<79>(53), 10) << endl;
	cout << primefield<79>(3) / primefield<79>(21) + primefield<79>(5) / primefield<79>(67) << endl;
	cout << primefield<79>(3) / primefield<79>(21) - primefield<79>(5) / primefield<79>(67) << endl;
	cout << factorial(primefield<79>(50)) << endl;
	primefield<79> partial_sum(0);
	for (unsigned int i = 1; i <= 50; ++i) {
		partial_sum += primefield<79>(1) / primefield<79>(i);
	}
	cout << partial_sum << endl;
	return 0;
}
