#include <Objects/gameobject.h>
#include <Objects/Pickups/pickup.h>


Pickup::Pickup(): GameObject()
{
    //ctor
    content_id += "_pickup";
    renderPriority = 1;
    stopsRays = false;
}

Pickup::~Pickup()
{
    //dtor
}
