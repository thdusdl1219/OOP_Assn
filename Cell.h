#ifndef CELLH
#define CELLH

#include "Global.h"
#include "King.h"
#include "AttackLaser.h"
#include "BlockMirror.h"
#include "TriMirror.h"
#include "HyperMirror.h"
#include "StunLaser.h"
#include "BeamSplitter.h"
#include <iostream>
class Board;
class Cell
{
    private:
        int row, col;
        enum UnitType unit;
        bool accesible;
				bool seam;
        Unit* uni;
				bool isHyper;
				Board* board;
				bool block_laser;
    public:
        Cell(int _row, int _col, Board* b);
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
				int getUnitstunturn();
				void setUnitstunturn(int);
				bool getseam();
				void setseam(bool);
				bool getHyper();
				void setHyper(bool);
				bool get_block();
				void set_block(bool);
				void Stun();
        ~Cell();
};
#endif
