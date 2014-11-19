#ifndef HYPERMIRRORH
#define HYPERMIRRORH
#include "Mirror.h"
class Cell;
class HyperMirror : public Mirror
{
    public:
        HyperMirror(Cell* _cell, Board* b); // 하이퍼거울을 초기화한다.
				virtual int Rotate();
};
#endif
