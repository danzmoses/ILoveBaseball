#include "stadium.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map
{
    private:
        Stadium* stadiums;               // IN: array of stadiums
        int** edges;                     // IN: 2D-array of links between stadiums (indices correspond to array of stadiums, value is the weight between two stadiums)
        unsigned int used;               // IN: number of stadiums
        unsigned int capacity;           // IN: capacity of arrays

    public:
        Map();
        ~Map();
        void expand();
        void add_stadiums(string name, vector<string>connected_stadiums, vector<int>edges);

        void add_stadium(Stadium stadium);

        Stadium* get_stadium(string name);
        Stadium* get_stadium(int index) { return &this->stadiums[index]; }
        int get_index(string name);

        vector<Stadium> get_stadiums();

        bool has_adjacent_edge(int stadium1, int stadium2);

        vector<int> trip(string start, set<int>& wanted_stadiums);
        vector<int> dijkstra(string start);
        vector<int> dijkstra(int start);
        vector<int> shortest_path_from_origin_to_wanted_stadium(int origin, const vector<int>& paths, const set<int>& wanted);
        int smallest_unvisited_adjacent_edge(int distances[], bool visited[]);

        string get_path(vector<int> path);
        int total_distance(vector<int> path);

        void load_stadiums(string file);
        void load_edges(string file);
};
#endif // MAP_H

