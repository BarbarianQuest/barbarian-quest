#ifndef CAULDRON_H
#define CAULDRON_H

#include <gameobject.h>


class Cauldron : public GameObject
{
    public:
        Cauldron();
        virtual ~Cauldron();

        void allocateAssets();

    protected:
    private:
};

#endif // CAULDRON_H
