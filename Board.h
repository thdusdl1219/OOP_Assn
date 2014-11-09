#include <iostream>
#include "Global.h"
#include "StatusBoard.h"
#include "Cell.h"
#include "King.h"
#include "Laser.h"
#ifndef BOARDH
#define BOARDH


class Board
{
    private:
        int rows, cols;
        enum Team ongoingTeam;
		Board* board;
        Cell* cell[81];
        StatusBoard* status;
        King* king[2];
        Laser* laser[4];
        void initGame();
        Cell* launchLaser(Cell* _startcell);
        Cell* beamCurCell(Cell* _cell);
        void swap(Cell*& _a, Cell*& _b);
		void Stun(Cell* _cell);
		void UnitMove(Cell** curcell);
		int Rotate_only(Cell** curcell);
		void Rotate(Cell** curcell);
		Cell* choiceLaser();
        void showBoard();
        void showBeam();
  public:
        Board ();
        void startGame();
		Cell* getCell(int _row, int _col);
        ~Board();
};

#endif
