#ifndef WEAPON_H
#define WEAPON_H

#include <Base Content/passivecontent.h>



class Weapon : public PassiveContent
{
    public:
        Weapon();
        virtual ~Weapon();

        fastMaths maths;
        Content* heldBy;

        sf::Clock attackClock;
        sf::Time attackTimer;

        int weapsize;
        int framenum;

        float reach, attackTime, front_delay, back_delay, knockback, fl_damage;

        sf::Vector2f currentHitboxPosition;

        float speed_mod, knockback_mod;

        bool attacking, readyToAttack;

        void setOwner(Content*);

        void setAnimationProperties();

        virtual void initialiseWeapon(Content*);

        virtual void attack();
        void startAttack();

        void allocateAssets();

        void hits(Content*);

        virtual void setHitboxProperties()
        {

        }
        virtual void evolveHitbox();

        void update();
    protected:
    private:

};



class Sword : public Weapon
{
    public:
        Sword();
        virtual ~Sword();

        void evolveHitbox();
        void setHitboxProperties();
    protected:
    private:
};

class Spear : public Weapon
{
    public:
        Spear();
        virtual ~Spear();

        void evolveHitbox();
        void setHitboxProperties();
    protected:
    private:
};

class Hammer : public Weapon
{
    public:
        Hammer();
        virtual ~Hammer();

        void evolveHitbox();
        void setHitboxProperties();
    protected:
    private:
};

#endif // WEAPON_H
