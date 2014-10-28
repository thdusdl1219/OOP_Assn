#ifndef ATTACKLASERH
#define ATTACKLASERH

#include "Laser.h"
class Cell;
class AttackLaser : public Laser
{
				public :
					AttackLaser(Cell* _cell);
};

#endif
