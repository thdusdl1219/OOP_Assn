#include "AttackLaser.h"
#include "Cell.h"
AttackLaser::AttackLaser(Cell* _cell, Board* b) : Laser(_cell, b){}
void AttackLaser::printUnit(char status[18][18])
{
	if(get_team() == ONE)
	{
		if((int)get_dir() == 1)
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'A';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = '|';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = 'L';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '|';
		}
		else
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'A';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'L';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '-';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '-';
		}
	}
	else
	{
		if((int)get_dir() == 1)
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = '|';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'a';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '|';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = 'l';
		}
		else
		{
			status[get_cell()->getrow()*2][get_cell()->getcol()*2] = 'a';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2] = 'l';
			status[get_cell()->getrow()*2][get_cell()->getcol()*2+1] = '-';
			status[get_cell()->getrow()*2+1][get_cell()->getcol()*2+1] = '-';
		}
	}
}
