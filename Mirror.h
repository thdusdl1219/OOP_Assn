#ifndef MIRRORH
#define MIRRORH

#include "Unit.h"
class Cell;

class Mirror : public Unit
{
	public :
		Mirror (Cell* _cell, Board* b);
		virtual int control_unit();
		virtual void printUnit(char[18][18]) = 0;
		virtual Cell* beamCurUnit() = 0;	
};

#endif
