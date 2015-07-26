#ifndef MULTIEMITTER_H
#define MULTIEMITTER_H

#include <SFML/Graphics.hpp>
#include <particleemitter.h>


class MultiEmitter : public sf::Drawable
{
    public:
        MultiEmitter();
        virtual ~MultiEmitter();

        vector<ParticleEmitter> Emitters;
        vector<sf::Vector2f> relativePositions;

        void setPosition(sf::Vector2f);
        void addEmitter(ParticleEmitter);

    protected:
    private:
};

#endif // MULTIEMITTER_H
