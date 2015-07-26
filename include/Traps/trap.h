#ifndef TRAP_H
#define TRAP_H

#include <gameobject.h>


class Trap : public GameObject
{
    public:
        Trap();
        virtual ~Trap();
        float lastFired, timeBetweenShots;
    protected:
    private:
};

#endif // TRAP_H
