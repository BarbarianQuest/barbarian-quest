#include "fastmaths.h"

fastMaths::fastMaths()
{
    //ctor
    int i;
    fastCos.resize(3600);
    fastSin.resize(3600);
    fastTan.resize(3600);
    pi = 3.14159265;
    radToDeg = (180/pi);
    degToRad = (pi/180);
    rng.seed(time(0));
    for(i=0; i<3600; i++)
    {
        float degrees = ( (float) (i))/10;
        float rads = degToRad*degrees;
        fastSin[i] = sin(rads);
        fastCos[i] = cos(rads);
        fastTan[i] = tan(rads);
    }

}

fastMaths::~fastMaths()
{
    //dtor
}

float fastMaths::round(float x)
{
    float ceil_x, floor_x;
    float diff_ceil, diff_floor;
    float x_rounded;
    ceil_x = ceil(x);
    floor_x = floor(x);
    diff_ceil = ceil_x - x;
    diff_floor = x - floor_x;
    if(diff_ceil <= diff_floor)
    {
        x_rounded = ceil_x;
    }
    if(diff_ceil > diff_floor)
    {
        x_rounded = floor_x;
    }
    return(x_rounded);
}

int fastMaths::roundAndCast(float x)
{
    float x_round = round(x);
    int x_cast = (int) x_round;
    return(x_cast);
}

float fastMaths::SinDeg(float x)
{
    while(x<0)
    {
        x+=360;
    }
    while(x>=360)
    {
        x-=360;
    }
    int degrees = roundAndCast(x*10);
    return(fastSin[degrees]);
}

float fastMaths::CosDeg(float x)
{
    while(x<0)
    {
        x+=360;
    }
    while(x>=360)
    {
        x-=360;
    }
    int degrees = roundAndCast(x*10);
    return(fastCos[degrees]);
}

float fastMaths::TanDeg(float x)
{
    int degrees = roundAndCast(x*10);
    return(fastTan[degrees]);
}

float fastMaths::Sin(float x)
{

    float asDegrees = radToDeg*x;
    return(SinDeg(asDegrees));
}

float fastMaths::Cos(float x)
{
    float asDegrees = radToDeg*fabs(x);
    return CosDeg(asDegrees);
}

float fastMaths::Tan(float x)
{

    float asDegrees = radToDeg*x;
    return TanDeg(asDegrees);
}

float fastMaths::sqrt(float x)
{

    unsigned int i = *(unsigned int*) &x;

  // adjust bias
  i  += 127 << 23;
  // approximation of square root
  i >>= 1;

  return *(float*) &i;
}

float fastMaths::magnitude(sf::Vector2f input)
{
    float mag;
    mag = fastMaths::sqrt(input.x*input.x + input.y*input.y);
    return mag;
}

sf::Vector2f fastMaths::unitVector(sf::Vector2f vector_in)
{
    sf::Vector2f unit;
    if(vector_in.x == 0 && vector_in.y == 0)
    {
        return(vector_in);
    }
    if(vector_in.x == 0)
    {
        unit.x = 0;
        if(vector_in.y > 0)
        {
            unit.y = 1;
        }
        if(vector_in.y < 0)
        {
            unit.y = -1;
        }
        return(unit);
    }
    if(vector_in.y == 0)
    {
        if(vector_in.x > 0)
        {
            unit.x = 1;
        }
        if(vector_in.x < 0)
        {
            unit.x = -1;
        }
        unit.y = 0;
        return(unit);
    }
    float mag = magnitude(vector_in);
    float recipmag = 1/mag;

    unit.x = vector_in.x*recipmag;
    unit.y = vector_in.y*recipmag;
    return(unit);
}

int fastMaths::randomInt(int min_val, int max_val)
{
    if(min_val >= max_val)
    {
        return(min_val);
    }

    boost::uniform_int<> spinner( min_val, max_val);
      boost::variate_generator< RNGType, boost::uniform_int<> >
                    random(rng, spinner);

    int i;
    for(i=0; i<rand()%max_val; i++)
    {
        random();
    }

    return(random());
}

sf::Color fastMaths::randomColor()
{
    sf::Color newcol;
    newcol.r = randomInt(0,256);
    newcol.g = randomInt(0,256);
    newcol.b = randomInt(0,256);
    return(newcol);

}

sf::Vector2f fastMaths::constantMag(float mag, sf::Vector2f direction)
{
    sf::Vector2f unit = unitVector(direction);
    sf::Vector2f out = mag*unit;
    return(out);
}

float fastMaths::dotProduct(sf::Vector2f first, sf::Vector2f second)
{
    float dot = first.x*second.x + first.y*second.y;
    return(dot);
}

float fastMaths::angleBetween(sf::Vector2f first, sf::Vector2f second)
{
    float dot = dotProduct(first,second);
    float prodMag = magnitude(first)*magnitude(second);
    float cos = dot/prodMag;
    return(cos);
}

float fastMaths::unitDotProduct(sf::Vector2f first,sf::Vector2f second)
{

}

float fastMaths::randomFloat(float min_val, float max_val)
{
    if(min_val >= max_val)
    {
        return(min_val);
    }
    boost::uniform_real<> spinner( min_val*1000, max_val*1000);
    boost::variate_generator< RNGType, boost::uniform_real<> >
                    random(rng, spinner);

    int i;
    for(i=0; i<rand()%roundAndCast(max_val*1000); i++)
    {
        random();
    }

    float random_out = random()*0.001;
    return(random_out);

}

sf::Vector2f fastMaths::randomVector(float mag)
{
    float dx, dy;
    int sign1, sign2;
    float perc = ((float)(rand()%100))/100;
    int spin = rand()%4;
    if(spin == 0)
    {
        sign1 = 1;
        sign2 = 1;
    }
    else if(spin == 1)
    {
        sign1 = 1;
        sign2 = -1;
    }
    else if(spin == 2)
    {
        sign1 = -1;
        sign2 = 1;
    }
    else if(spin == 3)
    {
        sign1 = -1;
        sign2 = -1;
    }
    dx = perc*mag;
    dy = fastMaths::sqrt(mag*mag-dx*dx);
    sf::Vector2f randVec(sign1*dx,sign2*dy);
    return randVec;
}
