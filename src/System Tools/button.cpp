#include <System Tools/menuitem.h>

Button::Button()
{
    oneclick = false;
    toggled = false;
    clicked = false;
    hover = false;
    hardButton=false;
}

Button::Button(const sf::Texture& buttonTex, int xpos, int ypos, int x_frames, int y_frames, int spool)
{
    oneclick = false;
    toggled = false;
    clicked = false;
    hover = false;
    hardButton=false;
    animInit(buttonTex,xpos,ypos,x_frames,y_frames,spool);
    //ctor
}

Button::~Button()
{

}

void Button::update(Vector2i m_pos,bool clik)
{
    checkHover(m_pos);
    checkClick(clik);
    return;
}

void Button::switchTo(bool switchval)
{
    if(switchval) {switchOn();}
    else {switchOff();}
    return;
}

void Button::setHard()
{
    hardButton = true;
}

bool Button::isHard()
{
    return hardButton;
}

void Button::animInit(const sf::Texture& buttonTex, int xpos, int ypos,int x_frames, int y_frames, int spool)
{
    itemAnim.setSimpleReels(buttonTex,x_frames,y_frames,0,spool);
    itemAnim.setPosition(xpos, ypos);
    position.x = xpos;
    position.y = ypos;
    width = itemAnim.xsize;
    height = itemAnim.ysize;
    return;
}


void Button::checkHover(Vector2i mousepos)
{
    float m_x = (float) mousepos.x;
    float m_y = (float) mousepos.y;
    float diff_x = m_x-position.x;
    float diff_y = m_y-position.y;
    if(fabs(diff_x) < 0.5*width && fabs(diff_y) < 0.5*height)
    {
        hover = true;

        if(!toggled)
        {
            itemAnim.frameJump(1);

        }
    }
    else
    {
        hover = false;
        if(!toggled)
        {
            itemAnim.frameJump(0);

        }
    }
}

void Button::checkClick(bool mouseclick)
{
    if (hover == true && mouseclick == true)
    {
        clicked = true;
        toggle();
        itemAnim.frameJump(2);
    }
    else
    {
        clicked = false;
        oneclick = false;
    }
}

bool Button::isOn()
{
    return toggled;
}

void Button::toggle()
{
    if(!toggled && !oneclick)
    {
        toggled = true;
        oneclick = true;
    }
    if(toggled && !oneclick)
    {
        toggled = false;
        oneclick = true;
    }
    return;
}

void Button::switchOff()
{
    toggled = false;
    itemAnim.frameJump(0);
}

void Button::switchOn()
{
    toggled = true;
    itemAnim.frameJump(2);
}

void Button::setText(string in_str)
{
    itemText.setString(in_str);
    itemText.setOrigin(0.5*itemText.getLocalBounds().width,itemText.getLocalBounds().height);
    itemText.setPosition(position.x,position.y);

    return;
}
