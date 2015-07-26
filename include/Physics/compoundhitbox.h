#ifndef COMPOUNDHITBOX_H
#define COMPOUNDHITBOX_H

#include <SFML/Graphics.hpp>
#include "circularhitbox.h"
#include "rectangularhitbox.h"
#include "layeredanimation.h"

using namespace std;


class CompoundHitbox : public sf::Drawable
{
    public:
        CompoundHitbox();
        virtual ~CompoundHitbox();

        sf::Vector2f localCoords;

        void* parent;

        bool inContact;

        vector<Hitbox *> hitboxElements;
        vector<CircularHitbox> circs;
        vector<RectangularHitbox> rects;

        void addCircularHitbox(sf::Vector2f, float);
        void addRectangularHitbox(sf::Vector2f, float,float);

        void addBasicRectHitbox(const LayeredAnimation &);

        void setLocalPosition(sf::Vector2f);

        void eraseAll();

        void setColor();
        void setColor(const sf::Color &);

        void makeSolid();
        void makeAir();

        bool solid;

        void Move(sf::Vector2f);
        void Rotate(float);
        void setPosition(sf::Vector2f);
        sf::Vector2f getPosition();

        void update();

    protected:
    private:

        sf::Vector2f absPosition;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            int i;
            for(i=0; i<rects.size(); i++)
            {
                target.draw(rects[i]);
            }
            for(i=0; i<circs.size(); i++)
            {
                target.draw(circs[i]);
            }
        }
};

#endif // COMPOUNDHITBOX_H
