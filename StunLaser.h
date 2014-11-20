#ifndef STUNLASERH
#define STUNLASERH

#include "Laser.h"

class Cell;
class StunLaser : public Laser
{
				public :
					StunLaser(Cell* _cell, Board* b);
					virtual void printUnit(char[18][18]);
};

#endif
