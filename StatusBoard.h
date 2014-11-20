#ifndef STATUSBOARDH
#define STATUSBOARDH
#include "Global.h"
#include "Cell.h"
class Board;
class StatusBoard
{
    private:
        char status[18][18];
        int rows, cols;
        int boardRows;
        int boardCols;
        bool beam[9][9];
				Board* board;
    public:
        StatusBoard(Board*);
        void setBeam(int _row, int _col, bool _a);
        void reset();
        void resetBeam();
        void setCell(Cell* cell);
        void printStatus();
        void setBeam();
        void printBeam();
};

#endif
