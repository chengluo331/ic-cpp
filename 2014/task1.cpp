#include <iostream>
using namespace std;

void f(unsigned long int& a, unsigned long int& b, unsigned long n){
	for (size_t i = 2; i < n; i++)
	{
		if (n%i==0){
			a = i;
			b = n / i;
			return;
		}
	}
}

int main(){
	unsigned long int a, b;
	f(a, b, 97343);
	cout << a << ',' << b << endl;
	f(a, b, 2539619);
	cout << a << ',' << b << endl;
	return 0;
}