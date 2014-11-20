#include "King.h"
#include <iostream>
#include "Cell.h"
#include "Board.h"
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

void King::printUnit(char status[18][18])
{
	if(get_team()  == ONE)
	{
		status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'K';
		status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'K';
		status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'K';
		status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'K';
	}
	else
	{
		status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'k';
		status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'k';
		status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'k';
		status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'k';
	}
}

Cell* King::beamCurUnit()
{
	if(get_board()->getattack())
		set_enable(false);
	else
		get_cell()->Stun();
	
	return get_cell();
}
