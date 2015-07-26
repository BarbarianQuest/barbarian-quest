#include <Objects/Static Blocks/cauldron.h>

Cauldron::Cauldron()
{
    //ctor
    content_id += "_cauldron";
    spriteAddresses.push_back("cauldron");
    movable = false;
    setOrigin(35,35);
    makeSolid();
    sf::Vector2f null(0,0);
    objHitbox.addCircularHitbox(null,20);
    setMass(0);
    particleOffset.y = -22;
    objParticles.setRadius(10);
    objParticles.setImpulseRange(0,0,0.5,0,0,1.0);
    objParticles.setLifetimeRange(0.1,1);
    objParticles.setParticleSizeRange(1,3);
}

Cauldron::~Cauldron()
{
    //dtor
}

void Cauldron::allocateAssets()
{
    objSprite.addLayer((assets->getTex(spriteAddresses[0])));
    objSprite.layers[0].changeReel(0);
    objSprite.layers[0].update();

    objSprite.setPosition(objPosition);
    objParticles.initialise(assets,"bubble",10,0);
}
