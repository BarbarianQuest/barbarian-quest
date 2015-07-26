#include <Tiles/voidtile.h>
#include <Tiles/wall.h>
#include "dungeon.h"

Dungeon::Dungeon()
{
    //ctor
    tilesize = 64;
    chunkSize = 1;
    renderRange = 1000;
    oneOverTilesize = 1.0/64;
    circTestRad = 5;
    circTestOriginx = circTestOriginy = 30;
    circTestAngle = 0;
}

Dungeon::~Dungeon()
{
    //dtor
}

void Dungeon::buildCircTest()
{
    circTestx = circTestOriginx + maths.roundAndCast(circTestRad*maths.SinDeg(circTestAngle));
    circTesty = circTestOriginy + maths.roundAndCast(circTestRad*maths.CosDeg(circTestAngle));
    circTestAngle += 1;
    if(circTestAngle > 360)
    {
        circTestAngle -= 360;
    }
}

int Dungeon::getYStrip(float y_pos)
{
    float distanceFromTop = maths.round(y_pos - TLCornerOfTLChunk.y);
    float zonesFromTop = distanceFromTop*oneOverTilesize;
    float roundedZone = floor(zonesFromTop);
    int y_zone = (int) roundedZone;
    return(y_zone);
}

int Dungeon::getXStrip(float x_pos)
{
    float distanceFromLeft = maths.round(x_pos - TLCornerOfTLChunk.x);

    float zonesFromLeft = distanceFromLeft*oneOverTilesize;
    float roundedZone = floor(zonesFromLeft);
    int x_zone = (int) roundedZone;
    return(x_zone);
}

void Dungeon::setChunkNeighbours()
{
    int i, j,k;
    vector<Chunk*> thisNeighbour; //with a little understanding
    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            thisNeighbour.clear();
            thisNeighbour = findNeighbours(&chunks[i][j]);
            chunks[i][j].setNeighbours(thisNeighbour);
            //debug.printNumber("size", (int) thisNeighbour.size());
            for(k=0; k<thisNeighbour.size(); k++)
            {
                bool up, left, right, down;
                int x_ind, y_ind;

                //debug.printVector("index", (sf::Vector2f) thisNeighbour[k]->chunkIndex);
                x_ind = thisNeighbour[k]->chunkIndex.x;

                y_ind = thisNeighbour[k]->chunkIndex.y;
                left = x_ind < i;
                right = x_ind > i;
                up = y_ind < j;
                down = y_ind > j;
                if(up && !down && !left && !right)
                {
                    chunks[i][j].up = thisNeighbour[k];
                    continue;
                }
                if(!up && down && !left && !right)
                {
                    chunks[i][j].down = thisNeighbour[k];
                    continue;
                }
                if(!up && !down && left && !right)
                {
                    chunks[i][j].left = thisNeighbour[k];
                    continue;
                }
                if(!up && !down && !left && right)
                {
                    chunks[i][j].right = thisNeighbour[k];
                    continue;
                }
                if(up && !down && left && !right)
                {
                    chunks[i][j].up_left = thisNeighbour[k];
                    continue;
                }
                if(up && !down && !left && right)
                {
                    chunks[i][j].up_right = thisNeighbour[k];
                    continue;
                }
                if(!up && down && left && !right)
                {
                    chunks[i][j].down_left = thisNeighbour[k];
                    continue;
                }
                if(!up && down && !left && right)
                {
                    chunks[i][j].down_right = thisNeighbour[k];
                    continue;
                }
            }
        }
    }
}

vector<Chunk*> Dungeon::fractalBloom(Chunk* centralChunk)
{
    vector<Chunk*> children;
    vector<Chunk*> bufferSpace;
    //debug.printNumber("index x", (int) centralChunk->chunkIndex.x);
    //debug.printNumber("index y", (int) centralChunk->chunkIndex.y);
    children.clear();
    bufferSpace.clear();
    int i;
    if(!centralChunk->active) {debug.println("not active"); return children;}
    if(centralChunk->checked) {debug.println("checked"); return children;}

    if(centralChunk->blocksLOS)
    {
        centralChunk->discovered = true;
        centralChunk->checked = true;
        children.push_back(centralChunk);
        return children;
    }

    centralChunk->discovered = true;
    centralChunk->checked = true;
    children.push_back(centralChunk);
    //children.insert(children.end(), centralChunk->neighbours.begin(),  centralChunk->neighbours.end());

    for(i=0; i<centralChunk->neighbours.size(); i++)
    {
        bufferSpace.clear();
        if(!centralChunk->neighbours[i]->checked && centralChunk->neighbours[i]->active )
        {
            bufferSpace = fractalBloom(centralChunk->neighbours[i]);
            children.insert(children.end(), bufferSpace.begin(), bufferSpace.end());
        }
    }

    /*for(i=0; i<children.size(); i++)
    {
        children[i]->setBoxColour(sf::Color::Yellow);
    }*/
    return(children);
}

vector<Chunk*> Dungeon::findNeighbours(Chunk* centralChunk)
{
    vector<Chunk*> neighbours;
    int y_ind = getXStrip(centralChunk->getCentre().x);
    int x_ind = getYStrip(centralChunk->getCentre().y);
    int max_ind_y = chunks.size() -1;
    if(max_ind_y == 0)
    {
        cout << "error! Not enough chunks!" << endl;
        return neighbours;
    }
    int max_ind_x = chunks[0].size() -1;

    int i, j;
    for(i=y_ind-1; i<=y_ind+1; i++)
    {
        if(i < 0) {continue;}
        if(i > max_ind_y) {continue;}
        for(j= x_ind-1; j<=x_ind+1; j++)
        {
            if(j < 0) {continue;}
            if(j > max_ind_x) {continue;}

            if(j==x_ind && i==y_ind) {continue;}

            neighbours.push_back(&chunks[i][j]);
        }
    }
    return(neighbours);
}

