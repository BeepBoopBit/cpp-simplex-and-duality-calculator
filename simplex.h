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
        // Check for the size of the vectors
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

    void solveForMinimization(std::vector<double*> constraints, std::vector<double> objective){
        // Check for the size of the vectors
        if((objective.size() <= 0 && objective.size() > 3 )){
            std::cout << "Error: The size of the vectors must be (0,2]" << std::endl;
            return;
        }

        // push all the contents to the _vectorTableau
        int pushCount = 0;
        for(int i = 0; i < constraints.size(); i++){
            std::vector<double> tempData;
            for(int j = 0; j < 2; ++j){
                tempData.push_back(constraints[i][j]);
            }
            for(int j = 0; j < constraints.size()+1; ++j){
                if(j == pushCount){
                    tempData.push_back(1);
                }else{
                    tempData.push_back(0);
                }
            }
            tempData.push_back(constraints[i][2]);
            _vectorTableau.push_back(tempData);
            ++pushCount;
        }

        // push the objective function to the _vectorTableau
        {
            std::vector<double> tempData;
            for(int i = 0; i < objective.size(); ++i){
                tempData.push_back(-1*objective[i]);
            }
            for(int j = 0; j < constraints.size()+2; ++j){
                if(j == pushCount){
                    tempData.push_back(1);
                }else{
                    tempData.push_back(0);
                }
            }
            _vectorTableau.push_back(tempData);
        }

        // Testing
        printTableauVector();
        solveSimplexVector();
    }

    void solveForMinimization(std::vector<std::vector<double>> tableau){
        _vectorTableau = tableau;
        solveSimplexVector();
    }

    std::vector<std::vector<double>> getTableau(){
        return _vectorTableau;
    }

    std::vector<double> getAnswers(){
        std::vector<double> answers;

        // check the columns of x1 and x2 if there is a value of one and put it in the answers
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(_tableau[j][i] == 1){
                    answers.push_back(_tableau[j][5]);
                }
            }
        }

        // push the last value of the objective function
        answers.push_back(_tableau[2][5]);
        return answers;
    }

    void printAnswers(){
        std::vector<double> answers = getAnswers();
        std::cout << "x1 = " << answers[0] << std::endl;
        std::cout << "x2 = " << answers[1] << std::endl;
        std::cout << "P = " << answers[2] << std::endl;
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
        double  lowest              = 0; // lowest value in the objective function
        int     pivotColumn         = 0;
        bool    isContainsNegative  = false;
        
        for(int i = 0; i < 6; ++i){
            if(_tableau[2][i] < lowest){
                lowest              = _tableau[2][i];
                isContainsNegative  = true;
                pivotColumn         = i;
            }
        }

        if(isContainsNegative){
            lowest          = INT_MAX; //  lowest value in the column
            int pivotRow    = 0;

            // Find the lowest value in the column by getting the ratio of the last column and the pivot column 
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

            double fDifference      = 0, // difference for the first relative row
                   sDifference      = 0; // difference for the second relative row
            bool   isFDifference    = true; // flag for the second difference

            // Identify pivot column formula
            for(int i = 0; i < 3; ++i){
                // if it's not in the pivot row
                if(i != pivotRow){
                    // check if it's the first difference
                    if(isFDifference){
                        // get the value of the pivot column relative to the current row
                        fDifference = _tableau[i][pivotColumn];
                        
                        // apply the formula using the fDifference
                        _tableau[i][pivotColumn] = _tableau[i][pivotColumn]-(fDifference*_tableau[pivotRow][pivotColumn]);

                        // apply the formula to all the rows
                        for(int j = 0; j < 6; ++j){
                            if(j == pivotColumn){
                                ++j;
                            }
                            _tableau[i][j] = _tableau[i][j]-(fDifference*_tableau[pivotRow][j]);
                        }
                    }else{
                        // get the value of the pivot column relative to the current row
                        sDifference = _tableau[i][pivotColumn];

                        // apply the formula using the fDifference
                        _tableau[i][pivotColumn] = _tableau[i][pivotColumn]-(sDifference*_tableau[pivotRow][pivotColumn]);

                        // apply the formula to all the rows
                        for(int j = 0; j < 6; ++j){
                            if(j == pivotColumn){
                                ++j;
                            }
                            _tableau[i][j] = _tableau[i][j]-(sDifference*_tableau[pivotRow][j]);
                        }
                    }
                    isFDifference = !isFDifference;
                }
            }
            printTableau();
            solveSimplex();
        }else{
            return;
        }
    }

    void solveSimplexVector(){
        double  lowest      = INT_MAX;
        int     pivotColumn = 0;
        auto    columnCount    = _vectorTableau[0].size(),
                rowCount = _vectorTableau.size();
        
        for(int i = 0; i < columnCount; ++i){
            double value = _vectorTableau[rowCount-1][i]; 
            if(value < lowest){
                lowest = value;
                pivotColumn = i;
            }
        }

        if(lowest >= 0){
            return;
        }
        lowest = INT_MAX;
        int pivotRow = 0;
        for(int i = 0 ; i < rowCount-1; ++i){
            double value = _vectorTableau[i][columnCount-1]/_vectorTableau[i][pivotColumn];
            if(value > 0 && value < lowest){
                lowest = value;
                pivotRow = i;
            }
        }

        double pivotFormula = 1/_vectorTableau[pivotRow][pivotColumn];

        for(int i = 0; i < columnCount; ++i){
            _vectorTableau[pivotRow][i] *= pivotFormula;
        }

        for(int i = 0; i < rowCount; ++i){
            if(i == pivotRow){
                ++i;
            }
            double difference = _vectorTableau[i][pivotColumn];
            for(int j = 0; j < columnCount; ++j){
                _vectorTableau[i][j] = _vectorTableau[i][j]-(difference*_vectorTableau[pivotRow][j]);
            }
            printTableauVector();
        }
        solveSimplexVector();
        printTableauVector();
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
    void printTableauVector(){
        std::cout << '[' << _printCount++ << "]\n";
        for(int i = 0; i < _vectorTableau.size(); ++i){
            for(int j = 0; j < _vectorTableau[i].size(); ++j){
                std::cout << std::setw(6) << _vectorTableau[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n";
    }

private: // Variables
    double _tableau[3][6]{
        {0, 0, 1.0, 0, 0, 0},
        {0, 0, 0, 1.0, 0, 0},
        {0, 0, 0, 0, 1.0, 0}
    };
    std::vector<std::vector<double>> _vectorTableau;
    int _printCount = 1;
};


#endif