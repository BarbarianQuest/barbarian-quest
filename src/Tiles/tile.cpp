#include "tile.h"


Tile::Tile() : StaticContent()
{
    //ctor
    tileSize = 64;
    roomPosition.x = 0;
    roomPosition.y = 0;
    id = 0;
    sf::Vector2f halfway(0,0);
    content_id = 1;
    content_type = "tile";
    setOrigin(32,32);
    objHitbox.addRectangularHitbox(halfway,64,64);
    spriteAddresses.push_back("tiles");

    rotateable = false;
    movable = false;
    blocksLOS = false;
    content_id += "_tile";

}

Tile::~Tile()
{
    //dtor
}

void Tile::setManager(ResourceManager* manager)
{
    assets = manager;
}

void Tile::allocateAssets()
{
    int i;
    for(i=0; i<spriteAddresses.size(); i++)
    {
        objSprite.addLayer((assets->getTex(spriteAddresses[i])));
        objSprite.layers[i].splitStaticSheet(tileSize,tileSize);
        objSprite.layers[i].changeReel(id);
        objSprite.layers[i].update();
        objSprite.setPosition(objPosition);
        if(rotateable)
        {
            int num = rand()%4;
            objSprite.Rotate(num*90);
        }
        objSprite.Rotate(rotation);
    }

}


void Tile::setTexture(const sf::Texture& tileTex)
{
    objSprite.addLayer(tileTex);
    objSprite.layers[0].splitStaticSheet(tileSize,tileSize);
    objSprite.layers[0].changeReel(id);
    objSprite.layers[0].centreOrigin();
    objSprite.layers[0].update();
    objSprite.setPosition(objPosition);
    if(rotateable)
    {
        int num = rand()%4;
        objSprite.Rotate(num*90);
    }
}

