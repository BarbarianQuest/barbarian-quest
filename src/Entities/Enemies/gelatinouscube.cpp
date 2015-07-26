#include "gelatinouscube.h"
using namespace std;

GelatinousCube::GelatinousCube(): Enemy()
{
    //ctor
    content_id += "_gelcube";
    setMass(2);
    setOrigin(28,74);
    sf::Vector2f nullVec(0,0);
    objHitbox.addRectangularHitbox(nullVec,56,40);
    objHitbox.makeSolid();
    spriteAddresses.push_back("gelatinous_cube");
    maxSpeed = 0;
    absMaxSpeed = 400;
    health = 3;
    maxhealth = 3;
    timerOffset = ((float) (rand()%100 ))/1000;
    maxTrail = 10;
    currentTrail = 0;

}

GelatinousCube::~GelatinousCube()
{
    //dtor
}

void GelatinousCube::evolveSpeed()
{
    float pulseFreq = 1.0 + timerOffset;
    float dieOffIn = 3.0;
    if(speedTime.asSeconds() >= pulseFreq)
    {
        currentTrail++;
        if(currentTrail == maxTrail)
        {
            currentTrail = 0;
        }
        slime[currentTrail]->setPosition(getPosition());
        speedClock.restart();
        maxSpeed = absMaxSpeed;
        return;
    }
    else
    {
        float increment = 0.5*(1.0/dieOffIn)*absMaxSpeed*speedTime.asSeconds();
        if(maxSpeed >= increment)
        {
            maxSpeed -= increment;
        }
        if(maxSpeed < increment)
        {
            maxSpeed = 0;
        }
    }

}

void GelatinousCube::extraAllocations()
{
    int i;
    for(i=0; i< maxTrail; i++)
    {
        slime.push_back(new Contaminant);
        slime.back()->initialiseAssets(assets);
    }
    /*particleOffset.y = 0;
    objParticles.setRadius(0);
    objParticles.setImpulseRange(0,0,0,0,0,0);
    objParticles.setLifetimeRange(5,5);
    objParticles.setParticleSizeRange(1,3);
    objParticles.initialise(assets,"particle",1,1);*/
}
