#include <System Tools/menuitem.h>

Slider::Slider()
{
    isSliderBuilt = false;
    gotFirstClick = false;
}

Slider::Slider(const Texture& backDropTex, const Texture& nubTex, int xpos, int ypos,int numberOfDivisions, int initialValue,string title)
{
    gotFirstClick = false;
    initSlider(backDropTex,nubTex,xpos,ypos,numberOfDivisions,initialValue,title);
}

Slider::~Slider()
{

}

void Slider::setNubPos(int division)
{
    if(!isSliderBuilt){return;}
    sliPosition = sliderBackdrop.getPosition();
    bufferSize = ((float) sliWidth)*0.15;
    zero_x = sliPosition.x - 0.5*sliWidth + bufferSize;
    if(division <= divisionNum && division >= 0)
    {
        itemAnim.setPosition(zero_x + division*divisionSize,sliPosition.y);
    }
    if(division > divisionNum)
    {
        selectedDivision = divisionNum;
        itemAnim.setPosition(zero_x + divisionSize*divisionNum,sliPosition.y);
    }
    if(division < 0)
    {
        selectedDivision = 0;
        itemAnim.setPosition(zero_x, sliPosition.y);
    }
    position = itemAnim.getPosition();
    return;
}


void Slider::checkHover(Vector2i mousepos)
{
    currentMouse = mousepos;
    float m_x = (float) mousepos.x;
    float m_y = (float) mousepos.y;
    float diff_x = m_x-position.x;
    float diff_y = m_y-position.y;
    if(fabs(diff_x) < 0.5*width && fabs(diff_y) < 0.5*height)
    {
        hover = true;

    }
    else
    {
        hover = false;

    }
}

void Slider::checkClick(bool mouseclick)
{
    if (hover == true && mouseclick == true)
    {
        clicked = true;
        if(!gotFirstClick)
        {
            onFirstClick = currentMouse;
            gotFirstClick = true;
            dragFrom = selectedDivision;
        }
        checkDrag();
        itemAnim.frameJump(1);
    }
    else if(mouseclick && clicked)
    {
        hover = true;
        itemAnim.frameJump(1);
        checkDrag();
    }
    else if(!mouseclick)
    {
        clicked = false;
        gotFirstClick = false;
        itemAnim.frameJump(0);
    }
}

void Slider::checkDrag()
{
    if(gotFirstClick && clicked)
    {
        itemAnim.frameJump(1);
        dragAmount.x = currentMouse.x - itemAnim.getPosition().x;
        x_drag = dragAmount.x;
        int divBoundary = divisionSize - 0.5*itemAnim.getSize().x;
        while(x_drag > divBoundary && selectedDivision<divisionNum)
        {
            selectedDivision++;
            setNubPos(selectedDivision);
            dragAmount.x = currentMouse.x - itemAnim.getPosition().x;
            x_drag = dragAmount.x;

        }
        while(x_drag < -divBoundary && selectedDivision>0)
        {

            selectedDivision--;
            setNubPos(selectedDivision);
            dragAmount.x = currentMouse.x - itemAnim.getPosition().x;
            x_drag = dragAmount.x;
        }
    }


}

void Slider::initSlider(const Texture& backDropTex, const Texture& nubTex, int xpos, int ypos,int numberOfDivisions, int initialValue, string title)
{
    divisionNum = numberOfDivisions;
    selectedDivision = initialValue;
    sliderBackdrop.setTexture(backDropTex);
    itemAnim.setSimpleReels(nubTex,1,2,0,0);

    sliWidth = sliderBackdrop.getLocalBounds().width;
    sliHeight = sliderBackdrop.getLocalBounds().height;
    bufferSize = ((float) sliWidth)*0.15;
    sliderBackdrop.setOrigin(0.5*sliWidth, 0.5*sliHeight);
    divisionSize = ((float)sliWidth - 2*bufferSize)/divisionNum;
    sliderBackdrop.setPosition(xpos,ypos);
    sliPosition = sliderBackdrop.getPosition();
    zero_x = sliPosition.x - 0.5*sliWidth + bufferSize;

    Vector2u throwaway = nubTex.getSize();
    width = throwaway.x;
    height = throwaway.y;
    isSliderBuilt = true;
    selectionStr = boost::lexical_cast<string>(selectedDivision);
    text = title;
    setNubPos(initialValue);
}

sf::Vector2f Slider::getPosition()
{
    return sliderBackdrop.getPosition();
}

Vector2f Slider::getSize()
{
    Vector2f sizeOfSlider;
    sizeOfSlider.x = sliderBackdrop.getLocalBounds().width;
    sizeOfSlider.y = sliderBackdrop.getLocalBounds().height;
    return(sizeOfSlider);
}

void Slider::setPosition(int _x, int _y)
{
    position.x = _x;
    position.y = _y - sliHeight;
    itemAnim.setPosition(_x,_y - sliHeight);

    sliderBackdrop.setPosition(_x,_y - 0.15*sliHeight);
    setNubPos(selectedDivision);
    itemText.setPosition(_x,_y + 0.45*sliHeight);
    return;
}

void Slider::update(Vector2i m_pos,bool clik)
{
    checkHover(m_pos);
    checkClick(clik);
    selectionStr = boost::lexical_cast<string>(selectedDivision);
    finalText = text + ": " + selectionStr;
    itemText.setString(finalText);
    itemText.setOrigin(0.5*itemText.getLocalBounds().width, 0.5*itemText.getLocalBounds().height);
    return;
}

int Slider::getValue()
{
    return selectedDivision;
}

void Slider::scale(float dx,float dy)
{
    itemAnim.Scale(dx,dy);
    itemText.setScale(dx,dy);
    sliderBackdrop.setScale(dx,dy);

    sliWidth = sliderBackdrop.getLocalBounds().width;
    sliHeight = sliderBackdrop.getLocalBounds().height;
    bufferSize = ((float) sliWidth)*0.15;
    divisionSize = ((float)sliWidth - 2*bufferSize)/divisionNum;
    zero_x = sliPosition.x - 0.5*sliWidth + bufferSize;
    Vector2f throwaway = itemAnim.getSize();
    width = throwaway.x;
    height = throwaway.y;
    setNubPos(selectedDivision);
    return;
}



