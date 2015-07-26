#ifndef DUNGEON_H
#define DUNGEON_H

#include <SFML/Graphics.hpp>
#include <System Tools/resourcemanager.h>

#include <physicsengine.h>
#include <room.h>

#include <Collective Headers/allcontenttypes.h>

#include <raygun.h>
#include <trap.h>
#include <player.h>
#include <debugtools.h>
#include <contentbuffer.h>
#include <System Tools/eventhandler.h>
#include <System Tools/stringtools.h>
#include <System Tools/chunk.h>
#include <Entities/entity.h>

using namespace std;


class Dungeon : public sf::Drawable
{
    public:
        Dungeon();
        virtual ~Dungeon();
        DebugTools debug;

        vector< vector<Chunk> > chunks;

        EventHandler* events;
        void setEventHandler(EventHandler*);

        StringTools stringtools;

        ContentBuffer buffer;

        //if a room is not a special room, it will access the textures defined here for tile sprites
        void setBasicFloorSheet(const sf::Texture &);
        void setBasicWallSheet(const sf::Texture &);
        vector<Content*> returnAllContent();
        vector<Content*> objects;
        vector<Content*> globalObjects;
        vector<Entity*> globalEntities;
        vector<vector <Content*> > tiles;


        vector<Content*> strays;
        vector<Chunk*> activeChunks;

        vector<Content*> players;
        void setPlayers(vector<Content> *);
        void setPlayers(vector<Player> *);

        Chunk* getParentChunk(Content*);
        Chunk* nearestDiscoveredChunk(Chunk*);
        sf::Vector2i getParentChunkIndex(Content*);

        vector <Raygun> globalRays;

        vector<Content*> activeObjects;

        void passObjectBetweenChunks(Content*, Chunk*, Chunk*);

        int chunkSize;

        ResourceManager* levelassets;
        PhysicsEngine* physics;
        fastMaths maths;

        void updateDelta(float);


        void setManager(ResourceManager*);
        void setPhysics(PhysicsEngine*);

        void arrangeChunks();

        int min_x;
        int max_x;
        int min_y;
        int max_y;

        void populateChunkTiles();
        void updateChunkObjects();
        void updateChunkEntities();

        void setHitboxMode(bool);

        float renderRange;

        void addPlayer(vector<Content*>);

        void resetFlags();
        void addHorizDoor(int,int,int);
        void addVertDoor(int,int,int);

        sf::Vector2i getTileSheetIndex(Chunk*);

        vector<Chunk*> findNeighbours(Chunk*);
        void setChunkNeighbours();

        vector<Chunk*> fractalBloom(Chunk*);

        float oneOverTilesize;
        sf::Vector2f TLCornerOfTLChunk;

        int circTestx, circTesty;
        int circTestRad;
        int circTestOriginx, circTestOriginy;
        float circTestAngle;

        void buildCircTest();

        //HERE BEGINS THE PATHFINDING ADVENTURE

        int getYStrip(float);
        int getXStrip(float);

        vector<Chunk*> drawLineBetweenChunks(Chunk*, Chunk*); //Detects which chunks are present along a line
        vector<Chunk*> drawLineBetweenPoints(sf::Vector2f, sf::Vector2f); //does the same for abs positions

        vector<Chunk*> getLOSBetweenChunks(Chunk*, Chunk*); //does the same as the above but cuts off anything occluded
        vector<Chunk*> getLOSBetweenChunks(sf::Vector2f, sf::Vector2f);

        bool checkLOSbetweenChunks(Chunk*,Chunk*); //finds if there is a clear line of sight between two chunks
        bool checkLOSbetweenPoints(sf::Vector2f, sf::Vector2f);

        sf::Vector2f getUnitVectorBetweenChunks(Chunk*, Chunk*);

        Raygun testGun;

        float min_chunk_x, min_chunk_y;
        float max_chunk_x, max_chunk_y;


        void replaceTile(int, int, Content*);

        void updateWindowInfo(sf::Vector2f);
        sf::Vector2f windowPosition;

        void populateTileSheet();

        void addBasicRoom(int,int,int,int); //builds a box room with no features
        void addBasicCircularRoom(int,int,int);

        void updateRooms();

        void addObjectToRoom(int,int,int,int);

        void addObject(int,int,int);
        void addObject(int,int,string);

        vector<Room> rooms;

    protected:
    private:

        sf::Texture defaultFloorTiles;
        sf::Texture defaultWallTiles;

        int gridsize_x, gridsize_y;
        int tilesize;
        int l,t,b,r;



        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {

        }

};

#endif // DUNGEON_H
