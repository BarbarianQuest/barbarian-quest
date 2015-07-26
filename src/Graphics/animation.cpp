#include "animation.h"
#include <math.h>


Animation::Animation()
{
    fps = 0;
    numberOfFrames = 0;
    numberOfTapes = 0;
    xsize = 0;
    ysize = 0;
    running = false;
    position.x = 0;
    position.y = 0;
    buffer = 0;
    delta = 0;
    switches = 0;
    current_frame = 0;
    current_spool = 0;
    lastFrameTime = 0;
    activeReel = 0;
    localRenderPriority = 0;
    continuous = true;
}

Animation::Animation(const sf::Texture& Spritesheet, int framex, int framey, int framespersec, int spool)
{
    fps = 0;
    numberOfFrames = 0;
    numberOfTapes = 0;
    xsize = 0;
    ysize = 0;
    running = false;
    position.x = 0;
    position.y = 0;
    buffer = 0;
    delta = 0;
    switches = 0;
    current_frame = 0;
    current_spool = 0;

    frame.setTexture(Spritesheet);

    sheetSize = Spritesheet.getSize();
    numberOfFrames = framex;
    numberOfTapes = framey;
    xsize = sheetSize.x/framex;
    ysize = sheetSize.y/framey;
    if(ysize < ((float)sheetSize.y/framey)) {buffer = 1;}
    fps = framespersec;
    if(fps>=1)
    {
        spf = 1.0/fps;
    }
    else
    {
        spf = 0;
    }
    runtime = ( (float) framey)/framespersec;
    framebox.height = ysize;
    framebox.width = xsize;
    framebox.top = 0;
    framebox.left = spool*xsize;
    frame.setTextureRect(framebox);
    origin.x = 0.5*xsize;
    origin.y = 0.5*ysize;
    frame.setOrigin(origin);
    lastFrameTime = 0;

}

Animation::~Animation()
{
    //dtor
}


void Animation::setLocalRenderPriority(int newpriority)
{
    localRenderPriority = newpriority;
}

void Animation::setOrigin(sf::Vector2f new_origin)
{
    origin = new_origin;
    frame.setOrigin(new_origin);
    frame.setPosition(getPosition());
}

void Animation::centreOrigin()
{
    xsize = frame.getLocalBounds().width;
    ysize = frame.getLocalBounds().height;
    frame.setOrigin(0.5*xsize,0.5*ysize);
}

void Animation::update()
{
    current_spool = activeReel;
    if(reels.size() > 0)
    {
    current_frame = reels[activeReel].currentFrame;
    framebox = reels[activeReel].getRect();
    frame.setTextureRect(framebox);
    }
}

void Animation::addReel(int x_pos,int y_pos,int x_size,int y_size,int num_frames,string reelTag)
{
    FilmReel newReel;
    newReel.setReelProperties(x_pos,y_pos,x_size,y_size,num_frames,reelTag);
    reels.push_back(newReel);
    return;
}

void Animation::setSpriteSheet(const sf::Texture & sheet)
{
    frame.setTexture(sheet);
    sheetSize = sheet.getSize();

}

void Animation::setFPS(int fps_in)
{
    fps = fps_in;
    spf = 1.0/fps;
    return;
}

sf::Vector2f Animation::getOrigin()
{
    return(frame.getOrigin());
}

void Animation::setSimpleReels(const sf::Texture& Spritesheet, int framex, int framey, int framespersec, int spool)
{
    frame.setTexture(Spritesheet);
    int i;


    sheetSize = Spritesheet.getSize();
    numberOfFrames = framex;
    numberOfTapes = framey;
    xsize = sheetSize.x/framex;
    ysize = sheetSize.y/framey;

    for(i=0; i<framex; i++)
    {
        addReel(i*xsize,0,xsize,ysize,framey,boost::lexical_cast<string>(i));
    }

    activeReel = 0;

    if(ysize < ((float)sheetSize.y/framey)) {buffer = 1;}
    fps = framespersec;
    if(fps>=1)
    {
        spf = 1.0/fps;
    }
    else
    {
        spf = 0;
    }
    runtime = ( (float) framey)/framespersec;

    current_spool = framex;
    current_frame = framey;
    framebox = reels[activeReel].getRect();
    frame.setTextureRect(framebox);
    frame.setOrigin(0.5*xsize,0.5*ysize);
    return;
}

void Animation::Move(sf::Vector2f amount)
{
    position = frame.getPosition();
    sf::Vector2f newpos = position + amount;
    frame.setPosition(newpos);
    return;
}

