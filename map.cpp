#include "map.h"

/************************************************************
 * Constructor Map(): Class Map
 * _________________________________________________________
 *  This method is the constructor for the Map class.
 *  Constructs an empty map.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      None
 *
 *  POST-CONDITIONS
 *      Constructs default map.
 ***********************************************************/
Map::Map()
{
    // OUTPUT: initialize a map with max capacity of 1
    this->used = 0;
    this->capacity = 1;
    this->stadiums = new Stadium[this->capacity];
    this->edges = new int*[this->capacity];
    this->edges[0] = new int[this->capacity];
}

/************************************************************
 * Deconstructor ~Map(): Class Map
 * _________________________________________________________
 *  This method is the deconstructor for the Map class.
 *  It deallocates reserved memory for the map.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      None
 *
 *  POST-CONDITIONS
 *      Deallocates reserved memory.
 ***********************************************************/
Map::~Map()
{
    delete [] this->stadiums;
    for (unsigned int i = 0; i < this->capacity; ++i)
        delete [] this->edges[i];
    delete [] this->edges;
}

/************************************************************
 * Mutator expand(): Class Map
 * _________________________________________________________
 *  This method increases the maximum capacity for the map.
 *  It does so by deallocating the old arrays, doubling the
 *  capacity, and reinitializing the arrays.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      None
 *
 *  POST-CONDITIONS
 *      Expands max capacity for the map.
 ***********************************************************/
void Map::expand()
{
    // OUTPUT: initialize temp variables to hold old data
    Stadium temp_stadiums[this->used];
    int temp_edges[this->used][this->used];

    // copy data into temp variables
    for (unsigned int i = 0; i < this->used; ++i)
    {
        temp_stadiums[i] = this->stadiums[i];
        for (unsigned int j = 0; j < this->used; ++j)
            temp_edges[i][j] = this->edges[i][j];
    }

    // OUTPUT: deallocate the current arrays
    delete [] this->stadiums;
    for (unsigned int i = 0; i < this->capacity; ++i)
        delete [] this->edges[i];
    delete [] this->edges;

    // OUTPUT: double the capacity
    this->capacity *= 2;

    // reinitialize the member variables
    this->stadiums = new Stadium[this->capacity];
    this->edges = new int*[this->capacity];
    for (unsigned int i = 0; i < this->capacity; ++i)
        this->edges[i] = new int[this->capacity];

    // OUTPUT: copy the data from the temp variables
    for (unsigned int i = 0; i < this->used; ++i)
    {
        this->stadiums[i] = temp_stadiums[i];
        for (unsigned int j = 0; j < this->used; ++j)
            this->edges[i][j] = temp_edges[i][j];
    }
}

/************************************************************
 * Mutator add_stadium(Stadium stadium): Class Map
 * _________________________________________________________
 *  This method adds a given stadium to the map.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      stadium: stadium to add
 *
 *  POST-CONDITIONS
 *      Adds stadium to map
 ***********************************************************/
void Map::add_stadium(Stadium stadium)  // IN: stadium to add
{
    // OUTPUT: expand if needed
    if (this->used + 1 == this->capacity)
        this->expand();

    // OUTPUT: add the stadium to the next available position
    this->stadiums[this->used] = stadium;
    ++this->used;
}

/************************************************************
 * Accessor get_stadium(string name): Class Map
 * _________________________________________________________
 *  Given a stadium name, returns the Stadium object that
 *  corresponds to the name
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      name: name of stadium
 *
 *  POST-CONDITIONS
 *      Returns stadium with given name
 ***********************************************************/
Stadium* Map::get_stadium(string name)  // IN: name of stadium
{
    // OUTPUT: attempt to find the stadium and return it
    for (unsigned int i = 0; i < this->used; ++i)
    {
        Stadium* temp = &this->stadiums[i];
        if (temp->name == name)
            return temp;
    }
    return nullptr;
}

/************************************************************
 * Accessor get_index(string name): Class Map
 * _________________________________________________________
 *  This method returns the index of a stadium given its name.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      name: name of stadium
 *
 *  POST-CONDITIONS
 *      Returns index of stadium
 ***********************************************************/
int Map::get_index(string name) // IN: name of stadium
{
    // OUTPUT: search for and return the stadium's index
    for (unsigned int i = 0; i < this->used; ++i)
        if (this->stadiums[i].name == name)
            return i;
    return -1;
}

/************************************************************
 * Accessor get_stadiums(): Class Map
 * _________________________________________________________
 *  This method returns a list of stadiums in the form of a
 *  vector.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      None
 *
 *  POST-CONDITIONS
 *      Returns stadiums in a vector
 ***********************************************************/
vector<Stadium> Map::get_stadiums()
{
    // OUTPUT: push all stadium objects into a vector
    vector<Stadium> temp;
    for (unsigned int i = 0; i < this->used; ++i)
        temp.push_back(this->stadiums[i]);
    return temp;
}

