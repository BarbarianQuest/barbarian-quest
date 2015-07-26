#include "ray.h"

Ray::Ray()
{
    //ctor
    granularity = 25;
    maxLength = 500;
    separation = maxLength/granularity;
    baseRay.setPrimitiveType(sf::LinesStrip);
    baseRay.resize(granularity);
    startPoint.x = 0;
    startPoint.y = 0;
    bearing = 0;
}

Ray::~Ray()
{
    //dtor
}

bool Ray::crossesRegion(sf::Rect<float> region)
{
    float bearing_sin = maths->SinDeg(bearing);
    float bearing_cos = maths->CosDeg(bearing);

    direction.x = bearing_sin;
    direction.y = bearing_cos;
    int i;
    return(true);
}

bool Ray::checkCollision(CompoundHitbox* obj)
{
    int i,j;
    bool runCheck = false;
    for(i=0; i<baseRay.getVertexCount(); i++)
    {
        for(j=0; j<obj->rects.size(); j++)
        {
            if(!obj->rects[j].solid) {continue;}
            if(baseRay[i].position.x > obj->rects[j].getAbsolutePosition().x - obj->rects[j].width
                && baseRay[i].position.x < obj->rects[j].getAbsolutePosition().x + obj->rects[j].width
                && baseRay[i].position.y > obj->rects[j].getAbsolutePosition().y - obj->rects[j].height
                && baseRay[i].position.y > obj->rects[j].getAbsolutePosition().y - obj->rects[j].height)
            {
                doCollision(i,&obj->rects[j]);
                runCheck = true;
            }
        }
        for(j=0; j<obj->circs.size(); j++)
        {
            if(obj->circs[j].simpleShape.contains(baseRay[i].position))
            {
                if(!obj->circs[j].solid) {continue;}
                if(maths->magnitude(baseRay[i].position-obj->circs[j].getAbsolutePosition()) < obj->circs[j].radius)
                {
                    doCollision(i,&obj->circs[j]);
                    runCheck = true;
                }
            }
        }
    }
    return(runCheck);
}

void Ray::doCollision(int element, RectangularHitbox* box)
{
    baseRay.resize(element+1);


}

void Ray::doCollision(int element, CircularHitbox* circ)
{
    baseRay.resize(element+1);
}

void Ray::setBearing(float newBearing)
{
    bearing = newBearing;
}

void Ray::setRotationSpeed(float newRotSpeed)
{
    angularSpeed = newRotSpeed;
}

void Ray::setMaths(fastMaths* newmath)
{
    maths = newmath;
    bearing = 0;

    float bearing_sin = maths->SinDeg(bearing);
    float bearing_cos = maths->CosDeg(bearing);

    direction.x = bearing_sin;
    direction.y = bearing_cos;

    angularSpeed = 0;
    rayColour = sf::Color::White;
    int i;
    for(i=0; i<baseRay.getVertexCount(); i++)
    {
        baseRay[i].color = rayColour;
    }
}


void Ray::setManager(ResourceManager* manager)
{
    assets = manager;
    //setMaths(&(assets->maths));
}

void Ray::setPosition(sf::Vector2f newpos)
{
    startPoint = newpos;
}

void Ray::resetSize()
{
    baseRay.resize(granularity);
}

void Ray::update()
{
    int i;
    resetSize();
    bearing += angularSpeed;
    float bearing_sin = maths->SinDeg(bearing);
    float bearing_cos = maths->CosDeg(bearing);

    direction.x = bearing_sin;
    direction.y = bearing_cos;

    for(i=0; i<baseRay.getVertexCount(); i++)
    {
        baseRay[i].color = rayColour;
    }
    for(i=0; i<baseRay.getVertexCount(); i++)
    {
        sf::Vector2f pos = i*separation*direction;
        pos += startPoint;
        baseRay[i].position = pos;
        /*randCol.r = maths.randomInt(0,255);
        randCol.g = maths.randomInt(0,255);
        randCol.b = maths.randomInt(0,255);*/
    }
}
