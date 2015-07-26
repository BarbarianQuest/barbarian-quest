#ifndef RAYGUN_H
#define RAYGUN_H

#include <SFML/Graphics.hpp>
#include <ray.h>



class Raygun : public sf::Drawable
{
    public:
        Raygun();
        virtual ~Raygun();

        vector<Ray> rays;
        sf::Vector2f position;

        bool globalScope;

        ResourceManager* assets;
        fastMaths* maths;

        int getSize();
        void setPosition(sf::Vector2f);
        void update();
        void setManager(ResourceManager*);
        void addRay(int);

    protected:
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            //target.draw(particleSprite);
            int i;
            for(i=0; i<rays.size(); i++)
            {
                target.draw(rays[i]);
            }
        }
};

#endif // RAYGUN_H
