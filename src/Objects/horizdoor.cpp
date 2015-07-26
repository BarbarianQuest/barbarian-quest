#include "horizdoor.h"

HorizDoor::HorizDoor(): GameObject()
{
    //ctor
    spriteAddresses.push_back("horiz_door");
    content_id += "_horizdoor";
    setOrigin(32,230);
    sf::Vector2f nullvec(128-32,0);
    objHitbox.addRectangularHitbox(nullvec,256,26);
    makeSolid();
    movable = false;
    impassable = true;
    locked = true;

}

HorizDoor::~HorizDoor()
{
    //dtor
}

void HorizDoor::unlock()
{
    objSprite.layers[0].changeReel(1);
    locked = false;
    objHitbox.eraseAll();
    sf::Vector2f leftvec(-32,-50);
    sf::Vector2f rightvec(256-32,-50);
    objHitbox.addRectangularHitbox(leftvec,26,128);
    objHitbox.addRectangularHitbox(rightvec,26,128);
    objHitbox.update();
    int i;
}

void HorizDoor::allocateAssets()
{
    objSprite.addLayer((assets->getTex(spriteAddresses[0])));
    objSprite.layers[0].splitStaticSheet(256,256);
    objSprite.layers[0].changeReel(0);
    objSprite.layers[0].update();
    objSprite.setPosition(objPosition);
}