vector<Chunk*> Dungeon::drawLineBetweenChunks(Chunk* startChunk, Chunk* endChunk)
{

    vector<Chunk*> chunksPassedThrough;
    sf::Vector2f startCentre = startChunk->getCentre();

    sf::Vector2f endCentre = endChunk->getCentre();

    float dx = endCentre.x - startCentre.x;
    float dy = endCentre.y - startCentre.y;

    int i,j,k;

    int yIndexAtStart = startChunk->chunkIndex.y; //getYStrip(startCentre.y);
    int xIndexAtStart = startChunk->chunkIndex.x; //getXStrip(startCentre.x);

    int yIndexAtEnd = endChunk->chunkIndex.x; //getYStrip(endCentre.y);
    int xIndexAtEnd = endChunk->chunkIndex.y;//getXStrip(endCentre.x);

    if(yIndexAtStart == yIndexAtEnd)
    {
        if(xIndexAtEnd >= xIndexAtStart)
        {
            //return a straight line along x
            for(i=xIndexAtStart; i<=xIndexAtEnd; i++)
            {
                chunksPassedThrough.push_back(&chunks[yIndexAtStart][i]);
            }
            for(i=0; i<chunksPassedThrough.size(); i++)
            {
                chunksPassedThrough[i]->setBoxColour(sf::Color::Red);
            }
        }
        if(xIndexAtEnd < xIndexAtStart)
        {
            //return a straight line along x
            for(i=xIndexAtEnd; i<=xIndexAtStart; i++)
            {
                chunksPassedThrough.push_back(&chunks[yIndexAtStart][i]);
            }
            for(i=0; i<chunksPassedThrough.size(); i++)
            {
                chunksPassedThrough[i]->setBoxColour(sf::Color::Red);
            }

        }
        startChunk->setBoxColour(sf::Color::Green);
        endChunk->setBoxColour(sf::Color::Magenta);
        return(chunksPassedThrough);
    }
    if(xIndexAtStart == xIndexAtEnd)
    {
        if(yIndexAtEnd >= yIndexAtStart)
        {
            //return a straight line along y
            for(i=yIndexAtStart; i<=yIndexAtEnd; i++)
            {
                chunksPassedThrough.push_back(&chunks[i][xIndexAtStart]);
            }
            for(i=0; i<chunksPassedThrough.size(); i++)
            {
                chunksPassedThrough[i]->setBoxColour(sf::Color::Red);
            }
        }
        if(yIndexAtEnd < yIndexAtStart)
        {
            //return a straight line along y
            for(i=yIndexAtEnd; i<=yIndexAtStart; i++)
            {
                chunksPassedThrough.push_back(&chunks[i][xIndexAtStart]);
            }
            for(i=0; i<chunksPassedThrough.size(); i++)
            {
                chunksPassedThrough[i]->setBoxColour(sf::Color::Red);
            }
        }

        startChunk->setBoxColour(sf::Color::Green);
        endChunk->setBoxColour(sf::Color::Magenta);
        return(chunksPassedThrough);
    }
    float gradient;
    gradient = dy/dx; //DON'T FORGET THIS IS THE OTHER WAY AROUND FOR THE SAKE OF OPTIMISATION IN CHUNK ACCESS

    int directionInX = 0;
    int directionInY = 0;
    if(endCentre.x < startCentre.x)
    {
        directionInX = -1;
        directionInX = -1;
    }
    if(endCentre.x > startCentre.x)
    {
        directionInX = +1;
    }

    if(endCentre.y < startCentre.y)
    {
        directionInY = -1;
    }
    if(endCentre.y > startCentre.y)
    {
        directionInY = +1;
    }
    float constant = startCentre.x;



    sf::Vector2f endPointInZone = startCentre;
    sf::Vector2f startPointInZone = startCentre;


    int zoneLastChunkX, zoneFirstChunkX;


    float ydiff;
    if(yIndexAtEnd >= yIndexAtStart)
    {
        for(i=yIndexAtStart; i<=yIndexAtEnd; i++)
        {
            if(i==yIndexAtStart || i==yIndexAtEnd)
            {
                ydiff = 32;
            }
            else
            {
                ydiff = 64;
            }
            startPointInZone = endPointInZone;
            endPointInZone.y += ydiff;
            endPointInZone.x = startPointInZone.x + gradient*ydiff;

            zoneLastChunkX = getXStrip(endPointInZone.x);
            zoneFirstChunkX = getXStrip(startPointInZone.x);

            if(zoneLastChunkX >= zoneFirstChunkX)
            {
                for(j=zoneFirstChunkX; j<=zoneLastChunkX; j++)
                {
                    chunksPassedThrough.push_back(&chunks[i][j]);
                }
            }
            if(zoneLastChunkX < zoneFirstChunkX)
            {
                for(j=zoneLastChunkX; j<=zoneFirstChunkX; j++)
                {
                    chunksPassedThrough.push_back(&chunks[i][j]);
                }
            }

        }
    }


    if(yIndexAtEnd < yIndexAtStart)
    {
        for(i=yIndexAtStart; i>=yIndexAtEnd; i--)
        {
            if(i==yIndexAtStart || i==yIndexAtEnd)
            {
                ydiff = 32;
            }
            else
            {
                ydiff = 64;
            }
            startPointInZone = endPointInZone;
            endPointInZone.y -= ydiff;
            endPointInZone.x = startPointInZone.x - gradient*ydiff;

            zoneLastChunkX = getXStrip(endPointInZone.x);
            zoneFirstChunkX = getXStrip(startPointInZone.x);

            if(zoneLastChunkX >= zoneFirstChunkX)
            {
                for(j=zoneFirstChunkX; j<=zoneLastChunkX; j++)
                {
                    chunksPassedThrough.push_back(&chunks[i][j]);
                }
            }
            if(zoneLastChunkX < zoneFirstChunkX)
            {
                for(j=zoneLastChunkX; j<=zoneFirstChunkX; j++)
                {
                    chunksPassedThrough.push_back(&chunks[i][j]);
                }
            }

        }
    }
    for(i=0; i<chunksPassedThrough.size(); i++)
    {
        chunksPassedThrough[i]->setBoxColour(sf::Color::Red);
    }
    startChunk->setBoxColour(sf::Color::Green);
    endChunk->setBoxColour(sf::Color::Magenta);
    return(chunksPassedThrough);
}

void Dungeon::setEventHandler(EventHandler* newEvents)
{
    events = newEvents;
}

void Dungeon::updateDelta(float newdel)
{
    int i,j;
    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            if(!chunks[i][j].active) {continue;}
            chunks[i][j].updateDelta(newdel);
        }
    }
}

void Dungeon::setBasicFloorSheet(const sf::Texture & floorSheet)
{
    int i;
    defaultFloorTiles = floorSheet;
    for(i=0; i< rooms.size(); i++)
    {
        rooms[i].setFloorSheet(floorSheet);
    }
}

void Dungeon::setManager(ResourceManager* manager)
{
    levelassets = manager;
    int i;
    for(i=0; i<rooms.size(); i++)
    {
        rooms[i].setManager(levelassets);
    }
    testGun.setManager(levelassets);
}

void Dungeon::setBasicWallSheet(const sf::Texture & wallSheet)
{
    defaultWallTiles = wallSheet;
}

void Dungeon::setPhysics(PhysicsEngine* in_phys)
{
    int i;
    physics = in_phys;
    for(i=0; i<rooms.size(); i++)
    {
        rooms[i].setPhysics(physics);
    }
}

void Dungeon::addBasicRoom(int xpos, int ypos, int xsize, int ysize)
{
    int i = 0;
    Room newRoom;
    newRoom.setPhysics(physics);
    newRoom.buildBasicRoom(xsize,ysize);
    newRoom.setRoomPosition(xpos,ypos);
    newRoom.setManager(levelassets);
    rooms.push_back(newRoom);
}

void Dungeon::addBasicCircularRoom(int xpos, int ypos, int radius)
{
    Room newRoom;
    newRoom.setPhysics(physics);
    newRoom.buildCircularRoom(radius);
    newRoom.setRoomPosition(xpos,ypos);
    newRoom.setManager(levelassets);
    rooms.push_back(newRoom);
}

