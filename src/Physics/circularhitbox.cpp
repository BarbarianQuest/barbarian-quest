#include "circularhitbox.h"

CircularHitbox::CircularHitbox() : Hitbox()
{
    marker.setFillColor(sf::Color::White);
    marker.setPointCount(12);
    id = 1;
}

CircularHitbox::~CircularHitbox()

{

}

void CircularHitbox::setColor(sf::Color color)
{
    marker.setFillColor(color);
}

void CircularHitbox::setRadius(float in_rad)
{
    radius = in_rad;
    simpleShape.height = 2*in_rad;
    simpleShape.width = simpleShape.height;
    marker.setRadius(radius);
    marker.setOrigin(radius,radius);
}

float CircularHitbox::getRadius()
{
    return(radius);
}

void CircularHitbox::update()
{
    sf::Vector2f pos = getAbsolutePosition();
    marker.setPosition(pos);
    simpleShape.top = pos.y - radius;
    simpleShape.left = pos.x - radius;
    point.setPosition(pos);
}


bool CircularHitbox::contains(sf::Vector2f point)
{

}
