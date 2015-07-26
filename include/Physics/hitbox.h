#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>



class Hitbox : public sf::Drawable
{
    public:
        Hitbox();
        virtual ~Hitbox();

        int id;

        void setRelativePosition(sf::Vector2f);
        void setAbsolutePosition(sf::Vector2f);
        void setParentPosition(sf::Vector2f);

        sf::Vector2f getRelativePosition();
        sf::Vector2f getAbsolutePosition();
        sf::Vector2f getParentPosition();



        void makeSolid();
        void makeAir();

        void Move(sf::Vector2f);
        void setPosition(sf::Vector2f);

        void Rotate(float);
        float getRotation();

        bool solid; //does it stop things moving through it?

        virtual float getRadius()
        {

        }

        virtual sf::Vector2f getBounds()
        {

        }

        virtual void update()
        {



        }

        virtual bool checkCollision(Hitbox*)
        {

        }

        virtual bool contains(sf::Vector2f)
        {

        }

        sf::RectangleShape point;

        sf::Rect<float> simpleShape;

    protected:
    private:

        sf::Vector2f absPosition;
        sf::Vector2f relPosition;
        sf::Vector2f parPosition;








        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {


        }
};



#endif // HITBOX_H
