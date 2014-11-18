#include "King.h"
#include <iostream>
using namespace std;
King::King(Cell* _cell) : Unit(_cell)
{
    enabled = true;
}

bool King::get_enable(){return enabled;}
void King::set_enable(bool en, enum Team kteam)
{
				enabled = en;
				cout << "[Laser] King of Player " << kteam << " is defeated." << endl;
}

