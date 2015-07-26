#ifndef FILMREEL_H
#define FILMREEL_H
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;


class FilmReel
{
    public:
        FilmReel();
        FilmReel(sf::Vector2i,int,int,int,string);
        virtual ~FilmReel();

        void setReelProperties(sf::Vector2i,int,int,int,string);
        void setReelProperties(int,int,int,int,int,string);
        void updateReel();

        void Forward();
        void Back();
        void goToFrame(int);

        std::string getTag();
        sf::IntRect getRect();

        int currentFrame;
        int numberOfFrames;

    protected:
    private:

        sf::IntRect currentRect;

        sf::Vector2i positionOnSheet;
        int xsize, ysize;

        int frameSize_x, frameSize_y;
        std::string nameTag;
};

#endif // FILMREEL_H