void Animation::Move(float dx, float dy)
{
    sf::Vector2f amount(dx,dy);
    position = frame.getPosition();
    sf::Vector2f newpos = position + amount;
    frame.setPosition(newpos);
    return;
}

void Animation::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    return;
}

void Animation::setPosition(int x, int y)
{
    sf::Vector2f pos(x,y);
    frame.setPosition(pos);
    return;
}

void Animation::Go()
{

    running = true;
    return;
}

void Animation::Stop()
{
    running = false;
    current_frame = 0;
    if(reels.size() > 0)
    {
        frameJump(current_frame);
    }

    return;
}

void Animation::Forward()
{
    reels[activeReel].Forward();
    update();
    return;
}

void Animation::Back()
{
    reels[activeReel].Back();
    update();
    return;
}

void Animation::Animate()
{

    if(fps == 0) {return;}
    if(running == false) {return;}
    animTimer = AnimClock.getElapsedTime();

    //position = frame.getPosition();
    float timeDifference = animTimer.asSeconds() - lastFrameTime;


    if (current_frame >= reels[activeReel].numberOfFrames)
    {
        //AnimClock.restart();
        //lastFrameTime = animTimer.asSeconds();
        if (continuous == false)
            {running = false; lastFrameTime = 0;}
    }

    if(timeDifference >= spf)
    {
        lastFrameTime = animTimer.asSeconds();
        current_frame += 1;
    }
    if(running == true)
    {
        frameJump(current_frame);
    }

    if(animTimer.asSeconds() > spf*reels[activeReel].numberOfFrames)
    {
        //AnimClock.restart();
    }


}


/*void Animation::Animate(int Spool, sf::Time elapsed, bool continuous)
{
    if(fps == 0) {return;}
    position = frame.getPosition();
    float timeDifference = elapsed.asSeconds() - lastFrameTime;
    if (current_frame >= reels[activeReel].numberOfFrames || running == false)
    {
        AnimClock.restart();
        lastFrameTime = elapsed.asSeconds();
        if (continuous == false)
            {running = false; lastFrameTime = 0;}
    }
    if(timeDifference >= spf)
    {
        lastFrameTime = elapsed.asSeconds();
        current_frame += 1;
    }

    if(running == true)
    {
        frameJump(current_frame);
    }
    //update();


    return;
}*/

//the following functions allow calls to empty space, use with caution.

/*void Animation::Jump(int in_x, int in_y)
{
    framebox.top = ysize*in_y;
    framebox.left = in_x*xsize;
    current_frame = in_y;
    current_spool = in_x;
    frame.setTextureRect(framebox);
}*/

void Animation::frameJump(int in_y)
{
    reels[activeReel].goToFrame(in_y);
    current_frame = in_y;
    update();
    return;
}

void Animation::changeReel(int in_x)
{
    if(in_x >= reels.size() || in_x < 0)
    {
        return;
    }
    activeReel = in_x;
    update();
    return;
}

void Animation::Scale(float dx, float dy)
{
    frame.scale(dx,dy);
    return;
}

void Animation::Rotate(float angle)
{
    frame.rotate(angle);
    return;
}

sf::Vector2f Animation::getSize()
{
    sf::Vector2f sizeOfFrame;
    sizeOfFrame.x = frame.getLocalBounds().width;
    sizeOfFrame.y = frame.getLocalBounds().height;
    return sizeOfFrame;
}

sf::Vector2f Animation::getPosition()
{
    return frame.getPosition();
}

sf::Vector2u Animation::getSheetSize()
{
    return sheetSize;
}

void Animation::setTextureRect(int top, int left, int height, int width)
{
    sf::IntRect rect;
    rect.top = top;
    rect.left = left;
    rect.height = height;
    rect.width = width;

    frame.setTextureRect(rect);

}

void Animation::setTextureRect(sf::IntRect new_rect)
{
    frame.setTextureRect(new_rect);
}

void Animation::splitStaticSheet(int x_size, int y_size) //turns an animation into a static sprite sheet. Not ideal...
{
    float x_sf, y_sf;
    x_sf = x_size;
    y_sf = y_size;
    xsize = x_size;
    ysize = y_size;

    int i,j;

    int x_num = floor(frame.getLocalBounds().width/x_sf);
    int y_num = floor(frame.getLocalBounds().height/y_sf);

    for(i=0; i<y_num; i++)
    {
        for(j=0; j<x_num; j++)
        {
            addReel(j*x_size,i*y_size,x_size,y_size,0,boost::lexical_cast<string>((j+1)*i+j));
        }
    }
    changeReel(0);
    activeReel = 0;
}
