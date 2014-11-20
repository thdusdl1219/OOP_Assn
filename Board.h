
#ifndef BOARDH
#define BOARDH
#include <iostream>
#include "Global.h"
#include "StatusBoard.h"
#include "Cell.h"
#include "King.h"
#include <cstdlib>
#include <ctime>
#include <fstream>


class Board
{
    private:
        int rows, cols;
        enum Team ongoingTeam;
        Cell* cell[81];
				Unit* king[2];
        StatusBoard* status;
				bool attack;
				
				bool getattack();
				void setattack(bool);

        void initGame();
        Cell* launchLaser(Cell* _startcell);
        Cell* beamCurCell(Cell* _cell);
				Cell* choiceLaser();
        void showBoard();
        void showBeam();
				bool testFile(std::ifstream&);
				void saveGame();
 public:
        Board ();
        void startGame(bool);
				bool loadGame(std::ifstream&);
				Cell** getCell(int);
        ~Board();
};

#endif
