#ifndef BLOCKMIRRORH
#define BLOCKMIRRORH
#include "Mirror.h"
class Cell;
class BlockMirror : public Mirror
{
    public:
        BlockMirror(Cell* _cell, Board* b); // 블록거울을 초기화한다.
};
#endif
