#include "entity.h"

Entity::Entity(): DynamicContent()
{
    //ctor
    content_id += "_entity";
    primeTargetSet = false;
    movable = true;
    destructable = true;
    health = 1;
    maxhealth = 1;
    path.setPrimitiveType(sf::LinesStrip);
}

Entity::~Entity()
{
    //dtor
}

void Entity::setVelocity()
{
    float speedToSpend = maxSpeed;
    impulse -= mass*velocity;
    if(path.getVertexCount() < 2)
    {
        return;
    }
    while(speedToSpend > 0)
    {
        sf::Vector2f nextStep;
        nextStep = path[1].position - path[0].position;
        float magStep = maths->magnitude(nextStep);
        sf::Vector2f unitStep = maths->unitVector(nextStep);
        if(speedToSpend <= magStep)
        {
            velocity += speedToSpend*unitStep;
            speedToSpend = 0;
        }
        else
        {
            speedToSpend -= magStep;
            velocity += magStep*unitStep;
        }
    }
}

void Entity::pathfind()
{
    if(primeTargetSet)
    {
        path.resize(2);
        path[0].position = getPosition();
        path[1].position = primeTarget->getPosition();
    }
}

void Entity::selectPrimeTarget()
{
    if(aggroed.size() > 0)
    {
        primeTarget = aggroed.front();
        primeTargetSet = true;
    }
}

bool Entity::hasPrimeTarget()
{
    return(primeTargetSet);
}


void Entity::update()
{
    int i;
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    selectPrimeTarget();
    pathfind();
    evolveSpeed();
    setVelocity();
    evolveMovement();
    for(i=0; i<path.getVertexCount(); i++)
    {
        path[i].color = sf::Color::Red;
    }
}

void Entity::addAggro(Content* obj)
{
    aggroed.push_back(obj);
    return;
}

void Entity::removeAggro(Content* obj)
{
    int i;
    for(i=0; i<aggroed.size(); i++)
    {
        if(aggroed[i]==obj)
        {
            aggroed.erase(aggroed.begin() + i);
            return;
        }
    }
}

void Entity::updateClocks()
{
    int i;
    adjustedVelocity = delta*velocity;
    adjustedImpulse = delta*impulse;
    objTime = objClock.getElapsedTime();
    inertTime = inertClock.getElapsedTime();
    airTime = airClock.getElapsedTime();
    speedTime = speedClock.getElapsedTime();
    moved = false;
    if(inertTime.asSeconds() < inertForThisLong)
    {
        inert = true;
    }
    else
    {
        inert = false;
    }
    if(airTime.asSeconds() < airForThisLong)
    {
        makeAir();
    }
    else
    {
        if(solid)
        {
            makeSolid();
        }
    }
    elevate();
    Animate();
    objRays.update();
    objParticles.update();
}
