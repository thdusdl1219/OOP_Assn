#ifndef HYPERMIRRORH
#define HYPERMIRRORH
#include "Mirror.h"
class Cell;
class HyperMirror : public Mirror
{
    public:
        HyperMirror(Cell* _cell); // 하이퍼거울을 초기화한다.
};
#endif
