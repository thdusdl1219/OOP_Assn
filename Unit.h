#ifndef UNITH
#define UNITH

#include "Global.h"
class Cell;

class Unit
{
				private:
					enum Direction dir;
					enum Team team;
					Cell* cell;
					bool stun;
					int stunturn;
				public :
					Unit(Cell* _cell);
					enum Direction get_dir();
					void set_dir(enum Direction dirr);
					enum Team get_team();
					void set_team(enum Team yourteam);
					bool getstun();
					void setstun(bool _st);
					int getturn();
					int incturn();
					void setturn(int _t);
//					Cell* get_cell();
//					void set_cell(Cell* newcell);
};
#endif
