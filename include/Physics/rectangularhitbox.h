#ifndef RECTANGULARHITBOX_H
#define RECTANGULARHITBOX_H

#include <hitbox.h>


class RectangularHitbox : public Hitbox
{
    public:
        RectangularHitbox();
        RectangularHitbox(float, float);
        virtual ~RectangularHitbox();

        void setBounds(float, float);
        float getWidth();
        float getHeight();
        void setColor(sf::Color);



        virtual float getRadius()
        {
        }

        virtual sf::Vector2f getBounds();

        virtual bool contains(sf::Vector2f);

        virtual void update();

        float height, width;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(solid)
            {
                target.draw(marker);
                target.draw(point);
            }
        }

    private:


        sf::Vector2f rectSize;

        sf::RectangleShape marker;


};



#endif // RECTANGULARHITBOX_H