void Dungeon::addObjectToRoom(int roomnum, int grid_x, int grid_y, int type)
{
    if(roomnum>= rooms.size() || roomnum < 0)
    {
        cout << "room does not exist\n";
        return;
    }
    rooms[roomnum].addObject(grid_x,grid_y,type);
    updateRooms();
}

void Dungeon::addObject(int grid_x,int grid_y, int type)
{
    if(type == 0)
    {
        addHorizDoor(grid_x,grid_y,0);
        return;
    }
    if(type == 1)
    {
        addVertDoor(grid_x, grid_y,0);
        return;
    }
    if(type == 2)
    {
        globalObjects.push_back(new Chest);
    }
    if(type == 3)
    {
        globalObjects.push_back(new ImmortalBox);
    }
    if(type == 4)
    {
        globalObjects.push_back(new Pot);
    }
    if(type == 5)
    {
        globalObjects.push_back(new Cauldron);
    }
    if(type == 6)
    {
        globalObjects.push_back(new VerticalArrowTrap);
    }
    if(type == 7)
    {
        globalObjects.push_back(new Football);
    }
    if(type == 8)
    {
        globalObjects.push_back(new Bomb);
    }
    if(type == 9)
    {
        globalEntities.push_back(new GelatinousCube);
        globalEntities.back()->addAggro(players.front());
        globalObjects.push_back(globalEntities.back());
    }
    globalObjects.back()->setPosition(grid_x*64,grid_y*64);
    globalObjects.back()->setManager(levelassets);
    globalObjects.back()->allocateAssets();
    globalObjects.back()->setMaths(&maths);
    globalObjects.back()->generateTag();
    globalObjects.back()->setEventHandler(events);
    globalObjects.back()->setDungeon(&globalObjects);
    globalObjects.back()->extraAllocations();

    int i,j;

}

bool isFloor(Content* tile)
{
    bool floortile = tile->idContains("floor");
    return(floortile);
}

bool isVoid(Content* tile)
{
    bool voidtile = tile->idContains("void") && tile->idContains("tile");
    return(voidtile);
}

vector<bool> checkTile(Content* tile)
{
    vector<bool> checks;
    bool this_floor, this_void;
    bool this_wall, this_leftwall, this_rightwall;
    bool this_topwall, this_secondtopwall, this_toptopwall;
    bool this_botwall, this_secondbotwall, this_botbotwall;
    bool this_BR, this_BL, this_TR, this_TL;

    this_floor = false;
    this_void = false;
    this_wall = false;
    this_leftwall = false;
    this_rightwall = false;
    this_toptopwall = false;
    this_topwall = false;
    this_secondbotwall = false;
    this_secondtopwall = false;
    this_botbotwall = false;
    this_botwall = false;
    this_BR = false;
    this_BL = false;
    this_TR = false;
    this_TR = false;

    this_floor = tile->idContains("floor");
    this_void =  tile->idContains("void") && tile->idContains("tile");
    this_wall = tile->idContains("wall");
    this_leftwall = tile->idContains("base_left") && this_wall;
    this_rightwall = tile->idContains("base_right") && this_wall;
    this_topwall = tile->idContains("base_top") && this_wall;
    this_secondtopwall = tile->idContains("base_secondtop") && this_wall;
    this_toptopwall = tile->idContains("base_toptop") && this_wall;
    this_botwall = tile->idContains("base_bot") && this_wall;
    this_secondbotwall = tile->idContains("base_secondbot") && this_wall;
    this_botbotwall = tile->idContains("base_bbot") && this_wall;
    this_BR = tile->idContains("base_BR") && this_wall;
    this_BL = tile->idContains("base_BL") && this_wall;
    this_TR = tile->idContains("base_TR") && this_wall;
    this_TL = tile->idContains("base_TL") && this_wall;

    checks.push_back(this_floor);
    checks.push_back(this_void);
    checks.push_back(this_wall);
    checks.push_back(this_leftwall);
    checks.push_back(this_rightwall);
    checks.push_back(this_topwall);
    checks.push_back(this_secondtopwall);
    checks.push_back(this_toptopwall);
    checks.push_back(this_botwall);
    checks.push_back(this_secondbotwall);
    checks.push_back(this_botbotwall);
    checks.push_back(this_TL);
    checks.push_back(this_TR);
    checks.push_back(this_BR);
    checks.push_back(this_BL);

    return(checks);

}

