#include "TriMirror.h"
#include "Cell.h"

TriMirror::TriMirror(Cell* _cell, Board* b) : Mirror(_cell,b){}

void TriMirror::printUnit(char status[18][18])
{
	if(get_team() == ONE)
	{
		switch(get_dir())
		{
			case UP:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'T';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case LEFT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'T';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				break;
			case DOWN:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'T';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case RIGHT:
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'T';
				break;
		}
	}
	else
	{
		switch(get_dir())
		{
			case UP:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 't';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case LEFT:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 't';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				break;
			case DOWN:
				status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '\\';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 't';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '\\';
				break;
			case RIGHT:
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '/';
				status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '/';
				status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 't';
				break;
		}
	}
}
