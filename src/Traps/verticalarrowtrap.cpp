#include "verticalarrowtrap.h"

VerticalArrowTrap::VerticalArrowTrap() : Trap()
{
    //ctor
    velocity.x = 0;
    velocity.y = 0;
    setMass(2);
    objectID = 0;
    movable = false;
    impassable = true;
    setOrigin(45,100);
    sf::Vector2f nullVec(0,0);
    objHitbox.addRectangularHitbox(nullVec,56,40);
    objHitbox.makeSolid();
    spriteAddresses.push_back("gargoyle");
    objRays.addRay(0);
    objRays.rays.back().setBearing(180);
    timeBetweenShots = 0.5;
    lastFired = 0;
}

VerticalArrowTrap::~VerticalArrowTrap()
{
    //dtor
}

void VerticalArrowTrap::detects(Content* obj)
{
    if((obj->idContains("player") || obj->idContains("entity")) && objTime.asSeconds() - lastFired > timeBetweenShots)
    {
        lastFired = objTime.asSeconds();
        (*dungeonContent).push_back(new Projectile);
        (*dungeonContent).back()->setManager(assets);
        (*dungeonContent).back()->setMaths(maths);
        (*dungeonContent).back()->allocateAssets();
        (*dungeonContent).back()->setPosition(objPosition);
        (*dungeonContent).back()->Rotate(180);
        (*dungeonContent).back()->impulse.x = 0;
        (*dungeonContent).back()->impulse.y = 500;
        (*dungeonContent).back()->makeInert(0.05);
    }
}
