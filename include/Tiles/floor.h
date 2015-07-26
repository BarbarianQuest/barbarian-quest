#ifndef FLOOR_H
#define FLOOR_H

#include <tile.h>


class Floor : public Tile
{
    public:
        Floor();
        Floor(const sf::Texture &);
        virtual ~Floor();
    private:
};

#endif // FLOOR_H
