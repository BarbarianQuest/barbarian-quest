#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <SFML/Graphics.hpp>
#include <particle.h>
#include <Particles/riser.h>
#include <Particles/trail.h>
#include <System Tools/resourcemanager.h>


class ParticleEmitter : public sf::Drawable
{
    public:
        ParticleEmitter();
        virtual ~ParticleEmitter();



        fastMaths *maths;

        void setMaths(fastMaths* );

        vector<Particle*> activeParticles;
        int maxNumberOfParticles;
        int currentNumberOfParticles;
        bool refreshDeadParticles;
        bool keepFull;
        bool waitForSpace; //OKAY sort of arcane. If true, a particle will not be created unless there's space
                            // if false, it will kill a particle prematurely to make space.
        Particle baseParticle;

        LayeredAnimation baseAnim;
        ResourceManager* assets;

        sf::Clock particleClock;
        sf::Time particleTimer;

        string particleTextureAddress;

        sf::Vector2f position;

        float minXImpulse,minYImpulse,minZImpulse;
        float maxXImpulse,maxYImpulse,maxZImpulse;

        void setImpulseRange(float, float, float, float, float, float);
        void setRadius(float);
        void setLifetimeRange(float, float);
        void setParticleSizeRange(float,float);

        float minLifetime, maxLifetime;
        float radius;
        float minParticleSize, maxParticleSize;

        void setManager(ResourceManager*);

        void setParticleTextureAddress(string);

        void setMaxNumberOfParticles(int);

        void setBaseParticle(const Particle &);

        void initialise(ResourceManager*, string, int,int);

        void setPosition(sf::Vector2f);
        void setPosition(float, float);

        void addNewParticles(int,int);
        void addNewParticle(int);
        void applyImpulseToParticle(int, sf::Vector3f);
        void applyImpulseToParticle(int, float, float, float);
        void applyImpulseToParticle(int, sf::Vector2f);
        void applyImpulseToParticle(int, float, float);
        void applyImpulseToAll(sf::Vector3f);
        void applyImpulseToAll(float, float, float);
        void applyImpulseToAll(sf::Vector2f);
        void applyImpulseToAll(float, float);

        void burst(int,sf::Vector3f); //makes new particles, then applies an impulse
        void burst(int,float,float,float);
        void burst(int,sf::Vector2f);
        void burst(int,float, float);

        void addSpecialParticle(const Particle &); //probably fucking useless...better to just add a second emitter.

        void update();

    protected:
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            int i;

            for(i=0; i<activeParticles.size(); i++)
            {
                target.draw(*activeParticles[i]);
            }
        }
};

#endif // PARTICLEEMITTER_H
