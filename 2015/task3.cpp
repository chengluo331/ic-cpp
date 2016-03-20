#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class polynomial{
	unsigned int _k;
	vector<double> _coeff;
public:
	polynomial(unsigned int k = 0) :_k(k){ _coeff.resize(k+1, 0.0); };
	polynomial(unsigned int k, double x) :_k(k){ _coeff.push_back(x); _coeff.push_back(1.0); };

	double& operator[](unsigned int i){ return _coeff[i]; };
	const double& operator[](unsigned int i) const{ return _coeff[i]; };
	polynomial operator+(const polynomial& q) const;
	polynomial operator*(const polynomial& q) const;
	polynomial operator*(double d) const;
	polynomial operator^(unsigned int m) const;
	double operator()(double x) const;
};

polynomial polynomial::operator+(const polynomial& q) const{
	polynomial r;
	const polynomial* p;
	if (_k>q._k){
		r = (*this);
		p = &q;
	}
	else{
		r = q;
		p = this;
	}
	for (size_t i = 0; i<=p->_k; i++){
		r[i] = (*p)[i];
	}
	return r;
}

polynomial polynomial::operator*(const polynomial & q) const{
	polynomial r(_k + q._k);
	for (size_t i = 0; i<=_k; i++){
		for (size_t j = 0; j<=q._k; j++){
			r._coeff[i + j] += _coeff[i] * q._coeff[j];
		}
	}
	return r;
}

polynomial polynomial::operator*(double d) const{
	polynomial r = (*this);
	for (size_t i = 0; i<=_k; i++){
		r[i] = d*_coeff[i];
	}
	return r;
}

double polynomial::operator()(double x) const{
	double v = 0;
	for (size_t i = 0; i<=_k; i++){
		v += _coeff[i] * pow(x, i);
	}
	return v;
}

polynomial polynomial::operator^(unsigned int m) const{
	polynomial r=(*this);
	for (size_t i = 1; i<m; i++){
		r = r*r;
	}
	return r;
}

polynomial operator*(double d, const polynomial& p){
	return p*d;
}

int main(){
	double x1 = -3.0, x2 = -1.0, x3 = 0.0, x4 = 2.0, x5 = 3.0;
	polynomial p = 1.0 / (x5 - x1) / (x5 - x4) / (x5 - x3) / (x5 - x2)*polynomial(1, -x1)*polynomial(1, -x2)*polynomial(1, -x3)*polynomial(1, -x4);
	polynomial q = 2.0*polynomial(1, -x5);
	polynomial r = (p ^ 2)*q;

	cout << p[3] << endl;
	cout << r[7] << endl;
	cout << r(-2) << endl;

	return 0;
}
