#include "BeamSplitter.h"
#include "Cell.h"
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
