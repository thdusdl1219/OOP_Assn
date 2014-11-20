
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
using namespace std;

class Board
{
    private:
        int rows, cols;
        enum Team ongoingTeam;
        Cell* cell[81];
				Unit* king[2];
        StatusBoard* status;
				bool attack;
				enum Direction Beamdir;
        void initGame();
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
				enum Direction getBeamdir();
				void setBeamdir(enum Direction);
        Cell* launchLaser(Cell* _startcell);
				void setattack(bool);
				bool getattack();
				Cell** getCell(int);
        ~Board();
};

#endif