void Dungeon::populateTileSheet()
{
    int i,j;
    int y_buffer = 4;
    int x_buffer = 2;
    sf::Vector2i room_pos;
    if(rooms.size() < 1)
    {
        debug.println("catastrophic room failure");
        return;
    }
    room_pos = rooms[0].getRoomPositionOnGrid();
    min_x = room_pos.x;
    max_x = room_pos.x + rooms[0].width;
    min_y = room_pos.y;
    max_y = room_pos.y + rooms[0].height;
    for(i=0; i<rooms.size();i++)
    {
        room_pos = rooms[i].getRoomPositionOnGrid();
        if(room_pos.x < min_x) {min_x = room_pos.y;}
        if(room_pos.y < min_y) {min_y = room_pos.y;}
        if(room_pos.x + rooms[i].width > max_x) {max_x = room_pos.x + rooms[i].width;}
        if(room_pos.y + rooms[i].height > max_y) {max_y = room_pos.y + rooms[i].height;}
    }

    t = min_y-y_buffer;
    l = min_x-x_buffer;
    r = max_x - 1+ x_buffer;
    b = max_y - 1;
    gridsize_x = max_x-min_x+2*x_buffer;
    gridsize_y = max_y-min_y+2*y_buffer;
    int sizeOfTileSheet = (max_x+min_x+2*x_buffer)*(max_y+min_y+2*y_buffer);
    int zoneNum_x = gridsize_x/chunkSize + 1;
    int zoneNum_y = gridsize_y/chunkSize + 1;

    chunks.resize(zoneNum_x);
    for(i=0; i<chunks.size(); i++)
    {
        chunks[i].resize(zoneNum_y);
    }

    tiles.resize(gridsize_y);
    for(i=0; i<tiles.size(); i++)
    {
        tiles[i].resize(gridsize_x);
    }
    for(i=0; i<tiles.size(); i++)
    {
        for(j=0; j<tiles[i].size(); j++)
        {
            tiles[i][j] = new VoidTile;
        }
    }

    /*cout << "drawing a ";
    cout << max_x-min_x+2*x_buffer;
    cout << " by ";
    cout << max_y-min_y+2*y_buffer;
    cout << " grid\n";*/
    for(i=0; i<rooms.size();i++)
    {
        room_pos = rooms[i].getRoomPositionOnGrid();
        /*cout << "room size: ";
        cout << rooms[i].height;
        cout << " , ";
        cout << rooms[i].width;
        cout <<"\n";*/
        for(j=0;j<rooms[i].height;j++)
        {
            vector<Content*> temp = rooms[i].returnTilesRowNum(j);
            std::vector<Content*>::iterator it = tiles[y_buffer+room_pos.y-min_y+j].begin();
            tiles[y_buffer+room_pos.y-min_y+j].erase(it+x_buffer+room_pos.x-min_x,it+x_buffer+room_pos.x-min_x+temp.size());
            tiles[y_buffer+room_pos.y-min_y+j].insert(it+x_buffer+room_pos.x-min_x,temp.begin(),temp.end());
        }
        /*cout << "room: ";
        cout << i;
        cout << " complete\n";*/
    }
    int maxsize = 0;
    for(i=0; i<tiles.size(); i++)
    {
        if (tiles[i].size() > maxsize)
        {
            maxsize = tiles[i].size();
        }
    }
    vector <Content*> padding;
    for(i=0; i<tiles.size(); i++)
    {
        padding.erase(padding.begin(), padding.end());
        padding.resize(maxsize - tiles[i].size());
        for(j=0; j<padding.size(); j++)
        {
            padding[j] = new VoidTile();
        }
        tiles[i].insert(tiles[i].end(),padding.begin(),padding.end());
    }

    for(i=0; i<tiles.size(); i++)
    {

        for(j=0; j<tiles[i].size(); j++)
        {

        }
    }

    /*cout << "all rooms complete\n";

    cout << "setting tile positions...\n";*/

    for(i=0; i<tiles.size(); i++)
    {
        for(j=0; j<tiles[i].size(); j++)
        {
            tiles[i][j]->setPosition((j+l)*tilesize, (i+t)*tilesize);
        }

    }
    //cout << "doing dungeon edge detection...\n";
    for(i=1; i<tiles.size()-1; i++)
    {
        for(j=1; j<tiles[i].size()-1; j++)
        {
            bool this_floor, this_void;
            bool floor_left, floor_right, floor_top, floor_bottom, floor_tl, floor_tr, floor_bl, floor_br;
            bool void_left, void_right, void_top, void_bottom, void_tl, void_tr, void_bl, void_br;

            this_floor = isFloor(tiles[i][j]);
            this_void = isVoid(tiles[i][j]);

            floor_left = isFloor(tiles[i][j-1]);
            void_left = isVoid(tiles[i][j-1]);
            floor_right = isFloor(tiles[i][j+1]);
            void_right = isVoid(tiles[i][j+1]);
            floor_top = isFloor(tiles[i-1][j]);
            void_top = isVoid(tiles[i-1][j]);
            floor_bottom = isFloor(tiles[i+1][j]);
            void_bottom = isVoid(tiles[i+1][j]);

            if(floor_left && void_right && this_void)
            {
                replaceTile(i,j,new RightWall);
            }
            if(floor_right && void_left && this_void)
            {
                replaceTile(i,j,new LeftWall);
            }

            if(floor_bottom && void_top && this_void)
            {
                replaceTile(i,j,new TopWall);
                replaceTile(i-1,j,new SecondTopWall);
                replaceTile(i-2,j, new TopTopWall);
            }
            if(floor_top && void_bottom && this_void)
            {
                replaceTile(i-2,j,new BotWall);
                replaceTile(i-1, j, new SecondBotWall);
                replaceTile(i,j,new BotBotWall);
            }


        }

    }

    int floor_index = 0;
    int void_index = 1;
    int wall_index = 2;
    int leftwall_index = 3;
    int rightwall_index = 4;
    int top_index = 5;
    int sectop_index = 6;
    int toptop_index = 7;
    int bot_index = 8;
    int secbot_index = 9;
    int botbot_index = 10;
    int TL_index = 11;
    int TR_index = 12;
    int BR_index = 13;
    int BL_index = 14;
            vector< vector <bool> > squareBools, allBools;
            vector<bool> this_tile, left, right, up, down, up_left, up_right, down_left, down_right;


    //cout << "correcting wall types...\n";
    for(i=1; i<tiles.size()-1; i++)
    {
        for(j=1; j<tiles[i].size()-1; j++)
        {
            Content* tile = tiles[i][j];

            int wallsInSquareContact = 0;
            int wallsInDiagContact = 0;

            this_tile = checkTile(tile);
            left = checkTile(tiles[i][j-1]);
            right = checkTile(tiles[i][j+1]);
            up = checkTile(tiles[i-1][j]);
            up_left = checkTile(tiles[i-1][j-1]);
            up_right = checkTile(tiles[i-1][j+1]);
            down = checkTile(tiles[i+1][j]);
            down_left = checkTile(tiles[i+1][j-1]);
            down_right = checkTile(tiles[i+1][j+1]);

            squareBools.clear();
            allBools.clear();

            squareBools.push_back(left);
            squareBools.push_back(right);
            squareBools.push_back(up);
            squareBools.push_back(down);

            allBools.insert(allBools.begin(), squareBools.begin(), squareBools.end());
            allBools.push_back(up_left);
            allBools.push_back(up_right);
            allBools.push_back(down_left);
            allBools.push_back(down_right);

            int k;

            for(k=0; k<squareBools.size(); k++)
            {
                if(squareBools[k][wall_index])
                {
                    wallsInSquareContact++;
                }
            }

            for(k=0; k<allBools.size(); k++)
            {
                if(allBools[k][wall_index])
                {
                    wallsInDiagContact++;
                }
            }

            bool sidewall = (this_tile[leftwall_index] || this_tile[rightwall_index]);
            bool sidewall_down = (down[leftwall_index] || down[rightwall_index]);
            bool sidewall_up = (up[leftwall_index] || up[rightwall_index]);
            bool sidewall_left = (left[leftwall_index] || left[rightwall_index]);
            bool sidewall_right = (right[leftwall_index] || right[rightwall_index]);
            //filling in gaps
            bool wallincontact;
            bool botbotedge, toptopedge, botbotvoid,diagbotwall;

            wallincontact = wallsInSquareContact >= 2 && (this_tile[wall_index] || this_tile[void_index]);
            botbotedge = wallincontact && (!this_tile[botbot_index] && down[floor_index]
                                        && (right[botbot_index] || left[botbot_index]));
            botbotvoid = wallincontact && (this_tile[void_index] && sidewall_up && !sidewall_down);
            toptopedge =  wallincontact && (!this_tile[top_index] && down[floor_index]
                                        && (right[top_index] || left[top_index]));

            diagbotwall = wallincontact &&( (this_tile[void_index] && (left[botbot_index] || left[rightwall_index]) && up[botbot_index] && !up_right[void_index] && !up_left[botbot_index]
                                            && !up_left[rightwall_index])
                                            || (this_tile[void_index] && (right[botbot_index] || right[leftwall_index]) && up[botbot_index] && !up_left[void_index] && !up_right[botbot_index]
                                            && !up_right[leftwall_index]));




            if(botbotvoid)
            {
                replaceTile(i,j,new BotBotWall);
                tiles[i][j]->makeSolid();
                tiles[i][j]->solid = true;
                replaceTile(i-1,j, new SecondBotWall);
                tiles[i-1][j]->makeSolid();
                tiles[i-1][j]->solid = true;
                replaceTile(i-2,j,new BotWall);
                tiles[i-2][j]->makeSolid();
                tiles[i-2][j]->solid = true;
            }



            if(botbotedge)
            {
                replaceTile(i,j,new BotBotWall);
                tiles[i][j]->makeSolid();
                tiles[i][j]->solid = true;
                replaceTile(i-1,j, new SecondBotWall);
                tiles[i-1][j]->makeSolid();
                tiles[i-1][j]->solid = true;
                replaceTile(i-2,j,new BotWall);
                tiles[i-2][j]->makeSolid();
                tiles[i-2][j]->solid = true;
            }

            if(diagbotwall)
            {
                replaceTile(i,j,new BotBotWall);
                tiles[i][j]->makeSolid();
                tiles[i][j]->solid = true;
                replaceTile(i-1,j, new SecondBotWall);
                tiles[i-1][j]->makeAir();
                tiles[i-1][j]->solid = false;
                replaceTile(i-2,j,new BotWall);
            }

            if(toptopedge)
            {
                replaceTile(i,j,new TopWall);
                tiles[i][j]->makeSolid();
                tiles[i][j]->solid = true;
                replaceTile(i-1,j, new SecondTopWall);
                tiles[i-1][j]->makeSolid();
                tiles[i-1][j]->solid = true;
                replaceTile(i-2,j,new TopTopWall);
                tiles[i-2][j]->makeSolid();
                tiles[i-2][j]->solid = true;
            }


        }

    }

    //cout << "first loop!\n";
    for(i=1; i<tiles.size()-1; i++)
    {
        for(j=1; j<tiles[i].size()-1; j++)
        {
            Content* tile = tiles[i][j];

            int wallsInSquareContact = 0;
            int wallsInDiagContact = 0;

            this_tile = checkTile(tile);
            left = checkTile(tiles[i][j-1]);
            right = checkTile(tiles[i][j+1]);
            up = checkTile(tiles[i-1][j]);
            up_left = checkTile(tiles[i-1][j-1]);
            up_right = checkTile(tiles[i-1][j+1]);
            down = checkTile(tiles[i+1][j]);
            down_left = checkTile(tiles[i+1][j-1]);
            down_right = checkTile(tiles[i+1][j+1]);

            squareBools.clear();
            allBools.clear();

            squareBools.push_back(left);
            squareBools.push_back(right);
            squareBools.push_back(up);
            squareBools.push_back(down);

            allBools.insert(allBools.begin(), squareBools.begin(), squareBools.end());
            allBools.push_back(up_left);
            allBools.push_back(up_right);
            allBools.push_back(down_left);
            allBools.push_back(down_right);

                        //filling in gaps
            bool wallincontact;
            bool botbotedge, toptopedge;

            int k;

            for(k=0; k<squareBools.size(); k++)
            {
                if(squareBools[k][wall_index])
                {
                    wallsInSquareContact++;
                }
            }

            for(k=0; k<allBools.size(); k++)
            {
                if(allBools[k][wall_index])
                {
                    wallsInDiagContact++;
                }
            }

            wallincontact = wallsInSquareContact >= 2 && (this_tile[wall_index] || this_tile[void_index]);

            bool sidewall = (this_tile[leftwall_index] || this_tile[rightwall_index]);
            bool sidewall_down = (down[leftwall_index] || down[rightwall_index]);
            bool sidewall_up = (up[leftwall_index] || up[rightwall_index]);
            bool sidewall_left = (left[leftwall_index] || left[rightwall_index]);
            bool sidewall_right = (right[leftwall_index] || right[rightwall_index]);

            bool sidewalledge = !sidewall && sidewall_down && (this_tile[botbot_index] || this_tile[secbot_index]
                                            || (this_tile[void_index] && ((left[top_index] || left[toptop_index])
                                            || (right[top_index] || right[toptop_index]))));

            bool sidewallmissing = !sidewall && up[bot_index] && down[toptop_index];


            if(sidewalledge)
            {
                if(up[leftwall_index] || down[leftwall_index])
                {
                    replaceTile(i,j, new LeftWall);
                    replaceTile(i-1,j, new LeftWall);
                    tiles[i-1][j]->makeAir();
                    tiles[i-1][j]->solid = false;
                }
                if(up[rightwall_index] || down[rightwall_index])
                {
                    replaceTile(i,j, new RightWall);
                    replaceTile(i-1,j, new RightWall);
                    tiles[i-1][j]->makeAir();
                    tiles[i-1][j]->solid = false;
                }
            }

            if(sidewallmissing)
            {
                if(left[floor_index])
                {
                    replaceTile(i,j, new RightWall);
                    tiles[i][j]->makeAir();
                    tiles[i][j]->solid = false;
                }
                if(right[floor_index])
                {
                    replaceTile(i,j, new LeftWall);
                    tiles[i][j]->makeAir();
                    tiles[i][j]->solid = false;
                }
            }



        }

    }
    for(i=1; i<tiles.size()-1; i++)
    {
        for(j=1; j<tiles[i].size()-1; j++)
        {
            Content* tile = tiles[i][j];

            int wallsInSquareContact = 0;
            int wallsInDiagContact = 0;

            this_tile = checkTile(tile);
            left = checkTile(tiles[i][j-1]);
            right = checkTile(tiles[i][j+1]);
            up = checkTile(tiles[i-1][j]);
            up_left = checkTile(tiles[i-1][j-1]);
            up_right = checkTile(tiles[i-1][j+1]);
            down = checkTile(tiles[i+1][j]);
            down_left = checkTile(tiles[i+1][j-1]);
            down_right = checkTile(tiles[i+1][j+1]);

            squareBools.clear();
            allBools.clear();

            squareBools.push_back(left);
            squareBools.push_back(right);
            squareBools.push_back(up);
            squareBools.push_back(down);

            allBools.insert(allBools.begin(), squareBools.begin(), squareBools.end());
            allBools.push_back(up_left);
            allBools.push_back(up_right);
            allBools.push_back(down_left);
            allBools.push_back(down_right);

                        //filling in gaps
            bool wallincontact;
            bool botbotedge, toptopedge;

            int k;

            for(k=0; k<squareBools.size(); k++)
            {
                if(squareBools[k][wall_index])
                {
                    wallsInSquareContact++;
                }
            }

            for(k=0; k<allBools.size(); k++)
            {
                if(allBools[k][wall_index])
                {
                    wallsInDiagContact++;
                }
            }

            wallincontact = wallsInSquareContact >= 2 && (this_tile[wall_index] || this_tile[void_index]);

            bool sidewall = (this_tile[leftwall_index] || this_tile[rightwall_index]);
            bool sidewall_down = (down[leftwall_index] || down[rightwall_index]);
            bool sidewall_up = (up[leftwall_index] || up[rightwall_index]);
            bool sidewall_left = (left[leftwall_index] || left[rightwall_index]);
            bool sidewall_right = (right[leftwall_index] || right[rightwall_index]);

                        //corners

            //case 1: a tile has walls on two sides and is a wall or void tile.
            bool corner;


            corner = wallincontact && (this_tile[botbot_index] || this_tile[toptop_index] || this_tile[bot_index] || this_tile[void_index] || sidewall);

            if(corner)
            {
                if(((left[bot_index] || left[toptop_index] || left[BL_index] || left[TL_index]) && (sidewall_up ||up[TR_index] || up[TL_index]))) {replaceTile(i,j,new BRCornerWall);}
                if(((right[bot_index] || right[toptop_index] || right[BR_index] || right[TR_index]) &&  (sidewall_up || up[TR_index] || up[TL_index]) )) {replaceTile(i,j,new BLCornerWall);}
                if((right[toptop_index] || right[bot_index] || right[BR_index] || right[TR_index]) &&  (sidewall_down || down[TR_index] || down[TL_index] )) {replaceTile(i,j,new TLCornerWall);}
                if((left[toptop_index] || left[bot_index]|| left[BL_index] || left[TL_index]) && (sidewall_down || down[TR_index] || down[TL_index]) ) {replaceTile(i,j,new TRCornerWall);}
                if(up[bot_index] && this_tile[bot_index] && (right[bot_index] || right[TR_index]) && up_left[BL_index])
                {
                    replaceTile(i,j,new BLCornerWall);
                    replaceTile(i-1,j, new TRCornerWall);
                    tiles[i][j]->makeAir();
                    tiles[i][j]->solid = false;
                }
                if(up[bot_index] && this_tile[bot_index] && (left[bot_index] || left[TL_index]) && up_right[BR_index])
                {
                    replaceTile(i,j,new BRCornerWall);
                    replaceTile(i-1,j, new TLCornerWall);
                    tiles[i][j]->makeAir();
                    tiles[i][j]->solid = false;
                }
                if(this_tile[void_index] && down[toptop_index] && (left[toptop_index] || left[BL_index]))
                {
                    replaceTile(i,j,new TRCornerWall);

                    replaceTile(i+1,j, new BLCornerWall);
                    tiles[i+1][j]->makeAir();
                    tiles[i+1][j]->solid = false;
                }
                if(this_tile[void_index] && down[toptop_index] && (right[toptop_index] || right[BR_index]))
                {
                    replaceTile(i,j,new TLCornerWall);
                    replaceTile(i+1,j, new BRCornerWall);
                    tiles[i+1][j]->makeAir();
                    tiles[i+1][j]->solid = false;
                }
            }


        }
    }
    arrangeChunks();
    populateChunkTiles();
}

