#ifndef KEY_H
#define KEY_H

#include "pickup.h"


class Key : public Pickup
{
    public:
        Key();
        virtual ~Key();

        void hits(Content*);
    protected:
    private:
};

#endif // KEY_H
