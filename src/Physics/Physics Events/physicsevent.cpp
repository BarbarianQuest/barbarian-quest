#include <Base Content/content.h>
#include <Physics/Physics Events/physicsevent.h>

PhysicsEvent::PhysicsEvent(): Content()
{
    //ctor
    content_id += "_physicsevent";
    renderPriority = 2;
}

PhysicsEvent::~PhysicsEvent()
{
    //dtor
}


void PhysicsEvent::allocateAssets()
{
    int i;
    for(i=0; i<spriteAddresses.size(); i++)
    {
        objSprite.addLayer((assets->getTex(spriteAddresses[i])));
        //objSprite.layers.back().changeReel(0);
        objSprite.layers.back().setFPS(animFPS);
        //objSprite.layers.back().splitStaticSheet(objSprite.layers.back().getSize().x, objSprite.layers.back().getSize().y);
        //objSprite.layers.back().update();
    }

    if(shadowString != "null")
    {
        initialiseShadow();
    }
    setPosition(objPosition);
}
