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

    void solveForMinimization(std::vector<std::vector<double>> data, std::vector<double> objectives){
        int count = 0;

        // Add the constraints to the tableau
        for(int i = 0; i < data.size(); ++i){
            std::vector<double> tempData;
            // Push all variables into tempData
            for(int j = 0; j < data[0].size()-1; ++j){
                tempData.push_back(data[i][j]);
            }

            // push the stack variables to tempData
            for(int j = 0; j < data.size()+1; ++j){
                if(count == j){
                    tempData.push_back(1);
                }else{
                    tempData.push_back(0);
                }
            }

            // push the last value into tempData
            tempData.push_back(data[i][data[0].size()-1]);
            
            // push tempData into _vectorTableau
            _vectorTableau.push_back(tempData);

            // Increment count for stack variables
            ++count;
        }
        
        { // Add the objective function to the tableau
            std::vector<double> tempData;
            for(int i = 0; i < objectives.size(); ++i){
                tempData.push_back(objectives[i]*-1);
            }
            for(int i = 0; i < data.size()+1; ++i){
                if(count == i){
                    tempData.push_back(1);
                }else{
                    tempData.push_back(0);
                }
            }
            tempData.push_back(0);
            _vectorTableau.push_back(tempData);
        }
        printTableauVector();
        solveSimplex();
    }

    void solveForMinimization(std::vector<std::vector<double>> tableau){
        _vectorTableau = tableau;
        solveSimplex();
    }

public: // Getters

    std::vector<std::vector<double>> getTableau(){
        return _vectorTableau;
    }

    std::vector<double> getAnswers(){
        std::vector<double> answers;

        // check the columns of x1 and x2 if there is a value of one and put it in the answers
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(_vectorTableau[j][i] == 1){
                    answers.push_back(_vectorTableau[j][5]);
                }
            }
        }

        // push the last value of the objective function
        answers.push_back(_vectorTableau[2][5]);
        return answers;
    }

public: // Utility Functions
    void printAnswers(){
        std::vector<double> answers = getAnswers();
        std::cout << "x1 = " << answers[0] << std::endl;
        std::cout << "x2 = " << answers[1] << std::endl;
        std::cout << "P = " << answers[2] << std::endl;
    }

private: // Auxillary Functions

    void solveSimplex(){
        auto    noOfEquation        = _vectorTableau.size()-1;
        auto    noOfVariables       = _vectorTableau[0].size()-1;
        double  lowest              = 0; // lowest value in the objective function (no need for INT_MAX since we only need negative values)
        int     pivotColumn         = 0;

        // find the lowest value in the objective function
        for(int i = 0; i < noOfEquation+1; ++i){
            if(_vectorTableau[noOfEquation][i] < lowest){
                lowest              = _vectorTableau[noOfEquation][i];
                pivotColumn         = i;
            }
        }

        // if the lowest value is less than zero, then we need to pivot
        if(lowest < 0){
            lowest          = INT_MAX; //  lowest value in the column
            int pivotRow    = 0;

            // Find the lowest value in the column by getting the ratio of the last column and the pivot column 
            for(int i = 0; i < noOfEquation; ++i){
                double temp = _vectorTableau[i][noOfVariables] / _vectorTableau[i][pivotColumn];
                if(temp < lowest){
                    lowest = temp;
                    pivotRow = i;
                }
            }

            // Initialize the Pivot Formula
            double pivotFormula = 1/_vectorTableau[pivotRow][pivotColumn];

            // if the pivot value is negative, make the pivot formula negative
            if(_vectorTableau[pivotRow][pivotColumn] < 0){
                pivotFormula *= -1;
                return;
            }            

            // Multiply the pivot row by the pivot formula
            for(int i = 0; i < noOfVariables+1; ++i){
                _vectorTableau[pivotRow][i] *= pivotFormula;
            }

            // Identify pivot column formula
            for(int i = 0; i < noOfEquation+1; ++i){
                // if it's not in the pivot row
                if(i != pivotRow){
                    // Get the multiplier
                    double fDifference = _vectorTableau[i][pivotColumn];

                    // apply the formula to all the rows
                    for(int j = 0; j < noOfVariables+1; ++j){
                        _vectorTableau[i][j] = _vectorTableau[i][j]-(fDifference*_vectorTableau[pivotRow][j]);
                    }
                }
                printTableauVector();
            }
            printTableauVector();
            solveSimplex();
        }else{
            return;
        }
    }

private: // solving simplex

private: // others
    void printTableauVector(){
        std::cout << '[' << _printCount++ << "]\n";
        for(int i = 0; i < _vectorTableau.size(); ++i){
            for(int j = 0; j < _vectorTableau[i].size(); ++j){
                std::cout << std::setw(8) << _vectorTableau[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n";
    }

private: // Variables
    std::vector<std::vector<double>> _vectorTableau;
    int _printCount = 1;
};


#endif