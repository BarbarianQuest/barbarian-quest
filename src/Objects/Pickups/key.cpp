#include <Objects/Pickups/pickup.h>
#include <Objects/Pickups/key.h>


Key::Key(): Pickup()
{
    //ctor
    content_id += "_key";
    spriteAddresses.push_back("key");
    setOrigin(12,16);
    makeSolid();
    sf::Vector2f null(0,0);
    objHitbox.addCircularHitbox(null,10);
    setMass(1.5);
    shadowString = "pickupshadow";
}

Key::~Key()
{
    //dtor
}

void Key::hits(Content* object)
{
    if(object->idContains("player"))
    {
        impassable = false;
        destroyMe = true;
        inert = true;
    }
    if(object->idContains("chest"))
    {

    }
}
