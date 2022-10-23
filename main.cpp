#include "duality.h"

int main(){
    SimplexMethod _calculator;
    double first[] = {0,1,10};
    double second[] = {2,5,60};
    double third[] = {3,1,44};
    std::vector<double*> data;
    data.push_back(first);
    data.push_back(second);
    data.push_back(third);
    std::vector<double> objective = {2,1};

    _calculator.solveForMinimization(data, objective);
    return 0;
}