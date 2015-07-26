#ifndef POT_H
#define POT_H

#include "container.h"


class Pot : public Container
{
    public:
        Pot();
        virtual ~Pot();

        void allocateAssets();

        //void isDestroyed();

    protected:
    private:
};

#endif // POT_H
