#include "Mirror.h"
#include <iostream>

using namespace std;

Mirror::Mirror(Cell* _cell, Board* b) : Unit(_cell, b) {}
int Mirror::control_unit()
{
	string choice;
	while(1)
	{
		cout << "What's your Command of this unit?\n";
		cout << "1. Move 2. Rotate\n";
		cout << ">> ";
		getline(cin,choice);
		if( choice.size() != 1 || (choice.at(0) != 49 && choice.at(0) != 50) )
		{
			cout << "[System] Please correct choice!\n";
			continue;
		}
		else if(choice.at(0) == 49)
		{
			UnitMove();
			return 0;
		}
		else
			return Rotate();
	}
}
