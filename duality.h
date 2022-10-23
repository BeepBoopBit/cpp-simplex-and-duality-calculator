#ifndef DUALITY_H
#define DUALITY_H
#include "simplex.h"

class DualityMethod{
public:
    DualityMethod(){

    }

public:
    void solveForMaximization(std::vector<std::vector<double>> data, std::vector<double> objectives){
        data.push_back(objectives);
        int multiplier = 1, count = 0;

        for(int i = 0; i < data[0].size(); ++i){
            if(i == data[0].size()-1){
                multiplier = -1;
            }
            std::vector<double> tempData;
            for(int j = 0; j < data.size()-1; ++j){
                tempData.push_back(data[j][i]*multiplier);
            }
            for(int j = 0; j < data.size()-1; ++j){
                if(count == j){
                    tempData.push_back(1);
                }else{
                    tempData.push_back(0);
                }
            }

            if(i == data[0].size()-1){
                tempData.push_back(0);
            }else{
                tempData.push_back(data[data.size()-1][i]*multiplier);
            }
            _vectorTableau.push_back(tempData);
            ++count;
        }
        printTableau();
        _simplex.solveForMinimization(_vectorTableau);
        _simplex.printAnswers();
        _vectorTableau = _simplex.getTableau();
    }

private: // test
    void printTableau(){
        for(int i = 0; i < _vectorTableau.size(); ++i){
            for(int j = 0; j < _vectorTableau[i].size(); ++j){
                std::cout << std::setw(6) << _vectorTableau[i][j] << " | ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
private:
    std::vector<std::vector<double>> _vectorTableau;
    SimplexMethod _simplex;
};

#endif // DUALITY_H