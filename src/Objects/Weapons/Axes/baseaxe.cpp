#include <Objects/Weapons/axe.h>
#include <Objects/Weapons/Axes/baseaxe.h>

BaseAxe::BaseAxe() : Axe()
{
    //ctor
    spriteAddresses.push_back("clear");

    reach = 50;
    attackTime = 0.1;
    front_delay = 0;
    back_delay = 0.1;
    knockback = 500;
    fl_damage = 1;
    headRadius = 15;

}

BaseAxe::~BaseAxe()
{
    //dtor
}

void BaseAxe::attack()
{

}