void Dungeon::addPlayer(vector<Content*> newPlay)
{
    int i;
    if(newPlay.size()==0) {return;}
    players.push_back(newPlay[0]);
    for(i=0; i<newPlay.size(); i++)
    {
        globalObjects.push_back(newPlay[i]);
    }
}

void Dungeon::arrangeChunks()
{
    int i, j;
    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            chunks[i][j].setPosition((i*chunkSize + min_x - 3.5)*64,(j*chunkSize + min_y - 6.5)*64);
            chunks[i][j].setChunkIndex(i,j);
            //cout << chunks[i][j].zoneBounds.left << ", " << chunks[i][j].zoneBounds.top << endl;
            chunks[i][j].setSize(chunkSize);
            if(i==0 && j==0) {TLCornerOfTLChunk.x = chunks[i][j].getCentre().x - 32; TLCornerOfTLChunk.y = chunks[i][j].getCentre().y - 32;}
        }
    }
    setChunkNeighbours();
}

void Dungeon::populateChunkTiles()
{
    int i,j,k,l;

    for(i=0; i<tiles.size(); i++)
    {
        for(j=0; j<tiles[i].size(); j++)
        {
            tiles[i][j]->setMaths(&maths);
            for(k=0; k<chunks.size(); k++ )
            {
                for(l=0; l<chunks[k].size(); l++)
                {
                    if(chunks[k][l].contentIsMember(tiles[i][j]))
                    {
                        chunks[k][l].addTile(tiles[i][j]);
                        if(tiles[i][j]->blocksLOS) {chunks[k][l].blocksLOS = true;}
                        chunks[k][l].setTileSheetIndex(i,j);
                    }
                }
            }
        }

    }


    min_chunk_x = chunks.front().front().zoneBounds.left;
    min_chunk_y = chunks.front().front().zoneBounds.top;
    max_chunk_x = chunks.back().back().zoneBounds.left;
    max_chunk_y = chunks.back().back().zoneBounds.top;
}

