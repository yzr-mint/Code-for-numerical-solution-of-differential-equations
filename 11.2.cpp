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

//Euler法
//方程形如u'=f(u,t), u(lb)=u0, t\in(lb,rb)
template<typename Datatype>
vector<Datatype>* Euler_method(Datatype f(Datatype, Datatype), Datatype u0, Datatype lb, Datatype rb, Datatype h) {
    vector<Datatype>* ts = linspace(lb, rb, h);
    vector<Datatype>* result = new vector<Datatype>;
    result->push_back(u0);
    for (auto i = ts->begin(); i != ts->end() - 1; i++) {
        result->push_back(result->back() + h * f(result->back(), *i));
    }
    return result;
}

//改进Euler法
//方程形如u'=f(u,t), u(lb)=u0, t\in(lb,rb)
//需要一个求解模块和一个迭代模块。迭代模块的收敛判断为5步。
template<typename Datatype>
Datatype iterate_solve(Datatype un, Datatype tn, Datatype tn1, Datatype h, Datatype f(Datatype, Datatype));

template<typename Datatype>
vector<Datatype>* advanced_Euler_method(Datatype f(Datatype, Datatype), Datatype u0, Datatype lb, Datatype rb, Datatype h) {
    vector<Datatype>* ts = linspace(lb, rb, h);
    vector<Datatype>* result = new vector<Datatype>;
    result->push_back(u0);
    for (auto i = ts->begin(); i != ts->end() - 1; i++) {
        result->push_back(iterate_solve(result->back(), *i, *(i + 1), h, f));
    }
    return result;
}

template<typename Datatype>
Datatype iterate_solve(Datatype un, Datatype tn, Datatype tn1, Datatype h, Datatype f(Datatype, Datatype)) {
    unsigned int step = 5;
    Datatype result = un;
    while (step > 0) {
        step--;
        result = un + h * (f(un, tn) + f(result, tn1)) / 2;
    }
    return result;
}

// 测试
#include <fstream>
typedef double datatype;

datatype function(datatype u, datatype t) {
    return -5 * u;
}

/*
int main() {

    ofstream output;
    output.open("output.csv", ios_base::out);

    const datatype h = (datatype)0.05;
    vector<datatype>* ts = linspace<datatype>(0, 1, h);
    for (auto i = ts->begin(); i != ts->end(); i++) {
        output << *i << ",";
    }
    output << endl;
    vector<datatype>* result1 = Euler_method<datatype>(function, 1, 0, 1, h);
    for (auto i = result1->begin(); i != result1->end(); i++) {
        output << *i << ",";
    }
    output << endl;
    vector<datatype>* result2 = advanced_Euler_method<datatype>(function, 1, 0, 1, h);
    for (auto i = result2->begin(); i != result2->end(); i++) {
        output << *i << ",";
    }
    output << endl;
}
*/