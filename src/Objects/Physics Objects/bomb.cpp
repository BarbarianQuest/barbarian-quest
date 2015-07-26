#include <Objects/gameobject.h>
#include <Objects/Physics Objects/bomb.h>
#include <Physics/Physics Events/explosion.h>


Bomb::Bomb() : GameObject()
{
    //ctor
    content_id += "_bomb";
    spriteAddresses.push_back("bomb");
    setOrigin(15,20);
    makeSolid();
    sf::Vector2f null(0,5);
    objHitbox.addRectangularHitbox(null,20,20);
    setMass(1);
    shadowString = "pickupshadow";
    ticking = false;
    fuseTime = 1;
    explode = new Explosion;
    explode->setManager(assets);
    explode->allocateAssets();

}

Bomb::~Bomb()
{
    //dtor
}

void Bomb::trigger()
{
    ticking = true;
}

void Bomb::update()
{

    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    if(!ticking) {fuseClock.restart();}
    fuseTimer = fuseClock.getElapsedTime();
    if(fuseTimer.asSeconds() > fuseTime)
    {
        destroyMe = true;
        explode->setPosition(getPosition());
        explode->setParameters(0.1,100,100,10);
        dungeonContent->push_back(explode);
    }
    evolveMovement();
}
