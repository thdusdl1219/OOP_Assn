#include "King.h"
#include <iostream>
using namespace std;
King::King(Cell* _cell, Board* b) : Unit(_cell,b)
{
    enabled = true;
}

bool King::get_enable(){return enabled;}
void King::set_enable(bool en)
{
				enabled = en;
				cout << "[Laser] King of Player " << get_team() << " is defeated." << endl;
}
int King::control_unit()
{
	string choice;
	while(1)
	{
		cout << "What's your Command of this unit?\n"; // 유닛을 어떻게 컨트롤할지 결정한다.
		cout << "1. Move\n";
		cout << ">> ";
		getline(cin,choice);
		cout << "\n";
		if(choice.size() != 1||choice.at(0) != 49 )
		{
			cout << "[System] Please correct choice!\n";
			continue;
		}
		else
		{
			UnitMove();
			return 0;
		}
	}
}
