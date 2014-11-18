#ifndef GLOBALH
#define GLOBALH

enum Direction
{
    UP = 1,
    DOWN = 3,
    LEFT = 2,
    RIGHT = 4,
};

enum Team
{
    ONE = 1,
    TWO = 2,
};

enum UnitType
{
    NONE,
    KING,
    ATTLASER,
    BLOCKMIRROR,
    TRIMIRROR,
    HYPERMIRROR,
		STULASER,
		SPLITTER,
};
#endif
