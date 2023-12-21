#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <Eigen/Eigen>
using namespace Eigen;
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

#define	LB	0
#define	RB	6.2831853071795864769
#define	H	0.05
double arr[5] = { 1 / pow(H,4), 1 / pow(H,2) - 4 / pow(H,4),\
	1 - 2 / pow(H,2) + 6 / pow(H,4), 1 / pow(H,2) - 4 / pow(H,4), 1 / pow(H,4) };
/*
int main() {
	vector<double>* xs = linspace<double>(LB - H, RB, H);
	xs->push_back(xs->back() + H);
	uint32_t N = xs->size();
	cout << "size: " << N << endl;

	MatrixXd A = MatrixXd::Zero(N, N);
	A(0, 0) = 1;
	A(0, 2) = -1;
	A(1, 1) = 1;
	for (uint32_t i = 2; i < N - 2; i++) {
		for (uint32_t j = 0; j <= 4; j++) {
			A(i, j + i - 2) = arr[j];
		}
	}
	A(N - 1, N - 1) = 1;
	A(N - 1, N - 3) = -1;
	A(N - 2, N - 2) = 1;

	VectorXd f = VectorXd::Zero(N);
	for (uint32_t i = 2; i < N - 2; i++) {
		f(i) = 601 * sin(5 * xs->at(i)) - 5 * sin(xs->at(i));
	}

	VectorXd u = A.fullPivHouseholderQr().solve(f);

	//for (uint32_t i = 1; i < N - 1; i++) {
	//	cout << xs->at(i) << ", " << u(i) << endl;
	//}
	for (uint32_t i = 1; i < N - 1; i++) {
		cout << xs->at(i) << ", ";
	}

	for (uint32_t i = 1; i < N - 1; i++) {
		cout << u(i) << ", ";
	}
}
*/