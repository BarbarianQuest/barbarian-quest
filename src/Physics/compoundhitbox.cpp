#include "compoundhitbox.h"

CompoundHitbox::CompoundHitbox()
{
    //ctor
    inContact = false;
    solid = false;
    localCoords.x = 0;
    localCoords.y = 0;
}

CompoundHitbox::~CompoundHitbox()
{
    //dtor
}

void CompoundHitbox::setColor()
{
    int i;
    sf::Color baseColor = sf::Color::White;
    if(inContact)
    {
        baseColor = sf::Color::Red;
    }
    for(i=0; i<rects.size(); i++)
    {
        rects[i].setColor(baseColor);
    }
    for(i=0; i<circs.size(); i++)
    {
        circs[i].setColor(baseColor);
    }
}

void CompoundHitbox::setColor(const sf::Color & baseColor)
{
    int i;
    for(i=0; i<rects.size(); i++)
    {
        rects[i].setColor(baseColor);
    }
    for(i=0; i<circs.size(); i++)
    {
        circs[i].setColor(baseColor);
    }
}

void CompoundHitbox::Move(sf::Vector2f amount)
{
    int i;
    for(i=0; i<hitboxElements.size(); i++)
    {
        hitboxElements[i]->Move(amount);
    }
}

void CompoundHitbox::setPosition(sf::Vector2f newPosition)
{
    int i;
    absPosition = newPosition;
    for(i=0; i<rects.size(); i++)
    {
        rects[i].setParentPosition(newPosition + localCoords);
    }
    for(i=0; i<circs.size(); i++)
    {
        circs[i].setParentPosition(newPosition + localCoords);
    }
}

void CompoundHitbox::setLocalPosition(sf::Vector2f new_origin)
{
    localCoords = new_origin;
}

void CompoundHitbox::makeSolid()
{
    int i;
    solid = true;
    for(i=0; i<rects.size(); i++)
    {
        rects[i].makeSolid();
    }
    for(i=0; i<circs.size(); i++)
    {
        circs[i].makeSolid();
    }
}

sf::Vector2f CompoundHitbox::getPosition()
{
    return absPosition;
}

void CompoundHitbox::makeAir()
{
    int i;
    solid = false;
    for(i=0; i<rects.size(); i++)
    {
        rects[i].makeAir();
    }
    for(i=0; i<circs.size(); i++)
    {
        circs[i].makeAir();
    }
}

void CompoundHitbox::addRectangularHitbox(sf::Vector2f localCoords, float width, float height)
{
    RectangularHitbox rectHitbox;
    rectHitbox.setBounds(width,height);
    rectHitbox.setRelativePosition(localCoords);
    rectHitbox.setParentPosition(absPosition);
    if(solid)
    {
        rectHitbox.makeSolid();
    }
    rectHitbox.update();
    rects.push_back(rectHitbox);
}

void CompoundHitbox::eraseAll()
{
    rects.erase(rects.begin(), rects.end());
    circs.erase(circs.begin(), circs.end());
}

void CompoundHitbox::addCircularHitbox(sf::Vector2f localCoords,float radius)
{
    CircularHitbox circHitbox;
    circHitbox.setRadius(radius);
    circHitbox.setRelativePosition(localCoords);
    circHitbox.setParentPosition(absPosition);
    if(solid)
    {
        circHitbox.makeSolid();
    }
    circHitbox.update();
    circs.push_back(circHitbox);
}

void CompoundHitbox::addBasicRectHitbox(const LayeredAnimation &)
{

}

void CompoundHitbox::update()
{
    int i;
    setColor();
    for(i=0; i<circs.size(); i++)
    {
        circs[i].update();
    }
    for(i=0; i<rects.size(); i++)
    {
        rects[i].update();
    }
}
