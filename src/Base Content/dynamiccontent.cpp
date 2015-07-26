#include <Base Content/content.h>
#include <Base Content/dynamiccontent.h>

DynamicContent::DynamicContent() : Content()
{
    //ctor
    content_id += "_dyn";
    renderPriority = 1;
    dynamic = true;
    impassable = true;
    solid = true;
    stopsRays = true;
    //movable = true;
}

DynamicContent::~DynamicContent()
{
    //dtor
}

void DynamicContent::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    evolveMovement();
}
