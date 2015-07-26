#ifndef GELATINOUSCUBE_H
#define GELATINOUSCUBE_H

#include <Contaminants/contaminant.h>
#include "enemy.h"

class GelatinousCube : public Enemy
{
    public:
        GelatinousCube();
        virtual ~GelatinousCube();

        void evolveSpeed();

        float timerOffset;

        void extraAllocations();

        std::vector<Contaminant*> slime;
        int maxTrail, currentTrail;

    protected:
    private:
};

#endif // GELATINOUSCUBE_H
