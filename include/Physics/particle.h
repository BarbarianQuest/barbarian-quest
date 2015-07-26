#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <layeredanimation.h>
#include <fastmaths.h>
#include <System Tools/resourcemanager.h>


class Particle : public sf::Drawable
{
    public:
        Particle();
        virtual ~Particle();

        fastMaths* maths;

        void setMaths(fastMaths*);
        string sprAddress;
        ResourceManager* assets;

        sf::CircleShape testPart;

        LayeredAnimation particleSprite;
        sf::Vector2f position;
        sf::Vector2f emitterPosition;
        float elevation;
        sf::Vector2f speed;
        sf::Vector2f impulse;
        sf::Vector3f drift;
        float verticalImpulse;

        float mass;
        float recipmass;

        void allocateAssets(ResourceManager*);

        void setPosition(sf::Vector2f);
        void setImpulse(sf::Vector3f);
        void setImpulse(float, float,float);

        void setEmitterPosition(sf::Vector2f);
        void setSprite(const sf::Texture &);

        void refresh(float);
        void setCreationTime(float);
        void setLifetime(float);

        void evolveParticle();

        bool gravity,spin,riser;
        float lifetime;
        float created_at;
        float radius;

        void setRadius(float);


    protected:
    private:


        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(particleSprite);
            //target.draw(testPart);
        }
};

#endif // PARTICLE_H
