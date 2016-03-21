#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

template <typename T>
class Laurent_polynomial{
	int _N;
	vector<T> _coeff;

public:
	Laurent_polynomial<T>(unsigned int N=0):_N(N){ _coeff.resize(_N*2+1); };
	Laurent_polynomial<T>(unsigned int N,T a) : _N(N){ _coeff.resize(_N * 2 + 1);
		for (size_t i = 0; i < _coeff.size(); i++) _coeff[i] = a;
	};

	int getN() const;
	T value(T x) const;
	T operator[](int i) const;
	T& operator[](int i);
	Laurent_polynomial<T> operator+(const Laurent_polynomial<T>& p) const;
};

template <typename T>
int Laurent_polynomial<T>::getN() const{
	return _N;
}

template <typename T>
T Laurent_polynomial<T>::value(T x) const{
	T v(0);
	for (int i = -_N; i <= _N; i++)
	{
		v += (*this)[i]* pow(x, i);
	}
	return v;
}

template <typename T>
T Laurent_polynomial<T>::operator[](int i) const{
	return _coeff[static_cast<unsigned int>(i+_N)];
}

template <typename T>
T& Laurent_polynomial<T>::operator[](int i){
	return _coeff[static_cast<unsigned int>(i + _N)];
}

template <typename T>
Laurent_polynomial<T> Laurent_polynomial<T>::operator+(const Laurent_polynomial<T>& p) const{
	const Laurent_polynomial<T>* ptr;
	Laurent_polynomial<T> r;
	if (_N < p._N){
		ptr = this;
		r = p;
	}
	else {
		ptr = &p;
		r = (*this);
	}
	for (int i = -ptr->_N; i <= ptr->_N; i++)
	{
		r[i]+=(*ptr)[i];
	}
	return r;
}

int main(){
	Laurent_polynomial<double> p(3, 2.0); // N = 2, a_n = 1.0, n = -N,...,N.
	Laurent_polynomial<double> q(5, -1.5), s;
	double x(2.1), y(-1.25);
	cout << "p(y) = " << p.value(y) << endl; // value of polynomial p at y
	s = p + q;
	for (int i = -s.getN(); i <= s.getN(); i++)
		cout << "s[" << i << "] = " << s[i] << endl; // print coefficients a_n of s
	cout << "s(x) = " << s.value(x) << endl;

	complex<double> f(2, -2), g(0, 5);
	Laurent_polynomial<complex<double> > u(2, f);
	Laurent_polynomial<complex<double> > v(5, g), t;
	complex<double> z(1, 2), w(0, -1);
	cout << "u(w) = " << u.value(w) << endl;
	t = u + v;
	for (int i = -t.getN(); i <= t.getN(); i++)
		cout << "t[" << i << "] = " << t[i] << endl;
	cout << "t(z) = " << t.value(z) << endl;

	return 0;
}