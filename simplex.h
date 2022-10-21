#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <iostream>

class SimplexMethod{
public: // Constructor
    SimplexMethod(){

    }

public:
    void solveForMinimization(std::vector<int> first, std::vector<int> second, std::vector<int> objective){
        if((first.size() <= 0 && first.size() > 3 ) || ((second.size() <= 0 && second.size() > 3 ))){
            std::cout << "Error: The size of the vectors must be (0,2]" << std::endl;
            return;
        }
        initializeTableau(first[0], first[1], first[2], second[0], second[1], second[2], objective[0], objective[1]);
        
    }

    void solveForMinization(int *first, int *second, int *objective){
        initializeTableau(first[0], first[1], first[2], second[0], second[1], second[2], objective[0], objective[1]);
    }


private: // Auxillary Functions

    void initializeTableau(int f1, int f2, int c1, int s1, int s2, int c2, int obj1, int obj2){
        _tableau[0][0] = f1;
        _tableau[0][1] = f2;
        _tableau[0][5] = c1;

        _tableau[1][0] = s1;
        _tableau[1][1] = s2;
        _tableau[1][5] = c2;

        _tableau[2][0] = obj1;
        _tableau[2][1] = obj2;
    }

private: // Variables
    int _tableau[3][6]{
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0}
    };
};


#endif