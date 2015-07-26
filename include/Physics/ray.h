#ifndef RAY_H
#define RAY_H

#include <SFML/Graphics.hpp>
#include <fastmaths.h>
#include <compoundhitbox.h>
#include <System Tools/resourcemanager.h>


class Ray : public sf::Drawable
{
    public:
        Ray();
        virtual ~Ray();

        fastMaths *maths;

        sf::VertexArray baseRay;
        sf::Vector2f startPoint;
        sf::Vector2f direction;
        float bearing;
        float maxLength;
        int granularity;
        float separation;

        sf::Color rayColour;
        float angularSpeed;

        ResourceManager* assets;

        void setPosition(sf::Vector2f);
        void setManager(ResourceManager*);
        void setMaths(fastMaths *);

        void update();

        void resetSize();


        bool crossesRegion(sf::Rect<float>);
        bool checkCollision(CompoundHitbox*);
        void doCollision(int, CircularHitbox*);
        void doCollision(int, RectangularHitbox*);

        void setBearing(float);
        void setRotationSpeed(float);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            //target.draw(particleSprite);
            target.draw(baseRay);
        }
    protected:
    private:
};

#endif // RAY_H
