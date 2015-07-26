#ifndef ENTITY_H
#define ENTITY_H

#include <Base Content/dynamiccontent.h>
#include <Base Content/content.h>


class Entity : public DynamicContent
{
    public:
        Entity();
        virtual ~Entity();

        vector <Content*> aggroed;
        Content* primeTarget;

        bool primeTargetSet;

        sf::VertexArray path;

        virtual void pathfind();

        virtual void selectPrimeTarget();

        sf::Clock speedClock;
        sf::Time speedTime;

        virtual void evolveSpeed()
        {

        }



        virtual void evolveBehaviour()
        {

        }

        bool hasPrimeTarget();

        void addAggro(Content*);
        void removeAggro(Content*);
        void setVelocity();
        void update();
        void updateClocks();

    protected:
    private:

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(showShadow)
            {
                target.draw(shadow);
            }
            target.draw(objSprite);
            if(drawHitbox)
            {
                target.draw(objHitbox);
                target.draw(path);
            }
            target.draw(objParticles);
            if(drawHitbox)
            {
                target.draw(objRays);
            }
        }
};

#endif // ENTITY_H
