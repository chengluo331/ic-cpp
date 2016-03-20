#include <iostream>
#include <cmath>
using namespace std;

unsigned int f(unsigned int a){
	return a%2==0?a/2:(3*a+1)/2;
}

unsigned int c(unsigned int a){
	unsigned int i=0;
	unsigned int fa=a;
	while(fa!=1){
		fa=f(fa);
		i++;
	}
	return i;
}

unsigned int M(unsigned int l, unsigned int r){
	unsigned int max_c=0;
	unsigned int a=l;
	while(a<=r){
		max_c=max(max_c,c(a));
		a++;
	}
	return max_c;
}

unsigned int S(unsigned int n,unsigned int l, unsigned int r){
	unsigned int s=0;
	unsigned int a=l;
	while(a<=r){
		if(c(a)==n){
			s+=a;
		}
		a++;
	}
	return s;
}

int main(){	
	cout << "c: " << c(201503) <<endl;
	cout << "M: " << M(2e5,3e5) <<endl;
	cout << "S: " << S(99,1,1e5) <<endl;
	
	return 0;
}