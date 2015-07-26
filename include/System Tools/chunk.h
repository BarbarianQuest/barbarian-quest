#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include <Base Content/content.h>



class Chunk : public sf::Drawable
{
    public:
        Chunk();
        virtual ~Chunk();
        fastMaths maths;

        sf::Vector2i tileSheetIndex;
        void setTileSheetIndex(int,int);

        sf::Vector2i chunkIndex;
        void setChunkIndex(int,int);

        vector<Content*> buffer;

        bool checked;

        bool active;
        void setActive();
        void setInactive();

        void updateDelta(float);

        int zoneSize;
        int zoneID;

        void setPosition(sf::Vector2f);
        void setPosition(float, float);

        void resetFlags();

        void setSize(int);

        sf::Rect<float> zoneBounds;
        sf::Rect<float> zoneBuffer;

        float bufferSize;
        sf::Vector2f TLposition;

        sf::Vector2f getCentre();
        bool contentInContact(Content*);
        bool contentIsMember(Content*);

        void addTile(Content*);
        void addObject(Content*);
        void addEntity(Content*);

        void removeObject(int);
        void removeEntity(int);

        bool displayed;
        bool discovered;
        bool blocksLOS;

        vector <Content*> Tiles;
        vector <Content*> Objects;
        vector <Content*> Entities;

        vector<Content*> strays;

        vector<Content*> inContact;

        vector <Content*> returnAllContent();

        vector <Chunk*> neighbours;
        Chunk* left,* right,* up,* down,* up_left,* up_right,* down_left,* down_right;

        void setNeighbours(vector<Chunk*>);
        void addNeighbour(Chunk*);
        vector <Chunk*> getNeighbours();

        void setBoxColour(sf::Color);

        void update();
        vector <Content*> returnStrays();
        sf::VertexArray boundsBox;
        void toggleDisplayed();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(displayed)
            {
                target.draw(boundsBox);
            }
        }
    protected:
    private:
};

#endif // CHUNK_H
