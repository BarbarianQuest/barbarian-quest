#include <Objects/Containers/container.h>
#include <Objects/Containers/chest.h>
#include <Objects/Pickups/key.h>


Chest::Chest(): Container()
{
    //ctor
    content_id += "_chest";
    spriteAddresses.push_back("chests");
    movable = false;
    setOrigin(36,71);
    makeSolid();
    sf::Vector2f null(0,-15);
    objHitbox.addRectangularHitbox(null,66,26);
    setMass(0);

}

Chest::~Chest()
{
    //dtor
}

void Chest::unlock()
{
    int i;
    objSprite.layers[0].changeReel(1);
    locked = false;
    for(i=0; i<contents.size(); i++)
    {
        contents[i]->setPosition(getPosition().x, getPosition().y);
        contents[i]->makeInert(0.5);
        contents[i]->makeAir(0.5);
        float randomExtra = ((float)(rand()%50));
        sf::Vector2f imp = maths->randomVector(550+randomExtra);
        contents[i]->setImpulse(imp);
    }

    contents.clear();

}

void Chest::allocateContents()
{
    int i;
    for(i=0; i<5; i++)
    {
        contents.push_back(new Key);
        contents.back()->setManager(assets);
        contents.back()->allocateAssets();
        contents.back()->setPosition(getPosition());
    }
}

void Chest::allocateAssets()
{
    objSprite.addLayer((assets->getTex(spriteAddresses[0])));
    objSprite.layers[0].splitStaticSheet(72,88);
    objSprite.layers[0].changeReel(0);
    objSprite.layers[0].update();
    objSprite.setPosition(objPosition);
    allocateContents();
}

void Chest::hits(Content*)
{

}
