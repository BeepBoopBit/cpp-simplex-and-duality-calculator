#include "simplex.h"

int main(){
    SimplexMethod _calculator;
    double first[] = {3,5,78};
    double second[] = {4,1,36};
    double objective[] = {5,4};
    _calculator.solveForMinimization(first, second, objective);
    _calculator.printAnswers();
    return 0;
}