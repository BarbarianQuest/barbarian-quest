#include <System Tools/menu.h>

Menu::Menu()
{
    buttons.resize(0);
    selected.resize(0);
    sliders.resize(0);
    keymaps.resize(0);
    items.resize(0);
    showMenu = false;
    showBackdrop = false;
    scrollable = false;
}

Menu::~Menu()
{
    //dtor
}

void Menu::basicConfig(bool onlyone,int xpos, int ypos, int space)
{
    oneChoice = onlyone;
    spacing = space;
    pos.x = xpos;
    pos.y = ypos;
    return;
}

void Menu::textConfig(const Font& in_font,int txtsize, long style,sf::Color color)
{
    menuFont = in_font;
    textSize = txtsize;
    textStyle = style;
    textColor = color;
    return;

}

void Menu::addScrollBar(const Texture& scrollBackdrop, const Texture& scrollNub, int x_size, int y_size)
{

}

void Menu::makeButtons(int optionnumber,bool onlyone, bool reelbased, const sf::Texture& buttonTex,int xpos, int ypos, int dist)
{
    int i;
    int actual_y, actual_x;
    oneChoice = onlyone;
    showMenu = false;
    showBackdrop = false;
    spacing = dist;
    pos.x = xpos;
    pos.y = ypos;

    buttons.resize(buttons.size() + optionnumber);
    selected.resize(selected.size() + optionnumber);

    for(i=0; i<optionnumber; i++)
    {
        actual_y = ypos+spacing*i;
        actual_x = xpos;
        if(reelbased)
        {
            buttons[i].animInit(buttonTex,actual_x,actual_y,optionnumber,3,i);
        }
        else
        {
            buttons[i].animInit(buttonTex,actual_x,actual_y,1,3,0);
        }
        buttons[i].orderID = i;
    }
    collateItems();
    //ctor
}

void Menu::makeButtons(int optionnumber,bool onlyone, bool reelbased, const sf::Texture& buttonTex,int xpos, int ypos)
{
    int i;
    int actual_y, actual_x;
    oneChoice = onlyone;
    showMenu = false;
    showBackdrop = false;
    pos.x = xpos;
    pos.y = ypos;

    buttons.resize(buttons.size() + optionnumber);
    selected.resize(selected.size() + optionnumber);

    int tex_height = (buttonTex).getSize().y;
    spacing = tex_height/3;

    for(i=0; i<optionnumber; i++)
    {
        actual_y = ypos+spacing*i;
        actual_x = xpos;

        if(reelbased)
        {
            buttons[i].animInit(buttonTex,actual_x,actual_y,optionnumber,3,i);
        }
        else
        {
            buttons[i].animInit(buttonTex,actual_x,actual_y,1,3,0);
        }
        buttons[i].orderID = i;
    }
    //ctor
    collateItems();
}

void Menu::collateItems()
{
    int i,j;
    int sliSize, butSize,keySize,itemSize;
    sliSize = sliders.size();
    butSize = buttons.size();
    keySize = keymaps.size();
    items.resize(sliSize+butSize+keySize);
    itemSize = items.size();

    for(i=0; i<items.size(); i++)
    {
        for(j=0; j<butSize; j++)
        {
            if(i == buttons[j].orderID)
            {
                items[i]=&buttons[j];
            }
        }
        for(j=0; j<sliSize; j++)
        {
            if(i == sliders[j].orderID)
            {
                items[i]=&sliders[j];
            }
        }
        for(j=0; j<keySize; j++)
        {
            if(i == keymaps[j].orderID)
            {
                items[i]=&keymaps[j];
            }
        }
    }
    return;
}

void Menu::addSlider(const Texture& backDropTex, const Texture& nubTex,int numberOfDivisions, int initialValue, string title)
{
    int y_val;
    if(items.size() > 0)
    {
       y_val = (*items.back()).getPosition().y +  spacing;
    }
    else
    {
        y_val = pos.y;
    }
    Slider newSlider(backDropTex, nubTex, pos.x, y_val,numberOfDivisions,initialValue,title);
    newSlider.setFont(menuFont);
    newSlider.setTextSize(textSize);
    newSlider.setText(title);
    newSlider.setTextColor(textColor);
    newSlider.setTextStyle(textStyle);
    newSlider.orderID = (items.size());
    sliders.push_back(newSlider);
    collateItems();
}