void Dungeon::updateChunkObjects()
{
    int i,j,k;
    for(k=0; k<globalObjects.size(); k++)
    {
        for(i=0; i<chunks.size(); i++)
        {
            for(j=0; j<chunks[i].size(); j++)
            {
                if(chunks[i][j].contentIsMember(globalObjects[k]))
                {
                    chunks[i][j].addObject(globalObjects[k]);
                }
            }
        }
    }


    //objects.insert(objects.end(), globalObjects.begin(), globalObjects.end());
    globalObjects.clear();

}


void Dungeon::replaceTile(int i, int j, Content* newTile)
{
    bool solid = tiles[i][j]->isSolid() && !tiles[i][j]->idContains("void");
    bool blocksLOS = tiles[i][j]->blocksLOS && !tiles[i][j]->idContains("void");
    if(solid)
    {
        newTile->makeSolid();
        newTile->blocksLOS = true;
    }

    if(blocksLOS)
    {
        newTile->blocksLOS = true;
    }

    tiles[i][j] = newTile;

    tiles[i][j]->setPosition((j+l)*tilesize,(t+i)*tilesize);
    tiles[i][j]->setManager(levelassets);
    tiles[i][j]->allocateAssets();
}

void Dungeon::updateWindowInfo(sf::Vector2f window_pos)
{
    windowPosition = window_pos;
}

void Dungeon::setHitboxMode(bool mode)
{
    int i,j,k;
    for(i=0; i<chunks.size(); i++)
        {
        for(j=0; j<chunks[i].size(); j++)
            {
                for(k=0; k<chunks[i][j].Objects.size(); k++)
                {
                    chunks[i][j].Objects[k]->drawHitbox = mode;
                }
                for(k=0; k<chunks[i][j].Tiles.size(); k++)
                {
                    chunks[i][j].Tiles[k]->drawHitbox = mode;
                }
            }
        }
}

void Dungeon::resetFlags()
{
    int i,j;
    for(i=0; i<chunks.size(); i++)
        {
        for(j=0; j<chunks[i].size(); j++)
            {
                chunks[i][j].resetFlags();
            }

        }
}

void Dungeon::setPlayers(vector<Content> * newplay)
{
    int i;
    int k, j;
    for(i=0; i<newplay->size(); i++)
    {
        players.push_back(&(*newplay)[i]);
    }

}

void Dungeon::setPlayers(vector<Player> * newplay)
{
    int i;
    int k, j;
    for(i=0; i<newplay->size(); i++)
    {
        players.push_back(&(*newplay)[i]);
    }
    for(k=0; k<players.size(); k++)
    {
        for(i=0; i<chunks.size(); i++)
        {
            for(j=0; j<chunks[i].size(); j++)
            {
                if(chunks[i][j].contentIsMember(players[k]))
                {
                    chunks[i][j].addObject(players[k]);
                }
            }
        }
    }
}

