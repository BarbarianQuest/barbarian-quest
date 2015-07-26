#include "verticdoor.h"

VerticDoor::VerticDoor(): GameObject()
{
    //ctor
    spriteAddresses.push_back("vertic_door");
    content_id += "_verticdoor";
    setOrigin(0,128 - 32);
    sf::Vector2f nullvec(0,64*2 + 32);
    objHitbox.addRectangularHitbox(nullvec,26,384);
    makeSolid();
    movable = false;
    impassable = true;
    locked = true;
}

VerticDoor::~VerticDoor()
{
    //dtor
}


void VerticDoor::unlock()
{
    objSprite.layers[0].changeReel(1);
    locked = false;
    objHitbox.eraseAll();
    sf::Vector2f leftvec(64,64-40);
    sf::Vector2f rightvec(64,384-64-20);
    objHitbox.addRectangularHitbox(leftvec,128,26);
    objHitbox.addRectangularHitbox(rightvec,128,26);
    objHitbox.update();
}

void VerticDoor::allocateAssets()
{
    objSprite.addLayer((assets->getTex(spriteAddresses[0])));
    objSprite.layers[0].splitStaticSheet(128,384);
    objSprite.layers[0].changeReel(0);
    objSprite.layers[0].update();
    objSprite.setPosition(objPosition);
}
