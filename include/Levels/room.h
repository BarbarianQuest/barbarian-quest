#ifndef ROOM_H
#define ROOM_H

#include <Collective Headers/allcontenttypes.h>
#include <Physics/physicsengine.h>


class Room : public sf::Drawable
{
    public:
        Room();
        virtual ~Room();

        void setFloorSheet(const sf::Texture &);
        void setWallSheet(const sf::Texture &);

        ResourceManager* roomAssets;
        void setManager(ResourceManager*);

        PhysicsEngine* physics;
        void setPhysics(PhysicsEngine*);

        vector<Content*> returnAllContent();

        void buildBasicRoom(int,int); //builds a box room with no features of size int x int
        void buildCircularRoom(int);

        void setRoomPosition(int,int); //sets the position of the room on the dungeon map in grid coords

        void collectLayers();

        void replaceTile(int,int,int,string); //for naming tiles for hardcode
        void replaceTile(int,int,int,int); //for tileIDs

        void addMetaTile(int,int,int,string);
        void addMetaTile(int,int,int,int);

        void addObject(int,int,int);

        vector<Content*> returnObjects();
        vector<Content*>  returnTilesRowNum(int);
        vector< vector<Content*> > returnTiles();

        sf::Vector2i getRoomPositionOnGrid();

        void update();

        int width, height;

    protected:
    private:

        sf::Vector2i roomPosition; //the top left tile of the room
        int x_0,y_0; //top left corner position

        int tileSize;

        sf::Texture floorSheet;
        sf::Texture wallSheet;

        vector<Content*> objects;

        vector<vector <vector <Content*> > > tileLayers;

        vector<vector<Content*> > floorTiles;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            int i,j,layer;
            for(layer=0; layer<tileLayers.size(); layer++)
            {
                for(i=0; i<floorTiles.size(); i++)
                {
                    for(j=0; j<floorTiles[i].size(); j++)
                    {
                        target.draw(*tileLayers[layer][i][j]);
                    }
                }
            }

        }
};

class Corridor: public Room
{
    public:
        Corridor();
        virtual ~Corridor();


};

#endif // ROOM_H
