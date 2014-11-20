#include "StunLaser.h"
#include "Cell.h"

StunLaser::StunLaser(Cell* _cell,Board* b) : Laser(_cell,b ){}
void StunLaser::printUnit(char status[18][18])
{
	if(get_team() == ONE)
	{
		if((int)get_dir() == 1)
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'S';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '|';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'L';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '|';
		}	
		else
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '-';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '-';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'S';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'L';
		}
	}
	else
	{
		if((int)get_dir() == 1)
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '|';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 's';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '|';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'l';
		}
		else
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '-';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '-';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 's';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'l';
		}
	}
}