/************************************************************
 * Mutator load_stadiums(string file): Class Map
 * _________________________________________________________
 *  This method loads stadiums from a given file
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      file: file name
 *
 *  POST-CONDITIONS
 *      Loads stadiums from file into map
 ***********************************************************/
void Map::load_stadiums(string file)
{
    ifstream in_file;               // IN: ifstream variable

    // OUTPUT: try to open the file
    in_file.open(file);
    if (!in_file)
    {
        cout << "ERROR: stadiums file not opened" << endl;
        exit(0);
    }

    string name;                        // IN: name of stadium
    string team;                        // IN: name of team
    string address1;                    // IN: address part 1
    string address2;                    // IN: address part 2
    string box_office_number;           // IN: box office number
    string date_opened;                 // IN: date opened
    string seating_capacity;            // IN: seating capacity
    string league;

    getline(in_file, league);
    // OUTPUT: read stadium information until end of file
    while (getline(in_file, name))
    {
        // OUTPUT: expand array if needed
        if (this->used + 1 == this->capacity)
            this->expand();

        getline(in_file, team);
        getline(in_file, address1);
        getline(in_file, address2);
        getline(in_file, box_office_number);
        getline(in_file, date_opened);
        getline(in_file, seating_capacity);
        in_file.get();                      // grab and remove new line


        // OUTPUT: add stadium to the last spot of the array
        this->stadiums[this->used] =
            Stadium(name, team, address1 + ", " + address2,
                    box_office_number, date_opened, seating_capacity,
                    league);
        // OUTPUT: increase size of array
        ++this->used;
    }

    // OUTPUT: close the file when done
    in_file.close();
}

/************************************************************
 * Mutator load_edges(string file): Class Map
 * _________________________________________________________
 *  This method loads the edges from a given file
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      file: file name
 *
 *  POST-CONDITIONS
 *      Loads edges from a file
 ***********************************************************/
void Map::load_edges(string file)   // IN: file name
{
    ifstream in_file;               // IN: ifstream variable

    // OUTPUT: try to open the file
    in_file.open(file);
    if (!in_file)
    {
        cout << "ERROR: edges.prn not opened" << endl;
        exit(0);
    }

    int distance;                   // IN: direct edge

    // OUTPUT: set each edge from the file
    for (unsigned int i = 0; i < this->used; ++i)
    {
        for (unsigned int j = 0; j < this->used; ++j)
        {
            in_file >> distance;
            this->edges[i][j] = distance;
        }
    }
    in_file.close();
}

vector<int> Map::dijkstra(string start)
{
    int origin = this->get_index(start);      // IN: starting city's index

    bool visited[this->used];       // S - set of visited nodes
    vector<int> previous;           // P - previous positions
    int distances[this->used];      // C - actual distances

    // OUTPUT: set all nodes except the origin to unvisited
    //         set the origin's distance to 0 and all other nodes to INT_MAX
    //         set all nodes' previous values to 0
    for (unsigned int i = 0; i < this->used; ++i)
    {
        if (i == origin)
            distances[i] = 0;
        else
            distances[i] = INT_MAX;
        visited[i] = false;
        previous.push_back(0);
    }

    // OUTPUT: loop until all of the nodes have been visited
    int count = 0;
    while (count != this->used)
    {
        // OUTPUT: find the node with smallest C[K] and add it to S
        int min_index = smallest_unvisited_adjacent_edge(distances, visited);
        visited[min_index] = true;

        // OUTPUT: iterate through the cities and update the distances/previous values for all neighbors of K not in S
        for (unsigned int i = 0; i < this->used; ++i)
        {
            // OUTPUT: if J is not visited and the edge is defined, check the distance from origin to J
            if (!visited[i] && this->edges[min_index][i] > 0)
            {
                // OUTPUT: the new distance is the distance from origin to K + the edge of J and K
                //         if it is smaller than J's current distance, update the distance and previous node of J
                int new_distance = distances[min_index] + this->edges[min_index][i];
                if (new_distance < distances[i])
                {
                    distances[i] = new_distance;
                    previous[i] = min_index;
                }
            }
        }
        // OUTPUT: increment the counter (size of S)
        ++count;
    }

    // OUTPUT: return the array of previous paths
    previous[origin] = -1;
    return previous;
}

