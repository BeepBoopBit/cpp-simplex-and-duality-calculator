#include "duality.h"

int main(){
    SimplexMethod _calculator;
    std::vector<double> first = {3,5,78};
    std::vector<double> second = {4,1,36};

    std::vector<std::vector<double>> data;
    data.push_back(first);
    data.push_back(second);

    std::vector<double> objective = {5,4};

    _calculator.solveForMinimization(data, objective);
    return 0;
}