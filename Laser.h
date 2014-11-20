#ifndef LASERH
#define LASERH

#include "Unit.h"
class Laser : public Unit
{
    public:
        Laser (Cell* _cell, Board* b); // 레이저를 초기화한다.
				virtual int control_unit();
				virtual int Rotate();
				virtual void printUnit(char[18][18]) = 0;
				virtual Cell* beamCurUnit(){return 0;}	
};
#endif
