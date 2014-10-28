#include "Unit.h"

Unit::Unit(Cell* _cell)
{
				dir = UP;
				cell = _cell;
				team = ONE;
				stun = false;
				stunturn = 0;
}

enum Direction Unit::get_dir(){return dir;}
void Unit::set_dir(enum Direction dirr){dir = dirr;}
enum Team Unit::get_team(){return team;}
void Unit::set_team(enum Team yourteam){team = yourteam;}
bool Unit::getstun(){return stun;}
void Unit::setstun(bool _st){stun = _st;}
int Unit::getturn(){return stunturn;}
int Unit::incturn(){return stunturn++;}
void Unit::setturn(int _t){stunturn = _t;} 
//Cell* Unit::get_cell(){return cell;}
//void Unit::set_cell(Cell* newcell){cell = newcell;}