Chunk* Dungeon::getParentChunk(Content* obj)
{
    int i,j;
    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            if(chunks[i][j].contentIsMember(obj))
            {
                return (&chunks[i][j]);
            }
        }

    }
}

sf::Vector2i Dungeon::getParentChunkIndex(Content* obj)
{
    int i,j;
    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            if(chunks[i][j].contentIsMember(obj))
            {
                sf::Vector2i chunkIndex(i,j);
                return (chunkIndex);
            }
        }

    }
}

sf::Vector2i Dungeon::getTileSheetIndex(Chunk* chu)
{
    return(chu->tileSheetIndex);
}

void Dungeon::addHorizDoor(int grid_x, int grid_y, int type)
{
    globalObjects.push_back(new HorizDoor);
    globalObjects.back()->setPosition(grid_x*64,grid_y*64);
    globalObjects.back()->setManager(levelassets);
    globalObjects.back()->allocateAssets();
    globalObjects.back()->setMaths(&maths);
    globalObjects.back()->setDungeon(&globalObjects);

    sf::Vector2i par = getParentChunkIndex(globalObjects.back());
    //cout << "par: " << par.x << ", " << par.y << endl;
    int i;
    for(i=0; i<4; i++)
    {
        chunks[par.x+i][par.y].blocksLOS = true;
    }


}

void Dungeon::addVertDoor(int grid_x, int grid_y, int type)
{
    globalObjects.push_back(new VerticDoor);


    globalObjects.back()->setPosition(grid_x*64,grid_y*64);
    globalObjects.back()->setManager(levelassets);
    globalObjects.back()->allocateAssets();
    globalObjects.back()->setMaths(&maths);
    globalObjects.back()->setDungeon(&globalObjects);
    sf::Vector2i par = getParentChunkIndex(globalObjects.back());
    int i;
    for(i=0; i<6; i++)
    {
        chunks[par.x][par.y+i-1].blocksLOS = true;
    }

}

void Dungeon::passObjectBetweenChunks(Content* obj, Chunk* from, Chunk* to)
{
    int i;
    for(i=0; i<from->Objects.size(); i++)
    {
        if(obj == from->Objects[i])
        {
            to->addObject(obj);
            from->Objects.erase(from->Objects.begin() + i);
        }
    }
}

Chunk* Dungeon::nearestDiscoveredChunk(Chunk* chu)
{
    int i;
    for(i=0; i<chu->neighbours.size(); i++)
    {
        if(chu->neighbours[i]->discovered && !chu->neighbours[i]->blocksLOS)
        {
            return(chu->neighbours[i]);
        }
    }
    return(chu);
}

void Dungeon::addObject(int objX, int objY, string objName)
{

    if(objName == "h_door"){addHorizDoor(objX,objY,0); return;}
    if(objName == "v_door"){addVertDoor(objX,objY,0); return;}
    if(objName == "bomb"){return;}
    debug.println(objName + " not found in object database");
    return;
}

void Dungeon::updateRooms()
{
    int i,j,k;
    int l, m;



    activeChunks.clear();
    activeObjects.clear();
    //BUILD ACTIVECHUNKS VECTOR

    int maxBuffer = 1000;
    int buffernum = 0;
    int globoSize = globalObjects.size();
    vector <Chunk*> inRange;

    for(i=0; i<events->events.size(); i++)
    {
        GameEvent* currentEvent = events->events[i];
        string command = currentEvent->getCommand();
        string args = currentEvent->getArgs();
        vector<string> variables = currentEvent->getVariables();
        string object = currentEvent->getObject();

        if(object == "error") {debug.println("barbscript error: object not provided"); continue;}


        if (command == "new")
        {
            string objectType = object;
            int object_x, object_y;
            debug.println("adding " + object +" to dungeon");

            //object position parsing
            if(variables.size() != 0)
            {
                cout << "trigger!";
            }
            addObject(0,0,objectType);
        }
    }
    events->clean();

    for(i=0; i<globoSize; i++)
    {
        if(globalObjects[i]->destroyMe)
        {
            globalObjects.erase(globalObjects.begin()+i);
            i--;
            globoSize -= 1;
            continue;
        }
        if(!globalObjects[i]->isBound())
        {
            for(l=0; l<chunks.size(); l++)
            {
                for(m=0; m<chunks[l].size(); m++)
                {
                    if(chunks[l][m].contentIsMember(globalObjects[i]))
                    {
                        chunks[l][m].addObject(globalObjects[i]);
                    }
                }
            }
            buffernum += 1;
            if(buffernum >= maxBuffer) {break;}
        }
    }

    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            if(fabs(maths.magnitude(chunks[i][j].getCentre() - windowPosition)) < renderRange)
            {
                    chunks[i][j].setActive();
                    inRange.push_back(&chunks[i][j]);
            }
            else
            {
                chunks[i][j].setInactive();
            }
            chunks[i][j].resetFlags();
        }
    }

    int player_x = getXStrip(windowPosition.x);
    int player_y = getYStrip(windowPosition.y);
    if(!chunks[player_x][player_y].blocksLOS)
    {
        fractalBloom(&chunks[player_x][player_y]);
    }
    if(chunks[player_x][player_y].blocksLOS)
    {
         fractalBloom(nearestDiscoveredChunk(&chunks[player_x][player_y]));
    }

    for(i=0; i<inRange.size(); i++)
    {
        if(inRange[i]->discovered)
        {
            activeChunks.push_back(inRange[i]);
        }
    }



    /*if(players.size() > 0)
    {
        int player_x = getXStrip(windowPosition.x);
        int player_y = getYStrip(windowPosition.y);
        activeChunks = fractalBloom(&chunks[player_y][player_x]);
        cout << "done with fractal, activeChunks is of size: " << activeChunks.size() << endl;
    }*/
    //ACTIVECHUNKS VECTOR COMPLETED

    //REALLOCATE OBJECT CHUNK INDICES



    for(i=0; i<activeChunks.size(); i++)
    {
        activeChunks[i]->update();

        for(j=0; j<activeChunks[i]->Objects.size(); j++)
        {
            if(activeChunks[i]->Objects[j]->idContains("horizdoor"))
            {

                if(!activeChunks[i]->Objects[j]->locked)
                {
                    //debug.println("found one!");
                    Chunk* doorChunk = activeChunks[i];
                    doorChunk->blocksLOS = false;
                    for(k=0; k<3; k++)
                    {
                        doorChunk = doorChunk->right;
                        doorChunk->blocksLOS = false;
                    }

                }
            }

             if(activeChunks[i]->Objects[j]->idContains("verticdoor"))
            {

                if(!activeChunks[i]->Objects[j]->locked)
                {
                    //debug.println("found one!");
                    Chunk* doorChunk = activeChunks[i];
                    doorChunk->blocksLOS = false;
                    for(k=0; k<4; k++)
                    {
                        doorChunk = doorChunk->down;
                        doorChunk->blocksLOS = false;
                    }

                }
            }
        }
        //activeObjects.insert(activeObjects.begin(), activeChunks[i]->Objects.begin(), activeChunks[i]->Objects.end());
        //activeChunks[i]->setBoxColour(sf::Color::Cyan);
    }



    /*for(i=0; i<holdingspace.size(); i++)
    {
        holdingspace[i]->setBoxColour(sf::Color::Yellow);
        if(holdingspace[i]->blocksLOS)
        {
             holdingspace[i]->setBoxColour(sf::Color::Red);
        }
    }*/

    for(i=0; i<activeChunks.size(); i++)
    {
            int currentSize = activeChunks[i]->Objects.size();
            for(k=0; k<currentSize; k++)
            {
                if(activeChunks[i]->Objects[k]->moved)
                {
                    if(!activeChunks[i]->contentIsMember(activeChunks[i]->Objects[k]))
                    {
                        activeChunks[i]->Objects[k]->free();
                        //int newX = getXStrip(activeChunks[i]->Objects[k]->getPosition().x);
                        //int newY = getYStrip(activeChunks[i]->Objects[k]->getPosition().y);
                        bool found = false;
                        for(l=0; l<activeChunks.size(); l++)
                        {
                                //if(l==i) {continue;}
                                if(activeChunks[l]->contentIsMember(activeChunks[i]->Objects[k]))
                                {
                                    activeChunks[l]->addObject(activeChunks[i]->Objects[k]);

                                }
                        }
                        //chunks[newY][newX].addObject(activeChunks[i]->Objects[k]);
                        activeChunks[i]->Objects.erase(activeChunks[i]->Objects.begin()+k);
                        k--;
                        currentSize = activeChunks[i]->Objects.size();
                    }
                }
            }

    }



