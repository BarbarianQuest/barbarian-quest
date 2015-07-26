#ifndef HORIZDOOR_H
#define HORIZDOOR_H

#include <gameobject.h>


class HorizDoor : public GameObject
{
    public:
        HorizDoor();
        virtual ~HorizDoor();

        void unlock();

        void allocateAssets();
    protected:
    private:
};

#endif // HORIZDOOR_H
