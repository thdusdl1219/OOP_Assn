#ifndef LASERH
#define LASERH

#include "Unit.h"
class Cell;
class Laser : public Unit
{
    public:
        Laser (Cell* _cell); // 레이저를 초기화한다.
};
#endif
