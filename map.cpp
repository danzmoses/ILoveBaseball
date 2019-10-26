#include "map.h"

Map::Map()
{
    this->used = 0;
    this->capacity = 1;
    this->stadiums = new Stadium[this->capacity];
    this->edges = new Edge*[this->capacity];
    this->edges[0] = new Edge[this->capacity];
}

void Map::expand()
{
    // double the capacity
    this->capacity *= 2;

    // initialize temporary variables to hold old data
    Stadium* temp_stadiums = new Stadium[this->capacity];
    int** temp_edges = new int*[this->capacity];
    for (int i = 0; i < used; ++i)
        temp_edges[i] = new int[this->capacity];

    // copy the data into the temp variables
    for (int i = 0; i < this->used; ++i)
    {
        temp_stadiums[i] = this->stadiums[i];
        for (int j = 0; j < this->used; ++j)
            temp_edges[i][j] = this->edges[i][j];
    }

    // deallocate the current arrays
    delete [] this->stadiums;
    for (int i = 0; i < this->used; ++i)
        delete [] this->edges[i];
    delete [] this->edges;

    // reinitialize the member variables
    this->stadiums = new Stadium[this->capacity];
    this->edges = new int*[this->capacity];
    for (int i = 0; i < this->capacity; ++i)
        this->edges[i] = new int[this->capacity];

    // copy the data from the temp variables
    for (int i = 0; i < this->used; ++i)
    {
        this->stadiums[i] = temp_stadiums[i];
        for (int j = 0; j < this->used; ++j)
            this->edges[i][j] = temp_edges[i][j];
    }

    // deallocate the temporary arrays
    delete [] temp_stadiums;
    for (int i = 0; i < this->used; ++i)
        delete [] temp_edges[i];
    delete [] temp_edges;
}