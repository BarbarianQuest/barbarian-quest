#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "physicsevent.h"


class Explosion : public PhysicsEvent
{
    public:
        Explosion();
        Explosion(float,float,float,int);
        virtual ~Explosion();

        float boom_radius;
        float boom_duration;
        float boom_impulse;
        int boom_damage;
        float inv_duration;

        float boom_increment;

        void setExplosionRadius(float);
        void setExplosionDuraton(float);
        void setExplosionImpulse(float);
        void setExplosionDamage(int);

        void setParameters(float,float,float,int);

        void allocateAssets();

        void hits(Content*);

        void evolveHitbox();

        void update();


    protected:
    private:
};

#endif // EXPLOSION_H
