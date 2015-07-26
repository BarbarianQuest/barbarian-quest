#ifndef BOMB_H
#define BOMB_H

#include <gameobject.h>
#include <Physics/Physics Events/explosion.h>


class Bomb : public GameObject
{
    public:
        Bomb();
        virtual ~Bomb();

        sf::Clock fuseClock;
        sf::Time fuseTimer;

        bool ticking;

        float fuseTime;
        void setFuseTime(float);

        void trigger();

        Explosion* explode;

        void update();

    protected:
    private:
};

#endif // BOMB_H
