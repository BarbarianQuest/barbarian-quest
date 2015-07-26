#include "particle.h"

Particle::Particle()
{
    //ctor
    mass = 1;
    recipmass = 1/mass;
    lifetime = 0;
    riser = false;

    drift.x = drift.y = drift.z = 0;
    impulse.x = impulse.y = verticalImpulse = 0;
    speed.x = speed.y = 0;
    radius = 0;
    elevation = 0;
    sprAddress = "error";
}

Particle::~Particle()
{
    //dtor
}

void Particle::setLifetime(float new_life)
{
    lifetime = new_life;
}

void Particle::setSprite(const sf::Texture & partSpr)
{
    particleSprite.addLayer(partSpr);
}

void Particle::allocateAssets(ResourceManager* manager)
{
    assets = manager;
    setMaths(&(assets->maths));
    particleSprite.addLayer(assets->getTex(sprAddress));
    testPart.setRadius(radius);
    testPart.setOrigin(radius,radius);
    testPart.setPointCount(36);
    testPart.setFillColor(sf::Color::Green);
    testPart.setOutlineThickness(0);
    //particleSprite.layers.back().setFPS(0);
    //sf::Vector2f orig(0.5*particleSprite.layers[0].getBounds().x,0.5*particleSprite.layers[0].getBounds().y);
    particleSprite.setOrigin();
    particleSprite.layers.back().changeReel(0);
    setPosition(emitterPosition);
}

void Particle::setMaths(fastMaths* newMaths)
{
    maths = newMaths;
}

void Particle::setRadius(float newrad)
{
    radius = newrad;
    testPart.setRadius(radius);
    testPart.setOrigin(radius,radius);
}

void Particle::setEmitterPosition(sf::Vector2f emitterPos)
{
    emitterPosition = emitterPos;
    setPosition(emitterPosition);
}

void Particle::setCreationTime(float creationTime)
{
    created_at = creationTime;
}

void Particle::refresh(float refreshed_at)
{
    elevation = 0;
    setPosition(emitterPosition);
    setCreationTime(refreshed_at);
}

void Particle::setPosition(sf::Vector2f newpos)
{
    particleSprite.setPosition(newpos);
    testPart.setPosition(newpos);
    position = newpos;
}

void Particle::setImpulse(sf::Vector3f newImp)
{
    impulse.x = newImp.x;
    impulse.y = newImp.y;
    verticalImpulse = newImp.z;
}

void Particle::setImpulse(float dx, float dy,float dz)
{
    sf::Vector3f newImp(dx,dy,dz);
    setImpulse(newImp);
}

void Particle::evolveParticle()
{
    if(!riser)
    {
        /*float gravconst = 0.1;
        float grav = gravconst*mass;
        sf::Vector2f unitGrav(0,1);
        sf::Vector2f twoDrift(drift.x, drift.y);
        if(maths->magnitude(twoDrift) > grav)
        {
            drift.y+=grav;
        }
        else
        {
            drift.x = 0;
            drift.y = 0;
        }*/
    }
    position+=(impulse*recipmass);
    position.x += drift.x;
    position.y += drift.y;
    elevation+=(verticalImpulse*recipmass + drift.z);
    sf::Vector2f unitImp = maths->unitVector(impulse);
    if(maths->magnitude(impulse) > mass)
    {
    impulse-=mass*unitImp;
    }
    else
    {
        impulse.x = 0;
        impulse.y = 0;
    }
    if(fabs(verticalImpulse) > mass)
    {
        if(verticalImpulse > 0)
        {
            verticalImpulse-=mass;
        }
        if(verticalImpulse < 0)
        {
            verticalImpulse +=mass;
        }
    }
    else
    {
        verticalImpulse = 0;
    }

    sf::Vector2f newPos(position.x, position.y + elevation);
    setPosition(newPos);
    particleSprite.layers[0].Animate();

}
