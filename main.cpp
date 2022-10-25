#include "duality.h"

void problemSet01(){
    SimplexMethod _calculator;
    std::vector<double> first = {0,1,10};
    std::vector<double> second = {2,5,60};
    std::vector<double> third = {3,1,44};
    std::vector<double> objective = {2,1};

    std::vector<std::vector<double>> data;
    data.push_back(first);
    data.push_back(second);
    data.push_back(third);

    _calculator.solveForMinimization(data, objective);
}

void problemSet02(){
    DualityMethod _calculator;
    std::vector<double> first = {3,8,0,30};
    std::vector<double> second = {5,1,5,40};
    std::vector<double> objective = {150,20,300};

    std::vector<std::vector<double>> data;
    data.push_back(first);
    data.push_back(second);

    _calculator.solveForMaximization(data, objective);
}

void testing00(){
    DualityMethod _calculator;
    std::vector<double> first = {1,2,4};
    std::vector<double> second = {7,6,20};
    std::vector<double> objective = {14,20};

    std::vector<std::vector<double>> data;
    data.push_back(first);
    data.push_back(second);

    _calculator.solveForMaximization(data, objective);
}


int main(){
    problemSet02();
    return 0;
}