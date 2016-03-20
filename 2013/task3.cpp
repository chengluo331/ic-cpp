#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

template <typename T>
class quaternion{
	T _x, _i, _j, _k;
public:
	quaternion<T>(T x = T(), T i = T(), T j = T(), T k = T()) :
		_x(x), _i(i), _j(j), _k(k){};
	static const quaternion i;
	static const quaternion j;
	static const quaternion k;
	quaternion operator+(const quaternion<T>& q) const;
	quaternion operator-() const;
	quaternion operator-(const quaternion<T>& q) const;
	quaternion operator*(const quaternion<T>& q) const;
	quaternion c() const;
	void print(ostream& os) const;
};

template <>
const quaternion<double> quaternion<double>::i = quaternion(0.0, 1.0, 0.0, 0.0);
template <>
const quaternion<double> quaternion<double>::j = quaternion(0.0, 0.0, 1.0, 0.0);
template <>
const quaternion<double> quaternion<double>::k = quaternion(0.0, 0.0, 0.0, 1.0);

template <typename T>
quaternion<T> quaternion<T>::operator + (const quaternion<T>& q) const{
	return quaternion(_x + q._x, _i + q._i, _j + q._j, _k + q._k);
}

template <typename T>
quaternion<T> quaternion<T>::operator-() const{
	return quaternion(-_x, -_i, -_j, -_k);
}

template <typename T>
quaternion<T> quaternion<T>::operator - (const quaternion<T>& q) const{
	return (*this)+(-q);
}

template <typename T>
quaternion<T> quaternion<T>::operator* (const quaternion<T>& q) const{
	return quaternion(_x*q._x - _i*q._i - _j*q._j - _k*q._k,
		_x*q._i + _i*q._x + _j*q._k - _k*q._j,
		_x*q._j - _i*q._k + _j*q._x + _k*q._i,
		_x*q._k + _i*q._j - _j*q._i + _k*q._x);
}

template <typename T>
quaternion<T> quaternion<T>::c() const{
	return quaternion(T(-0.5))*((*this) + i*(*this)*i + j*(*this)*j + k*(*this)*k);
}

template <typename T>
void quaternion<T>::print(ostream& os) const{
	if (_i == T() && _j == T() && _k == T()){
		os << _x;
	}
	else{
		os << '(' << _x << ',' << _i << ',' << _j << ',' << _k << ')';
	}
}

template <typename T>
ostream& operator<<(ostream& os, const quaternion<T>& q){
	q.print(os);
	return os;
}

int main(){
	/*quaternion<int> a(1, 2, 3, 4), b(-1, 0, 3, 2), c;
	
	c = a*a - b*b;
	complex<double> z1(1, 1), z2(0, -1), z3(-1, 1), z4(5, 0);
	quaternion<complex<double> > aa(z1, z2, z3, z4), bb(z4, z3, z2, z1), cc;
	cc = aa*aa - bb*bb;*/

	quaternion<long int> a(123456789, 12345, 54321, 987654321), b(-999, 111, 222, 333);
	cout << a*b << endl;
	cout << b*a << endl;
	cout << a*a - b*b << endl;

	complex<double> a1(1, 1), a2(-5, 0), a3(2, -3), a4(0, 1);
	complex<double> b1(0, 0), b2(0, 5), b3(1, -1), b4(8, 9);

	quaternion<complex<double> > A(a1, a2, a3, a4), B(b1, b2, b3, b4);
	cout << A*B << endl;
	cout << B*A << endl;
	cout << A*A - B*B << endl;

	return 0;
}