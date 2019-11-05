#include "stadium.h"

string Stadium::get_name() const
{
    return name;
}

string Stadium::get_team() const
{
    return team;
}

string Stadium::get_league() const
{
    return league;
}

void Stadium::update_name(string new_name)
{
    name = new_name;
}

void Stadium::update_team(string new_team)
{
    team = new_team;
}

void Stadium::update_league(string new_league)
{
    league = new_league;
}