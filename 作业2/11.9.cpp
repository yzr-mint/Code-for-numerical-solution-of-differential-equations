# include <vector>
# include <iostream>
using namespace std;

template<typename Datatype>
Datatype extrapolate_a(const unsigned int index) {
	Datatype a[7] = { 1., 1. / 2., 5. / 12., 3. / 8., 251. / 720., 95. / 288., 10987. / 60480. };
	return a[index];
}

template<typename Datatype>
vector<Datatype>* delta(vector<Datatype>* vec) {
	vector<Datatype>* result = new vector<Datatype>;
	if (!vec->size()) {
		return result;
	}
	for (auto i = vec->begin(); i != vec->end() - 1; i++) {
		result->push_back(*(i + 1) - *i);
	}
	return result;
}

template<typename Datatype>
vector<Datatype>* get_f(vector<Datatype>* us, vector<Datatype>* ts, Datatype func(Datatype, Datatype)) {
	vector<Datatype>* result = new vector<Datatype>;
	if (!us->size() || us->size() != ts->size()) {
		cout << "error!" << endl;
		return result;
	}
	for (int i = 0; i != us->size(); i++) {
		result->push_back(func(us->at(i), ts->at(i)));
	}
	return result;
}

template<typename Datatype>
Datatype step(vector<Datatype>* us, vector<Datatype>* ts, Datatype h, Datatype func(Datatype, Datatype)) {
	Datatype un = us->back();
	vector<Datatype>* fs = get_f(us, ts, func);
	for (int i = 0; i < us->size(); i++) {
		un += extrapolate_a<Datatype>(i) * fs->back() * h;
		fs = delta(fs);
	}
	delete fs;
	return un;
}

template<typename Datatype>
vector<Datatype>* solve_exterpolate(vector<Datatype>* u0, vector<Datatype>* t0, Datatype h, Datatype func(Datatype, Datatype), Datatype ub) {
	vector<Datatype>* result = new vector<Datatype>({ u0->back() });
	vector<Datatype>* us = new vector<Datatype>(*u0);
	vector<Datatype>* ts = new vector<Datatype>(*t0);
	for (Datatype now = ts->back(); now < ub; now += h) {
		us->push_back(step(us, ts, h, func));
		result->push_back(us->back());
		us->erase(us->begin());
		ts->push_back(ts->back() + h);
		ts->erase(ts->begin());
	}
	return result;
}


template<typename Datatype>
Datatype interpolate_a(const unsigned int index) {
	Datatype a[7] = { 1., -1. / 2., -1. / 12., -1. / 24., -19. / 720., -3. / 160., -863. / 60480. };
	return a[index];
}

template<typename Datatype>
void iterate(vector<Datatype>* us, vector<Datatype>* ts, Datatype h, Datatype func(Datatype, Datatype)) {
	Datatype newu = *(us->end() - 2);
	vector<Datatype>* fs = get_f(us, ts, func);
	for (int i = 0; i < us->size(); i++) {
		newu += interpolate_a<Datatype>(i) * fs->back() * h;
		fs = delta(fs);
	}
	delete fs;
	*(us->end() - 1) = newu;
	return;
}

template<typename Datatype>
vector<Datatype>* solve_interpolate(vector<Datatype>* u0, vector<Datatype>* t0, Datatype h, Datatype func(Datatype, Datatype), Datatype ub) {
	vector<Datatype>* result = new vector<Datatype>({ u0->back() });
	vector<Datatype>* us = new vector<Datatype>(*u0);
	vector<Datatype>* ts = new vector<Datatype>(*t0);
	for (Datatype now = ts->back(); now < ub; now += h) {
		us->push_back(step(us, ts, h, func));
		result->push_back(us->back());
		ts->push_back(ts->back() + h);
		for (int i = 0; i < 5; i++) {
			iterate(us, ts, h, func);
		}
		us->erase(us->begin());
		ts->erase(ts->begin());
	}
	return result;
}



template<typename Datatype>
Datatype func(Datatype u, Datatype t) {
	return -5 * u;
}

// ≤‚ ‘
#include <fstream>

typedef double datatype;

template<typename Datatype>
vector<Datatype>* linspace(Datatype lb, Datatype rb, Datatype step) {
	vector<Datatype>* a = new vector<Datatype>;
	a->push_back(lb);
	for (; lb < rb; lb += step) {
		a->push_back(lb + step);
	}
	return a;
}

// 0.1
// vector<datatype>* u0 = new vector<datatype>({ 4.4816890703 ,2.7182818285 ,1.6487212707 ,1 });
// vector<datatype>* t0 = new vector<datatype>({ -0.3,-0.2,-0.1,0 });
// 0.05
// vector<datatype>* u0 = new vector<datatype>({ 2.1170000166 ,1.6487212707 ,1.2840254167, 1 });
// vector<datatype>* t0 = new vector<datatype>({ -0.15,-0.1,-0.05,0 });

/*
int main() {

	ofstream output;
	output.open("output.csv", ios_base::out);

	datatype now = 0;
	vector<datatype>* u0 = new vector<datatype>({ 4.4816890703 ,2.7182818285 ,1.6487212707 ,1 });
	vector<datatype>* t0 = new vector<datatype>({ -0.3,-0.2,-0.1,0 });
	datatype h = t0->at(1) - t0->at(0);

	vector<datatype>* ts = linspace<datatype>(0, 1, h);
	for (auto i = ts->begin(); i != ts->end(); i++) {
		output << *i << ",";
	}
	output << endl;

	auto result1 = solve_exterpolate<datatype>(u0, t0, h, func, 1);
	for (auto i = result1->begin(); i != result1->end(); i++) {
		output << *i << ",";
	}
	output << endl;

	auto result2 = solve_interpolate<datatype>(u0, t0, h, func, 1);
	for (auto i = result2->begin(); i != result2->end(); i++) {
		output << *i << ",";
	}
	output << endl;

	return 0;
}
*/





