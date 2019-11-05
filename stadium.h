#ifndef STADIUM_H_
#define STADIUM_H

#include <iostream>
#include <string>
using namespace std;

class Stadium
{
    private:
        string name;
        string team;
        string league;
    public:
        explicit Stadium(string name): name(name), team(""), league("") {}
        Stadium(): name(""), team(""), league("") {}
        string get_name()const;
        string get_team()const;
        string get_league()const;
        void update_name(string new_name);
        void update_team(string new_team);
        void update_league(string new_league);
};

#endif  // STADIUM_H_
