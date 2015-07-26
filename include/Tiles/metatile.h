#ifndef METATILE_H
#define METATILE_H

#include <SFML/Graphics.hpp>
#include "tile.h"


class Metatile : public sf::Drawable
{
    public:
        Metatile();
        virtual ~Metatile();
    protected:
    private:

        std::vector< std::vector<Tile> > componentTiles;
};

#endif // METATILE_H
