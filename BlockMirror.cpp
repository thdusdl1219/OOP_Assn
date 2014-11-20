#include "BlockMirror.h"
#include "Cell.h"
#include <iostream>
#include "Board.h"
using namespace std;
BlockMirror::BlockMirror(Cell* _cell, Board* b) : Mirror(_cell,b){}

void BlockMirror::printUnit(char status[18][18])
{
	if(get_team() == ONE)
	{
		switch(get_dir())
		{
			case UP:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '-';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'B';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '-';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'M';
				break;
			case DOWN:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'B';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '-';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'M';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '-';
				break;
			case LEFT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '|';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '|';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'B';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'M';
				break;
			case RIGHT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'B';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'M';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '|';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '|';
				break;	
		}
	}
	else
	{
		switch(get_dir())
		{
			case UP:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '-';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'b';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '-';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'm';
				break;
			case DOWN:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'b';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '-';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'm';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '-';
				break;
			case LEFT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '|';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '|';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'b';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'm';
				break;
			case RIGHT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'b';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'm';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '|';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '|';
				break;
		}
	}
}

Cell* BlockMirror::beamCurUnit()
{
	char tmprow = get_cell()->getrow() + 65;
	char tmpcol = get_cell()->getcol() + 49;
	Cell* result = NULL;
	switch(get_dir())
	{
		case UP:
			if(get_board()->getBeamdir() != DOWN)
			{
				if(get_board()->getattack())
				{
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				}
				else
					get_cell()->Stun();
				result = get_cell();
			}
			else
			{
				cout << "[System] BlockMirror blocked laser" << endl;
				get_board()->setBeamdir(UP);
				result = get_cell();
			}
			break;
		case DOWN:
			if(get_board()->getBeamdir() != UP)
			{
				if(get_board()->getattack())
				{
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				}
				else
					get_cell()->Stun();
				result = get_cell();
			}
			else
			{
				cout << "[System] BlockMirror blocked laser" << endl;
				get_board()->setBeamdir(DOWN);
				result = get_cell();
			}
			break;
		case LEFT:
			if(get_board()->getBeamdir() != RIGHT)
			{
				if(get_board()->getattack())
				{
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				}
				else
					get_cell()->Stun();
				result = get_cell();
			}
			else
			{
				cout << "[System] BlockMirror blocked laser" << endl;
				get_board()->setBeamdir(LEFT);
				result = get_cell();
			}
			break;
		case RIGHT:
			if(get_board()->getBeamdir() != LEFT)
			{
				if(get_board()->getattack())
				{
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				}
				else
					get_cell()->Stun();
				result = get_cell();
			}
			else
			{
				cout << "[System] BlockMirror blocked laser" << endl;
				get_board()->setBeamdir(RIGHT);
				result = get_cell();
			}
			break;
	}
	return result;
}	
