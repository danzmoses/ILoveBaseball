#ifndef MAP_H
#define MAP_H

#include "stadium.h"
#include <iostream>
using namespace std;

class Map
{
    private:
        Stadium* stadiums;      // array of stadiums
        int** edges;            // 2D-array of links between stadiums (indices correspond to array of stadiums, value is the weight between two stadiums)
        int used;               // number of stadiums
        int capacity;           // capacity of arrays

    public:
        Map();
        void expand();
};

#endif // MAP_H