void Menu::addButton(const Texture& buttonTex, string title)
{
    int y_val;
    if(items.size() > 0)
    {
       y_val = (*items.back()).getPosition().y + spacing;
    }
    else
    {
        y_val = pos.y;
    }
    Button newButton(buttonTex,pos.x,y_val,1,3,0);
    newButton.setFont(menuFont);
    newButton.setTextSize(textSize);
    newButton.setText(title);
    newButton.setTextColor(textColor);
    newButton.setTextStyle(textStyle);
    newButton.orderID = (items.size());
    buttons.push_back(newButton);
    collateItems();
}

void Menu::addHardButton(const Texture& buttonTex, string title,bool switchedOn)
{
    int y_val;
    if(items.size() > 0)
    {
       y_val = (*items.back()).getPosition().y + spacing;
    }
    else
    {
        y_val = pos.y;
    }
    Button newButton(buttonTex,pos.x,y_val,1,3,0);
    newButton.setFont(menuFont);
    newButton.setTextSize(textSize);
    newButton.setText(title);
    newButton.setTextColor(textColor);
    newButton.setTextStyle(textStyle);
    newButton.orderID = (items.size());
    newButton.setHard();
    newButton.switchTo(switchedOn);
    buttons.push_back(newButton);
    collateItems();
}

void Menu::addKeyMap(const Texture& buttonTex, string title,string init_char)
{
    int y_val;
    if(items.size() > 0)
    {
       y_val = (*items.back()).getPosition().y + spacing;
    }
    else
    {
        y_val = pos.y;
    }
    KeyMap newKeyMap(buttonTex,pos.x,y_val,1,3,0);
    newKeyMap.setFont(menuFont);
    newKeyMap.setTextSize(textSize);
    newKeyMap.setText(title,init_char);
    newKeyMap.setTextColor(textColor);
    newKeyMap.setTextStyle(textStyle);
    newKeyMap.orderID = (items.size());
    keymaps.push_back(newKeyMap);
    collateItems();
}



void Menu::setPosition(int xpos, int ypos)
{
    //collateItems();
    int i;
    int actual_y, actual_x;


    for(i=0; i<items.size(); i++)
    {

        actual_y = ypos+(*items[i]).getPosition().y - pos.y;
        actual_x = xpos;
        (*items[i]).setPosition(actual_x,actual_y);
    }
    if(showBackdrop)
    {
        centreBackdrop();
    }
    pos.x = xpos;
    pos.y = ypos;

}


void Menu::scale(float x_factor, float y_factor)
{
    int i;
    int new_y, new_x;
    float newspacing,correction;
    for(i=0; i<items.size(); i++)
    {
        newspacing =((float) spacing)*y_factor;// - ((float) (*items[i]).getSize().y);
        correction = +((float) (*items[i]).getSize().y) - y_factor*((float) (*items[i]).getSize().y);
        (*items[i]).scale(x_factor,y_factor);
        new_y = (*items[i]).getPosition().y - spacing*i + newspacing*i + correction;
        new_x = pos.x;

        (*items[i]).setPosition(new_x,new_y);
    }
    spacing = (int) newspacing;
    if(showBackdrop)
    {
        Backdrop.setScale(x_factor,y_factor);
        centreBackdrop();
    }
}

void Menu::setTexture(int n, const sf::Texture& Tex)
{

}

void Menu::update(Vector2i m_pos, bool clik,string keyboardInput)
{
    selected.resize(buttons.size());
    if(showMenu)
    {
        unsigned int i,j;
        for(i=0; i<buttons.size(); i++)
        {
            buttons[i].update(m_pos, clik);
            if(oneChoice && buttons[i].isClicked())
            {
                for(j=0; j<buttons.size(); j++)
                {
                    if(j==i){continue;}
                    buttons[j].switchOff();
                }
                for(j=0; j<keymaps.size(); j++)
                {
                    keymaps[j].switchOff();
                }
            }
            selected[i] = buttons[i].isOn();
        }

        for(i=0; i<keymaps.size(); i++)
        {
            keymaps[i].update(m_pos, clik,keyboardInput);
            if(oneChoice && keymaps[i].isClicked())
            {
                for(j=0; j<buttons.size(); j++)
                {
                    buttons[j].switchOff();
                }
                for(j=0; j<keymaps.size(); j++)
                {
                    if(j==i){continue;}
                    keymaps[j].switchOff();
                }
            }
        }
        for(i=0; i<sliders.size(); i++)
        {
            sliders[i].update(m_pos,clik);
        }
    }
}

vector<bool> Menu::chosenItem()
{
    return selected;
}

void Menu::open()
{
    showMenu = true;
    return;
}

