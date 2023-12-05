#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

double f(double t, double u) {
    return 4 * t * sqrt(u);
}


double RungeKutta(double t0, double u0, double h) {
    double k1, k2, k3;
    double t = t0 + h;
    k1 = f(t0, u0);
    k2 = f(t0 + 2 * h / 3, u0 + 2 * h * k1 / 3);
    k3 = f(t0 + 2 * h / 3, u0 + 2 * h * k2 / 3);
    return u0 + h * (1.0 / 4 * k1 + 3.0 / 8 * k2 + 3.0 / 8 * k3);
}

template<typename Datatype>
vector<Datatype>* linspace(Datatype lb, Datatype rb, Datatype step) {
    vector<Datatype>* a = new vector<Datatype>;
    a->push_back(lb);
    for (; lb < rb; lb += step) {
        a->push_back(lb + step);
    }
    return a;
}

int main() {
    double t0 = 0.0;
    double t_end = 2.0;
    vector<double> hs = { 0.1,0.5,1 };

    ofstream output;
    output.open("output.csv", ios_base::out);

    for (auto h : hs) {
        double u0 = 1.0;
        vector<double>* ts = linspace(t0, t_end, h);
        for (auto t = ts->begin(); t != ts->end(); t++) {
            cout << *t << ", ";
        }
        cout << "\n";
        for (auto t = ts->begin(); t != ts->end(); t++) {
            cout << u0 << ", ";
            u0 = RungeKutta(*t, u0, h);
        }
        cout << "\n";
    }
    return 0;
}