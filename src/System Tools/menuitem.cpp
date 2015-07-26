#include <System Tools/menuitem.h>

MenuItem::MenuItem()
{
    oneclick = false;
    clicked = false;
    hover = false;
}


MenuItem::MenuItem(const sf::Texture& buttonTex, int xpos, int ypos, int x_frames, int y_frames, int spool)
{
    oneclick = false;
    clicked = false;
    hover = false;
    itemAnim.setSimpleReels(buttonTex,x_frames,y_frames,0,spool);
    itemAnim.setPosition(xpos, ypos);
    position.x = xpos;
    position.y = ypos;
    width = itemAnim.xsize;
    height = itemAnim.ysize;
    //ctor
}


MenuItem::~MenuItem()
{
    //dtor
}

void MenuItem::setPosition(int _x, int _y)
{
    position.x = _x;
    position.y = _y;
    itemAnim.setPosition(_x,_y);
    itemText.setPosition(_x,_y);
    return;
}

void MenuItem::checkHover(Vector2i mousepos)
{
    return;
}


void MenuItem::checkClick(bool mouseclick)
{
    if (hover == true && mouseclick == true)
    {
        clicked = true;
    }
    else
    {
        clicked = false;
        oneclick = false;
    }
}



bool MenuItem::isClicked()
{
    return clicked;
}

void MenuItem::update(Vector2i m_pos,bool clik)
{
    checkHover(m_pos);
    checkClick(clik);
    return;
}

void MenuItem::scale(float dx,float dy)
{
    itemAnim.Scale(dx,dy);
    itemText.setScale(dx,dy);
    return;
}

Vector2f MenuItem::getSize()
{
    Vector2f sizeOfButton = itemAnim.getSize();
    return(sizeOfButton);
}

void MenuItem::setFont(const Font& in_font)
{
    default_font = in_font;
    itemText.setFont(in_font);
    itemText.setOrigin(0.5*itemText.getLocalBounds().width,0.5*itemText.getLocalBounds().height);
    return;
}

void MenuItem::setTextSize(int scale)
{
    itemText.setCharacterSize(scale);
    return;
}

void MenuItem::setText(string in_str)
{
    itemText.setString(in_str);
    itemText.setOrigin(0.5*itemText.getLocalBounds().width,itemText.getLocalBounds().height);
    return;
}

void MenuItem::setTextStyle(long style)
{
    itemText.setStyle(style);
    itemText.setOrigin(0.5*itemText.getLocalBounds().width,itemText.getLocalBounds().height);
    return;
}

void MenuItem::setTextColor(sf::Color color)
{
    itemText.setColor(color);
    return;
}

sf::Vector2f MenuItem::getPosition()
{
    return itemAnim.getPosition();
}
