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
