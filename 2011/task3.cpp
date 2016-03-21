#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class gen_charfn{
	T _alpha;
	double _a, _b;
public:
	gen_charfn<T>(T alpha = T(), double a = 0.0, double b = 0.0) : _alpha(alpha), _a(a), _b(b){};
	T operator()(double x) const{ return (x >= _a&&x < _b) ? _alpha : T(); };
	T intR() const { return _alpha*(_b - _a); };
	gen_charfn<T>& operator+=(const gen_charfn<T> & x) { _alpha += x._alpha; return (*this); };
	gen_charfn<T> operator+(const gen_charfn<T> & x) const{ gen_charfn<T> r = (*this); r += x; return r; };
	double get_a() const{ return _a; };

	gen_charfn<T>& operator*=(const T& b){
		_alpha *= b;
		return (*this);
	}
	gen_charfn<T>& operator*=(const gen_charfn<T>& c) {
		(*this) *= c._alpha;
	}
};

template <typename T>
class step_function{
	vector<gen_charfn<T> > _v;
public:
	step_function(unsigned int n = 0){ for (size_t i = 0; i < n; i++) _v.push_back(gen_charfn<T>()); };
	void push_back(const gen_charfn<T>& c){ _v.push_back(c); };
	T operator()(double x) const{
		T s = T();
		for (size_t i = 0; i < _v.size(); i++) {
			s += _v[i](x);
		}
		return s;
	};
	T intR() const {
		T s = T();
		for (size_t i = 0; i < _v.size(); i++) {
			s += _v[i].intR();
		}
		return s;
	};
	step_function<T> operator+(const step_function<T>& s) const{
		const step_function<T>* p;
		step_function<T> r;
		if (s._v.size() < _v.size()){
			p = &s;
			r = (*this);
		}
		else{
			p = (*this);
			r = s;
		}
		double a = p->_v[0].get_a();
		size_t j = 0;
		for (size_t i = 0; i < r._v.size(); i++)
		{
			if (r._v[i].get_a() == a){
				j = i; break;
			}
		}
		for (size_t i = 0; i < p->_v.size(); i++)
		{
			r._v[j] += p->_v[i];
			j++;
		}
		return r;
	};

	step_function<T> operator*(const T& b) const{
		step_function<T> r = (*this);
		for (size_t i = 0; i < _v.size(); i++)
		{
			r._v[i] *= b;
		}
		return r;
	}
	step_function<T> operator*(const gen_charfn<T>& c) const{
		step_function<T> r = (*this);
		for (size_t i = 0; i < r._v.size(); i++)
		{
			if (r._v[i].get_a() == c.get_a()){
				r._v[i]*=c; break;
			}
		}
		return r;
	}
	step_function<T> operator*(const step_function<T>& s) const{
		const step_function<T>* p;
		step_function<T> r;
		if (s._v.size() < _v.size()){
			p = &s;
			r = (*this);
		}
		else{
			p = (*this);
			r = s;
		}
		double a = p->_v[0].get_a();
		size_t j = 0;
		for (size_t i = 0; i < r._v.size(); i++)
		{
			if (r._v[i].get_a() == a){
				j = i; break;
			}
		}
		for (size_t i = 0; i < p->_v.size(); i++)
		{
			r._v[j] *= p->_v[i]; // only this line is different from the + operator
			j++;
		}
		return r;
	}
};

void uniform_partition(vector<double>& partition, double a=0.0, double b=1.0, unsigned int n = 10000){
	for (size_t i = 0; i <= n; i++)
	{
		double xi = a + static_cast<double>(i)*(b - a) / n;
		partition.push_back(xi);
	}
}

void logarithmic_partition(vector<double>& partition, double a = 0.0, double b = 1.0, unsigned int n = 10000){
	for (size_t i = 0; i <= n; i++)
	{
		double xi = log(exp(a) + i*(exp(b) - exp(a)) / n);
		partition.push_back(xi);
	}
}

template <typename T>
T interpolate(T (*f)(double), const vector<double>& partition){
	step_function<T> s;
	for (size_t i = 0; i < partition.size()-1; i++)
	{
		double xi = partition[i];
		double xi1 = partition[i+1];
		gen_charfn<T> c(f(xi),xi,xi1);
		s.push_back(c);
	}
	return s.intR();
}



int main(){

	vector<double> partition;
	uniform_partition(partition);

	cout << interpolate<double>(sin, partition) << endl; // 0.4597 from wolframalpha

	partition.clear();
	logarithmic_partition(partition);
	cout << interpolate<double>(sin, partition) << endl;
	
	return 0;
}