#include "BeamSplitter.h"
#include "Cell.h"
#include <iostream>
#include "Board.h"
using namespace std;

BeamSplitter::BeamSplitter(Cell* _cell, Board* b) : Mirror(_cell, b) {}

void BeamSplitter::printUnit(char status[18][18])
{
	if(get_team() == ONE)
	{
		switch(get_dir())
		{
			case UP:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'S';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case LEFT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'S';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				break;
			case DOWN:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'S';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case RIGHT:
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'S';
				break;
		}
	}
	else
	{
		switch(get_dir())
		{
			case UP:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 's';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case LEFT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 's';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				break;
			case DOWN:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 's';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case RIGHT:
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 's';
				break;
		}
	}
}


Cell* BeamSplitter::beamCurUnit()
{
	char tmprow = get_cell()->getrow() + 65;
	char tmpcol = get_cell()->getcol() + 49;
	Cell* result = NULL;
	Cell* remove = NULL;
	switch((int)get_dir())
	{
		case 1:
			if(get_board()->getBeamdir() == DOWN || get_board()->getBeamdir() == LEFT)
			{
				if(get_board()->getattack())
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				else
					get_cell()->Stun();
				result = get_cell();
			}
			else if(get_board()->getBeamdir() == UP)
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(LEFT); // 빔의 방향을 바꾼다. -> 반사시킨다.
			}
			else
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(DOWN);
			}
			break;
		case 2:
			if(get_board()->getBeamdir() == DOWN || get_board()->getBeamdir() == RIGHT)
			{
				result = get_cell();
				if(get_board()->getattack())
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				else
					get_cell()->Stun();
			}
			else if(get_board()->getBeamdir() == UP)
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(RIGHT);
			}
			else
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(DOWN);
			}
			break;
		case 3:
			if(get_board()->getBeamdir() == UP || get_board()->getBeamdir() == RIGHT)
			{
				result = get_cell();
				if(get_board()->getattack())
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				else
					get_cell()->Stun();
			}
			else if(get_board()->getBeamdir() == DOWN)
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(RIGHT);
			}
			else
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(UP);
			}
			break;
		case 4:
			if(get_board()->getBeamdir() == UP || get_board()->getBeamdir() == LEFT)
			{
				result = get_cell();
				if(get_board()->getattack())
					cout << "[System] Player "<< get_team() <<"'s Unit at ("<< tmprow <<" "<< tmpcol <<") is in destroyed." << endl;
				else
					get_cell()->Stun();
			}
			else if(get_board()->getBeamdir() == DOWN)
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(LEFT);
			}
			else
			{
				remove = get_board()->launchLaser(get_cell());
				if(remove != NULL && get_board()->getattack())
				{
					remove->setseam(true);
				}
				get_board()->setBeamdir(UP);
			}
			break;
	}
	return result;
}
