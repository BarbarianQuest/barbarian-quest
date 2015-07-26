
#include <Base Content/passivecontent.h>
#include <Base Content/content.h>

PassiveContent::PassiveContent() : Content()
{
    //ctor
    content_id += "_pas";
    dynamic = false;
    movable = true;
    impassable = true;
    solid = true;
    stopsRays = true;
}

PassiveContent::~PassiveContent()
{
    //dtor
}

void PassiveContent::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    evolveMovement();
}
