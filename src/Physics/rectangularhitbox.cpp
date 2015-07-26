#include "rectangularhitbox.h"


RectangularHitbox::RectangularHitbox() : Hitbox()
{
    marker.setFillColor(sf::Color::White);
    id = 2;
}

RectangularHitbox::~RectangularHitbox()
{

}

void RectangularHitbox::setColor(sf::Color color)
{
    marker.setFillColor(color);
}

sf::Vector2f RectangularHitbox::getBounds()
{
    sf::Vector2f bounds;
    bounds.x = width;
    bounds.y = height;
    return(bounds);
}

void RectangularHitbox::setBounds(float in_width, float in_height)
{
    width = in_width;
    height = in_height;
    rectSize.x = width;
    rectSize.y = height;
    simpleShape.height = in_height;
    simpleShape.width = in_width;
    marker.setSize(rectSize);
    marker.setOrigin(width*0.5,height*0.5);
    update();
}

void RectangularHitbox::update()
{
    sf::Vector2f pos = getAbsolutePosition();
    marker.setPosition(pos);
    simpleShape.top = pos.y - height*0.5;
    simpleShape.left = pos.x - width*0.5;
    point.setPosition(pos);
}


bool RectangularHitbox::contains(sf::Vector2f point)
{

}
