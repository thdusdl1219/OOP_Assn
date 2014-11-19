#ifndef UNITH
#define UNITH

#include "Global.h"
class Cell;
class Board;
class Unit
{
				private:
					enum Direction dir;
					enum Team team;
					Cell* cell;
					bool stun;
					int stunturn;
					Board* board;
				public :
					enum Direction get_dir();
					void set_dir(enum Direction dirr);
					enum Team get_team();
					void set_team(enum Team yourteam);
					bool getstun();
					void setstun(bool _st);
					int getturn();
					int incturn();
					void setturn(int _t);
					Unit(Cell* _cell, Board* b);
					virtual int control_unit() = 0;
					virtual int Rotate();
					virtual bool get_enable(){return true;}
					virtual void set_enable(bool){}
					void UnitMove();
					int getrow();
					int getcol();
					void swap(Cell*&, Cell*&);
					Cell* get_cell();
					void set_cell(Cell* newcell);
					virtual ~Unit(){}
};
#endif
