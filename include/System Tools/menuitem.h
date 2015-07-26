#pragma once

#ifndef MENUITEM_H
#define MENUITEM_H
#include<SFML/Graphics.hpp>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include<lexical_cast.hpp>

#include "animation.h"

using namespace std;
using namespace sf;


class MenuItem: public Drawable
{
    public:
        MenuItem();
        MenuItem(const sf::Texture&, int,int,int,int,int);
        virtual ~MenuItem();

        Animation itemAnim;

        virtual void setFont(const Font&);
        virtual void setTextStyle(long);
        virtual void setTextColor(sf::Color);

        virtual void scale(float,float);
        virtual void update(Vector2i,bool);
        virtual void setPosition(int, int);
        virtual void setText(string);
        virtual void checkHover(Vector2i);
        virtual void checkClick(bool);
        virtual bool isClicked();
        virtual void setTextSize(int);

        virtual sf::Vector2f getPosition();
        virtual Vector2f getSize();


        int orderID;



    protected:

        string text;
        Text itemText;
        Vector2f position;
        int width, height;
        bool hover;
        bool clicked;
        bool oneclick;
        Font default_font;


    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {

        }


};

class Button:public MenuItem
{
    public:
        Button();
        Button(const sf::Texture&, int,int,int,int,int);
        virtual ~Button();

        virtual bool isOn();
        virtual void toggle();
        virtual void switchOff();
        virtual void switchOn();


        virtual void checkHover(Vector2i);
        virtual void update(Vector2i,bool);
        virtual void checkClick(bool);
        virtual void setText(string);
        virtual void animInit(const sf::Texture&,int,int,int,int,int);

        void switchTo(bool);

        void setHard();
        bool isHard();

        bool toggled;

        private:
        bool hardButton;



        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(itemAnim);
            target.draw(itemText);
        }

};

class KeyMap:public Button
{
    public:
        KeyMap();
        KeyMap(const sf::Texture&, int,int,int,int,int);

        virtual ~KeyMap();

        void inputChar(string);
        string getSelection();

        virtual void update(Vector2i,bool,string);
        virtual void setText(string,string);
        virtual void setPosition(int,int);

        virtual void setFont(const Font&);
        virtual void setTextStyle(long);
        virtual void setTextColor(sf::Color);
        virtual void setTextSize(int);

    private:

        string activeChar;
        Text activeCharDisplay;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(itemAnim);
            target.draw(itemText);
            target.draw(activeCharDisplay);
        }


};

class Slider:public MenuItem
{
    public:
        Slider();
        Slider(const Texture&, const Texture&,int,int,int,int,string);
        ~Slider();

        void initSlider(const Texture&, const Texture&,int,int,int,int,string);
        void setNubPos(int);

        virtual void checkHover(Vector2i);
        virtual void setPosition(int, int);
        virtual void checkClick(bool);
        virtual void update(Vector2i,bool);
        virtual void scale(float,float);

        void checkDrag();
        int getValue();


        virtual sf::Vector2f getPosition();
        virtual Vector2f getSize();

    private:
        bool isSliderBuilt;
        Sprite sliderBackdrop;
        float sliWidth,sliHeight,divisionNum;
        float divisionSize;
        float zero_x; //where the slider starts
        Vector2f sliPosition;
        Vector2i onFirstClick, dragAmount,currentMouse;
        int x_drag,dragFrom;
        bool gotFirstClick,holdclick;
        int selectedDivision;
        string selectionStr, finalText;
        Text sliderText;
        float bufferSize;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(sliderBackdrop);
            target.draw(itemAnim);
            target.draw(itemText);
        }

};

#endif // MENUITEM_H
