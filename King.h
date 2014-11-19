#ifndef KINGH
#define KINGH

#include "Unit.h"
class Cell;

class King : public Unit
{
    private:
        bool enabled;
    public:
        King (Cell* _cell, Board* b); // 왕을 초기화한다.
        virtual bool get_enable();
        virtual void set_enable(bool);
				virtual int control_unit();
};

#endif
