#include <iostream>
#include <string>

using namespace std;

unsigned int score(string s){
	unsigned int n=0;
	for(size_t i=0; i<s.size(); i++){
		n+=(i+1)*((int)s[i] - (int)'A');
	}
	return n;
}

int main(){

	cout << score("ZEOULOUS") << endl;
	cout << score("TRANSPORTER") << endl;
	cout << score("LECTURERS") << endl;
	
	return 0;
}