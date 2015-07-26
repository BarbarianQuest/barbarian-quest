#include "hitbox.h"

Hitbox::Hitbox()
{
    //ctor
    point.setFillColor(sf::Color::Black);
    sf::Vector2f sizeofpoint(1,1);
    point.setSize(sizeofpoint);
    solid = false;
    id = 0;
}

Hitbox::~Hitbox()
{
    //dtor
}

void Hitbox::Move(sf::Vector2f amount)
{
    setParentPosition(getParentPosition() + amount);
}

void Hitbox::setAbsolutePosition(sf::Vector2f newPosition)
{

    absPosition = newPosition;
    update();
}

void Hitbox::setRelativePosition(sf::Vector2f newRelativePosition)
{
    absPosition = parPosition + newRelativePosition;
    relPosition = newRelativePosition;
    setAbsolutePosition(absPosition);
}

void Hitbox::setParentPosition(sf::Vector2f newPosition)
{
    parPosition = newPosition;
    setAbsolutePosition(parPosition + relPosition);
}

void Hitbox::makeSolid()
{
    solid = true;
    return;
}

void Hitbox::makeAir()
{
    solid = false;
    return;
}



sf::Vector2f Hitbox::getAbsolutePosition()
{
    return absPosition;
}

sf::Vector2f Hitbox::getParentPosition()
{
    return parPosition;
}

sf::Vector2f Hitbox::getRelativePosition()
{
    return relPosition;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
