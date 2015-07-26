#include <Objects/gameobject.h>
#include <Objects/Physics Objects/football.h>

Football::Football() : GameObject()
{
    //ctor
    content_id += "_football";
    spriteAddresses.push_back("ball");
    setOrigin(15,15);
    makeSolid();
    sf::Vector2f null(0,0);
    objHitbox.addRectangularHitbox(null,26,26);
    setMass(1);
    shadowString = "pickupshadow";
}

Football::~Football()
{
    //dtor
}
