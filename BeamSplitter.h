#ifndef BEAMSPLITTERH
#define BEAMSPLITTERH
#include "Mirror.h"
class Cell;
class BeamSplitter : public Mirror
{
				public :
					BeamSplitter(Cell* _cell);
};
#endif
