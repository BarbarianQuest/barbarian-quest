#include "projectile.h"

Projectile::Projectile() : DynamicContent()
{
    //ctor
    spriteAddresses.push_back("arrow");
    content_id += "_projectile";
    setOrigin(9,23);
    sf::Vector2f nullvec(0,-10);
    setMass(0.5);
    objHitbox.addCircularHitbox(nullvec,10);
    makeSolid();
    movable = true;
    impassable = false;
    stopsRays = false;
    friction = 0;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::hits(Content* obj)
{
    if(obj->impassable == true)
    {
        destroyMe = true;
        inert = true;
        obj->impulse += mass*velocity;
    }
    if(obj->idContains("player"))
    {

    }
    if(obj->destructable)
    {
        obj->damageBy(1);
    }
}

void Projectile::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    evolveMovement();
}
