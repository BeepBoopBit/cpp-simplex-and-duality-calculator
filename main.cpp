#include "simplex.h"

int main(){
    SimplexMethod _calculator;
    int first[] = {1,2,3};
    int second[] = {3,2,1};
    int objective[] = {1,2};
    _calculator.solveForMinimization(first, second, objective);
}