void Menu::close()
{
    unsigned int i;
    showMenu = false;
    for(i=0; i<buttons.size(); i++)
    {
        if(!buttons[i].isHard())
        {
            buttons[i].switchOff();
        }
        selected[i] = buttons[i].isOn();
    }
    return;
}

void Menu::select(int num)
{
    buttons[num].switchOn();
}

void Menu::addBackdrop(const Texture& backTex)
{
    showBackdrop = true;
    Backdrop.setTexture(backTex);
    return;
}

void Menu::centreBackdrop()
{
    Backdrop.setOrigin(0.5*Backdrop.getLocalBounds().width,0.5*Backdrop.getLocalBounds().height);
    Backdrop.setPosition(pos.x,pos.y  + 0.5*((float)ysize) - (*items.front()).getSize().y);
}

void Menu::centreMenu(float amount_x, float amount_y, int w_x, int w_y)
{
    if(buttons.size()>0)
    {
        buttonSize = buttons[0].getSize();
    }
    else
    {
        buttonSize.x = buttonSize.y = 0;
    }
    if(sliders.size()>0)
    {
        sliderSize = sliders[0].getSize();
    }
    else
    {
        sliderSize.x = sliderSize.y = 0;
    }
    xsize = buttonSize.x;
    //ysize = buttons.size()*(buttonSize.y + spacing) + sliders.size()*(sliderSize.y+spacing) - spacing;
    ysize = -((*items.front()).getPosition().y - (*items.front()).getSize().y) + ((*items.back()).getPosition().y + (*items.back()).getSize().y);
    Vector2f idealPos;
    idealPos.x = amount_x*((float)w_x);
    idealPos.y = amount_y*((float)w_y) - 0.5*((float)ysize) + (*items.front()).getSize().y;
    setPosition(idealPos.x, idealPos.y);
    if(showBackdrop)
    {
        centreBackdrop();
    }
    return;
}

void Menu::centreMenu(int w_x, int w_y)
{
    if(buttons.size()>0)
    {
        buttonSize = buttons[0].getSize();
    }
    else
    {
        buttonSize.x = buttonSize.y = 0;
    }
    if(sliders.size()>0)
    {
        sliderSize = sliders[0].getSize();
    }
    else
    {
        sliderSize.x = sliderSize.y = 0;
    }
    xsize = buttonSize.x;
    ysize = buttons.size()*(buttonSize.y + spacing) + sliders.size()*(sliderSize.y + spacing) - spacing;
    ysize = -((*items.front()).getPosition().y - (*items.front()).getSize().y) + ((*items.back()).getPosition().y + (*items.back()).getSize().y);
    Vector2f idealPos;
    idealPos.x = 0.5*w_x;
    idealPos.y = 0.5*w_y - 0.25*ysize;
    setPosition(idealPos.x, idealPos.y);
    if(showBackdrop)
    {
        centreBackdrop();
    }
    return;
}

void Menu::deselectAll()
{
    int i;
    for(i=0; i<buttons.size(); i++)
    {
        if(!buttons[i].isHard())
        {
            buttons[i].switchOff();
        }
    }
    return;
}

bool Menu::isOpen()
{
    return showMenu;
}

void Menu::setFont(const Font& in_font)
{
    int i;
    menuFont = in_font;
    for(i=0; i< buttons.size(); i++)
    {
        buttons[i].setFont(menuFont);
    }
    return;
}

void Menu::setButtonText(vector<string> buttonStr)
{
    int i;
    if(buttonStr.size() != buttons.size())
    {

    }

    for(i=0; i<buttons.size(); i++)
    {
        buttons[i].setText(buttonStr[i]);
    }
    collateItems();
}

void Menu::setButtonTextSize(int scale)
{
    int i;
    textSize = scale;
    for(i=0; i<buttons.size(); i++)
    {
        buttons[i].setTextSize(scale);
    }

}

void Menu::textInit(const Font& in_font, int scale, vector<string> buttonStr)
{
    setFont(in_font);
    setButtonTextSize(scale);
    setButtonText(buttonStr);
    return;
}

void Menu::setTextStyle(long style)
{
       int i;
    for(i=0; i<buttons.size(); i++)
    {
        buttons[i].setTextStyle(style);
    }

}

void Menu::setTextColor(sf::Color color)
{
    int i;
    for(i=0; i<buttons.size(); i++)
    {
        buttons[i].setTextColor(color);
    }
    for(i=0; i<sliders.size(); i++)
    {
        sliders[i].setTextColor(color);
    }
}
