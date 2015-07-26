#ifndef BASEAXE_H
#define BASEAXE_H

#include <Weapons/axe.h>


class BaseAxe : public Axe
{
    public:
        BaseAxe();
        virtual ~BaseAxe();

        void attack();

    protected:
    private:
};

#endif // BASEAXE_H
