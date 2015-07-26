#include <System Tools/chunk.h>

Chunk::Chunk()
{
    //ctor
    boundsBox.resize(5);
    boundsBox.setPrimitiveType(sf::LinesStrip); //change back to linesstrip to exit detailed debug
    zoneSize = 16;
    bufferSize = 0;
    zoneID = 0;
    zoneBounds.height = zoneBounds.width = zoneSize*64;
    setInactive();
    displayed = true;
    discovered = false;
    blocksLOS = false;
    checked = false;
    tileSheetIndex.x = 0;
    tileSheetIndex.y = 0;
    chunkIndex.x = chunkIndex.y = 0;
}

Chunk::~Chunk()
{
    //dtor
}

void Chunk::setBoxColour(sf::Color newCol)
{
    int i;
    for(i=0; i<boundsBox.getVertexCount(); i++)
    {
        boundsBox[i].color = newCol;
    }
}

void Chunk::setTileSheetIndex(int grid_x, int grid_y)
{
    tileSheetIndex.x = grid_x;
    tileSheetIndex.y = grid_y;
}

void Chunk::setActive()
{
    active = true;
    return;
}

void Chunk::setInactive()
{
    active = false;
    return;
}

void Chunk::toggleDisplayed()
{
    displayed = !displayed;
}

void Chunk::setPosition(sf::Vector2f newpos)
{
    zoneBounds.left = maths.round(newpos.x);
    zoneBounds.top = maths.round(newpos.y);
    zoneBuffer.left = zoneBounds.left - bufferSize;
    zoneBuffer.top = zoneBounds.top - bufferSize;
    boundsBox[0].position = newpos;
    boundsBox[4].position = newpos;
}

void Chunk::updateDelta(float newdel)
{
    int i;
    for(i=0; i<Objects.size(); i++)
    {
        Objects[i]->setDelta(newdel);
    }
}

sf::Vector2f Chunk::getCentre()
{
    sf::Vector2f centre;
    centre.x = zoneBounds.left + zoneBounds.width*0.5;
    centre.y = zoneBounds.top + zoneBounds.height*0.5;
    return(centre);
}

void Chunk::setPosition(float newx, float newy)
{
    sf::Vector2f newPos(newx,newy);

    setPosition(newPos);
}

void Chunk::setSize(int newSize)
{
    zoneSize = newSize;
    zoneBounds.height = zoneBounds.width = zoneSize*64;
    zoneBuffer.height = zoneBuffer.width = zoneSize*64 + 2*bufferSize;
    boundsBox[1].position.x = boundsBox[2].position.x = zoneBounds.left + zoneBounds.width -1;
    boundsBox[1].position.y = zoneBounds.top + 1;
    boundsBox[2].position.y = boundsBox[3].position.y = zoneBounds.top + zoneBounds.height -1;
    boundsBox[3].position.x = zoneBounds.left +1;
}

bool Chunk::contentInContact(Content* obj)
{
    int i;
    for(i=0; i<obj->objHitbox.rects.size(); i++)
    {
        if(zoneBuffer.intersects(obj->objHitbox.rects[i].simpleShape))
        {
            return(true);
        }
    }
    for(i=0; i<obj->objHitbox.circs.size(); i++)
    {
        if(zoneBuffer.intersects(obj->objHitbox.circs[i].simpleShape))
        {
            return(true);
        }
    }
    return(false);
}

bool Chunk::contentIsMember(Content* obj)
{
    return(zoneBounds.contains(obj->getPosition()));
}

void Chunk::addTile(Content* newTile)
{
    Tiles.push_back(newTile);
}

void Chunk::addObject(Content* newObj)
{
    newObj->setParentChunkIndex(chunkIndex);
    Objects.push_back(newObj);
    newObj->bind();
}

void Chunk::setChunkIndex(int c_x, int c_y)
{
    chunkIndex.x = c_x;
    chunkIndex.y = c_y;
}

void Chunk::resetFlags()
{
    int i;
    inContact.clear();
}

void Chunk::addNeighbour(Chunk* newNeighbour) //everybody needs good neighboursss
{
    neighbours.push_back(newNeighbour);
}

vector<Chunk*> Chunk::getNeighbours()
{
    return(neighbours);
}

void Chunk::setNeighbours(vector<Chunk*> newNeighbours)
{
    neighbours = newNeighbours;
}

void Chunk::update()
{
    strays.clear();
    vector<int> rogueElements;
    vector<Content*> tempBuffer;
    setBoxColour(sf::Color::White);
    int i;
    checked = false;

    for(i=0; i<Objects.size(); i++)
    {
        Objects[i]->update();

    }

    if(blocksLOS)
    {
        setBoxColour(sf::Color::Red);
    }

    for(i=0; i<Objects.size(); i++)
    {
        if(Objects[i]->destroyMe)
        {
            //delete Objects[i];
            Objects.erase(Objects.begin()+i);
        }
    }

}

vector<Content*> Chunk::returnStrays()
{
    return(strays);
}
