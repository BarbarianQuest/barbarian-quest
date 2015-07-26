#include <Objects/gameobject.h>
#include <Objects/Containers/container.h>

Container::Container(): GameObject()
{
    //ctor
    locked = true;
    solid = true;
}

Container::~Container()
{
    //dtor
}

void Container::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    evolveMovement();
    int i;
    for(i=0; i<contents.size(); i++)
    {
        contents[i]->delta = delta;
    }
}
