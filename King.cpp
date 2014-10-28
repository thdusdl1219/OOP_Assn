#include "King.h"

King::King(Cell* _cell) : Unit(_cell)
{
    enabled = true;
}

bool King::get_enable(){return enabled;}
void King::set_enable(bool en){enabled = en;}
