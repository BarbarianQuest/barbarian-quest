#include <Tiles/tiles.h>
#include "room.h"

Room::Room()
{
    //ctor
    tileSize = 64;
    tileLayers.resize(1);
}

Room::~Room()
{
    //dtor
}

void Room::setFloorSheet(const sf::Texture & floorTex)
{
    int i,j;
    floorSheet = floorTex;
    for(i=0; i<floorTiles.size(); i++)
    {
        for(j=0; j<floorTiles[i].size(); j++)
        {
            //floorTiles[i][j]->setTexture(roomAssets->getTex("tiles"));
            //floorTiles[i][j]->initialiseAssets(roomAssets);
        }
    }
}

void Room::setManager(ResourceManager* manager)
{
    roomAssets = manager;
    int i,j;
    for(i=0; i<floorTiles.size(); i++)
    {
        for(j=0; j<floorTiles[i].size(); j++)
        {
            (*floorTiles[i][j]).initialiseAssets(roomAssets);
        }
    }
    for(i=0; i<objects.size(); i++)
    {
        objects[i]->initialiseAssets(roomAssets);
    }
}

void Room::setWallSheet(const sf::Texture & wallTex)
{

}

vector<Content*> Room::returnAllContent()
{
    int i;
    vector<Content*> roomContent;
    for(i=0; i<floorTiles.size(); i++)
    {
        roomContent.insert(roomContent.end(),floorTiles[i].begin(),floorTiles[i].end());
    }
    for(i=0; i<objects.size(); i++)
    {
        roomContent.insert(roomContent.end(),objects.begin(),objects.end());
    }
    //add enemies and stuff here
    return roomContent;
}

void Room::setPhysics(PhysicsEngine* in_phys)
{
    physics = in_phys;
}

void Room::collectLayers()
{
    int i;
    for(i=0; i<tileLayers.size(); i++)
    {
        tileLayers[i] = floorTiles;
    }
    return;
}

void Room::addObject(int grid_x, int grid_y, int item_id)
{
    objects.push_back(new ImmortalBox);
    objects.back()->setLocalPosition(grid_x,grid_y);

    //objects.back()->initialiseAssets(roomAssets);
}

void Room::buildCircularRoom(int radius)
{
    int i,j;
    width = height = 2*radius;
    int distanceToCentre;
    int radsqu = radius*radius;
    floorTiles.resize(2*radius);
    for(i = 0; i<floorTiles.size(); i++)
    {
        floorTiles[i].resize(2*radius);
    }

    for(i=0; i<floorTiles.size(); i++)
    {
        for(j=0; j<floorTiles[i].size();j++)
        {
                int xdist = (abs(i-radius));
                int ydist = (abs(j-radius));
                distanceToCentre = xdist*xdist + ydist*ydist;
                if(distanceToCentre < radsqu)
                {
                    floorTiles[i][j] = new Floor;
                }
                else
                {
                    floorTiles[i][j] = new VoidTile;
                }
        }
    }
    for(i=0; i<floorTiles.size(); i++)
    {
        for(j=0; j<floorTiles[i].size();j++)
        {

            floorTiles[i][j]->setLocalPosition(j,i);
        }
    }
    //addObject(2,2,0);
    collectLayers();
}

void Room::buildBasicRoom(int grid_y, int grid_x)
{
    int i,j;
    int tileNum = (grid_x)*(grid_y);
    width = grid_x; height = grid_y;
    bool left,right,top,bottom,tl,tr,bl,br,corner,floor,topwall,topwallbase;

    floorTiles.resize(grid_y);

    for(i=0; i<floorTiles.size(); i++)
    {
        floorTiles[i].resize(grid_x);
    }

    for(i=0; i<floorTiles.size(); i++)
    {
        for(j=0; j<floorTiles[i].size();j++)
        {
                floorTiles[i][j] = new Floor;
        }
    }

    for(i=0; i<floorTiles.size(); i++)
    {
        for(j=0; j<floorTiles[i].size();j++)
        {

            floorTiles[i][j]->setLocalPosition(j,i);
        }
    }
    //addObject(2,2,0);
    collectLayers();

}

void Room::update()
{
    int i,j;
    for(i=0; i<objects.size(); i++)
    {
        if(objects[i]->destroyMe)
        {
            objects.erase(objects.begin()+i);
        }
    }
}

vector <Content*> Room::returnObjects()
{
    return(objects);
}

vector <Content*> Room::returnTilesRowNum(int rowNum)
{
    return(floorTiles[rowNum]);
}

vector <vector <Content*> > Room::returnTiles()
{
    return(floorTiles);
}

sf::Vector2i Room::getRoomPositionOnGrid()
{
    return(roomPosition);
}

void Room::setRoomPosition(int xpos, int ypos)
{
    int i,j;
    roomPosition.x = xpos;
    roomPosition.y = ypos;
    for(i=0; i<floorTiles.size();i++)
    {
        for(j=0; j<floorTiles[i].size(); j++)
        {
            (*floorTiles[i][j]).setParentRoomPosition(xpos,ypos);
        }
    }
    for(i=0; i<objects.size(); i++)
    {
        objects[i]->setParentRoomPosition(xpos,ypos);
    }

}
