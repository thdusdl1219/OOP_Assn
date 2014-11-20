#ifndef BEAMSPLITTERH
#define BEAMSPLITTERH
#include "Mirror.h"
class Cell;
class BeamSplitter : public Mirror
{
				public :
					BeamSplitter(Cell* _cell, Board* b);
					virtual void printUnit(char[18][18]);
};
#endif
