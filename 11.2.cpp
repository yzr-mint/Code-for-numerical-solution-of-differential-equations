# include <vector>
# include <iostream>

using namespace std;
typedef double datatype;

datatype function(datatype u, datatype t) {
    return 5 * u;
}

const datatype h = (datatype)0.05;

vector<datatype>* linspace(datatype lb, datatype rb, datatype step) {
    vector<datatype>* a = new vector<datatype>;
    for (; lb <= rb; lb += step) {
        a->push_back(lb);
    }
    return a;
}
//Euler·¨