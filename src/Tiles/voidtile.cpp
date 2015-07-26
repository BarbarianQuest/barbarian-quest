#include "voidtile.h"

VoidTile::VoidTile() : Tile()
{
    //ctor
    content_id += "_void";
    id = 0;
    render = false;
}

VoidTile::~VoidTile()
{
    //dtor
}
