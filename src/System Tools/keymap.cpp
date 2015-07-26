#include <System Tools/menuitem.h>


KeyMap::KeyMap()
{

}

KeyMap::KeyMap(const sf::Texture& buttonTex, int xpos, int ypos,int x_frames, int y_frames, int spool)
{
    oneclick = false;
    toggled = false;
    clicked = false;
    hover = false;
    animInit(buttonTex,xpos,ypos,x_frames,y_frames,spool);
}

KeyMap::~KeyMap()
{

}

void KeyMap::inputChar(string in_str)
{

    if(in_str.size()<1){return;}

    activeChar = in_str[0];
    return;
}

string KeyMap::getSelection()
{
    return activeChar;
}

void KeyMap::update(Vector2i m_pos,bool clik,string keyIn)
{

    checkHover(m_pos);
    checkClick(clik);
    activeCharDisplay.setString(activeChar);
    if(toggled && keyIn.size() != 0)
    {
        activeChar = keyIn[0];
        toggle();
    }

    return;
}

void KeyMap::setText(string in_str,string init_char)
{
    itemText.setString(in_str);
    itemText.setOrigin(0,itemText.getLocalBounds().height);
    itemText.setPosition(position.x,position.y);

    activeChar = init_char[0];
    activeCharDisplay.setString(init_char);
    activeCharDisplay.setOrigin(0.5*activeCharDisplay.getLocalBounds().width,0.5*activeCharDisplay.getLocalBounds().height);
    activeCharDisplay.setPosition(position.x,position.y);

    return;
}

void KeyMap::setFont(const Font& in_font)
{
    default_font = in_font;
    itemText.setFont(in_font);
    activeCharDisplay.setFont(in_font);
    itemText.setOrigin(0,itemText.getLocalBounds().height);
    activeCharDisplay.setOrigin(0.5*activeCharDisplay.getLocalBounds().width,0.5*activeCharDisplay.getLocalBounds().height);
    return;
}

void KeyMap::setTextSize(int scale)
{
    itemText.setCharacterSize(scale);
    activeCharDisplay.setCharacterSize(scale);
    return;
}

void KeyMap::setTextStyle(long style)
{
    itemText.setStyle(style);
    itemText.setOrigin(0,itemText.getLocalBounds().height);
    activeCharDisplay.setStyle(style);
    activeCharDisplay.setOrigin(0.5*activeCharDisplay.getLocalBounds().width,activeCharDisplay.getLocalBounds().height);
    return;
}

void KeyMap::setTextColor(sf::Color color)
{
    itemText.setColor(color);
    activeCharDisplay.setColor(color);
    return;
}


void KeyMap::setPosition(int _x, int _y)
{
    position.x = _x;
    position.y = _y;
    itemAnim.setPosition(_x,_y);
    itemText.setPosition(_x-0.45*itemAnim.getSize().x,_y);
    activeCharDisplay.setPosition(_x+0.425*itemAnim.getSize().x,_y-5);
    return;
}
