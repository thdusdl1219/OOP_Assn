#include "BlockMirror.h"
#include "Cell.h"
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

