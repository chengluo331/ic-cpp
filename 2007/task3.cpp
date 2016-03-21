#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <numeric>
#include <limits>   

using namespace std;

class RV{
public:
	virtual double generate() = 0;
	virtual double pdf(const double &) = 0;
	virtual double cdf(const double &) = 0;
};

class uni :public RV{
	double _a, _b;
public:
	uni(double a = 0.0, double b = 1.0) :_a(a), _b(b){ assert(a < b && "a<b!"); };
	double generate(){
		return static_cast<double>(rand()) / RAND_MAX*(_b - _a) + _a;
	};
	double pdf(const double & x){
		return (x >= _a&&x <= _b) ? 1.0 / (_b - _a) : 0.0;
	};
	double cdf(const double & x) {
		if (x < _a){
			return 0.0;
		}
		else if (x >= _a && x <= _b){
			return (x - _a) / (_b - _a);
		}
		else{
			return 1.0;
		}
	};
};

class norm: public RV{
	uni _gen;
	double _u, _s;
public:
	norm(double u = 0.0, double s = 1.0) :_u(u), _s(s){};
	double generate(){
		const double epsilon = numeric_limits<double>::min();
		double u1, u2;
		do
		{
			u1 = _gen.generate();
			u2 = _gen.generate();
		} while (u2 <= epsilon);
		return sqrt(-2.0*log(u2))*cos(2 * M_PI*u1)*_s + _u;
	};
	double pdf(const double & x){
		return 1.0 / (_s*sqrt(2 * M_PI))*exp(-(x - _u)*(x - _u) / (2.0*_s*_s));
	};
	double cdf(const double & x) {
		assert(false && "ask Dr.Antoine Jacquier to tell you a very easy approach :) http://wwwf.imperial.ac.uk/~ajacquie/IC_AMDP/IC_AMDP_Docs/Code/bs.py ");
		return 0;
	};
};

double indicator(double a, double b, double x){
	return (x >= a && x <= b) ? 1.0 : 0;
}

double mc(double(*f)(double), RV& dist, double a=0, double b=1, unsigned int n = 1000){
	double s = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		double x = dist.generate();
		s += f(x) / dist.pdf(x)*indicator(a,b,x);
	}
	return s / n;
}

double c(double x){
	return 1.0;
}

double nexp(double x){ // change variable
	return exp(-x)+exp(-1.0/x)/x/x;
}

double mean(const vector<double>& v){
	double sum = accumulate(v.begin(), v.end(), 0.0);
	return sum / v.size();
}

double var(const vector<double>& v){
	double m = mean(v);
	double var = 0.0;
	for (size_t i = 0; i < v.size(); i++)
	{
		var += (v[i] - m)*(v[i] - m);
	}
	return var / v.size();
}


int main(){
	//uni u_nexp;
	//cout << mc(nexp, u_nexp) << endl;

	//uni u_c(.25, 1.0);
	//cout << mc(c, u_c) << endl;

	vector<double> w;
	uni u_pi(0.0, M_PI);
	for (size_t i = 0; i < 100; i++)
	{
		w.push_back(mc(sin, u_pi, 0, M_PI));
	}
	cout << mean(w) << endl;
	cout << var(w) << endl;

	w.clear();
	norm n_std;
	for (size_t i = 0; i < 100; i++)
	{
		w.push_back(mc(sin, n_std, 0, M_PI));
	}
	cout << mean(w) << endl;
	cout << var(w) << endl;

	w.clear();
	norm n_pi(M_PI / 2.0, 1);
	for (size_t i = 0; i < 100; i++)
	{
		w.push_back(mc(sin, n_pi, 0, M_PI));
	}
	cout << mean(w) << endl;
	cout << var(w) << endl;

	return 0;
}