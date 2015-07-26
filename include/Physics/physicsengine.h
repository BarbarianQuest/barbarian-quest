#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include <Base Content/content.h>
#include <Base Content/dynamiccontent.h>
#include <Base Content/staticcontent.h>
#include <Functions/fastmaths.h>
#include <debugtools.h>
#include <System Tools/chunk.h>


class PhysicsEngine
{
    public:
        PhysicsEngine();
        virtual ~PhysicsEngine();

        fastMaths maths;
        DebugTools debug;

        float physics_range;

        vector <sf::Rect<float> > chunkZones;
        vector <bool> chunkActive;
        vector <int> chunkContactSize;

        void makeGrid(int,int,int,int,int);
        void updateActiveZones(vector< vector <Chunk> > *);
        sf::Vector2i getZone(sf::Vector2f);

        int min_zone_x, min_zone_y;

        bool checkCollision(Content*,Content*);
        bool checkCollision(sf::Vector2f, CompoundHitbox*);
        //bool checkCollision(DynamicContent*, StaticContent*);
        void autoLoopOverVector(vector<Content*>);
        void loopOverOneVector(Content*,vector<Content*>);
        void loopOverTwoVectors(vector<Content*>, vector<Content*>);

        bool hitboxOverlap(RectangularHitbox*,RectangularHitbox*);
        bool hitboxOverlap(RectangularHitbox*,CircularHitbox*);
        bool hitboxOverlap(CircularHitbox*,RectangularHitbox*);
        bool hitboxOverlap(CircularHitbox*,CircularHitbox*);

        sf::Vector2f getOverlap(Content*, Content*);

        void doCollision(Content*, Content*, sf::Vector2f);

        sf::Vector2f getOverlap(RectangularHitbox*, RectangularHitbox*);
        sf::Vector2f getOverlap(RectangularHitbox*, CircularHitbox*);
        sf::Vector2f getOverlap(CircularHitbox*, RectangularHitbox*);
        sf::Vector2f getOverlap(CircularHitbox*, CircularHitbox*);


    protected:
    private:
};

#endif // PHYSICSENGINE_H
