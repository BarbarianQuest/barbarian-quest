#ifndef CIRCULARHITBOX_H
#define CIRCULARHITBOX_H

#include <hitbox.h>



class CircularHitbox : public Hitbox
{
    public:
        CircularHitbox();
        CircularHitbox(float);
        virtual ~CircularHitbox();

        void setRadius(float);
        virtual float getRadius();
        void setColor(sf::Color);

        virtual bool contains(sf::Vector2f);

        float radius;

        virtual sf::Vector2f getBounds()
        {

        }

        virtual void update();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(solid)
            {
                target.draw(marker);
                target.draw(point);
            }
        }


    private:


        sf::CircleShape marker;



};

#endif // CIRCULARHITBOX_H
