#ifndef TILE_H
#define TILE_H

#include <Base Content/staticcontent.h>


class Tile : public StaticContent
{
    public:
        Tile();
        Tile(const sf::Texture &);
        virtual ~Tile();

        void setManager(ResourceManager*);
        void allocateAssets();

        void setTexture(const sf::Texture &); //defaults to the 1st tile in the sheet if setSpriteBox is not called
        void setSpriteBox(int, int); //selects a 64x64 tile from the sheet to access as the sprite

        void setLocalPosition(int, int); //sets the position of the tile in the room
        void setGlobalPosition(int, int); //sets the position of the tile in the dungeon (should not be used directly)
        void setParentRoomPosition(int, int); //if a room moves, this should be called

        sf::Vector2f getAbsPosition();
        sf::Vector2f getRelPosition();
        sf::Vector2f getAppPosition();

        int tileSize;
        sf::IntRect tileRect;


        int id;

        bool rotateable;

    protected:
    private:


        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(objSprite);
            if(drawHitbox)
            {
                target.draw(objHitbox);
            }
        }
};
#endif // TILE_H
