#ifndef MIRRORH
#define MIRRORH

#include "Unit.h"
class Cell;

class Mirror : public Unit
{
	public :
		Mirror (Cell* _cell, Board* b);
		virtual int control_unit();
};

#endif