vector<int> Map::dijkstra(int start)
{
    int origin = start;      // IN: starting city's index

    bool visited[this->used];       // S - set of visited nodes
    vector<int> previous;           // P - previous positions
    int distances[this->used];      // C - actual distances

    // OUTPUT: set all nodes except the origin to unvisited
    //         set the origin's distance to 0 and all other nodes to INT_MAX
    //         set all nodes' previous values to 0
    for (unsigned int i = 0; i < this->used; ++i)
    {
        if (i == origin)
            distances[i] = 0;
        else
            distances[i] = INT_MAX;
        visited[i] = false;
        previous.push_back(0);
    }

    // OUTPUT: loop until all of the nodes have been visited
    int count = 0;
    while (count != this->used)
    {
        // OUTPUT: find the node with smallest C[K] and add it to S
        int min_index = smallest_unvisited_adjacent_edge(distances, visited);
        visited[min_index] = true;

        // OUTPUT: iterate through the cities and update the distances/previous values for all neighbors of K not in S
        for (unsigned int i = 0; i < this->used; ++i)
        {
            // OUTPUT: if J is not visited and the edge is defined, check the distance from origin to J
            if (!visited[i] && this->edges[min_index][i] > 0)
            {
                // OUTPUT: the new distance is the distance from origin to K + the edge of J and K
                //         if it is smaller than J's current distance, update the distance and previous node of J
                int new_distance = distances[min_index] + this->edges[min_index][i];
                if (new_distance < distances[i])
                {
                    distances[i] = new_distance;
                    previous[i] = min_index;
                }
            }
        }
        // OUTPUT: increment the counter (size of S)
        ++count;
    }

    // OUTPUT: return the array of previous paths
    previous[origin] = -1;
    return previous;
}

vector<int> Map::shortest_path_from_origin_to_wanted_stadium(int origin, const vector<int> &paths, const set<int> &wanted)
{
    int min_distance = INT_MAX;
    int min_index;
    for (set<int>::iterator it = wanted.begin(); it != wanted.end(); ++it)
    {
        int temp_index = *it;
        int temp_distance = 0;
        while (paths[temp_index] != origin)
        {
            temp_distance += this->edges[temp_index][paths[temp_index]];
            temp_index = paths[temp_index];
        }
        temp_distance += this->edges[temp_index][paths[temp_index]];

        if (min_distance > temp_distance)
        {
            min_distance = temp_distance;
            min_index = *it;
        }
    }
    cout << "MIN DISTANCE: " << min_distance << endl;
    vector<int> shortest_path;
    int temp = min_index;
    while (paths[temp] != origin)
    {
        shortest_path.push_back(temp);
        temp = paths[temp];
    }
    shortest_path.push_back(temp);
    std::reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

int Map::smallest_unvisited_adjacent_edge(int distances[], bool visited[])
{
    int min_index;                              // IN: index of node with smallest distance to origin
    int min_distance;                           // IN: value of smallest distance to origin

    // OUTPUT: first, find an unvisited node with a defined distance
    //         set the min index and min distance with that node
    int first_index = 0;
    while (visited[first_index])
        ++first_index;
    min_index = first_index;
    min_distance = distances[first_index];

    // OUTPUT: then, iterate through the cities starting at the found index
    for (unsigned int i = first_index; i < this->used; ++i)
    {
        // OUTPUT: if the distance is defined and the distance from the current node to origin is smaller
        //         than min_distance, update min index and min distance
        if (!visited[i] && distances[i] < min_distance)
        {
            min_index = i;
            min_distance = distances[i];
        }
    }

    // OUTPUT: finally, return the minimum index of the node will smallest distance to origin
    return min_index;
}

vector<int> Map::trip(string start, set<int>& wanted_stadiums)
{
    string stadium_name = start;
    int stadium_index = this->get_index(stadium_name);
    vector<int> paths;
    vector<int> shortest_path;
    vector<int> final_path;

    wanted_stadiums.erase(stadium_index);

    final_path.push_back(stadium_index);
    do
    {
        // get all paths from origin using dijkstra
        paths = this->dijkstra(stadium_name);
        cout << "DIJKSTRA" << endl;
        // of all paths, get the path of least weight
        shortest_path = this->shortest_path_from_origin_to_wanted_stadium(stadium_index, paths, wanted_stadiums);
        cout << "SHORTEST: " << this->get_path(shortest_path) << endl;
        // in the shortest path, remove all wanted stadiums included in the path
        // push the path to the final path
        for (unsigned int i = 0; i < shortest_path.size(); ++i)
        {
            if (wanted_stadiums.find(shortest_path[i]) != wanted_stadiums.end())
                wanted_stadiums.erase(shortest_path[i]);
            final_path.push_back(shortest_path[i]);
        }

        // set the new stadium name to be the latest stadium visited
        stadium_name = this->stadiums[final_path[final_path.size() - 1]].name;
        stadium_index = final_path[final_path.size() - 1];
    } while(!wanted_stadiums.empty());
    return final_path;
}




// GIVEN A PATH IN THE RIGHT ORDER, RETURN IT AS A STRING
string Map::get_path(vector<int> path)
{
    string temp;
    for (unsigned int i = 0; i < path.size(); ++i)
    {
        if (i + 1 >= path.size())
            temp += this->stadiums[path[i]].name;
        else
            temp += this->stadiums[path[i]].name + " -> ";
    }
    return temp;
}

// GIVEN A PATH IN THE RIGHT ORDER, RETURN THE TOTAL DISTANCE
int Map::total_distance(vector<int> path)
{
    int total = 0;
    for (unsigned int i = 0; i + 1 < path.size(); ++i)
        total += this->edges[path[i]][path[i + 1]];
    return total;
}






























