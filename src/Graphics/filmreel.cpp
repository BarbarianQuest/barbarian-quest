#include "filmreel.h"

FilmReel::FilmReel()
{
    //ctor
}

FilmReel::~FilmReel()
{
    //dtor
}

void FilmReel::setReelProperties(sf::Vector2i localCoords, int x_size,int y_size,int numberofframes,std::string name)
{
    positionOnSheet = localCoords;
    xsize = x_size;
    ysize = y_size;
    numberOfFrames = numberofframes;
    nameTag = name;

    currentFrame = 0;

    updateReel();

    return;
}


void FilmReel::setReelProperties(int xpos, int ypos, int x_size,int y_size,int numberofframes,std::string name)
{
    positionOnSheet.x = xpos;
    positionOnSheet.y = ypos;
    xsize = x_size;
    ysize = y_size;
    numberOfFrames = numberofframes;
    nameTag = name;

    currentFrame = 0;

    updateReel();

    return;
}

sf::IntRect FilmReel::getRect()
{
    updateReel();
    return currentRect;
}

void FilmReel::updateReel()
{

    if (currentFrame >= numberOfFrames) {currentFrame = 0;}
    currentRect.height = ysize;
    currentRect.width = xsize;
    currentRect.left = positionOnSheet.x;
    currentRect.top = currentFrame*currentRect.height + positionOnSheet.y;


}

std::string FilmReel::getTag()
{
    return nameTag;
}

void FilmReel::Forward()
{
    currentFrame += 1;
    updateReel();
    return;
}

void FilmReel::Back()
{
    currentFrame -= 1;
    updateReel();
    return;
}

void FilmReel::goToFrame(int framenum)
{

    currentFrame = framenum;

    updateReel();
    return;
}
