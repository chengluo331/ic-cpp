#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <numeric>
#include <limits>   


using namespace std;

struct point{
	double _x, _y;
	point(double x=0.0, double y=0.0) :_x(x), _y(y){};
	bool in(double x1,double x2, double y1,double y2) const{
		return _x >= x1&&_x <= x2&&_y >= y1&&_y <= y2;
	}
	point operator*(const point& p) const{
		return point(_x*p._x, _y*p._y);
	}
	point operator*(double d) const{
		return point(_x*d, _y*d);
	}
	point operator+(const point& p) const{
		return point(_x+p._x, _y+p._y);
	}
};

point operator*(double d, const point& p) {
	return p*d;
}

template <typename T>
class RV{
public:
	virtual T generate() = 0;
	virtual double pdf(const T &) = 0;
	virtual double cdf(const T &) = 0;
};

class uniform2d :public RV<point>{
	double _a1, _b1,_a2, _b2;
public:
	uniform2d(double a1 = 0.0, double b1 = 1.0, double a2 = 0.0, double b2 = 1.0) :
		_a1(a1), _b1(b1), _a2(a2), _b2(b2){
		assert(a1 < b1 && "a<b!"); assert(a2 < b2 && "a<b!");
	};
	point generate(){
		double x = static_cast<double>(rand()) / RAND_MAX*(_b1 - _a1) + _a1;
		double y = static_cast<double>(rand()) / RAND_MAX*(_b2 - _a2) + _a2;
		return point(x,y);
	};
	double pdf(const point& p){
		return (p._x >= _a1 && p._x <= _b1 && p._y >= _a2 && p._y <= _b2) ? 1.0 / (_b1 - _a1) / (_b2 - _a2) : 0.0;
	};
	double cdf(const point& p) {
		assert(false && "looooool it's a joke. i don't know how to do that");
		return 0;
	};
};

class normal2d : public RV<point>{
	uniform2d _gen;
	point _u, _s;
public:
	normal2d(const point& u = point(), const point& s = point(1,1)) :_u(u), _s(s){};
	point generate(){
		const double epsilon = numeric_limits<double>::min();
		point u1, u2;
		do
		{
			u1 = _gen.generate();
			u2 = _gen.generate();
		} while (u2._x <= epsilon || u2._y <= epsilon);
		point r = -2.0*point(log(u2._x), log(u2._y));
		return point(sqrt(r._x),sqrt(r._y))*point(cos(2 * M_PI*u1._x), cos(2 * M_PI*u1._y))*_s + _u;
	};
	double pdf(const point & p){
		return 1.0 / 2.0 / M_PI/ _s._x / _s._y*exp(-0.5*((p._x - _u._x)*(p._x - _u._x) / _s._x / _s._x + (p._y - _u._y)*(p._y - _u._y) / _s._y / _s._y));
	};
	double cdf(const point & x) {
		assert(false && "that's impossible!");
		return 0;
	};
};

double indicator(const point& p, double x1, double x2, double y1, double y2){
	return p.in(x1, x2, y1, y2);
}

template <typename T>
double mc(double(*f)(const T&), RV<T>& dist, 
	double x1 = 0.0, double x2 = 1.0, double y1 = 0.0, double y2 = 1.0, unsigned int n = 1000){
	double s = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		T x = dist.generate();
		s += f(x) / dist.pdf(x)*indicator(x, x1, x2, y1, y2);
	}
	return s / n;
}

double c(const point& x){
	return 1.0;
}

double nexp(const point& p){ // change variable
	return (exp(-p._x) + exp(-1.0 / p._x) / p._x / p._x)*p._y;
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

double h(const point& p){
	double x = p._x;
	double y = p._y;
	return exp(-x*x+x*y)*cos(x*M_PI)*sin(y*M_PI);
}

void monte_carlo(vector<double>& v, RV<point>& dist, double x1 = 0.0, double x2 = 1.0, double y1 = 0.0, double y2 = 1.0, unsigned int n=1000){
	v.clear();
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(mc<point>(h, dist, x1, x2, y1, y2, n));
	}
	cout << mean(v) << endl;
	cout << var(v) << endl;
}

int main(){
	uniform2d u_c(-4.0, 4.0, 0.25, 1.0);
	cout << mc<point>(c, u_c,-4.0,4.0,0.25,1.0) << endl;

	uniform2d u_nexp;
	cout << mc<point>(nexp, u_nexp, 0,1,0,1,10000) << endl;

	uniform2d u_f(-3.0, 3.0,-1.0,1.0);
	vector<double> w;
	monte_carlo(w, u_f, -3.0, 3.0, -1.0, 1.0, 100);
	monte_carlo(w, u_f, -3.0, 3.0, -1.0, 1.0, 1000);
	monte_carlo(w, u_f, -3.0, 3.0, -1.0, 1.0, 10000);
	
	normal2d n_std;
	monte_carlo(w, n_std, -3.0, 3.0, -1.0, 1.0, 100);
	monte_carlo(w, n_std, -3.0, 3.0, -1.0, 1.0, 1000);
	monte_carlo(w, n_std, -3.0, 3.0, -1.0, 1.0, 10000);

	normal2d n_pi(point(M_PI / 2.0, M_PI / 2.0), point(1, 1));
	monte_carlo(w, n_pi, -3.0, 3.0, -1.0, 1.0, 100);
	monte_carlo(w, n_pi, -3.0, 3.0, -1.0, 1.0, 1000);
	monte_carlo(w, n_pi, -3.0, 3.0, -1.0, 1.0, 10000);

	return 0;
}