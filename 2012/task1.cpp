#include <iostream>
using namespace std;

unsigned long int mm(unsigned long int a, unsigned long int b, unsigned int m){
	return ((a%m)*(b%m)) % m;
}

unsigned long int ms(unsigned long int a, unsigned long int b, unsigned int m){
	return ((a%m) + (b%m)) % m;
}

unsigned long int fm(unsigned long int n, unsigned int m){
	unsigned long int f = mm(1, 2, m);
	unsigned long int i = 3;
	while (i <= n){
		f = mm(f, i,m);
		i++;
	}
	return f;
}

unsigned long int pm(unsigned long int a, unsigned long int b, unsigned int m){
	unsigned long int p = mm(a, a, m);
	unsigned long int i = 3;
	while (i <= b){
		p = mm(p, a, m);
		i++;
	}
	return p;
}

unsigned long int sm(unsigned long int n, unsigned int m){
	unsigned long int i = 1;
	unsigned long int s = 0;
	while (i <= n){
		s = ms(s,pm(i, i, m),m);
		i++;
	}
	return s;
}

int main(){
	cout << fm(80, 997) << endl;
	cout << pm(7, 128, static_cast<unsigned int>(1e06)) << endl;
	cout << sm(1000, 877) << endl;
	return 0;
}