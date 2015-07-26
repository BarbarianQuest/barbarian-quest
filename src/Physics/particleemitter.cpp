#include "particleemitter.h"

ParticleEmitter::ParticleEmitter()
{
    //ctor
    particleTextureAddress = "bubble";
    waitForSpace = true;
    refreshDeadParticles = true;
    particleTimer = particleClock.getElapsedTime();
    keepFull = true;
    setImpulseRange(0,0,0,0,0,0);
    setRadius(0);
    setLifetimeRange(0,1);
    setParticleSizeRange(1,1);
}

ParticleEmitter::~ParticleEmitter()
{
    //dtor
}

void ParticleEmitter::setParticleSizeRange(float min_rad, float max_rad)
{
    minParticleSize = min_rad;
    maxParticleSize = max_rad;
}

void ParticleEmitter::setManager(ResourceManager* manager)
{
    assets = manager;

}

void ParticleEmitter::setMaxNumberOfParticles(int maxnum)
{
    maxNumberOfParticles = maxnum;
}

void ParticleEmitter::addNewParticles(int num, int type)
{
    int i;
    for(i=0; i<num; i++)
    {
        addNewParticle(type);
    }
}

void ParticleEmitter::addNewParticle(int type)
{
    particleTimer = particleClock.getElapsedTime();
    if(activeParticles.size()<maxNumberOfParticles)
    {
        if(type == 0)
        {
            activeParticles.push_back(new Riser);
            //activeParticles.back()->setImpulse(0,-10,0);
        }
        if(type == 1)
        {
            activeParticles.push_back(new Trail);
        }
        activeParticles.back()->sprAddress = particleTextureAddress;
        activeParticles.back()->allocateAssets(assets);
        activeParticles.back()->setEmitterPosition(position);
        activeParticles.back()->setCreationTime(particleTimer.asSeconds());


    }
}

void ParticleEmitter::initialise(ResourceManager* manager, string address, int maxnum, int type)
{
    assets = manager;
    setMaths(&(assets->maths));
    particleTextureAddress = address;
    baseParticle.allocateAssets(assets);
    maxNumberOfParticles = maxnum;
    addNewParticles(maxnum,type);
}

void ParticleEmitter::setBaseParticle(const Particle & basePart)
{
    baseParticle = basePart;
}

void ParticleEmitter::setPosition(sf::Vector2f newpos)
{
    position = newpos;
}

void ParticleEmitter::setImpulseRange(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z)
{
    maxXImpulse = max_x;
    minXImpulse = min_x;
    maxYImpulse = max_y;
    minYImpulse = min_y;
    maxZImpulse = max_z;
    minZImpulse = min_z;
}

void ParticleEmitter::setRadius(float newrad)
{
    radius = newrad;
}

void ParticleEmitter::setLifetimeRange(float min_life, float max_life)
{
    minLifetime = min_life;
    maxLifetime = max_life;
}

void ParticleEmitter::setMaths(fastMaths* newMaths)
{
    maths = newMaths;
}

void ParticleEmitter::update()
{
    int i;
    particleTimer = particleClock.getElapsedTime();
    int truesize = activeParticles.size();
    for(i=0; i<truesize; i++)
    {
        activeParticles[i]->evolveParticle();


            if((particleTimer.asSeconds() - activeParticles[i]->created_at) > activeParticles[i]->lifetime)
            {
                if(refreshDeadParticles)
                {
                    activeParticles[i]->refresh(particleTimer.asSeconds());
                    float lifetime = maths->randomFloat(minLifetime, maxLifetime);
                    float zimp = maths->randomFloat(minZImpulse, maxZImpulse);
                    float partRad = maths->randomFloat(minParticleSize, maxParticleSize);
                    if(zimp != 0)
                    {
                        activeParticles[i]->setImpulse(0,0,-zimp);
                    }
                    activeParticles[i]->setLifetime(lifetime);
                    activeParticles[i]->setRadius(partRad);
                    sf::Vector2f randOffset;

                    randOffset.x = (maths->randomFloat(-10*radius,10*radius)*0.1);
                    randOffset.y = (maths->randomFloat(-10*radius,10*radius)*0.1);

                    activeParticles[i]->setEmitterPosition(position + randOffset);
                }
                if(!refreshDeadParticles)
                {
                    activeParticles.erase(activeParticles.begin() + i);
                    truesize--;
                    i--;
                }
            }

    }
}
