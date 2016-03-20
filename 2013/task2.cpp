#include <iostream>
#include <cmath>

using namespace std;

class quaternion{
	double _x, _i, _j, _k;
public:
	quaternion(double x = 0.0, double i = 0.0, double j = 0.0, double k = 0.0) :
		_x(x), _i(i), _j(j), _k(k){};
	static const quaternion i;
	static const quaternion j;
	static const quaternion k;
	quaternion operator+(const quaternion& q) const;
	quaternion operator-() const;
	quaternion operator-(const quaternion& q) const;
	quaternion operator*(const quaternion& q) const;
	double norm() const;
	quaternion inv() const;
	quaternion c() const;
	void print(ostream& os) const;
};

const quaternion quaternion::i = quaternion(0.0, 1.0, 0.0, 0.0);
const quaternion quaternion::j = quaternion(0.0, 0.0, 1.0, 0.0);
const quaternion quaternion::k = quaternion(0.0, 0.0, 0.0, 1.0);

quaternion quaternion::operator + (const quaternion& q) const{
	return quaternion(_x + q._x, _i + q._i, _j + q._j, _k + q._k);
}

quaternion quaternion::operator-() const{
	return quaternion(-_x, -_i, -_j, -_k);
}

quaternion quaternion::operator - (const quaternion& q) const{
	return (*this)+(-q);
}

quaternion quaternion::operator* (const quaternion& q) const{
	return quaternion(_x*q._x - _i*q._i - _j*q._j - _k*q._k,
		_x*q._i + _i*q._x + _j*q._k - _k*q._j,
		_x*q._j - _i*q._k + _j*q._x + _k*q._i,
		_x*q._k + _i*q._j - _j*q._i + _k*q._x);
}

quaternion quaternion::c() const{
	return quaternion(- 0.5)*((*this) + i*(*this)*i + j*(*this)*j + k*(*this)*k);
}

double quaternion::norm() const{
	return sqrt(_x*_x + _i*_i + _j*_j + _k*_k);
}

quaternion quaternion::inv() const{
	double n = (*this).norm();
	return quaternion(1.0 / n*n)*((*this).c());
}

void quaternion::print(ostream& os) const{
	if (_i == 0 && _j==0 && _k==0){
		os << _x;
	}
	else{
		os << '(' << _x << ',' << _i << ',' << _j << ',' << _k << ')';
	}
}

ostream& operator<<(ostream& os, const quaternion& q){
	q.print(os);
	return os;
}

int main(){
	quaternion a(-0.25, 3.0, 0.0, 1.0);
	quaternion b(0.0, 0.0, 5.0, -2.0);
	cout << quaternion::i*a*quaternion::j*b*quaternion::k << endl;
	cout << a*a - b*b << endl;
	cout << (a+b).c() << endl;
	cout << a.inv() << endl;
	cout << b.inv()*a << endl;
	cout << a*b.inv() << endl;
	return 0;
}