#ifndef VOIDTILE_H
#define VOIDTILE_H

#include <tile.h>


class VoidTile : public Tile
{
    public:
        VoidTile();
        virtual ~VoidTile();


    protected:
    private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {

        }
};

#endif // VOIDTILE_H
