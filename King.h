#ifndef KINGH
#define KINGH

#include "Unit.h"
class Cell;

class King : public Unit
{
    private:
        bool enabled;
    public:
        King (Cell* _cell); // 왕을 초기화한다.
        bool get_enable();
        void set_enable(bool en);
};

#endif
