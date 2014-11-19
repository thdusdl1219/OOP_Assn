#include "Cell.h"

Cell::Cell(int _row, int _col)
{
    row = _row;
    col = _col;
    unit = NONE;
		uni = NULL;
    accesible = true;
		seam = false;
		isHyper = false;

}

bool Cell::getseam(){return seam;}
void Cell::setseam(bool _se){seam = _se;}

bool Cell::getHyper(){return isHyper;}
void Cell::setHyper(bool _hy){isHyper = _hy;}


Unit* Cell::getUni(){return uni;}
enum UnitType Cell::getUnit(){return unit;}
int Cell::setrow(int _row){return row = _row;}
int Cell::setcol(int _col){return col = _col;}
int Cell::getrow(){return row;}
int Cell::getcol(){return col;}
bool Cell::getaccesible(){return accesible;}
void Cell::setaccesible(bool _acc){accesible = _acc;}
void Cell::setUnitstun(bool _stun) // 유닛의 스턴 상태를 변경하는 함수
{
	if(uni != NULL)
		uni->setstun(_stun);
}

bool Cell::getUnitstun() // 유닛의 스턴 상태를 얻어오는 함수
{
	if(uni != NULL)
		return uni->getstun();
	else
		return false;
}

void Cell::setUnitstunturn(int turn)
{
	if(uni != NULL)
		uni->setturn(turn);
}

int Cell::getUnitstunturn()
{
	if(uni != NULL)
		return uni->getturn();
	else
		return 0;
}

Cell::~Cell()
{
    if(uni != NULL)
    {
        delete uni;
        uni = NULL;
    }
}

void Cell::setUnit(enum UnitType _unit) // 유닛의 타입을 받아서 유닛을 할당하는 함수.
{
    unit = _unit;
    switch(unit)
    {
        /* 이미 할당되어 있던 유닛이 있다면 파괴한다. */
            if(uni != NULL)
            {
                delete uni;
                uni = NULL;
            }
        case 0: 
            break;
        case 1:
            uni = new King(this);
            break;
        case 2:
           uni = new AttackLaser(this);
           accesible = false;
           break;
        case 3:
           uni = new BlockMirror(this);
           break;
        case 4:
           uni = new TriMirror(this);
           break;
        case 5:
           uni = new HyperMirror(this);
           break;
				case 6:
					 uni = new StunLaser(this);
					 break;
				case 7:
					 uni = new BeamSplitter(this);
					 break;
    }
   
}
bool Cell::movableTo() // 셀이 접근 가능한 곳인지 확인한다.
{
    if(accesible && unit == NONE)
        return true;
    else
        return false;
}
void Cell::removeUnit() // 셀에 있는 유닛을 삭제한다.
{
    unit = NONE;
    if(uni != NULL)
    {
        delete uni;
        uni = NULL;
    }
}
enum Team Cell::getUnitTeam() // 셀에 있는 유낫의 팀을 리턴 
{
	if(uni != NULL)
		return uni->get_team();
	return ONE;
}

void Cell::setUnitTeam(enum Team _team) // 셀에 있는 유닛의 팀을 변경
{
	if(uni != NULL)
		uni->set_team(_team);
}
enum Direction Cell::getUnitDir() // 셀에 있는 유닛의 방향을 리턴
{
	if(uni != NULL)
		return uni->get_dir();
    return UP;
}
void Cell::setUnitDir(enum Direction _dir) // 셀에 있는 유닛의 방향을 변경
{
	if(uni != NULL)
		uni->set_dir(_dir);
}
