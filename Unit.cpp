#include "Unit.h"
#include <iostream>
#include "Cell.h"
#include "Board.h"
using namespace std;

Unit::Unit(Cell* _cell, Board* b) // 모든 유닛들의 부모 클래스인 Unit을 초기화하는 함수
{
				dir = UP;
				cell = _cell;
				team = ONE;
				stun = false;
				stunturn = 0;
				board = b;
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
Cell* Unit::get_cell(){return cell;}
void Unit::set_cell(Cell* newcell){cell = newcell;}
int Unit::getrow()
{
	return cell->getrow();
}
int Unit::getcol()
{
	return cell->getcol();
}
/* 유닛을 스왑할 떄 쓰이는 함수, 두 셀을 서로 스왑하고 row와 col만 다시 지정해준다. */
void Unit::swap(Cell*& _a, Cell*& _b)
{
	int tmprowb;
	int tmpcolb;
	int tmprowa;
	int tmpcola;
	Cell* tmp;

	tmp = _b;
	tmprowb = _b->getrow();
	tmpcolb = _b->getcol();
	tmprowa = _a->getrow();
	tmpcola = _a->getcol();
	_b = _a;
	_b->setrow(tmprowb);
	_b->setcol(tmpcolb);
	_a = tmp;
	_a->setrow(tmprowa);
	_a->setcol(tmpcola);
	cout << "[Log] Player"<< get_team() <<": " << (char)(tmprowa + 65) << " " << (char)(tmpcola + 49) << " => " << (char)(tmprowb + 65) << " " << (char)(tmpcolb + 49) << endl;
	if(_a->getHyper())
	{
		_a->setHyper(false);
		Cell** choose = board->getCell(rand()%81);
		while((*choose)->getUni() != NULL || !(*choose)->movableTo())
			choose = board->getCell(rand()%81);
		swap(_b, (*choose));
	}	
}

void Unit::UnitMove() // 유닛이 움직이는 경우를 처리하는 함수
{
	string input;
	while(1)
	{
		cout << "Which Position do you want it to move?\n"; // 유닛을 이동시킨다.
		cout << ">> ";
		getline(cin,input);
		cout << "\n";
		if(input.size() != 3 || input.at(0) < 65 || input.at(0) > 105 || (input.at(0) > 73 && input.at(0) < 97) || input.at(1) != 32 || input.at(2) < 49 || input.at(2) > 57)
		{
			cout << "[System] Input Format of position is \"Row Col\".\n";
			cout << "         ex) D 4, e 2, or etc.\n"; 
			continue;
		}
		else
		{
			if(input.at(0) > 96)
				input.at(0) -= 32;
			Cell** movTo = board->getCell((input.at(0)-65)*9 + (input.at(2)-49));
			if((*movTo) == cell)
			{
				cout << "You must move your Unit\n";
				continue;
			}
			if((*movTo)->getrow() <= cell->getrow()+1 && (*movTo)->getrow() >= cell->getrow()-1 && (*movTo)->getcol() <= cell->getcol()+1 && (*movTo)->getcol() >= cell->getcol()-1)
			{
				if(cell->getUnit() != HYPERMIRROR)
				{
					if((*movTo)->movableTo())
					{
						swap(*board->getCell(cell->getrow()*9+getcol()),*movTo);
						cout << endl;
						break;
					}
					else
					{
						cout << "[System] You can't move your Unit to there\n";
						continue;
					}
				}
				else
				{
					if((*movTo)->getaccesible())
					{
						swap(*board->getCell(cell->getrow()*9+getcol()),*movTo);
						cout << endl;
						break;
					}
					else
					{
						cout << "[System] You can't move your Unit to there\n";
						continue;
					}
				}

			}
			else
			{
				cout << "[System] You can't move your Unit to there\n";
				continue;                                   
			}
		}
	}

}

int Unit::Rotate()
{
	string choice;
	while(1)
	{
		enum Direction curdir = get_dir();
		cout << "Do you want it to Rotate?\n";
		cout << "1. LEFT 2. RIGHT\n";
		cout << ">> ";
		getline(cin,choice);
		if(choice.size() != 1)
		{
			cout << "[System] Please correct choice!\n";
			continue;
		}
		if(choice.at(0) == 49)
		{
			if(curdir != 4)
			{
				set_dir((enum Direction)(curdir + 1));
			}
			else
			{
				set_dir((enum Direction)1);
			}
			cout << endl;
			char tmprow = cell->getrow() + 65;
			char tmpcol = cell->getcol() + 49;
			cout << "[Log] Player"<< get_team() <<": " << tmprow << " " << tmpcol << " ROTATE\n";
			return 0;
		}
		else if(choice.at(0) == 50)
		{
			if(curdir != 1)
			{
				set_dir((enum Direction)(curdir - 1));
			}
			else
			{
				set_dir((enum Direction)4);
			}
			return 0;
		}
		else
		{
			cout << "[System] You should input 1 or 2\n";
			continue;
		}
	}
}
