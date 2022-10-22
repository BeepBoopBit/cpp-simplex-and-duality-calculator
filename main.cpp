#include "simplex.h"

int main(){
    SimplexMethod _calculator;
    double first[] = {0,1,10};
    double second[] = {2,5,60};
    double third[] = {3,1,44};
    // double objective[] = {5,4};
    std::vector<double*> constraints;
    constraints.push_back(first);
    constraints.push_back(second);
    constraints.push_back(third);
    std::vector<double> objective;
    objective.push_back(5);
    objective.push_back(4);
    _calculator.solveForMinimization(constraints, objective);
    return 0;
}