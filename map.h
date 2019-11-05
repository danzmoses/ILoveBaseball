#ifndef MAP_H_
#define MAP_H_

#include "stadium.h"
#include <iostream>
#include <string>
#include <vector>

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
        ~Map();
        void expand();
        void add_stadiums(string name, vector<string>connected_stadiums, vector<int>edges);
};

#endif  // MAP_H_