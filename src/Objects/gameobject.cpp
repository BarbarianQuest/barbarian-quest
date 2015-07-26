#include "gameobject.h"

GameObject::GameObject() : PassiveContent()
{
    //ctor
    renderPriority = 1;
    content_id += "_obj";
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::setManager(ResourceManager* manager)
{
    assets = manager;
}

void GameObject::allocateAssets()
{
    int i;
    for(i=0; i<spriteAddresses.size(); i++)
    {
        objSprite.addLayer((assets->getTex(spriteAddresses[i])));
    }
    if(shadowString != "null")
    {
        initialiseShadow();
    }
    objSprite.layers[0].changeReel(0);
    objSprite.layers[0].update();
    setPosition(objPosition);
}

