
#include <Objects/Weapons/weapon.h>
#include <Objects/Weapons/axe.h>

Axe::Axe() : Weapon()
{
    headRadius = 0;
    arcSize = 90;
}

Axe::~Axe()
{

}

void Axe::initialiseWeapon(Content* owner)
{
    setOwner(owner);
    allocateAssets();
    setHitboxProperties();
    degreesPerSec = arcSize/attackTime;
}

void Axe::evolveHitbox()
{
    float baseang = 0;
    if(heldBy->facing == 0)
    {
        baseang = 360-0.5*arcSize;
    }
    if(heldBy->facing == 1)
    {
        baseang = 180-0.5*arcSize;
    }
    if(heldBy->facing == 3)
    {
        baseang = 270-0.5*arcSize;
    }
    if(heldBy->facing == 2)
    {
        baseang = 90-0.5*arcSize;
    }

    float sinang = maths.SinDeg(baseang + degreesPerSec*attackTimer.asSeconds());
    currentHitboxPosition.x = sinang*reach;
    float cosang = maths.CosDeg(baseang + degreesPerSec*attackTimer.asSeconds());
    currentHitboxPosition.y = cosang*reach;
    objHitbox.circs.back().setRelativePosition(currentHitboxPosition);
}

void Axe::setHitboxProperties()
{
    currentHitboxPosition.x = reach;
    currentHitboxPosition.y = 0;
    objHitbox.addCircularHitbox(currentHitboxPosition,headRadius);
}
