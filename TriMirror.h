#ifndef TRIMIRRORH
#define TRIMIRRORH
#include "Mirror.h"
class Cell;
class TriMirror : public Mirror
{
    public:
        TriMirror(Cell* _cell, Board* b); // 삼각거울을 초기화한다.
};
#endif
