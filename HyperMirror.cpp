#include "HyperMirror.h"
#include <iostream>
using namespace std;
HyperMirror::HyperMirror(Cell* _cell, Board* b) : Mirror(_cell,b){}
int HyperMirror::Rotate()
{
	int check = 0;
	string choice;
	while(1)
	{
		enum Direction curdir = get_dir();
		cout << "Do you want it to Rotate?\n"; // 유닛을 회전시킬지 말지를 정한다.
		cout << "1. OK 2. Cancel\n";
		cout << ">> ";
		getline(cin,choice);
		if(choice.size() != 1)
		{
			cout << "[System] Please correct choice!\n";
			continue;
		}
		if(choice.at(0) == 49)
		{
			if(curdir == 1)
			{
				set_dir((enum Direction)(curdir + 1));
			}
			else
			{
				set_dir((enum Direction)(curdir - 1));
			}
			cout << endl;
			char tmprow = getrow() + 65;
			char tmpcol = getcol() + 49;
			cout << "[Log] Player"<< get_team() <<": " << tmprow << " " << tmpcol << " ROTATE\n";
			break;
		}
		else if(choice.at(0) == 50)
		{
			cout << "[System] Don't rotate!\n";
			check = 1;
			break;
		}
		else
		{
			cout << "[System] You should input 1 or 2\n";
			continue;
		}
	}
	return check;
}
