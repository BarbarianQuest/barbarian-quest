#include "immortalbox.h"

ImmortalBox::ImmortalBox() : GameObject()
{
    //ctor
    velocity.x = 0;
    velocity.y = 0;
    setMass(3);
    content_id += "_compcube";
    objectID = 0;
    setOrigin(28,74);
    sf::Vector2f nullVec(0,0);
    objHitbox.addRectangularHitbox(nullVec,56,40);
    objHitbox.makeSolid();
    spriteAddresses.push_back("companion_cube");

}

ImmortalBox::~ImmortalBox()
{
    //dtor
}

void ImmortalBox::notInContact()
{
    velocity.x = 0;
    velocity.y = 0;
}

void ImmortalBox::hits(Content* otherContent)
{

}

void ImmortalBox::allocateAssets()
{
    objSprite.addLayer((assets->getTex(spriteAddresses[0])));
    objSprite.layers[0].splitStaticSheet(56,94);
    objSprite.layers[0].changeReel(objectID);
    objSprite.setOrigin(getOrigin());
    objSprite.layers[0].update();
    objSprite.setPosition(objPosition);
}

