#ifndef CHEST_H
#define CHEST_H

#include "container.h"


class Chest : public Container
{
    public:
        Chest();
        virtual ~Chest();

        void hits(Content*);
        void unlock();
        void allocateAssets();
        void allocateContents();

    protected:
    private:
};

#endif // CHEST_H