//OBJECT REALLOCATION COMPLETE

//BUILD INCONTACT VECTORS

    for(i=0; i<activeChunks.size(); i++)
        {
            for(l=0; l<activeChunks.size(); l++)
            {
                            //if(!chunks[l][m].active) {continue;}
                if(l==i)
                {
                    activeChunks[l]->inContact.insert(activeChunks[l]->inContact.end(),activeChunks[l]->Objects.begin(),activeChunks[l]->Objects.end());
                    continue;
                }

                for(j=0; j<activeChunks[i]->Objects.size(); j++)
                {
                    if(activeChunks[l]->contentInContact(activeChunks[i]->Objects[j]))
                    {
                        activeChunks[l]->inContact.push_back(activeChunks[i]->Objects[j]);
                    }
                }
            }
        }

//COMPLETED INCONTACT VECTORS

//DO PHYSICS
            for(l=0; l<activeChunks.size(); l++)
            {
                physics->autoLoopOverVector(activeChunks[l]->inContact);
                for(i=0; i<activeChunks[l]->inContact.size(); i++)
                {
                    physics->loopOverOneVector(activeChunks[l]->inContact[i],activeChunks[l]->Tiles);
                }
            }

//PHYSICS DONE


//BEGIN RAY PHYSICS
int f, g, h;



for(g=0; g<activeChunks.size(); g++)
{
        if(activeChunks[g]->Objects.size() == 0) {continue;}
        for(f=0; f<activeChunks[g]->Objects.size(); f++)
        {
            if(activeChunks[g]->Objects[f]->objRays.getSize() == 0) {continue;}

            for(j=0; j<activeChunks.size(); j++)
            {
                    if(activeChunks[j]->inContact.size() == 0 && activeChunks[j]->Tiles.size() == 0) {continue;}
                    for(l=0; l<activeChunks[g]->Objects[f]->objRays.rays.size(); l++)
                    {
                        for(i=0; i<activeChunks[g]->Objects[f]->objRays.rays[l].baseRay.getVertexCount(); i++)
                        {
                            if(!activeChunks[j]->zoneBounds.contains(activeChunks[g]->Objects[f]->objRays.rays[l].baseRay[i].position)) {continue;}
                            for(k=0; k<activeChunks[j]->Tiles.size(); k++)
                            {
                                if(!activeChunks[j]->Tiles[k]->stopsRays) {continue;}
                                if(physics->checkCollision(activeChunks[g]->Objects[f]->objRays.rays[l].baseRay[i].position, &activeChunks[j]->Tiles[k]->objHitbox))
                                {
                                    activeChunks[g]->Objects[f]->objRays.rays[l].baseRay.resize(i+1);
                                    activeChunks[g]->Objects[f]->detects(activeChunks[j]->inContact[k]);
                                }
                            }
                            for(k=0; k<activeChunks[j]->inContact.size();k++)
                            {
                                if(activeChunks[j]->inContact[k] == activeChunks[g]->Objects[f]) {continue;}
                                if(!activeChunks[j]->inContact[k]->stopsRays) {continue;}
                                if(physics->checkCollision(activeChunks[g]->Objects[f]->objRays.rays[l].baseRay[i].position, &activeChunks[j]->inContact[k]->objHitbox))
                                {
                                    activeChunks[g]->Objects[f]->objRays.rays[l].baseRay.resize(i+1);
                                    activeChunks[g]->Objects[f]->detects(activeChunks[j]->inContact[k]);
                                }
                            }

                        }
                    }
            }
        }
}


buildCircTest();
drawLineBetweenChunks(&chunks[circTestOriginx][circTestOriginy], &chunks[circTestx][circTesty]);

//END RAY PHYSICS

/*
    strays.insert(strays.end(), globalObjects.begin(), globalObjects.end());
    globalObjects.clear();

    int straysToClear;
    if(strays.size()<maxBuffer) {straysToClear = strays.size();}
    if(strays.size()>=maxBuffer) {straysToClear = maxBuffer;}

        for(i=0; i<chunks.size(); i++)
        {
            for(j=0; j<chunks[i].size(); j++)
            {

                for(k=0; k<straysToClear; k++)
                {
                    if(chunks[i][j].contentIsMember(strays[k]))
                    {
                        chunks[i][j].addObject(strays[k]);
                        continue;
                    }
                }
            }
        }

        strays.erase(strays.begin(), strays.begin()+straysToClear);
    //globalObjects.clear();

    /*objects.clear();

    objects.insert(objects.end(),globalObjects.begin(),globalObjects.end());


    for(i=0; i<chunks.size(); i++)
    {
        for(j=0; j<chunks[i].size(); j++)
        {
            if(!chunks[i][j].active) {continue;}
            objects.insert(objects.end(), chunks[i][j].Objects.begin(), chunks[i][j].Objects.end());
        }
    }*/
}

vector<Content*> Dungeon::returnAllContent()
{
    int i,j;
    vector<Content*> roomIterator;
    vector<Content*> levelContent;
    levelContent.insert(levelContent.end(), globalObjects.begin(), globalObjects.end());

    for(i=0;i<activeChunks.size();i++)
    {
            levelContent.insert(levelContent.end(), activeChunks[i]->Tiles.begin(), activeChunks[i]->Tiles.end());
            levelContent.insert(levelContent.end(), activeChunks[i]->Objects.begin(), activeChunks[i]->Objects.end());
    }

    return levelContent;
}
