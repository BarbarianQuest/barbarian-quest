#include "floor.h"

Floor::Floor() : Tile()
{
    //
    int spin = rand()%30;
    id = 13;
    content_id += "_floor";
    if(spin == 0)
    {
        id = 1;
    }
    rotateable = true;
    stopsRays = false;
}

Floor::~Floor()
{
    //dtor
}
