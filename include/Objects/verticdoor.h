#ifndef VERTICDOOR_H
#define VERTICDOOR_H

#include <gameobject.h>


class VerticDoor : public GameObject
{
    public:
        VerticDoor();
        virtual ~VerticDoor();

        void unlock();

        void allocateAssets();

    protected:
    private:
};

#endif // VERTICDOOR_H
