#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int bubble_sort(vector<double>& v){
	int swap = 0;
	int last_swap = -1;
	while (last_swap!=swap){
		last_swap = swap;
		for (size_t i = 0; i < v.size() - 1; i++)
		{
			if (v[i] > v[i + 1]){
				double d = v[i];
				v[i] = v[i + 1];
				v[i + 1] = d;
				swap++;
			}
		}
	}	
	return swap;
}

int main(){
	ifstream in("data.txt");
	if (in){
		double d;
		vector<double> v;
		while (in >> d){
			v.push_back(d);
		}
		
		int swap = bubble_sort(v);
		cout << swap << endl;

		ofstream out("sorted.txt");

		for (size_t i = 0; i < v.size(); i++)
		{
			out << v[i] << ' ';
		}
		out.close();
	}
	in.close();

	return 0;
}