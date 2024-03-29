#include "Cell.h"
#ifndef STATUSBOARDH
#define STATUSBOARDH

class StatusBoard
{
    private:
        char status[18][18];
        int rows, cols;
        int boardRows;
        int boardCols;
        bool beam[9][9];
        enum Direction Beamdir;
				bool attack;
    public:
        StatusBoard();
        void setBeam(int _row, int _col, bool _a);
        enum Direction getBeamdir();
        void setBeamdir(enum Direction _dir);
        void reset();
        void resetBeam();
        void setCell(Cell* cell);
        void printStatus();
        void setBeam();
        void printBeam();
				void setattack(bool _att);
				bool getattack();
};

#endif
