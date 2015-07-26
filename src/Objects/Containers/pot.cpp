#include <Objects/Containers/container.h>
#include <Objects/Containers/pot.h>

Pot::Pot() : Container()
{
    //ctor
    content_id += "_pot";
    spriteAddresses.push_back("pots");
    movable = true;
    destructable = true;
    health = 1;
    maxhealth = 1;
    setOrigin(32,48);

    sf::Vector2f null(0,-14);
    objHitbox.addCircularHitbox(null,26);
    makeSolid();
    setMass(10);
}

Pot::~Pot()
{
    //dtor
}

void Pot::allocateAssets()
{
    objSprite.addLayer((assets->getTex(spriteAddresses[0])));
    objSprite.layers[0].splitStaticSheet(64,64);
    objSprite.layers[0].changeReel(rand()%2);
    objSprite.layers[0].update();
    objSprite.setPosition(objPosition);
    //allocateContents();
}
