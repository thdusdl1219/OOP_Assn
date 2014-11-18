#ifndef CELLH
#define CELLH

#include "Unit.h"
#include "Global.h"
#include "King.h"
#include "AttackLaser.h"
#include "StunLaser.h"
#include "BlockMirror.h"
#include "TriMirror.h"
#include "HyperMirror.h"
#include "BeamSplitter.h"

#include <iostream>

class Cell
{
    private:
        int row, col;
        enum UnitType unit;
        bool accesible;
				bool seam;
        Unit* uni;
				bool isHyper;
    public:
        Cell(int _row, int _col);
        Unit* getUni();
        enum UnitType getUnit();
        void setUnit(enum UnitType _unit);
        int setrow(int _row);
        int getrow();
        int setcol(int _col);
        int getcol();
        bool getaccesible();
        void setaccesible(bool _acc);
        bool movableTo();
        void removeUnit();
        enum Team getUnitTeam();
        void setUnitTeam(enum Team _team);
        enum Direction getUnitDir();
        void setUnitDir(enum Direction _dir);
				void setUnitstun(bool _stun);
				bool getUnitstun();
				bool getseam();
				void setseam(bool);
				bool getHyper();
				void setHyper(bool);
        ~Cell();
};
#endif
