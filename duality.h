#ifndef DUALITY_H
#define DUALITY_H
#include "simplex.h"

class DualityMethod{
public:
    DualityMethod(){

    }

public:
    void solveForMaximization(std::vector<std::vector<double>> data, std::vector<double> objectives){
        int multiplier = 1, count = 0, objIndex = 0;
        for(int i = 0; i < data[0].size(); ++i){
            std::vector<double> tempData;
            for(int j = 0; j < data.size(); ++j){
                tempData.push_back(data[j][i]*multiplier);
            }
            auto tempSize = tempData.size() + 1;
            for(int j = 0; j < data.size()+tempSize; ++j){
                if(count == j){
                    tempData.push_back(1);
                }else{
                    tempData.push_back(0);
                }
            }
            if(objIndex < objectives.size()){
                tempData.push_back(objectives[objIndex++]);
            }else{
                tempData.push_back(0);
            }
            _vectorTableau.push_back(tempData);
            ++count;
            if(i == data[0].size()-2){
                multiplier = -1;
            }
        }

        printTableau();
        _simplex.solveForMinimization(_vectorTableau);
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