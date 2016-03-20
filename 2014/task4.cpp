#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
using namespace std;

class fraction { // from cw3
	friend ostream &operator<< (ostream &os, const fraction &f);
private:
	int numerator, denominator;
	void reduce();
public:
	// constructors
	fraction(int n = 0, int d = 1) : numerator(n), denominator(d) { reduce(); }
	fraction(const fraction& f){ numerator = f.numerator; denominator = f.denominator; }

	// assignment
	fraction& operator= (const fraction &f);

	fraction operator+ () const { return fraction(*this); }
	fraction operator- () const { fraction res(-numerator, denominator); return res; }

	fraction operator+ (const fraction &f) const;
	fraction operator* (const fraction &f) const;
	fraction operator- (const fraction &f) const;
	fraction operator/ (const fraction &f) const;

	fraction operator+ (int i) const;
	fraction operator- (int i) const;
	operator double() const;

	fraction &operator+= (const fraction &f);
};

int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }

// return 1 if positive -1 otherwise
int sign(int x){
	return (x > 0) - (x < 0);
}

ostream &operator<< (ostream &os, const fraction &f){
	if (f.numerator == 0) {
		os << 0;
	}
	else if (f.denominator == 1) {
		os << f.numerator;
	}
	else{
		os << f.numerator << "/" << f.denominator;
	}
	return os;
}

/*
* reduce a fraction
*	- assert on non zero denominator
*	- do nothing if numerator is 0
*	- divide both n and d by their positive gcd, attribute sign of the fraction on numerator
*/
void fraction::reduce(){
	assert(denominator != 0 && "create fraction with 0 as denominator");
	if (numerator == 0) return;
	int _sign = sign(numerator)*sign(denominator);
	numerator = abs(numerator);
	denominator = abs(denominator);
	int _gcd = gcd(numerator, denominator);
	if (_gcd > 1){
		numerator /= _gcd;
		denominator /= _gcd;
	}
	numerator *= _sign;
}

// assignment
fraction& fraction::operator= (const fraction &f){
	if (this != &f){
		numerator = f.numerator; denominator = f.denominator;
	}
	return *this;
}

fraction fraction::operator+ (const fraction &f) const{
	fraction r(*this);
	return r += f;
}

fraction fraction::operator* (const fraction &f) const{
	fraction res(numerator*f.numerator, denominator*f.denominator);
	return res;
}

fraction fraction::operator- (const fraction &f) const{
	return *this + (-f);
}

fraction fraction::operator/ (const fraction &f) const{
	fraction res(numerator*f.denominator, denominator*f.numerator);
	return res;
}

fraction fraction::operator+ (int i) const{
	fraction r(i, 1);
	return *this + r;
}

fraction fraction::operator- (int i) const{
	return *this + (-1);
}

fraction &fraction::operator+= (const fraction &f){
	numerator = numerator*f.denominator + denominator*f.numerator;
	denominator = denominator*f.denominator;
	reduce();
	return *this;
}

fraction::operator double() const {
	return static_cast<double>(numerator) / denominator;
}

fraction operator+ (int i, const fraction& f){
	return f + i;
}

fraction operator- (int i, const fraction& f){
	return -f + i;
}

double operator- (const fraction& f, double d){
	return static_cast<double>(f)-d;
}

///////////////////////////////////////////////////////////////

template <typename T>
T gibonacci(int n, const T& F0, const T& F1){
	vector<T> v(n + 1); v[0] = F0; v[1] = F1;
	for (size_t i = 2; i <= static_cast<unsigned int>(n); i++)
	{
		v[i] = v[i - 1] + v[i - 2];
	}
	return v[n];
}

template <typename T>
int glimit_phi(double epsilon, const T& F0, const T& F1){
	vector<T> f; f.push_back(F0); f.push_back(F1);
	double d = abs(static_cast<double>(F1) / F0 - (1 + sqrt(5)) / 2);
	int n = 1;
	while (d >= epsilon){
		n++;
		f.push_back(f[n - 1] + f[n - 2]);
		d = abs(static_cast<double>(f[n]) / f[n - 1] - (1 + sqrt(5)) / 2);
	}
	return n;
}

template <typename T1,typename T2>
T2 r_N(const T2& x, int N, const T1& F0, const T1& F1){
	vector<T1> v(N + 1); v[0] = F0; v[1] = F1;
	T2 s = F0 + F1*x;
	T2 x_p = x*x;
	for (size_t i = 2; i <= static_cast<unsigned int>(N); i++)
	{
		v[i] = v[i - 1] + v[i - 2];
		s += v[i] * x_p;
		x_p = x_p * x;
	}
	return s;
}

int main(){
	cout << gibonacci<fraction>(20, fraction(1,2), fraction(1,3)) << endl;
	int n = glimit_phi<fraction>(1e-6, fraction(1,2), fraction(1,3));
	cout << n << endl;
	cout << gibonacci<fraction>(n, fraction(1,2), fraction(1,3)) << endl;
	cout << r_N<fraction>(fraction(3,8), 5, fraction(1,2), fraction(1,3)) << endl;

	cout << gibonacci<short>(90, 0, 1) << endl;
	cout << gibonacci<unsigned int>(90, 0, 1) << endl;
	cout << gibonacci<unsigned long>(90, 0, 1) << endl;
	cout << gibonacci<float>(90, 0, 1) << endl;
	
	return 0;
}