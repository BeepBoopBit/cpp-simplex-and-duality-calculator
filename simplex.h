#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <iostream>
#include <iomanip>

class SimplexMethod{
public: // Constructor
    SimplexMethod(){

    }

public:
    void solveForMinimization(std::vector<double> first, std::vector<double> second, std::vector<double> objective){
        if((first.size() <= 0 && first.size() > 3 ) || ((second.size() <= 0 && second.size() > 3 ))){
            std::cout << "Error: The size of the vectors must be (0,2]" << std::endl;
            return;
        }
        initializeTableau(first[0], first[1], first[2], second[0], second[1], second[2], objective[0], objective[1]);
        solveSimplex();
    }

    void solveForMinimization(double first[3], double second[3], double objective[2]){
        initializeTableau(first[0], first[1], first[2], second[0], second[1], second[2], objective[0], objective[1]);
        solveSimplex();
    }


private: // Auxillary Functions

    void initializeTableau(double f1, double f2, double c1, double s1, double s2, double c2, double obj1, double obj2){
        _tableau[0][0] = f1;
        _tableau[0][1] = f2;
        _tableau[0][5] = c1;

        _tableau[1][0] = s1;
        _tableau[1][1] = s2;
        _tableau[1][5] = c2;

        _tableau[2][0] = obj1*-1;
        _tableau[2][1] = obj2*-1;

        printTableau();

    }

    void solveSimplex(){
        double lowest = 0;
        int pivotColumn = 0;
        bool isContainsNegative     = false;
        
        // Lowest -> lowest value in the objective function
        for(int i = 0; i < 6; ++i){
            if(_tableau[2][i] < lowest){
                lowest              = _tableau[2][i];
                isContainsNegative  = true;
                pivotColumn         = i;
            }
        }

        if(isContainsNegative){
            lowest          = INT_MAX; // Lowest -> lowest value in the column
            int pivotRow    = 0;

            // Find the lowest value in the column 
            for(int i = 0; i < 2; ++i){
                double temp = _tableau[i][5] / _tableau[i][pivotColumn];
                if(temp < lowest){
                    lowest = temp;
                    pivotRow = i;
                }
            }

            // Initialize the Pivot Formula
            double pivotFormula = 1/_tableau[pivotRow][pivotColumn];

            // if the pivot value is negative, make the pivot formula negative
            if(_tableau[pivotRow][pivotColumn] < 0){
                pivotFormula *= -1;
                return;
            }            

            // Multiply the pivot row by the pivot formula
            for(int i = 0; i < 6; ++i){
                _tableau[pivotRow][i] *= pivotFormula;
            }


            // Identify pivot column formula
            double fDifference = 0,
                   sDifference = 0;
            bool isSDifference = true;
            for(int i = 0; i < 3; ++i){
                if(i != pivotRow){
                    if(isSDifference){
                        fDifference = _tableau[i][pivotColumn];
                        _tableau[i][pivotColumn] = _tableau[i][pivotColumn]-(fDifference*_tableau[pivotRow][pivotColumn]);
                        for(int j = 0; j < 6; ++j){
                            if(j == pivotColumn){
                                ++j;
                            }
                            _tableau[i][j] = _tableau[i][j]-(fDifference*_tableau[pivotRow][j]);
                        }
                    }else{
                        sDifference = _tableau[i][pivotColumn];
                        _tableau[i][pivotColumn] = _tableau[i][pivotColumn]-(sDifference*_tableau[pivotRow][pivotColumn]);
                        for(int j = 0; j < 6; ++j){
                            if(j == pivotColumn){
                                ++j;
                            }
                            _tableau[i][j] = _tableau[i][j]-(sDifference*_tableau[pivotRow][j]);
                        }
                    }
                    isSDifference = !isSDifference;
                }
            }
            printTableau();
            solveSimplex();
        }else{
            return;
        }
    }

private: // solving simplex

private: // others
    void printTableau(){
        std::cout << '[' << _printCount++ << "]\n";
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 6; ++j){
                std::cout << std::setw(5) << _tableau[i][j] << "|";
            }
            std::cout << "\n-------------------------------------\n";
        }
        std::cout << "\n";
    }

private: // Variables
    double _tableau[3][6]{
        {0, 0, 1.0, 0, 0, 0},
        {0, 0, 0, 1.0, 0, 0},
        {0, 0, 0, 0, 1.0, 0}
    };
    int _printCount = 1;
};


#endif