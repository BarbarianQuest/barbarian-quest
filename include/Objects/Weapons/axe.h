#ifndef AXE_H
#define AXE_H



#include "weapon.h"

class Axe : public Weapon
{
    public:
        Axe();
        virtual ~Axe();

        float arcSize;
        float degreesPerSec;

        float headRadius;

        void initialiseWeapon(Content*);
        void evolveHitbox();
        void setHitboxProperties();
    protected:
    private:
};

#endif // AXE_H
