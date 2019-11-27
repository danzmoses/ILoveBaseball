<<<<<<< HEAD
#include <string>
#include <vector>
using namespace std;

#ifndef STADIUM_H
#define STADIUM_H

struct Stadium
{
    string name;
    vector<string> teams;
    string address;
    string box_office_number;
    string date_opened;
    string seating_capacity;
    string league;

    Stadium() {}
    Stadium(string name,
            string team,
            string address,
            string box_office_number,
            string date_opened,
            string seating_capacity,
            string league)
    {
        this->name = name;
        this->teams.push_back(team);
        this->address = address;
        this->box_office_number = box_office_number;
        this->date_opened = date_opened;
        this->seating_capacity = seating_capacity;
        this->league = league;
    }

    void add_team(string team)
    {
        this->teams.push_back(team);
    }

    void remove_team(int index)
    {
        this->teams.erase(this->teams.begin() + index);
    }
};

#endif // STADIUM_H
=======
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
>>>>>>> 9bd10836bcb8c4a3e3e776121d1c4ea862696841
