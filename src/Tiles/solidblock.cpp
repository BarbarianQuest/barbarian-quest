#include "solidblock.h"

SolidBlock::SolidBlock() : Tile()
{
    //ctor
    objHitbox.makeSolid();
}

SolidBlock::~SolidBlock()
{
    //dtor
}
