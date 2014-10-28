#include <iostream>
#include "Global.h"
#include "StatusBoard.h"
#include "Cell.h"
#include "King.h"
#include "AttackLaser.h"
#include "StunLaser.h"
#include "Unit.h"
#include "Laser.h"
#ifndef BOARDH
#define BOARDH


class Board
{
    private:
        int rows, cols;
        enum Team ongoingTeam;
        Cell* cell[81];
        StatusBoard* status;
        King* king[2];
        Laser* laser[4];
        void initGame();
        Cell* launchLaser(Cell* _startcell);
        Cell* beamCurCell(Cell* _cell);
        void swap(Cell*& _a, Cell*& _b);
    public:
        Board ();
        void startGame();
        void showBoard();
        void showBeam();
        ~Board();
};

#endif
