#include "raygun.h"

Raygun::Raygun()
{
    //ctor
    globalScope = true;
    rays.resize(0);
}

Raygun::~Raygun()
{
    //dtor
}

int Raygun::getSize()
{
    return(rays.size());
}

void Raygun::update()
{
    int i;
    for(i=0; i<rays.size(); i++)
    {
        rays[i].update();
    }
}

void Raygun::setPosition(sf::Vector2f newpos)
{
    int i;
    position = newpos;
    for(i=0; i<rays.size(); i++)
    {
        rays[i].startPoint = newpos;
    }
}

void Raygun::addRay(int type)
{
    rays.resize(rays.size()+1);
    rays.back().startPoint = position;
    //rays.back().setManager(assets);
    //rays.back().setMaths(maths);
}

void Raygun::setManager(ResourceManager* manager)
{
    int i;
    assets = manager;
    maths = &assets->maths;
    for(i=0; i<rays.size(); i++)
    {
        rays[i].setManager(assets);
        rays[i].setMaths(maths);
    }
}
