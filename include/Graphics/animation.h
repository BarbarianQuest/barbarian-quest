#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include "filmreel.h"
#include<lexical_cast.hpp>

//a test

class Animation : public sf::Drawable
{
    public:
        Animation();
        Animation(const sf::Texture&,int, int, int, int);
        virtual ~Animation();
        sf::Sprite frame;

        void setSpriteSheet(const sf::Texture&);

        void setSimpleReels(const sf::Texture&,int, int, int, int); //old method of adding single row animations

        void addReel(sf::Vector2i,int,int,int,string);
        void addReel(int,int,int,int,int,string);

        void changeReel(int);
        void changeReel(std::string);

        //void Animate(int, sf::Time, bool);
        void Animate();
        void Forward();
        void Back();
        void Move(sf::Vector2f);
        void Move(float, float);
        void setPosition(sf::Vector2f);
        void setPosition(int, int);
        void centreOrigin();

        void setFPS(int);
        void Jump(int,int);
        void frameJump(int); //in y
        void Go();
        void Stop();
        void Scale(float, float);
        void Rotate(float);
        void update();
        void setTextureRect(int,int,int,int);
        void setTextureRect(sf::IntRect);
        void splitStaticSheet(int,int);
        void setOrigin(sf::Vector2f);
        void setRelativePosition(sf::Vector2f);
        void setLocalRenderPriority(int);
        sf::Vector2f getOrigin();
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        sf::Vector2f position;
        sf::Vector2f origin;
        sf::Vector2u getSheetSize();
        sf::Clock AnimClock;
        sf::Time animTimer;

        int xsize, ysize; //boxsize
        int localRenderPriority;

    protected:

    private:
        bool running, continuous;
        sf::Texture reel;
        int numberOfFrames, numberOfTapes; //framex and framey in older programs

        vector<FilmReel> reels;
        int activeReel;

        int fps;
        sf::Vector2u sheetSize;
        sf::IntRect framebox;
        sf::Vector2f relativePosition;
        float runtime;
        float spf;
        float lastFrameTime;
        int buffer; //for idiot proofing
        int delta;
        int switches;
        int current_spool;
        int current_frame;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(frame);
        }


};

#endif // ANIMATION_H
