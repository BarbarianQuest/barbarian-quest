#ifndef DEBUGDISPLAY_H
#define DEBUGDISPLAY_H
#include <SFML/Graphics.hpp>
#include <lexical_cast.hpp>

using namespace std;


class debugDisplay : public sf::Drawable
{
    public:
        debugDisplay();
        virtual ~debugDisplay();

        void update();
        void toggleDisplay();
        void setFont(const sf::Font &);
        void setP1pos(sf::Vector2f);
        void setP1tile(sf::Vector2f);
        void setPosition(sf::Vector2f);
        void setFPS(float);
        void setP1velocity(sf::Vector2f);
        void setP1chunk(sf::Vector2i);

    protected:
    private:

        string P1pos_string, P1tile_string, fps_string, P1velocity_string,P1chunk_string;
        sf::Text P1pos, P1tile, FPS, P1velocity, P1chunk;

        bool displayed;
        int textsize;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(displayed)
            {
                target.draw(P1pos);
                target.draw(P1tile);
                target.draw(FPS);
                target.draw(P1velocity);
                target.draw(P1chunk);
            }
        }
};

#endif // DEBUGDISPLAY_H
