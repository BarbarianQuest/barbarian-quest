#include "contaminant.h"

Contaminant::Contaminant(): PassiveContent()
{
    //ctorcontent_id += "_gelcube";
    setMass(0);
    makeAir();
    spriteAddresses.push_back("particle");
    renderPriority = 5;

}

Contaminant::~Contaminant()
{
    //dtor
}
