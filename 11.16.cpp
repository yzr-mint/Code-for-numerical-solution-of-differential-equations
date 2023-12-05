# include <vector>
# include <iostream>
using namespace std;

template<typename Datatype>
vector<Datatype>* linspace(Datatype lb, Datatype rb, Datatype step) {
	vector<Datatype>* a = new vector<Datatype>;
	a->push_back(lb);
	for (; lb < rb; lb += step) {
		a->push_back(lb + step);
	}
	return a;
}

template<typename Datatype>
Datatype step(Datatype h, Datatype un, Datatype un1) {
	Datatype h2 = h / 2;
	return (2 * un1 - (1 + h2) * un) / (1 - h2);
}
/*
#include <fstream>
typedef double datatype;
int main() {

	ofstream output;
	output.open("output.csv", ios_base::out);

	constexpr datatype h = 0.05;
	datatype un = 1;
	datatype un1 = 1.05;
	datatype tmp = 0;

	vector<datatype>* ts = linspace<datatype>(0, 1, h);
	for (auto i = ts->begin(); i != ts->end(); i++) {
		output << *i << ",";
	}
	output << endl;

	for (auto i = 0; i != ts->size(); i++) {
		if (i == 0) {
			output << un << ",";
		}
		else if(i == 1){
			output << un1 << ",";
		}
		else {
			tmp = step(h, un, un1);
			output << tmp << ",";
			un = un1;
			un1 = tmp;
		}
	}

	return 0;
}
*/