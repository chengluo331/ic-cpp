#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int fibonacci(int n, int F0=0, int F1=1){
	vector<int> v(n+1); v[0] = F0; v[1] = F1;
	for (size_t i = 2; i <= static_cast<unsigned int>(n) ; i++)
	{
		v[i] = v[i - 1] + v[i - 2];
	}
	return v[n];
}

int flimit_phi(double epsilon, int F0 = 0, int F1 = 1){
	vector<int> f; f.push_back(F0); f.push_back(F1);
	double d = abs((static_cast<double>(f[1]) / f[0]) - (1 + sqrt(5)) / 2);	
	int n = 1;
	while (d >= epsilon){
		n++;
		f.push_back(f[n - 1] + f[n - 2]);
		d = abs((static_cast<double>(f[n]) / f[n - 1]) - (1 + sqrt(5)) / 2);
	}
	return n;
}

double s_N(double x, int N, int F0 = 0, int F1 = 1){
	vector<int> v(N + 1); v[0] = F0; v[1] = F1;
	double s = F0 + F1*x;
	for (size_t i = 2; i <= static_cast<unsigned int>(N); i++)
	{
		v[i] = v[i - 1] + v[i - 2];
		s += v[i] * pow(x, i);
	}
	return s;
}


int main(){
	cout << fibonacci(20, 3, 4) << endl;
	int n = flimit_phi(1e-6, 3, 4);
	cout << n << endl;
	cout << fibonacci(n, 3, 4) << endl;
	cout << s_N(0.1, 10, 3, 4) << endl;

	return 0;
}