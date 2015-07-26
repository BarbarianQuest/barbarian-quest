#include "wall.h"

Wall::Wall() : Tile()
{
    //ctor
    content_id += "_wall";
    content_type = "wall";
    objHitbox.makeSolid();
    impassable = true;
    wall = true;
    solid = true;
    id = 9+17;
    renderPriority = 5;
}

Wall::~Wall()
{
    //dtor
}

void Wall::hits(Content* thing)
{

}

TopWall::TopWall() : Wall()
{
    //ctor
    renderPriority = 1;
    tileSize = 64;
    id = 29;
    content_id += "_base_top";

}

TopWall::~TopWall()
{
    //dtor
}

SecondTopWall::SecondTopWall() : Wall()
{
    id = 16;
    renderPriority = 1;

    objHitbox.makeAir();
    content_id += "_base_secondtop";
    solid = false;
}

SecondTopWall::~SecondTopWall()
{

}

TopTopWall::TopTopWall()
{
    id = 17;
    renderPriority = 1;
    objHitbox.makeAir();
    content_id += "_base_toptop";
    solid = false;
    blocksLOS = true;
}

TopTopWall::~TopTopWall()
{

}

SecondBotWall::SecondBotWall() : Wall()
{
    id = 16;
    renderPriority = 4;
    objHitbox.makeAir();
    content_id += "_base_secondbot";
    solid = false;
}

SecondBotWall::~SecondBotWall()
{

}


BotWall::BotWall() : Wall()
{
    //ctor
    renderPriority = 4;
    objHitbox.makeAir();
    id = 17;
    content_id += "_base_bot";
    solid = false;
}

BotWall::~BotWall()
{
    //dtor
}

BotBotWall::BotBotWall() : Wall()
{
    //ctor
    renderPriority = 1;
    content_id += "_base_bbot";
    id = 29;
    blocksLOS = true;
}

BotBotWall::~BotBotWall()
{
    //dtor
}

LeftWall::LeftWall() : Wall()
{
    //ctor

    id = 17;
    rotation = 90;
    content_id += "_base_left";
    blocksLOS = true;
}

LeftWall::~LeftWall()
{
    //dtor
}

RightWall::RightWall() : Wall()
{
    //ctor
    id = 17;
    rotation = 90;
    content_id += "_base_right";
    blocksLOS = true;
}

RightWall::~RightWall()
{
    //dtor
}

TLCornerWall::TLCornerWall() : Wall()
{
    //ctor
    id = 8;
    objHitbox.makeAir();
    rotation = 0;
    content_id += "_base_TL";
    solid = false;
    blocksLOS = true;
}

TLCornerWall::~TLCornerWall()
{
    //dtor
}

TRCornerWall::TRCornerWall() : Wall()
{
    //ctor
    id = 8;
    objHitbox.makeAir();
    rotation = 90;
    content_id += "_base_TR";
    solid = false;
    blocksLOS = true;
}

TRCornerWall::~TRCornerWall()
{
    //dtor
}

BLCornerWall::BLCornerWall() : Wall()
{
    //ctor
    id = 8;
    rotation = -90;
    content_id += "_base_BL";
}

BLCornerWall::~BLCornerWall()
{
    //dtor
}

BRCornerWall::BRCornerWall(): Wall()
{
    //ctor
    id = 8;
    rotation = 180;
    content_id += "_base_BR";
}

BRCornerWall::~BRCornerWall()
{
    //dtor
}

