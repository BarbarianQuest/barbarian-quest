#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "menuitem.h"

using namespace std;
using namespace sf;



class Menu : public sf::Drawable
{
    public:
        Menu();

        virtual ~Menu();


        void basicConfig(bool,int,int,int);
        void textConfig(const Font&, int,long,sf::Color);


        void makeButtons(int,bool,bool,const sf::Texture&,int,int,int);
        void makeButtons(int,bool,bool,const sf::Texture&,int,int);

        void addSlider(const Texture&, const Texture&,int,int,string);
        void addButton(const Texture&,string);
        void addHardButton(const Texture&,string,bool);
        void addKeyMap(const Texture&,string,string);

        void setTexture(int,const sf::Texture&);
        void update(Vector2i, bool,string);
        void open();
        void close();
        void select(int);
        void scale(float,float);
        void centreMenu(float,float,int,int);
        void centreMenu(int,int);
        void addBackdrop(const Texture&);
        void setPosition(int,int);
        void centreBackdrop();
        void deselectAll();
        void setFont(const Font&);
        void setButtonText(vector<string>);
        void setButtonTextSize(int);
        void textInit(const Font&, int, vector<string>);

        void addScrollBar(const Texture&, const Texture&, int, int);

        void setTextStyle(long);
        void setTextColor(sf::Color);
        void collateItems();
        bool isOpen();

        vector<bool> chosenItem();

        vector<Slider> sliders;
        vector<Button> buttons;
        vector<KeyMap> keymaps;
        vector<MenuItem*> items;

    protected:
    private:
        bool oneChoice;
        bool showMenu;
        bool scrollable;
        Vector2i pos;
        float spacing;
        Sprite Backdrop;
        bool showBackdrop;
        Vector2f buttonSize, sliderSize;
        vector<bool> selected;
        float xsize, ysize;

        Font menuFont;
        int textSize;
        long textStyle;
        sf::Color textColor;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            unsigned int i;
            if(showBackdrop)
            {
                target.draw(Backdrop);
            }
            if(showMenu)
            {
                /*for(i=0; i<buttons.size(); i++)
                {
                    target.draw(buttons[i]);
                }
                for(i=0; i<sliders.size(); i++)
                {
                    target.draw(sliders[i]);
                }*/
                for(i=0; i<items.size(); i++)
                {
                    target.draw(*items[i]);
                }
            }
        }
};

#endif // MENU_H
